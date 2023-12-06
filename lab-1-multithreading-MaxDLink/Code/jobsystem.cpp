//biggest class to write! 
#include <iostream> 

#include "jobsystem.h" 
#include "jobworkerthread.h" 

#include <cstring> //TODO - added for strcmp line 85


JobSystem* JobSystem::s_jobSystem = nullptr; 
//JobSystem static so have to create instance in cpp file

//not a function pointer but highly related 
//typedef for a function pointer that takes a job as an input and returns void 
//name of typedef is JobCallback
//makes all code dealing with function pointers a lot simpler 
typedef void (*JobCallback)(Job* completedJob); 

JobSystem::JobSystem(){
    //vector has to refactor itself to reallocate memory 
    //by telling how much memory to reserve, can speed up run time
    //can control when hitches happen --> reserving memory at beginning super good! 
    //sometimes cannot reserve memory at beginning because do not know how much memory will be needed
    //vectors can double itself in size, all doubling happens at once at initialization if tell program how much memory is needed 
    //TODO - at some point going to run out of memory so a circular buffer would be great to add to this code later!  
    m_jobHistory.reserve(256 * 1024);

}

JobSystem::~JobSystem(){//letting threads finish is the nice way to clean up -- even though can kill 
    m_workerThreadsMutex.lock();
    int numWorkerThreads = (int)m_workerThreads.size(); 
    //we built in functions for letting threads run to completion. Will call those 

    //First, tell each worker thread to stop picking up jobs 
    for(int i = 0; i < numWorkerThreads; ++i){
        m_workerThreads[i]->ShutDown(); 
    }

    while(!m_workerThreads.empty()){
        //going through vector of multithreads 
        //deleting worker thread objects, but threads are not a concern 
        delete m_workerThreads.back(); 
        m_workerThreads.pop_back(); 
    }
    m_workerThreadsMutex.unlock(); 


}

//ensures theres only one job system created 
JobSystem* JobSystem::CreateOrGet(){
    if(!s_jobSystem){//if there isnt a job system, create one
        s_jobSystem = new JobSystem(); 
    }
    return s_jobSystem; //if theres already one then return it
}

//if there is a job system, delete it & set to nullptr 
void JobSystem::Destroy(){
    if(s_jobSystem){
        delete s_jobSystem; 
        s_jobSystem = nullptr; 
    }
}

void JobSystem::CreateWorkerThread(const char* uniqueName, unsigned long workerJobChannels){
    
    JobWorkerThread* newWorker = new JobWorkerThread (uniqueName, workerJobChannels, this); 

    m_workerThreadsMutex.lock();
    m_workerThreads.push_back(newWorker); 
    m_workerThreadsMutex.unlock();

    m_workerThreads.back() -> StartUp();

}

void JobSystem::DestroyWorkerThread(const char* uniqueName){
    m_workerThreadsMutex.lock(); 
    JobWorkerThread* doomedWorker = nullptr; 
    std::vector<JobWorkerThread*>::iterator it = m_workerThreads.begin();  

    for(; it != m_workerThreads.end(); ++it){
        if(strcmp( (*it)->m_uniqueName, uniqueName) == 0){
            doomedWorker = *it; 
            m_workerThreads.erase(it); 
            break; 
        }
    }
    


    m_workerThreadsMutex.unlock();

    if( doomedWorker){
        doomedWorker->ShutDown(); 
        delete doomedWorker; 
    }
}

void JobSystem::QueueJob(Job* job){//working w/ job histories & job queue 
//pushing creaetd job into job queue
//update job entry record to say job is queued
    m_jobsQueuedMutex.lock(); 

    m_jobHistoryMutex.lock(); 
    m_jobHistory.emplace_back(JobHistoryEntry(job->m_jobType, JOB_STATUS_QUEUED)); 
    m_jobHistoryMutex.unlock(); 

    m_jobsQueued.push_back(job); 
    m_jobsQueuedMutex.unlock(); 
    
}

JobStatus JobSystem::GetJobStatus(int jobID) const{//jobstatus is an array that we are pushing onto an array 
//should be indexed so we dont have to search through array
//more complex system where jobs can overwrite previous jobs then this will not be enough -- would have to search the loop 
    m_jobHistoryMutex.lock();

    JobStatus jobStatus = JOB_STATUS_NEVER_SEEN; 
    if(jobID < (int) m_jobHistory.size()){ //if(jobID, (int) m_jobHistory.size()){
        jobStatus = (JobStatus) m_jobHistory[jobID].m_jobStatus; 
    }

    m_jobHistoryMutex.unlock();

    return jobStatus; 
}

bool JobSystem::IsJobComplete(int jobID) const{
    //return JobStatus (jobID) == JOB_STATUS_COMPLETED; 
    return (GetJobStatus(jobID)) == (JOB_STATUS_COMPLETED); 
}

void JobSystem::FinishCompletedJobs(){

    std::deque<Job*> jobsCompleted; 

    m_jobsCompletedMutex.lock(); 

    jobsCompleted.swap(m_jobsCompleted); //grabs all completed objects in deck and copies into local deck 
    //allows processing while not keeping queue locked up 

    m_jobsCompletedMutex.unlock(); 

    for(Job* job : jobsCompleted){
        job->JobCompletedCallback(); //grab callback 
    

    m_jobHistoryMutex.lock(); 
    m_jobHistory[job->m_jobID].m_jobStatus = JOB_STATUS_RETIRED; //update status 
    m_jobHistoryMutex.unlock();
    delete job;  //delete the job 

    }

}

void JobSystem::FinishJob(int jobID){
    while(!IsJobComplete(jobID)){
        JobStatus jobStatus = GetJobStatus(jobID); 
        if(jobStatus == JOB_STATUS_NEVER_SEEN || jobStatus == JOB_STATUS_RETIRED){ 
            std::cout << "ERROR: Waiting for job(#:" << jobID << ") - no such job in JobSystem!" << std::endl; 
            return; 
        }

        m_jobsCompletedMutex.lock();
        Job* thisCompletedJob = nullptr; 
        for(auto jcIter = m_jobsCompleted.begin(); jcIter != m_jobsCompleted.end(); ++jcIter){
            Job* someCompletedJob = *jcIter; 
            if(someCompletedJob->m_jobID == jobID){
                thisCompletedJob = someCompletedJob;
                m_jobsCompleted.erase(jcIter);
                break; 
            }
        }
        m_jobsCompletedMutex.unlock(); 

        if(thisCompletedJob == nullptr){
            std::cout << "Error: Job #" << jobID << " was status complete but not found in completed list!" << std::endl; 

        }

        thisCompletedJob -> JobCompletedCallback();  //find job 
        
        m_jobHistoryMutex.lock(); 
        m_jobHistory[thisCompletedJob->m_jobID].m_jobStatus = JOB_STATUS_RETIRED; //update history record 
        m_jobHistoryMutex.unlock(); 
        delete thisCompletedJob; //delete job 

    }
}

void JobSystem::OnJobCompleted(Job* jobJustExecuted){
    totalJobs++; //for testing - not important 

    //running on two at same time protect both 
    m_jobsCompletedMutex.lock(); 
    m_jobsRunningMutex.lock(); 

    std::deque<Job*>::iterator runningJobItr = m_jobsRunning.begin(); 
    for(; runningJobItr != m_jobsRunning.end(); ++runningJobItr){
        if( jobJustExecuted == * runningJobItr){
            m_jobHistoryMutex.lock(); 
            m_jobsRunning.erase(runningJobItr); 
            m_jobsCompleted.push_back(jobJustExecuted); 
            m_jobHistory[jobJustExecuted->m_jobID].m_jobStatus = JOB_STATUS_COMPLETED; 
            m_jobHistoryMutex.unlock(); 
            break; 
        }
    } 

    m_jobsRunningMutex.unlock();
    m_jobsCompletedMutex.unlock(); 

    //can add many more things to job system -- this shows how to loop through two differnet decks grab one erase one 
    //swap command very quick in this .cpp file  

}

Job* JobSystem::ClaimAJob(unsigned long workerJobChannels){
    m_jobsQueuedMutex.lock(); 
    m_jobsRunningMutex.lock(); 

    Job* claimedJob = nullptr; 
    std::deque< Job * >::iterator queuedJobIter = m_jobsQueued.begin(); 
    for( ; queuedJobIter != m_jobsQueued.end(); ++queuedJobIter){
        Job* queuedJob = *queuedJobIter; 

        if((queuedJob->m_jobChannels & workerJobChannels) != 0){//bit mask logic operator not an & op. if 0 then something =1 for some reason 
            claimedJob = queuedJob; 
            
            m_jobHistoryMutex.lock(); //locks thread so every other thread is waiting 
            m_jobsQueued.erase(queuedJobIter); 
            m_jobsRunning.push_back(claimedJob); 
            m_jobHistory[claimedJob->m_jobID].m_jobStatus = JOB_STATUS_RUNNING;
            //
            //DEAD LOCK WAS HERE BUT FIXED BY MOVING UNLOCK TO LINE 241
            // 
            m_jobHistoryMutex.unlock(); //does not affect thread that grabs first job
            //will get stuck with deadlock unless unlock here
            break; 
        }
    }

    m_jobsRunningMutex.unlock();
    m_jobsQueuedMutex.unlock(); 

    return claimedJob; 
}