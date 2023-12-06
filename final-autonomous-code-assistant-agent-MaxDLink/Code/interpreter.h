#include <future> 
#include "./lib/job.h"
#include "JobSystemAPI.h" //for kicking off jobs with the parsed flowscript....
#include <queue> //for basic thread control
//#include <unordered_set> //TODO - for valid job names

//could have taken everything in compilejob.cpp and put it on top of compilejob.h instead 
//in general should put dependencies in .cpp files instead of .h files
//if you put dependencies in .h files, then everything that includes that .h file will have to include those dependencies
//pragma once prevents children from calling imports again 
//when working on large code bases, when making changes in .h have to change every single .cpp file that includes that .h file
//if dependencies are in .cpp files, then only have to change .cpp file that includes that .h file -> faster compile times 
//when dont need it there then dont include it, use forward declarations etc. 
//keep dependencies in .cpp files (unless creating object in .h, then need them in .h) 
class Interpreter : public Job{
    
    private: 
    std::string makefile; //string for grabbing makefile path 
    MyJobSystemAPI* jobSystemObj; //holds job system object from main.cpp

    JobSystem* jsForAPI; //gives more fine control of job functions like queueing etc. TODO - FOR TESTING ONLY 
    std::map<std::string, Job*> jobsForAPIMap;
    //TODO - validJobs is not needed? jobQueue vector already cross checked against a set of valid job names in customvisitor.cpp
    //std::unordered_set <std::string> validJobs = {"compilejob", "parsingjob", "outputjob", "countingjob", "controlstatement", "loopstatement"}; //holds valid job names

    //integer vars for conditional flow testing 
    //fsCond1 > fsCond2 runs compilejob-->countingjob 
    //fsCond1 < fsCond2 runs compilejob-->parsingjob-->outputjob
    //TODO - should be in flowscript not hard coded? 
    int fsCond1 = 1; 
    int fsCond2 = 0; //TODO - change names in flowscript to match 
    //std::vector<std::string> jobs; //holds the job labels that customJob gets from the parsed flowscript file 
    bool loopCond = 0; //holds boolean value from loop.txt file to test looping of jobs 

    std::vector<std::string> jobLabels; //for storing job strings //TODO - can I use jobQueue in customvisitor.cpp instead??? Cleaner??? 

    public: 
    Interpreter(unsigned long jobChannels, int jobType, const std::string & passedInMakeFile, MyJobSystemAPI* jobSystemPassedIn, JobSystem* jsForAPIPassed, std::map<std::string, Job*> &jobsForAPIMapPassed): Job(jobChannels, jobType), makefile(passedInMakeFile), jobSystemObj(jobSystemPassedIn), jsForAPI(jsForAPIPassed), jobsForAPIMap(jobsForAPIMapPassed) {}; //constructor - TODO - added passing jobs vector to constructor to add parsing job to jobs vector
    ~Interpreter() {};
    std::string output; //string for output added
    int returnCode;  //return code added 
    void Execute() override; 
    void ExecuteParse(); 
    void JobCompletedCallback() override; 
    void CondFlow(); 
    void Loop(); 
}; 