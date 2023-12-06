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

#include "customvisitor.h" //for visiting the node_definitions in the tree

#include "customerrorlistener.h" //for flowscript error logging 

void Interpreter::ExecuteParse(){//TODO - this function should be in a separate thread and not interpreter? in lab 3 it was in customjob.cpp as "Execute" function... 

    std::cout << "EXECUTING PARSING FROM CUSTOMJOB" << std::endl;

    CustomErrorListener errorListener; //create error listener object

    // Path to flowscript input file taken in 
    std::ifstream stream("./Data/LLM-Flowscript-Response.txt"); // Adjust the path to the location of your .txt file
    if (!stream) {
        std::cerr << "Cannot open file: ../Data/LLM-Flowscript-Response.txt" << std::endl;
        return; // Handle the error as you see fit
    }
    antlr4::ANTLRInputStream input(stream);

    // Create a lexer that feeds off of the input stream
    FlowscriptGrammarLexer lexer(&input);

    // Create a buffer of tokens pulled from the lexer
    antlr4::CommonTokenStream tokens(&lexer);

    // Create a parser that feeds off the tokens buffer
    FlowscriptGrammarParser parser(&tokens);

    //attach the customerror listener to the parser 
    parser.removeErrorListeners(); //remove default error listener
    parser.addErrorListener(&errorListener); //add custom error listener

    //attach the custom listener to the lexer 
    lexer.removeErrorListeners(); //remove default error listener
    lexer.addErrorListener(&errorListener); //add custom error listener

    // Begin parsing at the root rule (replace 'script' with your actual root rule name)
    antlr4::tree::ParseTree *tree = parser.flowscript();

    //parsing now complete, so write errors to json file if there are any errors 
    //errorListener.writeErrorsToFile("./Data/flowscript-errors.json");


    // Now you can use the tree however you need to
    //std::cout << tree->toStringTree(&parser) << std::endl; //TODO - use this tree to run the jobs in interpreter situationally based on what is in the tree..... 

    std::cout << "visiting tree!" << std::endl; 

    //TODO - use visitor design pattern to visit tree 

    //TODO - JobQUEUE is holding info, but jobLabels is not... why?
   CustomVisitor visitor; //create visitor object
   visitor.visit(tree); //visit tree. Will call visitNode_definition function in customvisitor.cpp and push back the strings "Job A", "Job B", and "Job C" to the jobQueue vector in customvisitor.cpp

// Aggregate errors from errorListener and visitor
json combinedErrors = json::array(); // Initialize as an empty JSON array

for (const auto& error : errorListener.getErrors()) {
       combinedErrors.push_back(error);
      
}

//TODO - commented out because customerrorlistener class gets both errors. Left in for future reference & feature implementation
// for (const auto& error : visitor.getSemanticErrors()) {
//        combinedErrors.push_back(error);
// }

// Write to file
std::ofstream errorFile("./Data/flowscript-error-output.json");
if (errorFile.is_open()) {
    errorFile << combinedErrors.dump(4);
    errorFile.close();
} else {
    std::cerr << "Unable to open error log file." << std::endl;
}

   //TODO - jobLabels holds "outputjob", "compilejob", "parsingjob", "outputjob"... this out of order is from grabbing only 4 of the 6 strings from the customvisitor jobqueue because customjob is a thread that finishes before the customvisitor class is done running... make a control structure for customjob to wait for costumvisitor to finish and make sure that jobQueue only holds three string values, not 6
   jobLabels = visitor.getJobLabels(); // Get the job labels

    //iterate through jobLabels to check if they are correct
    // for(const auto& label : jobLabels){
    //     std::cout << "\n\nCUSTOMJOB JOB LABELS: \n\n" << label << std::endl;
    // }
    // Print the job labels (optional)
    //write lablel to a file 
    std::ofstream file("./Data/jobprocessflow.txt"); //open file to write to
    for (const std::string& label : jobLabels) {
        file << label << std::endl;
        //TODO - printing labels for testing only... 
        //std::cout << label << std::endl; //jobs original naming convention in the fsp1.txt file was "Job A", "Job B", "Job C", but they were changed to "compilejob", "parsingjob", and "outputjob" respectfully for testing purposes. 
    } //TODO - get labels vector into intepreter and run jobs based on those strings. Here the strings are "Job A", "Job B", "Job C" but for testing purposes I should change these strings in the fsp1.txt file to be "compilejob", "parsejob", "outputjob" to ensure I can run the jobs in the jobsystem. Then I can adopt the jobsystem's string identifiers it uses to run the native jobs to match the flowscript name conventions later. ASK HIM ABOUT THIS NAMING CONVENTION FOR STRING IDENTIFIERS.  
    file.close(); //close file
    std::cout << "CustomJob [ID: " << this->GetUniqueID() << "] has been executed." << std::endl;
    //call jobcompletedCallback 

    //JobCompletedCallback(); 

}
void Interpreter::Execute(){
   std::cout << "INTERPRETING" << std::endl; 
    //TODO - ADD INTERPRETER FUNCTIONALITY IN ALL API SECTIONS, RIGHT NOW CAN JUST CREATE INTERPRETER JOB 
    // jobSystemObj->registerCustomJob(CustomJob::CreateCustomJob, "customjob"); //register custom job
    // jobSystemObj->createCustomJob("customjob"); //create custom job

    //  Job* job = jobsForAPIMap["customjob"];

    //TODO - PARSE WITH ANTLR AND EXECUTE CUSTOMJOBS THAT ARE PRE-REG IN MAIN HERE!!! 


 
    //execute customJobs 
    //jobsForAPIMap["customjob"]->Execute(); 
    //TODO - this should be done by customjob.cpp or no? Right now it is handled by the above function "ExecuteParse" in interpreter.cpp. in lab 3 it was handled by customjob.cpp execute function. bad practice to have one thread do multiple things... 
    //jobsForAPIMap["customjob"] -> ExecuteParse(); //parse flowscript files like in lab 3 
    ExecuteParse(); //parse flowscript files like in lab 3
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
