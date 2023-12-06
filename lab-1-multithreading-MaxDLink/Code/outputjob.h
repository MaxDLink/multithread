#include "job.h"
#include "json.hpp" //for creating output json 
using json = nlohmann::json; 
class OutputJob : public Job{
    private:
    public: 
    OutputJob(unsigned long jobChannels, int jobType): Job(jobChannels, jobType) {}; 
    ~OutputJob() {};


    void Execute(); 
    void JobCompletedCallback(); 
    void NonLinkerError(json & errors); //handle writing errors that are not linker errors 
    void LinkerError(json & errors); //handle linker error
}; 