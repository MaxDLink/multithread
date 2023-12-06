#pragma once

#include "./lib/job.h"
#include <map>
#include <string>

// Function pointer type for job creation
typedef Job* (*JobFactoryFunction)();

class JobFactory {
public:
    // Register a custom job's factory function
    void Register(JobFactoryFunction factoryFunction, const std::string& jobTypeName);
    
    // Create a job using its factory function
    Job* Create(const std::string& jobTypeName);

    //Job* CreateCustomJob();

private:
    // Map to store the factory functions for different job types
    std::map<std::string, JobFactoryFunction> m_registeredJobs;
};
