#pragma once 
#include <mutex> 
#include <map> 
#include <deque> 
#include <vector> 
#include <thread> 

#include "job.h" 

class JobSystem; 

class JobWorkerThread{
    friend class JobSystem; //just pointer to jobsystem so just a forward declaration here. Faster compiler time 
    //linker error if cannot find the declaration later 
    private: 
    JobWorkerThread(const char* uniqueName, unsigned long workerJobChannels, JobSystem* jobSystem); 
    ~JobWorkerThread(); 
    //this is actually the thread -- will run jobs 
    //give job unique name so can identify which thread is running which job
    //has pointer so that can access jobsystem

    void StartUp(); //Kick off actual thread, which will call Work()
    void Work(); //Called in private thread, blocks forever until StopWorking() is called
    void ShutDown(); //Signal that work should stop at next opportunity 

    bool IsStopping() const; 
    void SetWorkerJobChannels(unsigned long workerJobChannels); //something can write to this function, so mutex lock should be around jobworkerchannels in jobworkerthread.cpp 
    static void WorkerThreadMain(void* workThreadObject); //start point -- define worker thread object & pass it into here to kick off 

    private: 
    const char *       m_uniqueName; 
    unsigned long      m_workerJobChannels = 0xffffffff; 
    bool               m_isStopping = false;
    JobSystem*         m_jobSystem = nullptr;
    std::thread*       m_thread = nullptr; 
    mutable std::mutex m_workerStatusMutex; 
}; 