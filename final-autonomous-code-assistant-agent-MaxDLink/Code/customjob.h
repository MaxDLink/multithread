#pragma once
#include "./lib/job.h"
#include <iostream> 
#include "customjob.h"
#include "JobSystemAPI.h" //for kicking off jobs with the parsed flowscript....
// CustomJob declaration
class CustomJob : public Job {

public:

    void Execute() override; // Declare the Execute method

    void ExecuteParse(); //declare the execute parsing method

    void SetFilePath(const std::string& path) { filePath = path; } //set file path for custom job

    void SetJobSystem(MyJobSystemAPI* jobSystem) { jsForCJ = jobSystem; } //set job system for custom job



    void JobCompletedCallback() override;  // Declare the callback method

    std::string escapeShellArgument(const std::string& arg); //for the code variable in customjob.cpp 

    std::string output; //string for output added
    int returnCode;  //return code added 

    // Factory function to create CustomJob
    static Job* CreateCustomJob(); //static so that it can be called without an instance of the custom job class, because we will be making custom job at runtime

    //callback signature to return jobLabels contents to interpreter.cpp 
    using JobCompletedCallbackType = std::function<void(const std::vector<std::string>&)>;

    JobCompletedCallbackType jobCompletedCallback; //member variable for callback function

    std::string readFileContents(const std::string& filePath); //function to read file contents 
    std::string processFile(const std::string& filePath); //function to check filetype and parse file contents based on filetype 
    std::string readAllFilesInDirectory(const std::string& directoryPath); //function to read all files in a directory
    //std::vector<std::string> getJobLabels() { return jobLabels;} //getter for jobLabels

    const std::vector<std::string>& getJobLabels() const {//Getter that returns jobQueue to customjob so that customjob can use the jobQueue to extract the joblabels //TODO - understand this relationship 
        std::cout << "\n\n\nJOBLABELS HOLDS THIS: " << std::endl; 
        for(const auto& labels : jobLabels){
            std::cout << labels << std::endl; 
        }
        std::cout << "GETTING JOB LABELS" << std::endl;
        return jobLabels; //TODO - jobLabels is not filled with anything... why? 
    }

private: 
    std::map<std::string, Job*> jobsForAPIMap; //holds the jobs map from main.cpp

    std::string filePath;

    MyJobSystemAPI* jsForCJ;

    std::vector<std::string> jobLabels; //for storing job strings //TODO - can I use jobQueue in customvisitor.cpp instead??? Cleaner??? 

}; //end of class CustomJob