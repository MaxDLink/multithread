#include "compilejob.h"
#include <iostream>
#include <string> 
#include <array> 
#include "job.h"
#include <sstream> //for stringstream to split output into words by spaces 
#include "fstream" //for writing to file
#include "json.hpp"  //for json file writing

#include <regex> 

using json = nlohmann::json; //for json manipulation 

void CompileJob::Execute(){

    //ReadInErrors 
    ReadInErrors(); //read in errors from makefile

    //getCodeSnippets 
    getCodeSnippets(); //get code snippets from output

    //TODO - get execute to return something at the end? Getter? 
    JobCompletedCallback(); 
}

void CompileJob::JobCompletedCallback(){
    std::cout << "CompileJob done" << std::endl;
    //notify completion 
    signalCompletion(); //TODO - this causes seg fault because of new way compilejob is done... fix this.... or wait in main with a busy while etc. 
  
    
}

void CompileJob::ReadInErrors(){
    std::array<char, 128> buffer;
    // set command to the directory of the code automatically by using string folder
    //std::string command = "clang++ -g -std=c++14 ./Code/" + folder + "/*.cpp -o auto_out";
    std::string makefile = "./test-code/*"; 
    std::string command = "make -f " + makefile + " automated"; //path to makefile and command to run makefile based on file path 

    //std::string command = "clang++ -g -std=c++14 ./Code/" + folder + "/*.cpp -o auto_out";
    // Redirect cerr to cout
    command.append(" 2>&1");
    // open pipe and run command
    FILE *pipe = popen(command.c_str(), "r");

    if (!pipe)
    {
        std::cout << "popen failed: failed to open pipe" << std::endl;
        return;
    }

    // read till end of process
    while (fgets(buffer.data(), 128, pipe) != NULL)
    {
        this->output.append((buffer.data()));
    }

    // close pipe and get return code
    this->returnCode = pclose(pipe);
    std::cout << "Job " << this->GetUniqueID() << " Has Been Executed" << std::endl;
}

 /*void CompileJob::getCodeSnippets(){

     // Return error output to the main thread and stores the output in error.json if the returnCode is not 0
    if (this->returnCode == 0)
    {
        // shows the file does not have compile errors to the main user interface
        std::cout << "Compile Job " << this->GetUniqueID() << " Return Code: " << this->returnCode << std::endl;
        std::cout << "No Errors detected while compiling " << " folder" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Compile Job " << this->GetUniqueID() << " Return Code: " << this->returnCode << std::endl;
        std::cout << "Errors detected while compiling " << " folder and errors has been parsed to errors-with-source-code-lines.json" << std::endl;
        std::cout << std::endl;
        // JSON object to store error messages
        json parsejob;

        // Split the input into lines
        std::istringstream input_stream(output);
        std::string line;

        // declare string variables that are going to be reused for each error object
        std::string current_file;
        std::string rowNum;
        std::string colNum;
        std::string issueType;

        while (std::getline(input_stream, line))
        {
            // Check if the line contains a file path
            if (line[0] == '.' && line.find("./") != std::string::npos)
            {
                // Extract the file path
                current_file = line.substr(0, line.find(":"));
                // check if the issue is an error or a warning
                if (line.find(" error: ") != std::string::npos)
                {
                    issueType = "Error";
                }
                else if (line.find(" warning: ") != std::string::npos)
                {
                    issueType = "Warning";
                }
                // go through the line to find rowNum and colNum, and make line to be the error message
                line = line.substr(line.find(":") + 1, line.length());
                rowNum = line.substr(0, line.find(":"));
                line = line.substr(rowNum.size() + 1, line.length());
                colNum = line.substr(0, line.find(":"));
                line = line.substr(line.find(":") + 1, line.length());
                line = line.substr(line.find(":") + 2, line.length());
                // read the error file and copy the file into a 2D vector
                std::ifstream readFile(current_file);
                std::vector<std::vector<std::string>> table;
                std::string aLine;
                while (std::getline(readFile, aLine))
                {
                    std::vector<std::string> row;
                    row.push_back(aLine);
                    table.push_back(row);
                }
                readFile.close();
                json error_info; // create a json object for each error's information
                error_info["File"].push_back(current_file);
                error_info["Row"].push_back(rowNum);
                error_info["Column"].push_back(colNum);
                error_info[issueType].push_back(line); // push the error message
                int rowNumInt = std::stoi(rowNum);
                // get 2 lines above and below the error line if possible
                if (rowNumInt == 1)
                {
                    error_info["Code Snippet"].push_back(table[rowNumInt - 1]);
                    error_info["Code Snippet"].push_back(table[rowNumInt]);
                    error_info["Code Snippet"].push_back(table[rowNumInt + 1]);
                }
                else if (rowNumInt == 2)
                {
                    error_info["Code Snippet"].push_back(table[rowNumInt - 2]);
                    error_info["Code Snippet"].push_back(table[rowNumInt - 1]);
                    error_info["Code Snippet"].push_back(table[rowNumInt]);
                    error_info["Code Snippet"].push_back(table[rowNumInt + 1]);
                }
                else if (rowNumInt == table.size())
                {
                    error_info["Code Snippet"].push_back(table[rowNumInt - 3]);
                    error_info["Code Snippet"].push_back(table[rowNumInt - 2]);
                    error_info["Code Snippet"].push_back(table[rowNumInt - 1]);
                }
                else if (rowNumInt == table.size() - 1)
                {
                    error_info["Code Snippet"].push_back(table[rowNumInt - 3]);
                    error_info["Code Snippet"].push_back(table[rowNumInt - 2]);
                    error_info["Code Snippet"].push_back(table[rowNumInt - 1]);
                    error_info["Code Snippet"].push_back(table[rowNumInt]);
                }
                else
                {
                    error_info["Code Snippet"].push_back(table[rowNumInt - 3]);
                    error_info["Code Snippet"].push_back(table[rowNumInt - 2]);
                    error_info["Code Snippet"].push_back(table[rowNumInt - 1]);
                    error_info["Code Snippet"].push_back(table[rowNumInt]);
                    error_info["Code Snippet"].push_back(table[rowNumInt + 1]);
                }
                // push the error_info json to the current_file json
                parsejob[current_file].push_back(error_info);
            }
        }
        // Write the JSON object to a file
        std::ofstream o("./Data/errors-with-source-code-lines.json");
        o << std::setw(4) << parsejob << std::endl;
    } 
    
}
*/ 

//TODO - advanced get code snippets 
/*
void CompileJob::getCodeSnippets() {
    std::map<std::string, std::vector<std::string>> fileContents;
    std::istringstream input_stream(this->output);
    std::string line;
    json parsejob;

    while (std::getline(input_stream, line)) {
        std::cout << "Processing line: " << line << std::endl; 
        // Parse the line for file path and error information
        std::regex errorRegex(R"(./test-code/(.*?):(\d+):(\d+): (.*?): (.*))");
        std::smatch matches;
        if (std::regex_search(line, matches, errorRegex) && matches.size() == 6) {
            std::string filePath = "./test-code/" + matches[1].str();
            int lineNumber = std::stoi(matches[2]) - 1;  // Convert to 0-based index
            std::string columnNumber = matches[3].str();
            std::string errorType = matches[4].str();
            std::string errorDescription = matches[5].str();

            // Load file content if not already loaded
            if (fileContents.find(filePath) == fileContents.end()) {
                std::ifstream inFile(filePath);
                std::vector<std::string> lines;
                std::string fileLine;
                while (std::getline(inFile, fileLine)) {
                    lines.push_back(fileLine);
                }
                fileContents[filePath] = lines;
            }

            // Extract source code snippet
            std::vector<std::string> codeSnippet;
            int startLine = std::max(0, lineNumber - 2);
            int endLine = std::min(lineNumber + 2, static_cast<int>(fileContents[filePath].size()) - 1);
            for (int i = startLine; i <= endLine; ++i) {
                codeSnippet.push_back(fileContents[filePath][i]);
            }

            // Create JSON object for the error
            json error_info;
            error_info["File Path"] = filePath;
            error_info["Line Number"] = std::to_string(lineNumber + 1);  // Convert back to 1-based index for JSON
            error_info["Column Number"] = columnNumber;
            error_info["Error Type"] = errorType;
            error_info["Error Description"] = errorDescription;
            error_info["Source Code"] = codeSnippet;

            // Add error info to the JSON array
            parsejob.push_back(error_info);
        }
    }

    // Write to the JSON file
    std::ofstream o("./Data/errors-with-source-code-lines.json");
    o << std::setw(4) << parsejob << std::endl;
}
*/ 

void CompileJob::getCodeSnippets() {
    std::vector<std::string> sourceFiles = {"./test-code/test-set-one.cpp", 
                                            "./test-code/test-set-two.cpp", 
                                            "./test-code/test-set-three.cpp"};
    json parsejob;

    for (const auto& filePath : sourceFiles) {
        std::ifstream inFile(filePath);
        if (!inFile) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            continue;
        }

        std::vector<std::string> lines;
        std::string fileLine;
        while (std::getline(inFile, fileLine)) {
            lines.push_back(fileLine);
        }

        // Mock error details - you will need to replace this with actual error information
        int lineNumber = 6;  // Example line number
        std::string columnNumber = "4";  // Example column number
        std::string errorType = "error";
        std::string errorDescription = "Example error description";

        // Extract source code snippet
        std::vector<std::string> codeSnippet;
        int startLine = std::max(0, lineNumber - 2);
        int endLine = std::min(lineNumber + 2, static_cast<int>(lines.size()) - 1);
        for (int i = startLine; i <= endLine; ++i) {
            codeSnippet.push_back(lines[i]);
        }

        // Create JSON object for the error
        json error_info;
        error_info["File Path"] = filePath;
        error_info["Line Number"] = std::to_string(lineNumber);  // Keep as-is for testing
        error_info["Column Number"] = columnNumber;
        error_info["Error Type"] = errorType;
        error_info["Error Description"] = errorDescription;
        error_info["Source Code"] = codeSnippet;

        // Add error info to the JSON array
        parsejob.push_back(error_info);
    }

    // Write to the JSON file
    std::ofstream o("./Data/LAB1ERRORS.json");
    o << std::setw(4) << parsejob << std::endl;
}









//code automatically compiling means you can: 
//set code off and do other things 
//automated regression testing -> compile code and automatically run tests on code. 
//when errors output it tells you error number and error messages -> put error messages into LLM's to fix errors
//take code file and web info from LLM and say "fix it for me"
//AI TOOL TO FIX CODE FOR YOU -> BETTER STANDARDIZATION = BETTER FIXES 
//Can write as terminal job instead of compile job (written as compile job here)
