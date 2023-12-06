#pragma once
#include "./lib/job.h"
#include <iostream> 

// CustomJob declaration
class CustomJob : public Job {
public: 
    void Execute() override; // Declare the Execute method

    void JobCompletedCallback() override;  // Declare the callback method
    
    std::string output; //string for output added
    int returnCode;  //return code added 

    // Factory function to create CustomJob
    static Job* CreateCustomJob(); //static so that it can be called without an instance of the custom job class, because we will be making custom job at runtime




private: 


}; //end of class CustomJob