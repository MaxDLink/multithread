#include <iostream> 
#include "JobSystemAPI.h" 
#include "customjob.h"

int main(void){
    //call API class functions for testing 
    MyJobSystemAPI jobSystem;

    jobSystem.getJobType(); 

    jobSystem.createJob("parsingjob"); //creating parsingjob first so we can use dependency function to reorder 
    jobSystem.createJob("compilejob");  
    jobSystem.dependency("compilejob", "parsingjob"); //parsingjob depends on compilejob, so compilejob will run first
    jobSystem.registerCustomJob(CustomJob::CreateCustomJob, "customjob"); //same functionality as compilejob, runs in background to demonstrate custom jobs at runtime. Can replace compilejob as the only call needed for this type of job. 
    jobSystem.createCustomJob("customjob"); 
    jobSystem.createJob("outputjob"); 

    jobSystem.startJobSystem(); //start job system, will create threads and run jobs in background

    jobSystem.getJobStatus("compilejob");
    jobSystem.getJobStatus("parsingjob");
    jobSystem.getJobStatus("outputjob");
    jobSystem.getJobStatus("customjob");

    jobSystem.completeJob("compilejob");
    jobSystem.completeJob("parsingjob");
    jobSystem.completeJob("outputjob");
    jobSystem.completeJob("customjob");

    jobSystem.destroyJob("compilejob");
    jobSystem.destroyJob("parsingjob");
    jobSystem.destroyJob("outputjob");
    jobSystem.destroyJob("customjob");

    //jobSystem.stopJobSystem(); //JS can still be used after stopping, just cleaning threads.... 
    //jobSystem.getJobType(); //demonstrate use of job system object after stopping it.... 
   

    jobSystem.destroyJobSystem();


    return 0; 

    //TODOS I COULD NOT GET TO BUT THAT SHOULD BE DONE IN THE FUTURE 
    //1. use the job system after you stop it.... the jobsystem can be used but you get seg faults and have to hard exit with exit(0); command 
    //2. be able to query the status of jobs that were reordered for dependencies with dependency function. As I currently have it, the dependency function makes new ID's for each job in the order they need to be in, and these dependencies are not updated in the job system, so the status of the jobs will not be able to be found if a dependency is ran... This could be it.. or it could just be threads running too quickly wiht concurrency etc. The jobstatus queries that were not being found were being queried after the job system was stopped with stopjobsystem function, so this whole comment could be an overreaction, but I should still investigate this to make sure... 

}

