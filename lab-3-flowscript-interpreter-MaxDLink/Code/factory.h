#pragma once

#include "./lib/job.h"
#include <map>
#include <string>

class MyJobSystemAPI; //forward declaration of job system API class

// Function pointer type for job creation
//typedef Job* (*JobFactoryFunction)();
//typedef Job* (*JobFactoryFunction)(const std::string& filePath, MyJobSystemAPI&); //updated to accept filePath as parameter so that customJob can interpret files passed to it. Modified to accept jobSystem obj. as parameter. 
typedef Job* (*JobFactoryFunction)();


class JobFactory {
public:
    // Register a custom job's factory function
    void Register(JobFactoryFunction factoryFunction, const std::string& jobTypeName);
    
    // Create a job using its factory function
    //Job* Create(const std::string& jobTypeName, const std::string& filePath, MyJobSystemAPI& jobSystem);

    Job* Create(const std::string& jobTypeName);

    //Job* CreateCustomJob();

private:
    // Map to store the factory functions for different job types
    std::map<std::string, JobFactoryFunction> m_registeredJobs;
};
