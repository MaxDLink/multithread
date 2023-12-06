#pragma once 
#include <mutex> 
#include <map> 
#include <deque> 
#include <vector> 
#include <thread> 


constexpr int JOB_TYPE_ANY = -1; 

class JobWorkerThread; 

enum JobStatus{
    JOB_STATUS_NEVER_SEEN, 
    JOB_STATUS_QUEUED, 
    JOB_STATUS_RUNNING, 
    JOB_STATUS_COMPLETED, 
    JOB_STATUS_RETIRED, 
    NUM_JOB_STATUSES
}; 

struct JobHistoryEntry{
    JobHistoryEntry(int jobType, JobStatus jobStatus): 
        m_jobType(jobType), 
        m_jobStatus(jobStatus){}

        int m_jobType = -1; 
        int m_jobStatus = JOB_STATUS_NEVER_SEEN;

}; 

class Job; 

class JobSystem{
    friend class JobWorkerThread; 

    public: 
    JobSystem(); 
    ~JobSystem(); 

    static JobSystem* CreateOrGet(); 
    static void Destroy(); 
    int totalJobs = 0; 

    void CreateWorkerThread(const char* uniqueName, unsigned long workerJobChannels=0xFFFFFFFF);
    void DestroyWorkerThread(const char* uniqueName);
    void QueueJob (Job* job); 

    //Status Queries 
    JobStatus GetJobStatus(int jobID) const; 
    bool IsJobComplete(int jobID) const;   


    void FinishCompletedJobs(); //main processing all the jobs you've done //move this function up to public to fix error with interface 
    void FinishJob(int jobID); //move this function up to public to fix interface error

    private: 
    Job* ClaimAJob(unsigned long workerJobFlags); 
    //goes through jobsQueued and returns a job that is not completed
    //that Job is moved from JobsQueued into jobsRunning
    void OnJobCompleted(Job* jobJustExecuted);
    //void FinishCompletedJobs(); //main processing all the jobs you've done //TODO - move these two functions up to public to fix error? 
    //void FinishJob(int jobID); //finishes a specific job    //TODO - move??

    static JobSystem* s_jobSystem; 

    std::vector<JobWorkerThread* > m_workerThreads; 
    mutable std::mutex             m_workerThreadsMutex; 
    std::deque<Job*>               m_jobsQueued;
    std::deque< Job* >             m_jobsRunning; 
    std::deque< Job* >             m_jobsCompleted; 
    mutable std::mutex             m_jobsQueuedMutex;
    mutable std::mutex             m_jobsRunningMutex;
    mutable std::mutex             m_jobsCompletedMutex;

    std::vector< JobHistoryEntry > m_jobHistory;
    mutable int                    m_jobHistoryLowestActiveIndex = 0; //oldest still running job would be lowest number 
    mutable std::mutex             m_jobHistoryMutex;




}; 
