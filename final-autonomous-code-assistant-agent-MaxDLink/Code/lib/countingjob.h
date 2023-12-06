#include "job.h"
#include "jobsystem.h"

#include <queue> //for basic thread control
class CountingJob : public Job{
    private: 
    bool isLinkerError = false; //for switching regex expression 
    public: 
    CountingJob(unsigned long jobChannels, int jobType): Job(jobChannels, jobType) {}; 
    ~CountingJob() {};
    void Execute() override; 
    void JobCompletedCallback() override; 
    void StringParsing(std::string &content, std::vector<std::string> &parsedStrings); 
    
}; 