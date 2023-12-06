#include "interpreter.h"
#include <iostream>
#include <string> 
#include <array> 
#include <sstream> //for stringstream to split output into words by spaces 
#include "fstream" //for writing to file
#include "./lib/json.hpp"  //for json file writing

#include "./lib/job.h"
#include "./lib/jobsystem.h"

//for job manipulation in interpreter class 
#include "JobSystemAPI.h"  //for kicking off jobs with the parsed flowscript....
#include "customjob.h"

using json = nlohmann::json; //for json manipulation 

#include "antlr4-runtime/antlr4-runtime.h"
#include "antlr/grammar-files/FlowscriptGrammarLexer.h"
#include "antlr/grammar-files/FlowscriptGrammarParser.h"

void Interpreter::Execute(){
   std::cout << "INTERPRETING" << std::endl; 
    //TODO - ADD INTERPRETER FUNCTIONALITY IN ALL API SECTIONS, RIGHT NOW CAN JUST CREATE INTERPRETER JOB 
    // jobSystemObj->registerCustomJob(CustomJob::CreateCustomJob, "customjob"); //register custom job
    // jobSystemObj->createCustomJob("customjob"); //create custom job

    //  Job* job = jobsForAPIMap["customjob"];

    //TODO - PARSE WITH ANTLR AND EXECUTE CUSTOMJOBS THAT ARE PRE-REG IN MAIN HERE!!! 


 
    //execute customJobs 
    jobsForAPIMap["customjob"]->Execute(); 

    //TODO - PASS VECTOR INTO CUSTOMJOB AND WAIT FOR CUSTOMJOB TO FINISH. PASS VECTOR WHEN YOU CREATE CUSTOMJOB IN MAIN.... THEN ALSO PASS THAT SAME VECTOR INTO INTERPRETER.... 
    //TODO - busy wait for customjob to finish, then execute the rest of the jobs... eventually move to a condvar wait like in JobSystemAPI.cpp queueSpecJob function... 
  

    //getter for setting the vector to the parsed job identifiers from the customjob
    //TODO - remove customjob getter and setter.... 

    
    //jobs = {"compilejob", "parsingjob", "outputjob"}; 
    //TODO - return customjob parsing in a stream and then use that stream to call the three native jobsystem jobs below... 
    //TODO - want to return line by line because doing approach one... 
  
    //read in strings from joblables.txt 
    std::ifstream file("./Data/jobprocessflow.txt"); //open file
    std::string jobType; 
    while(std::getline(file, jobType)){ //get each line from file

        //std::cout << "EXECUTING JOB: " << jobType << std::endl;
        //TODO - temporary conditional ignore for bad strings. remove once reading by edge_definition not node_definition 
        std::cout << "EXECUTING JOB: " << jobType << std::endl;
            if(jobType == "controlstatement"){
                CondFlow(); //execute conditional flow
                break; 
            }
            else if(jobType == "loopstatement"){
                Loop(); //execute loop logic 
                jobsForAPIMap["outputjob"]->Execute(); //execute output job
                break; //break out of while loop -- done!
                //TODO - replace break with something that actually really exits the entire else statement... 
            }
            //TODO - add a check here with a hardcoded set or the same problem? redundant??? Already did this with jobQueue? 
            //else if(){
                jobsForAPIMap[jobType]->Execute(); //execute job

            //}
        
            
        }

        //jobsForAPIMap[jobType]->Execute(); //execute job

    
    file.close(); //close file
    //delete joblabels.txt file
    //std::remove("./Data/joblabels.txt"); //delete file

    //overloading execute function from job.h base class, so execute can call these, based on string? too confusing... 
    //execute needs to take flowscript parsed data passed in and call the jobs based on that data.

    //either pass a string to execute and have execute call the correct job based on the string, or have execute take in a vector of jobs and call them all.
    //OR give customjob the ability to call those functions here? 

    //jobsForAPIMap["customjob"]->ExecuteCompileJob(); //execute compile job

    //would like to do this but cannot because job.h has no ExecuteCompileJob, so I could change job.h and add the job funcitonality, but thats bad encapsulation.... 

    //he does not care about how I run the customjob or what I put in it, so I should mess with its innerworkings... 

    //TODO - make jobSystemAPI a friend class to interpter.cpp so that interpeter  an access jobSystemAPI's data members in a cleaner way? Would not have to pass in jobsForAPI map
     

    //TODO - WHY AM I USING CUSTOMJOB HERE? BECAUSE RUNTIME CAN GET AROUND JOBSYSTEM ERRORING OUT WHEN STARTED TWICE? HOW DO I RUN OTHER THREADS OFF THIS CHILD THREAD????? 
    //TODO - //jobSystemObj->addJobs(); //add jobs to job system
    // jsForAPI -> QueueJob(job); //queue custom job
    

    //TODO - decouple the create threads function and add jobs to the job system function. 
    //jobSystemObj->startJobSystem(); //start job system, will create threads and run jobs in background
    //MyJobSystemAPI jobSystem;

    //if we parsed compileJob
    // jobSystem.registerCustomJob(CustomJob::CreateCustomJob, "customjob"); //same functionality as compilejob, runs in background to demonstrate custom jobs at runtime. Can replace compilejob as the only call needed for this type of job. 
    // jobSystem.createCustomJob("customjob"); 

    

    //TODO - get jobsystem from main.cpp into interpreter.cpp 
    //TODO - job systems are linked, so you are working with one class object that manages a single job system. The job system is created in the JobSystemAPI.cpp
    //TODO - THE OBJECT IN MAIN IS WHAT ALLOWS YOU TO CREATE CUSTOM JOBS, PASS THAT OBJECT HERE!!!!! & CREATE CUSTOM JOBS BASED ON THE ANTLR PARSING!!! 
   std::cout << "Interpreter [ID: " << this->GetUniqueID() << "] has been executed." << std::endl;
   JobCompletedCallback(); 
}

void Interpreter::JobCompletedCallback(){
    std::cout << "interpreter Job done" << std::endl;
    //notify completion 
    signalCompletion(); //TODO - encapsulated version of thread control with condvar
    
}

void Interpreter::CondFlow(){
    if(fsCond1 > fsCond2){
        std::cout << "fsCond1 > fsCond2" << std::endl;
        jobsForAPIMap["countingjob"]->Execute(); //execute compile job
    } else{
        std::cout << "fsCond1 < fsCond2" << std::endl;
        jobsForAPIMap["parsingjob"]->Execute(); //execute parsing job
        jobsForAPIMap["outputjob"]->Execute(); //execute output job
    }
}

void Interpreter::Loop(){
    //change loopHit to 1 to confirm we are in the loop  
    std::ofstream loopHitFile("./Data/loopHit.txt"); //open file
    if(!loopHitFile){
        std::cout << "ERROR: FILE NOT FOUND" << std::endl;
    }
    loopHitFile << "1" << std::endl; //write 1 to file
    loopHitFile.close(); //close file
    //grab boolean value from file 
    std::ifstream file("./Data/loopbool.txt"); //open file
    if(!file){
        std::cout << "ERROR: FILE NOT FOUND" << std::endl;
    }
    std::string boolData;
    std::getline(file, boolData); //get each line from file
    file.close(); //close file
    loopCond = std::stoi(boolData); //convert string to int
    if(loopCond == 0){//false, so run parsingjob again 
        //TODO - The parsingJob called above this loopCond should not increment the parsingJobCounter file... parsingJobCounter file should only be incremented in this loop... 
        jobsForAPIMap["parsingjob"]->Execute(); //execute output job
        Loop(); //call loop again - recursion 
    }

    //erase parsingJobLoopCounter.txt file and write 0 to it
    std::ofstream file2("./Data/parsingJobLoopCounter.txt"); //open file to write to
    file2 << "0" << std::endl; //write 0 to file
    file2.close(); //close file

    //erase loopbool.txt file and write 0 to it 
    std::ofstream file3("./Data/loopbool.txt"); //open file to write to
    file3 << "0" << std::endl; //write 0 to file
    file3.close(); //close file

    // //write 0 to loopHit.txt file to confirm we are out of the loop
    // std::ofstream loopHitFile2("./Data/loopHit.txt"); //open file
    // if(!loopHitFile2){
    //     std::cout << "ERROR: FILE NOT FOUND" << std::endl;
    // }
    // loopHitFile2 << "0" << std::endl; //write 0 to file
    // loopHitFile2.close(); //close file

    //TODO - is outputjob execution needed here?... 
    // //boolean evaluated to false so run outputjob
    // jobsForAPIMap["outputjob"]->Execute(); //execute output job

}






//code automatically compiling means you can: 
//set code off and do other things 
//automated regression testing -> compile code and automatically run tests on code. 
//when errors output it tells you error number and error messages -> put error messages into LLM's to fix errors
//take code file and web info from LLM and say "fix it for me"
//AI TOOL TO FIX CODE FOR YOU -> BETTER STANDARDIZATION = BETTER FIXES 
//Can write as terminal job instead of compile job (written as compile job here)
