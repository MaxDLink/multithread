#pragma once // if theres multiple places that include job.h, there will only include once. 
//If make two jobs without, then you would get compile error 
//prevents problem of redefine and circular includes (includes call eachother, loop)
#include <mutex> 
#include <map> 
#include <deque> 
#include <vector> 
#include <thread> 

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
    
    private: 
    int m_jobID = -1;
    int m_jobType = -1;

    unsigned long m_jobChannels = 0xFFFFFFFF; //32 bits, each bit represents a channel.

}; 