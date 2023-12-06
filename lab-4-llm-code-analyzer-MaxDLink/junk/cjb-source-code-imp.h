#include "job.h"
#include <future> 
#include "jobsystem.h"
#include <queue> //for basic thread control
//could have taken everything in compilejob.cpp and put it on top of compilejob.h instead 
//in general should put dependencies in .cpp files instead of .h files
//if you put dependencies in .h files, then everything that includes that .h file will have to include those dependencies
//pragma once prevents children from calling imports again 
//when working on large code bases, when making changes in .h have to change every single .cpp file that includes that .h file
//if dependencies are in .cpp files, then only have to change .cpp file that includes that .h file -> faster compile times 
//when dont need it there then dont include it, use forward declarations etc. 
//keep dependencies in .cpp files (unless creating object in .h, then need them in .h) 
class CompileJob : public Job{
    private: 
    std::string makefile; //string for grabbing makefile path 
    
    public: 
    CompileJob(unsigned long jobChannels, int jobType, const std::string & passedInMakeFile): Job(jobChannels, jobType), makefile(passedInMakeFile) {}; //constructor - TODO - added passing jobs vector to constructor to add parsing job to jobs vector
    ~CompileJob() {};

    std::string output; //string for output added
    int returnCode;  //return code added 
    void Execute() override; 
    void JobCompletedCallback() override; 
    void ReadInErrors(); //function to read in errors from makefile
    void getCodeSnippets(); //function to get code snippets from output
    

}; 