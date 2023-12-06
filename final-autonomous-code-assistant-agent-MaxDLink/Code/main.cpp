#include <iostream> 
#include "JobSystemAPI.h" 
#include "customjob.h"

#include <fstream> //for reading in files
#include "./lib/json.hpp" //for json manipulation
#include <sstream> //for reading the output.json file in main to check if it contains "No errors found!"
using json = nlohmann::json;

//helper functions 

std::string readFileContents(const std::string& filePath) {
    //call processFile function to read file contents
    std::string file_content;
    std::ifstream file(filePath);
    if (file.is_open()) {
        file_content.assign((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
    return file_content;
}

std::string processFile(const std::string& filePath) {
    std::string file_content = readFileContents(filePath);

    if (filePath.size() >= 5 && filePath.substr(filePath.size() - 5) == ".json") {
        // Parse the JSON data
        json json_data = json::parse(file_content);
        // Serialize JSON object to string
        return json_data.dump(4); // '4' for pretty printing
    } else if (filePath.size() >= 4 && (filePath.substr(filePath.size() - 4) == ".txt" || filePath.substr(filePath.size() - 4) == ".cpp" || filePath.substr(filePath.size() - 2) == ".h")) {
        // For .txt, .cpp, and .h files, just read and return the file content
        return file_content;
    } else {
        std::cerr << "Unsupported file type for file: " << filePath << std::endl;
        return "";
    }
}


std::string escapeShellArgument(const std::string& arg) {
    std::string escaped;
    for (char c : arg) {
        // Add a backslash before special characters
        if (c == '"' || c == '\\' || c == '$') {
            escaped += '\\';
        }
        escaped += c;
    }
    return escaped;
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

void flowScriptInterpreter(MyJobSystemAPI& jobSystem, const std::string& jobType){//interpreting flowscript with this function 

    jobSystem.createJob("compilejob"); //create compile job
    jobSystem.createJob("parsingjob"); //create parsing job
    jobSystem.createJob("outputjob"); //create output job

    //TODO - pass jobs vector into here by ref 
    //interpret flowscript files
    jobSystem.createJob("interpreterjob"); //create interpreter job

    //jobSystem.initialize(); //initialize job system -- creates threads in isolated function to avoid creating too many threads & running out of resources
    jobSystem.queueSpecJob("interpreterjob"); //queue interpreter job
}


void LLMCall(MyJobSystemAPI& jobSystem, const std::string& jobType, std::string& promptToPassIn){ //instantiate LLM job thread 


    //make custom job to call to LLM 
    jobSystem.registerCustomJob(CustomJob::CreateCustomJob, "LLM"); //register custom job
    jobSystem.createCustomJob("LLM"); //create custom job
    //give customJob prompt and IP address 
    jobSystem.getLLMJob()->SetPrompt(promptToPassIn); //returns LLM job type for manipulation 
    jobSystem.getLLMJob()->SetIP("Dummy-there-is-no-ip"); //sets the IP value for the LLM job type. In this case localHost 4891 port #. 
    
    jobSystem.queueSpecJob("LLM"); //queue interpreter job

    //TODO - is this going to malfunction? Does this wait work? --- says cannot wait on invalid job because job finishes before getting to this wait function, so is this wait function irrelevant? 
    //waitForJobToComplete(jobSystem, "LLM"); //wait for LLM job to finish
}

void reloadErrors(){//this function repopulates the ./test-code directory with the backup error files from the ./test-code=backups directory
    // Array of file names that need to be reset
    std::array<std::string, 3> file_names = {"test-set-one.cpp", "test-set-three.cpp", "test-set-two.cpp"};

    // Iterate through the file names and copy each from the backup directory to the test-code directory
    for (const std::string& file_name : file_names) {
        std::string command = "cp ./test-code-backups/" + file_name + " ./test-code/" + file_name;
        // Execute the copy command
        int result = system(command.c_str());
        // Check if the command was successful
        if (result != 0) {
            std::cerr << "Failed to copy " << file_name << std::endl;
        } else {
            std::cout << "Successfully reset errors for " << file_name << std::endl;
        }
    }

}

int main(void){
    //TODO - change from an int to a forever loop 
    int i = 0;
    while(i != 10){//while loop that breaks when the output.json file reads "No errors or warnings - compiled successfully"
        //call API class functions for testing 
        MyJobSystemAPI jobSystem; //create job system object

        jobSystem.initialize(); //initialize job system -- creates threads in isolated function to avoid creating too many threads & running out of resources 

        //JSON file path for flowScript prompt 
        std::string flowScriptPromptFilePath = "./Data/fsp1.txt";
        std::string flowScript = processFile(flowScriptPromptFilePath); //read the json file and store the output in a string called code
        flowScript = escapeShellArgument(flowScript); //escape the code string to be used in the command string below

        std::string writeFlowScriptPrompt = "Please write flowscript code based on the context. Context: Here is flowscript for you to base your flowscript off of. The flowScript must connect jobs in order where 'compilejob' is the first job, 'parsingjob' is the second job, and 'outputjob' is the third job. Only those three jobs should be created. Question: Please write flowscript that mimics this flowscript: " + flowScript; 

        //TODO - pass a generic prompt to this thread from main so that you can run this function multiple times and create multiple LLM jobs in the running of main. One job should write the flowscript with zero/fewshot training, then the second call should fix the errors with a while loop... 
        LLMCall(jobSystem, "LLM", writeFlowScriptPrompt); //instantiate LLM job thread to write flowScript 
        //interpret flowscript that LLMCall writes on line 121 of main.cpp  
        flowScriptInterpreter(jobSystem, "interpreterjob"); //interpreting flowscript with this function

        // JSON file path for output.json file from lab one that contains coding errors 
        std::string json_file_path = "./Data/output.json";

        std::string code = processFile(json_file_path); //read the json file and store the output in a string called code
        code = escapeShellArgument(code); //escape the code string to be used in the command string below

        //read source code files from ./test-code directory 
        std::string sourceCodeMain = "./test-code/main.cpp";
        std::string sourceCodeTestOneCpp = "./test-code/test-set-one.cpp";
        std::string sourceCodeTestTwoCpp = "./test-code/test-set-two.cpp";
        std::string sourceCodeTestThreeCpp = "./test-code/test-set-three.cpp";

        //read in the .h files 
        std::string headerFileTestSetOne = "./test-code/test-set-one.h";
        std::string headerFileTestSetTwo = "./test-code/test-set-two.h";
        std::string headerFileTestSetThree = "./test-code/test-set-three.h";
        //TODO - figure out why test-code-one.cpp does not include the headers when it is fed to the LLM from the combinedSourceCode string below. Something with how it is read into the combinedSourceCode from the processFile? 
        std::string combinedSourceCode = processFile(sourceCodeMain) + processFile(sourceCodeTestOneCpp) + processFile(headerFileTestSetOne) + processFile(sourceCodeTestTwoCpp) + processFile(headerFileTestSetTwo) + processFile(sourceCodeTestThreeCpp) + processFile(headerFileTestSetThree); //read the json file and store the output in a string called code
        combinedSourceCode = escapeShellArgument(combinedSourceCode); //escape the code string to be used in the command string below

        std::cout << "\n\n\n\ncombinedSourceCode: \n\n\n\n\n\n" << combinedSourceCode << std::endl;
        //std::string errorsWithSourceCode = code + "\n\n\n\nThose were the errors, now here is the source code: \n\n\n\n" + combinedSourceCode; 
        std::string errorsWithSourceCode = code + combinedSourceCode; 

        std::cout << "\n\n\n\nerrorsWithSourceCode: \n\n\n\n\n\n" << errorsWithSourceCode << std::endl;
        //load a json prompt format from a json file for the LLM to use to format the output.json file
        //TODO - make sure the fixErrorsPrompt makes the LLM include the .h header files in their associated .cpp test-set files that are fixed. I.E. test-set-one.cpp, test-set-two.cpp, test-set-three.cpp
        std::string fixErrorsPrompt = "Answer question based on the context. Context: Here is code with errors in a json file format. This json file format does not include all the errors so please refer to the full source files that are at the end of this provided prompt. Fix the errors in each of these .cpp files and format your output on the full source code files at the end of this input. In your response, output the entire .cpp files with all errors fixed. These fixed .cpp files should be returned as neatly formatted strings that can be written to .cpp files to be ran later. Add a description of what you did to fix the errors. Please output your fixes in a SINGLE json file like this format with a [ { 'File Path: ' field, followed by a 'Fixed .cpp: ' field, and finally ending with a 'Description: ' field } ]. Please make sure that every 'Fixed .cpp:' field starts with an #include <iostream> header'. Make sure to include any .h files that are associated with the .cpp files in your 'Fixed .cpp: ' output field. Before you output the json file be sure to say 'Here are the fixed .cpp files:' Question: " + errorsWithSourceCode;
        LLMCall(jobSystem, "LLM", fixErrorsPrompt); //instantiate LLM job thread to fix errors in C++ code 


        jobSystem.destroyJobSystem();

        //read in output.json file and check if it says "No errors found!"
        // Open the file
        std::ifstream file("./Data/output.json");
        if (!file.is_open()) {
            std::cerr << "Could not open the file 'output.json'" << std::endl;
            return 1;
        }

        // Read the file into a string
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string fileContent = buffer.str();
        // Close the file
        file.close();
        // Check if the file contains "No errors found!"
        if (fileContent.find("No errors or warnings - compiled successfully") != std::string::npos) {
            std::cout << "No errors found!" << std::endl;
            break; //exit the while loop if no errors are found
        } else {

            //continue the while loop if errors are found
            std::cout << "Errors were found or the specific message is not present." << std::endl;
        }
        i++; //increment i to exit the while loop after 10 iterations so that github actions doesn't run forever

    } 
    //This function can be uncommented to easily reload the errors in the ./test-code directory from the files in the ./test-code-backup directory. 
    //The ./fixed-test-code directory also exists if you would like to test fixed code with no errors by pasting that code into the ./test-code directory. 
    //reloadErrors(); //this function repopulates the ./test-code directory with the backup error files from the ./test-code=backups directory


    //check if fixed code runs -- //TODO - this is currently broken, fix it later 

    // std::string cdToFixedCode = "cd test-code"; //cd ./final-autonomous-code-assistant-agent-MaxDLink/test-code


    // std::string compileFixedCode = "clang++ main.cpp test-set-one.cpp test-set-two.cpp test-set-three.cpp -o fixedCode";

    // std::string runFixed = "./fixedCode"; 

    // std::cout << "\n\n\n\nRUNNING THE FIXED CODE TO DOUBLE CHECK THAT IT WORKS!\n\n\n\n";
    // system(cdToFixedCode.c_str()); //cd to the test-code directory to get ready to run fixed code 
    // system(compileFixedCode.c_str()); //compile fixed code
    // system(runFixed.c_str()); //run the fixed code to verify it works!

    return 0; 

}

