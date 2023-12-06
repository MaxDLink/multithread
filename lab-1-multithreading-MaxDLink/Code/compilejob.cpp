#include "compilejob.h"
#include <iostream>
#include <string> 
#include <array> 
#include "job.h"
#include <sstream> //for stringstream to split output into words by spaces 
#include <queue> //for basic thread control

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
  
    //split output and feed into stream 
    std::stringstream ss(this->output); //create stringstream from output string
    std::string transcribeOut; //string to store words from output string
    while(std::getline(ss, transcribeOut, '\n')){ //while there are words in the stringstream
        //std::cout << "TranscribeOut: " << transcribeOut << std::endl; 
        streamCjb.push(transcribeOut); //push word to stream
    }
    
    std::cout << "Job " << this->GetUniqueID() << " has been executed." << std::endl;

}

void CompileJob::JobCompletedCallback(){
    //std::cout << "Compile Job " << this->GetUniqueID() << " Return code " << this->returnCode << std::endl;
    //std::cout << "Compile Job" << this->GetUniqueID() << " Output \n" << this->output << std::endl;
    //std::cout << "Compile Job " << this->GetUniqueID() << " has been completed." << std::endl;

}






//code automatically compiling means you can: 
//set code off and do other things 
//automated regression testing -> compile code and automatically run tests on code. 
//when errors output it tells you error number and error messages -> put error messages into LLM's to fix errors
//take code file and web info from LLM and say "fix it for me"
//AI TOOL TO FIX CODE FOR YOU -> BETTER STANDARDIZATION = BETTER FIXES 
//Can write as terminal job instead of compile job (written as compile job here)
