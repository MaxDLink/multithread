#include <iostream> 
#include "JobSystemAPI.h" 
#include "customjob.h"

int main(void){
    //call API class functions for testing 
    MyJobSystemAPI jobSystem; //create job system object

    jobSystem.initialize(); //initialize job system -- creates threads in isolated function to avoid creating too many threads & running out of resources 

    // jobSystem.registerCustomJob(CustomJob::CreateCustomJob, "customjob"); //register custom job
    // jobSystem.createCustomJob("customjob"); //create custom job

    // //std::string flowScriptFile = "Data/fsp1.txt"; 
    // //jobSystem.setJobSystemObj(&jobSystem); //set job system object for custom job

    // //create native jobs 
    // jobSystem.createJob("countingjob"); //create render job //TODO - add to api functionality completely just like interpreter job
    // jobSystem.createJob("compilejob"); //create compile job
    // jobSystem.createJob("parsingjob"); //create parsing job
    // jobSystem.createJob("outputjob"); //create output job

    // jobSystem.createJob("interpreterjob"); //create interpreter job

    // jobSystem.initialize(); //initialize job system -- creates threads in isolated function to avoid creating too many threads & running out of resources
    // jobSystem.queueSpecJob("interpreterjob"); //queue interpreter job

    //make compilejob 
    //jobSystem.createJob("compilejob"); //create compile job
    //jobSystem.createJob("parsingjob"); //create parsing job
    //jobSystem.createJob("outputjob"); //create output job

    //prompt passing to LLM customjob without code var. Code added later in customJob.cpp. //TODO  - change this later to have code appended to prompt here? 
    //TODO - here I am relying on AI response so the json file format can be changed by changing this prompt 
    std::string promptToPassIn = "Answer question based on the context. Context: Here is code in a json file format with errors. Please fix these errors and add a description of what you did to fix the errors. Question: "; 

    //make custom job to call to LLM 
    jobSystem.registerCustomJob(CustomJob::CreateCustomJob, "LLM"); //register custom job
    jobSystem.createCustomJob("LLM"); //create custom job
    //give customJob prompt and IP address 
    jobSystem.getLLMJob()->SetPrompt(promptToPassIn); //returns LLM job type for manipulation 
    jobSystem.getLLMJob()->SetIP("Dummy-there-is-no-ip"); //sets the IP value for the LLM job type. In this case localHost 4891 port #. 
    
    jobSystem.initialize(); //initialize job system -- creates threads in isolated function to avoid creating too many threads & running out of resources

    //jobSystem.queueSpecJob("compilejob"); //queue interpreter job
    //jobSystem.queueSpecJob("parsingjob"); //queue interpreter job
    //jobSystem.queueSpecJob("outputjob"); //queue interpreter job
    // waitForJobToComplete(jobSystem, "compilejob"); 
    // waitForJobToComplete(jobSystem, "parsingjob"); 
    // waitForJobToComplete(jobSystem, "outputjob"); 
    
    jobSystem.queueSpecJob("LLM"); //queue interpreter job

    jobSystem.destroyJobSystem();


    return 0; 

    //TODOS I COULD NOT GET TO BUT THAT SHOULD BE DONE IN THE FUTURE 
    //1. use the job system after you stop it.... the jobsystem can be used but you get seg faults and have to hard exit with exit(0); command 
    //2. be able to query the status of jobs that were reordered for dependencies with dependency function. As I currently have it, the dependency function makes new ID's for each job in the order they need to be in, and these dependencies are not updated in the job system, so the status of the jobs will not be able to be found if a dependency is ran... This could be it.. or it could just be threads running too quickly wiht concurrency etc. The jobstatus queries that were not being found were being queried after the job system was stopped with stopjobsystem function, so this whole comment could be an overreaction, but I should still investigate this to make sure... 

}
//TODO - deprecated function, remove later? 
void waitForJobToComplete(MyJobSystemAPI& jobSystem, const std::string& jobType){
    //wait for compilejob to finish
    int jobStatus = jobSystem.getJobStatus(jobType); 
    int completed = 3; 

    //busy while loop for compilejob 
    while(jobStatus != completed){
        if(jobStatus == -1){
            std::cout << "invalid job, I cannot wait on a non-existant job. Exiting while-loop" << std::endl; 
            break; 
        }
        std::cout << "waiting for" << jobType << " to complete" << std::endl; 
        jobStatus = jobSystem.getJobStatus(jobType); 
    }

    std::cout << jobType + " finished!" << std::endl;

}

