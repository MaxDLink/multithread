#include <iostream> 
#include <string> 
#include <thread> 
#include <sstream> 
#include <fstream> //for reading and writing to file 
#include "./lib/jobsystem.h"
#include "./lib/compilejob.h"
#include "./lib/parsingjob.h"
#include "./lib/outputjob.h"
#include "./lib/job.h"
#include "interpreter.h"
#include <queue> //for streaming content from compile job to parsing job
#include "./lib/json.hpp" //for json file writing
#include "JobSystemAPI.h"
#include "factory.h"
#include "customjob.h"
#include "./lib/countingjob.h"
#include <condition_variable> //for thread control -- more elegant than busy while 

using json = nlohmann::json; //for json json manipulation 

//define a constructor 
MyJobSystemAPI::MyJobSystemAPI(){    //TODO - remember to manage this memory with the destructor later! IS THIS SECITON NEEDED OR WAS THE METHOD WITHOUT IT OKAY???
    jsForAPI = JobSystem::CreateOrGet(); //create job system 
    jobFactory = new JobFactory(); //create job factory 
}

//destructor for deleting jobFactory pointer 
MyJobSystemAPI::~MyJobSystemAPI(){
    delete jobFactory; //TODO - remember to call this at some point later if needed to delete jobFactory pointer from memory 
}

void MyJobSystemAPI::getJobType(){
    std::cout << "The job types are compilejob, parsingjob, outputjob, customjob" << std::endl; 
} 

void MyJobSystemAPI::createJob(const std::string& jobType){
    if(jobType == "compilejob"){
                std::cout << "Creating CompileJob" << std::endl; 
                std::string directoryToMakefile = "makefile"; //explanatory var for makefile directory 
                //created a compile job
                CompileJob* cjb = new CompileJob(0xFFFFFFFF, 1, directoryToMakefile); //pass in directory to makefile to run make command in cjb 
                jobMutex.lock(); //lock mutex for job system API
                //jobsForAPI.push_back(cjb); //add compile job to jobs vector
                jobsForAPI[jobType] = cjb; //add compile job to jobs map
                jobOrder.push_back(jobType); //add job string name to job order vector
                jobMutex.unlock(); //unlock mutex for job system API
            }
            else if(jobType == "countingjob"){
                std::cout << "Creating counting job" << std::endl; 
                //make parsejob 
                CountingJob* cnt = new CountingJob(0xFFFFFFFF, 1); 
                jobMutex.lock(); //lock mutex for job system API
                //jobsForAPI.push_back(pjb); //add parsing job to jobs vector
                jobsForAPI[jobType] = cnt;
                jobOrder.push_back(jobType); //add job string name to job order vector
                jobMutex.unlock(); //unlock mutex for job system API
            }
            else if(jobType == "interpreterjob"){
                //TODO - change this from being hardcoded to being passed in? Path to flowscript file 
                std::string flowScriptFile = "Data/fsp1.txt"; 

                std::cout << "Creating InterpreterJob" << std::endl; 
                //make parsejob 
                Interpreter* ijb = new Interpreter(0xFFFFFFFF, 1, flowScriptFile, jsFromMain, jsForAPI, jobsForAPI); 
                jobMutex.lock(); //lock mutex for job system API
                //jobsForAPI.push_back(pjb); //add parsing job to jobs vector
                jobsForAPI[jobType] = ijb;
                jobOrder.push_back(jobType); //add job string name to job order vector
                jobMutex.unlock(); //unlock mutex for job system API
            }
            else if(jobType == "parsingjob"){
                std::cout << "Creating ParsingJob" << std::endl; 
                //make parsejob 
                ParsingJob* pjb = new ParsingJob(0xFFFFFFFF, 1); 
                jobMutex.lock(); //lock mutex for job system API
                //jobsForAPI.push_back(pjb); //add parsing job to jobs vector
                jobsForAPI[jobType] = pjb;
                jobOrder.push_back(jobType); //add job string name to job order vector
                jobMutex.unlock(); //unlock mutex for job system API

            }
            else if(jobType == "outputjob"){
                std::cout << "Creating OutputJob" << std::endl; 
                OutputJob* ojb = new OutputJob(0xFFFFFFFF, 1); //takes errors.json from data folder
                jobMutex.lock(); //lock mutex for job system API
                //jobsForAPI.push_back(ojb); //add output job to jobs vector
                jobsForAPI[jobType] = ojb; 
                jobOrder.push_back(jobType); //add job string name to job order vector
                //js->QueueJob(ojb); //queue output job 
                jobMutex.unlock(); //unlock mutex for job system API
            }
            else{
                std::cout << "invalid job type" << std::endl; 
            }
}

void MyJobSystemAPI::destroyJob(const std::string& jobType){
    if(jobType == "compilejob"){
        std::cout << "Destroying CompileJob" << std::endl;
        //delete jobsForAPI.at(0); //delete cjb
        delete jobsForAPI[jobType];
        jobsForAPI.erase(jobType);
    }
    else if(jobType == "parsingjob"){
        std::cout << "Destroying ParsingJob" << std::endl; 
        //delete jobsForAPI.at(1); //delete pjb
        delete jobsForAPI[jobType];
        jobsForAPI.erase(jobType);
    }
    else if(jobType == "outputjob"){
        std::cout << "Destroying OutputJob" << std::endl; 
        //delete jobsForAPI.at(2); //delete ojb
        delete jobsForAPI[jobType];
        jobsForAPI.erase(jobType);
    }
    else if(jobType == "customjob"){
        std::cout << "Destroying CustomJob" << std::endl; 
        //delete jobsForAPI.at(3); //delete custom job
        //TODO - destroy function pointer here also 
        delete jobsForAPI[jobType];
        jobsForAPI.erase(jobType);
    }
    else{
        std::cout << "invalid job type" << std::endl; 
    }
}

void MyJobSystemAPI::getJobStatus(const std::string& jobType){
    
    Job* job = jobsForAPI[jobType]; //retrieve specific job from map

    if(jobType == "compilejob"){
        std::cout << "CompileJob status: " << jsForAPI->GetJobStatus(job->GetUniqueID()) << std::endl; 
    }
    else if(jobType == "parsingjob"){
        std::cout << "ParsingJob status: " << jsForAPI->GetJobStatus(job->GetUniqueID()) << std::endl; 
    }
    else if(jobType == "outputjob"){
        std::cout << "OutputJob status: " << jsForAPI->GetJobStatus(job->GetUniqueID()) << std::endl; 
    }
    else if(jobType == "customjob"){
        std::cout << "CustomJob status: " << jsForAPI->GetJobStatus(job->GetUniqueID()) << std::endl; 
    }
    else{
        std::cout << "invalid job type" << std::endl; 
    }
}

void MyJobSystemAPI::completeJob(const std::string& jobType){
    Job* job = jobsForAPI[jobType]; //retrieve specific job from map

    if(jobType == "compilejob"){
        std::cout << "Completing CompileJob" << std::endl;
        jsForAPI->FinishJob(job->GetUniqueID()); //finish compile job
    }
    else if(jobType == "parsingjob"){
        std::cout << "Completing ParsingJob" << std::endl; 
        jsForAPI->FinishJob(job->GetUniqueID()); //finish parsing job
    }
    else if(jobType == "outputjob"){
        std::cout << "Completing OutputJob" << std::endl; 
        jsForAPI->FinishJob(job->GetUniqueID()); //finish output job
    }
    else if(jobType == "customjob"){
        std::cout << "Completing CustomJob" << std::endl; 
        jsForAPI->FinishJob(job->GetUniqueID()); //finish custom job
    }
    else{
        std::cout << "invalid job type" << std::endl; 
    }
}

 void MyJobSystemAPI::startJobSystem(){
    std::cout << "Creating Job System" << std::endl; 

    //JobSystem* js = JobSystem::CreateOrGet();   

    std::cout << "Creating Worker Threads" << std::endl; 

    //determined by number of cores on machine 
    jsForAPI->CreateWorkerThread("Thread1", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread2", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread3", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread4", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread5", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread6", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread7", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread8", 0xFFFFFFFF);

    for(const std::string& jobType : jobOrder){
        Job* job = jobsForAPI[jobType]; //retrieve specific job from map
        std::cout << "Queuing WITH JOB ID: " << job->GetUniqueID() << std::endl;

        std::promise<void> jobCompletionPromise;
        std::future<void> jobCompletionFuture = jobCompletionPromise.get_future();

        jsForAPI->QueueJob(job); //queue job
    

        
        //pass condition bool to child threads --> make a function in job that gets the condition bool, sets it to true. Use that function in child jobs. 
        
        std::unique_lock<std::mutex> lock(jobMutex);

        job->cv.wait(lock, [job]{ return job->condition; });
        //job->waitForCompletion();
    }

 }

void MyJobSystemAPI::initialize(){
    
    std::cout << "Creating Worker Threads" << std::endl; 

    //determined by number of cores on machine 
    jsForAPI->CreateWorkerThread("Thread1", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread2", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread3", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread4", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread5", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread6", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread7", 0xFFFFFFFF);
    jsForAPI->CreateWorkerThread("Thread8", 0xFFFFFFFF);


}

void MyJobSystemAPI::queueSpecJob(const std::string& JobType) {//TODO - take out? Not being used anymore?
    //TODO - add jobs to job system here for customJob... 
    //for(const std::string& jobType : jobOrder){
        Job* job = jobsForAPI[JobType]; //retrieve specific job from map
        std::cout << "Queuing WITH JOB ID: " << job->GetUniqueID() << std::endl;

        std::promise<void> jobCompletionPromise;
        std::future<void> jobCompletionFuture = jobCompletionPromise.get_future();

        jsForAPI->QueueJob(job); //queue job
    

        
        //pass condition bool to child threads --> make a function in job that gets the condition bool, sets it to true. Use that function in child jobs. 
        
        std::unique_lock<std::mutex> lock(jobMutex);

        job->cv.wait(lock, [job]{ return job->condition; });
        //job->waitForCompletion();
    //}
}


void MyJobSystemAPI::setJobSystemObj(MyJobSystemAPI* jobSystemObjPassedInFromMain){
    jsFromMain = jobSystemObjPassedInFromMain; //set job system object from main.cpp
}

 void MyJobSystemAPI::destroyJobSystem(){
    //jsForAPI->FinishCompletedJobs(); //TODO - causes seg fault.... why? Finishing jobs then destroying job system causes seg fault because double destruction? Move to stopJobSystem() instead because there you just want the object and not the jobs 
    std::cout << "Job system destroyed!" << std::endl; 
    jsForAPI->Destroy();
    //std::cout << "total jobs completed " << jsForAPI->totalJobs <<std::endl; //TODO - (low priority) this totaljobs completed value should be fixed to update as jobs are completed
    //TOOD - reads 62 jobs completed when only 3 jobs are completed when running custom job as one of the jobs. 
 }

 void MyJobSystemAPI::stopJobSystem(){
    std::cout << "Stopping System...child threads being cleaned.. jobsystem still running...." << std::endl; 
    jsForAPI->FinishCompletedJobs();
 }

void MyJobSystemAPI::dependency(const std::string& jobType1, const std::string& jobType2){
    //TODO - (low priority) change this function to make job B only execute when Job A is done etc with future and promise? its low priority because it works as is for that purpose so it is not crucial to change it.
    std::cout << "Setting dependency" << std::endl;
    std::vector <std::string> dependencies; 
    dependencies.push_back(jobType1);
    dependencies.push_back(jobType2);   
    
    for(const auto& job : jobOrder){
        if(std::find(dependencies.begin(), dependencies.end(), job) == dependencies.end()){
            dependencies.push_back(job); //add job to dependencies vector if it is not already in there
        }
    }

    jobMutex.lock(); //lock mutex for job system API
    jobOrder = dependencies; //update job order vector with new priority
    jobMutex.unlock(); //unlock mutex for job system API

    int ID = 0; //increments in for loop to set each job ID to matching ID val 
    for(const auto& jobType : jobOrder){
        Job* job = jobsForAPI[jobType]; //retrieve specific job from map to change ID 
        job->setUniqueID(ID); //set new ID val
        ID++; //increment ID val
    }

}    

void MyJobSystemAPI::createCustomJob(const std::string& jobType){
    Job* customJob = jobFactory->Create(jobType);  // Use the factory to create the job
    if (customJob) {
        jobsForAPI[jobType] = customJob;  // Store the custom job in the API's job map
        jobOrder.push_back(jobType);
    } else {
        std::cout << "Failed to create custom job: " << jobType << std::endl;
    }
}

void MyJobSystemAPI::registerCustomJob(JobFactoryFunction factoryFunction, const std::string& jobTypeName) {
    jobFactory->Register(factoryFunction, jobTypeName); //factory function pointer is job object from customJobs create function with the set filepath and jobsystem 
}





