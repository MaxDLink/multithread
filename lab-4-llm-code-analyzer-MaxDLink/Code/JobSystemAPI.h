#pragma once 

#include <string>
#include <set> 
#include <queue> //TODO - remove this later? Not being used in parsejob or compilejob anymore. Might be being used in compileJob for json parsing, double check. 
#include "./lib/jobsystem.h"
#include <future> 
#include "factory.h"
class MyJobSystemAPI {
private: 
    // JobSystem* jsForAPI; 
    JobSystem* jsForAPI = JobSystem::CreateOrGet();   

    //std::vector<Job*> jobsForAPI; 
    std::map<std::string, Job*> jobsForAPI; //holds job pointers for job system API and unordered set for dependency function
    std::vector<std::string> jobOrder; //holds job order for calling from map in correct order 
    std::mutex jobMutex; //mutex for job system API

    MyJobSystemAPI* jsFromMain; //holds job system from main.cpp

    // std::unordered_map<std::string, std::unordered_set<std::string>> dependencies; //holds job dependencies for dependency function
    //TODO - remember to manage this memory with the destructor later! 
    JobFactory* jobFactory; //for calling register function in factory.h for custom jobs 
    

public:
    MyJobSystemAPI(); 
    ~MyJobSystemAPI(); //for deleting JobFactory pointer
    Job* getLLMJob(); 
    void createJob(const std::string& jobType);
    void destroyJob(const std::string& jobType);
    void completeJob(const std::string& jobType);
    int getJobStatus(const std::string& jobType);
    void setJobSystemObj(MyJobSystemAPI* jobSystemObjPassedInFromMain); //set job system object from main.cpp
    void startJobSystem();
    void initialize(); 
    void queueSpecJob(const std::string& JobType); //TODO - build this add job function to add jobs to job system
    void stopJobSystem();
    void destroyJobSystem();
    void dependency(const std::string& jobType1, const std::string& jobType2); //TODO - add more string types later?? two is fine for now. Or call multiple times & let it build off previous priority list. 
    //void createCustomJob(const std::string& jobType, const std::string& filePath, MyJobSystemAPI& jobSystem);
    void createCustomJob(const std::string& jobType);

    void registerCustomJob(JobFactoryFunction factoryFunction, const std::string& jobTypeName);

};
