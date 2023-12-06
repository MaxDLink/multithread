#include "compilejob.h"
#include <iostream>
#include <string> 
#include <array> 
#include "job.h"
#include <sstream> //for stringstream to split output into words by spaces 
#include "fstream" //for writing to file
#include "json.hpp"  //for json file writing
using json = nlohmann::json; //for json manipulation 

void CompileJob::Execute(){
    std::array< char, 128 > buffer; //buffer to store output
    std::string command = "make -f " + makefile + " automated"; //path to makefile and command to run makefile based on file path 
    
    //Redirect cerr to cout - easy way to see errors when working with multiple threads 
    //then can capture cout and get all errors 
    command.append(" 2>&1"); //redirects stderr to stdout
    //spin up a thread that is going to grab code, compile it, and return a result 
    //Terminal tells you there is an error in code, but with threads you cannot tell where the error is 
    //cout to terminal is not thread safe (standard commands like that are not thread safe)

    //open pipe and run command 
    FILE* pipe = popen(command.c_str(), "r"); //opens a pipe and will send something to it 
    //gives terminal to work on, but this terminal is open inside a thread 
    //turns command into a c string and sends it to the pipe
    //you can only open pipe to read in this case "r"

    if(!pipe){
        std::cout << "Pipe failed to open" << std::endl;
        return; 
    }

    //read till end of process: 
    while(fgets(buffer.data(), 128, pipe) != NULL){//reading buffer until get to end of file - same concept as finishing reading in terminal 
        this->output.append(buffer.data()); //append to output string
    }
    //close pipe and get return code 
    this->returnCode = pclose(pipe); //close pipe and get return code. Fine = 0, error = returns offset other than 0
  
    //split output and feed into stream //TODO - take out stream variable? Not needed anymore if we are writing to file
    std::stringstream ss(this->output); // Create stringstream from output string
    nlohmann::json j; // Create JSON object using nlohmann::json

    std::string transcribeOut; // String to store lines from output string
    while(std::getline(ss, transcribeOut, '\n')) { // While there are lines in the stringstream
        j["outputLines"].push_back(transcribeOut);  // Add line to JSON object under "outputLines" key
    }
    
    // Write JSON object to a file named compileJobOutput.json
    std::ofstream fileOutput("Data/compileJobOutput.json");
    fileOutput << j.dump(4);  // 4 spaces as indent
    fileOutput.close();
    
    std::cout << "CompileJob [ID: " << this->GetUniqueID() << "] has been executed." << std::endl;
    JobCompletedCallback(); 
}

void CompileJob::JobCompletedCallback(){
    std::cout << "CompileJob done" << std::endl;
    //notify completion 
    signalCompletion(); //TODO - encapsulated version of thread control with condvar
    
}






//code automatically compiling means you can: 
//set code off and do other things 
//automated regression testing -> compile code and automatically run tests on code. 
//when errors output it tells you error number and error messages -> put error messages into LLM's to fix errors
//take code file and web info from LLM and say "fix it for me"
//AI TOOL TO FIX CODE FOR YOU -> BETTER STANDARDIZATION = BETTER FIXES 
//Can write as terminal job instead of compile job (written as compile job here)
