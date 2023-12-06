#pragma once // if theres multiple places that include job.h, there will only include once. 
//If make two jobs without, then you would get compile error 
//prevents problem of redefine and circular includes (includes call eachother, loop)
#include <mutex> 
#include <map> 
#include <deque> 
#include <vector> 
#include <thread> 
#include <iostream> 
#include <condition_variable>
class Job{
    friend class JobSystem; 
    friend class JobWorkerThread; 
    public: 
    Job(unsigned long jobChannels = 0xFFFFFFFF, int jobType = -1) : m_jobChannels(jobChannels), m_jobType(jobType) {
        static int s_nextJobID = 0; 
        m_jobID = s_nextJobID++; 
    }

    virtual ~Job() {}

    virtual void Execute() = 0; //body set = 0 so purely virtual, abstract class. Must inherent the execute function 
    virtual void JobCompletedCallback() {} //do not have to implement this function (body not set to zero, so if implemented then does nothing)
                                            //can call if want to.
    int GetUniqueID() const { return m_jobID; } //job type that returns will be a const so cannot be manipulated 
    
    void setUniqueID(int id) { m_jobID = id; } //set job id to id passed in inside the job system API dependency function to match new dependency order. For job status to update correctly.
    void signalCompletion() {//signals job complete 
        std::lock_guard<std::mutex> lock(jobMutex);
        condition = true;
        cv.notify_one();
    }


    // bool isComplete() const { return condition; } //TODO - an encapsulated version of thread control with cond. var 
    // void waitForCompletion() {//waits for job to complete
    //     std::unique_lock<std::mutex> lock(jobMutex);
    //     cv.wait(lock, [this]{ return condition; });
    // }

    //for thread control accross child jobs 
    std::condition_variable cv; //condition variable for job system API thread control 
    bool condition = false; //bool for condition variable for job system API thread control. Starts false because child job not complete at first. 

    //promptFromMain & IPFromMain are variables that are private to the job.h class, but that are set from the prompt/ip values in main.cpp. 
    void SetPrompt(const std::string& promptPassedIn) {promptFromMain = promptPassedIn; } //set prompt for custom job

    void SetIP(const std::string& ipPassedIn) {ipFromMain = ipPassedIn; } //set ip for custom job

    //prompt/ip public so that customjob.cpp can access them
    std::string promptFromMain; //for storing prompt string
    std::string ipFromMain; //for storing ip string
    
    private: 
    int m_jobID = -1;
    int m_jobType = -1;
    std::mutex jobMutex;

    bool JobComplete = true; //condition in main to true with setter function in job.h 

    unsigned long m_jobChannels = 0xFFFFFFFF; //32 bits, each bit represents a channel.

  
    

    // //for thread control accross child jobs -- //TODO - for the encapsulated version of thread control with condvar 
    // std::condition_variable cv; //condition variable for job system API thread control 
    // bool condition = false; //bool for condition variable for job system API thread control. Starts false because child job not complete at first. 



}; 