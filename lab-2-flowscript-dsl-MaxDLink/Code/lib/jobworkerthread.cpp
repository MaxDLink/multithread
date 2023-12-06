#include "jobworkerthread.h"
#include "jobsystem.h" 

JobWorkerThread::JobWorkerThread(const char* uniqueName, unsigned long workerJobChannels, JobSystem* jobSystem) : 
    m_uniqueName(uniqueName), 
    m_workerJobChannels(workerJobChannels), 
    m_jobSystem(jobSystem){
}

JobWorkerThread::~JobWorkerThread(){
    //If we havent already, 
    //signal thread that we should exit as soon as it can (after its current job if any)
    ShutDown(); 

    //Block on the thread's main until it has a chance to finish its current job and exit 
    //cleanup process 
    m_thread->join(); 
    delete m_thread; 
    m_thread = nullptr; 

}

void JobWorkerThread::StartUp(){
    m_thread = new std::thread(WorkerThreadMain, this); //passing worker main as the starting point for this thread
}

//when using class method arguments are self so the arguments are the list of parameters 
//Global function pointer just need a pointer to a function 
//Function is offset because it is a member function pointer --> WorkerThreadMain is a member function of JobWorkerThread
//WorkerThreadMain is the obj and this is the function pointer 

void JobWorkerThread::Work(){
    //thread wants a job so looking for threads that are not busy 
    while(!IsStopping()){ //while we are not stopping
        //worker job channels can be accessed to the main thread 
        //needs protection 
        //use mutex control -- want mutex commands to be as fast as possible 

        m_workerStatusMutex.lock(); 
        unsigned long workerJobChannels = m_workerJobChannels;
        m_workerStatusMutex.unlock(); 

        Job* job = m_jobSystem->ClaimAJob(m_workerJobChannels); 
        //if we got a job, execute it and then tell the job system we are done with it
        if(job){
            job->Execute(); 
            m_jobSystem->OnJobCompleted(job); //going to move the completed job to the completed queue for the main thread to reconcile 
        }
        //prevents CPU from hanging 
        //without this line the CPU would spin too fast looking for jobs 
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

void JobWorkerThread::ShutDown(){//stop working 
    //m_isStopping can be called by main thread, so needs Mutex protection 
    //thread protect this so that data does not get corrupted with reading & writing at same time 
    m_workerStatusMutex.lock(); 
    m_isStopping = true; 
    m_workerStatusMutex.unlock(); 
}

bool JobWorkerThread::IsStopping() const{
    m_workerStatusMutex.lock();
    bool shouldClose = m_isStopping; //created local bool & copied member property into it 
    //could have just returned m_isStopping, but will not be mutex protected 
    //so if we return m_isStopping, it could be changed by another thread before we return it
    //code would work until the one time it doesnt work, and then it would be a nightmare to debug
    //DO NOT want to pass out vars in other threads to other stuff if they can be read by more than one thread at at time 
    //so we create a local copy of the member variable, new one every time we call this function
    //getter and setter in multithread env, always want member copies in local vars 
    m_workerStatusMutex.unlock(); 

    return shouldClose; 
}

void JobWorkerThread::SetWorkerJobChannels(unsigned long workerJobChannels){
    m_workerStatusMutex.lock(); 
    m_workerJobChannels = workerJobChannels; //could be set in main thread, so protect it w/ mutex lock/unlock
    m_workerStatusMutex.unlock(); 
}

//worker thread main is a static function 
//only one of these functions exist for the entire class 
//need to past instance you want to call into this workerthread main
//so we pass in the this pointer as a void pointer 
//void pointer can take any type of object & libraries can handle any type 
//know should be a worker thread obj. 
//void pointer is the starting spot, casting tells how to interpret obj. 
//void pointer does not tell you how big, how much memory to grab, etc. --> just tells you address in memory 
//casting tells you how big it is, gives offsets, shows how to interpret 
//could add an inhertitence tree to this structure as long as the inheritence tree is compatible 
//if making different types of job worker threads this function would still work --> can use this function to start any type of thread
//RTTI - run time type information <-- super slow so NOT recommended being used 
//with this structure, as long as obj. has work function then it will work. 

void JobWorkerThread::WorkerThreadMain(void* workThreadObject){
    
    JobWorkerThread* thisWorker = (JobWorkerThread*) workThreadObject; //cast to jobworkerthread pointer 
    thisWorker->Work(); //call work function 
}
