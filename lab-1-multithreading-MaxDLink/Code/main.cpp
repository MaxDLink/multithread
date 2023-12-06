#include <iostream> 
#include <string> 
#include <thread> 

#include "jobsystem.h"
#include "renderjob.h"
#include "compilejob.h"
#include "parsingjob.h"
#include "outputjob.h"
#include <queue> //for streaming content from compile job to parsing job

//TODO - add promise #include <future> for thread waiting instead of busy whiles? 
int main(void){

    //basicThreadControl btc; 
    //btc.kickoff();

    //find out how many cores are on the machine 
    //unsigned int nCores = std::thread::hardware_concurrency();
    //std::cout << "Number of cores: " << nCores << std::endl;
    std::cout << "Creating Job System" << std::endl; 

    JobSystem* js = JobSystem::CreateOrGet();   

    std::cout << "Creating Worker Threads" << std::endl; 

    //determined by number of cores on machine 
    js->CreateWorkerThread("Thread1", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread2", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread3", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread4", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread5", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread6", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread7", 0xFFFFFFFF);
    js->CreateWorkerThread("Thread8", 0xFFFFFFFF);

    std::cout << "Creating Jobs" << std::endl; 

    std::vector<Job*> jobs; 

    std::queue<std::string> stream;

    std::string directoryToMakefile = "makefile"; //explanatory var for makefile directory 
    //created a compile job
    CompileJob* cjb = new CompileJob(0xFFFFFFFF, 1, stream, directoryToMakefile); //pass in directory to makefile to run make command in cjb 
    jobs.push_back(cjb); 
    js->QueueJob(cjb); //queue compile job

    std::cout << "Queuing CJB" << std::endl; 

    while(!js->IsJobComplete(0) == 1){} //busy for cjb 

    //make parsejob 
    ParsingJob* pjb = new ParsingJob(0xFFFFFFFF, 1, stream); 
    jobs.push_back(pjb); //add parsing job to jobs vector
    js->QueueJob(pjb); //queue parsing job

    while(!js->IsJobComplete(1) == 1){} //busy for pjb 

    //make output job
    OutputJob* ojb = new OutputJob(0xFFFFFFFF, 1); //takes errors.json from data folder
    jobs.push_back(ojb); //add output job to jobs vector 
    js->QueueJob(ojb); //queue output job 

    while(!js->IsJobComplete(2) == 1){}

    js->FinishCompletedJobs();
    std::cout << "total jobs completed " << js->totalJobs <<std::endl;
    js->Destroy();

    return 0; 

}

