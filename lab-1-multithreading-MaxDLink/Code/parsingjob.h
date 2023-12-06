#include "job.h"
#include "jobsystem.h"

#include <queue> //for basic thread control
class ParsingJob : public Job{
    private: 
    std::queue<std::string> streamPjb;
    bool isLinkerError = false; //for switching regex expression 

    public: 
    ParsingJob(unsigned long jobChannels, int jobType, std::queue <std::string> & stream): Job(jobChannels, jobType), streamPjb(stream) {}; 
    ~ParsingJob() {};
    void Execute(); 
    void JobCompletedCallback(); 
    void StringParsing(std::string &content, std::vector<std::string> &parsedStrings); 
}; 