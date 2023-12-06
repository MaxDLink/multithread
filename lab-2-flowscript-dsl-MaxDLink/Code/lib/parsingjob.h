#include "job.h"
#include "jobsystem.h"

#include <queue> //for basic thread control
class ParsingJob : public Job{
    private: 
    bool isLinkerError = false; //for switching regex expression 
    public: 
    ParsingJob(unsigned long jobChannels, int jobType): Job(jobChannels, jobType) {}; 
    ~ParsingJob() {};
    void Execute() override; 
    void JobCompletedCallback() override; 
    void StringParsing(std::string &content, std::vector<std::string> &parsedStrings); 
    
}; 