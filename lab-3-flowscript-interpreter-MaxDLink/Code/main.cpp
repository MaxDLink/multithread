#include <iostream> 
#include "JobSystemAPI.h" 
#include "customjob.h"

int main(void){
    //call API class functions for testing 
    MyJobSystemAPI jobSystem; //create job system object

    jobSystem.initialize(); //initialize job system -- creates threads in isolated function to avoid creating too many threads & running out of resources 

    //TODO- for lab 3 - main needs to have the flowscript files and needs to create and pass files to interpreter job 
    //read in flowscript files and pass to interpreter job
    
    //customJob registering: 
    //TODO - pass jobs vector into here by ref 
    jobSystem.registerCustomJob(CustomJob::CreateCustomJob, "customjob"); //register custom job
    jobSystem.createCustomJob("customjob"); //create custom job

    //std::string flowScriptFile = "Data/fsp1.txt"; 
    //jobSystem.setJobSystemObj(&jobSystem); //set job system object for custom job

    //create native jobs 
    jobSystem.createJob("countingjob"); //create render job //TODO - add to api functionality completely just like interpreter job
    jobSystem.createJob("compilejob"); //create compile job
    jobSystem.createJob("parsingjob"); //create parsing job
    jobSystem.createJob("outputjob"); //create output job

    //TODO - pass jobs vector into here by ref 
    //interpret flowscript files
    jobSystem.createJob("interpreterjob"); //create interpreter job

    jobSystem.initialize(); //initialize job system -- creates threads in isolated function to avoid creating too many threads & running out of resources
    jobSystem.queueSpecJob("interpreterjob"); //queue interpreter job

    //assume flowscript jobs are known!!! Create and register them here!!!

    // jobSystem.registerCustomJob(CustomJob::CreateCustomJob, "customjob"); //register custom job
    // jobSystem.createCustomJob("customjob"); //create custom job

    //TODO - combine into one single register function later? All main should do is register jobs pre-execution of interpreter, and this does it but is convoluted in two lines 

    // jobSystem.registerCustomJob(CustomJob::CreateCustomJob, "customjob"); //register custom job
    // jobSystem.createCustomJob("customjob"); //create custom job

    //jobSystem.startJobSystem(); //add jobs to job system

    jobSystem.destroyJobSystem();


    return 0; 

    //TODOS I COULD NOT GET TO BUT THAT SHOULD BE DONE IN THE FUTURE 
    //1. use the job system after you stop it.... the jobsystem can be used but you get seg faults and have to hard exit with exit(0); command 
    //2. be able to query the status of jobs that were reordered for dependencies with dependency function. As I currently have it, the dependency function makes new ID's for each job in the order they need to be in, and these dependencies are not updated in the job system, so the status of the jobs will not be able to be found if a dependency is ran... This could be it.. or it could just be threads running too quickly wiht concurrency etc. The jobstatus queries that were not being found were being queried after the job system was stopped with stopjobsystem function, so this whole comment could be an overreaction, but I should still investigate this to make sure... 

}

