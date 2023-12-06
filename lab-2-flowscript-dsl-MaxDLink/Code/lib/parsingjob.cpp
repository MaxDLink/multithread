#include "parsingjob.h"
#include <iostream>
#include <string> 
#include "job.h"
#include <fstream> //for writing to file 
#include <cstdio> //for removing file
#include <regex> //for parsing
#include "json.hpp" 
#include <sstream> //for linker error parsing 

using json = nlohmann::json; 

void ParsingJob::Execute(){

    std::string content; 

   nlohmann::json errorJsonArray = nlohmann::json::array(); // Initialize a JSON array to append errors to json 
   std::vector<std::string> parsedStrings; //vector to store parsed strings

    //START PARSING & WRITING TO JSON FILE
    // Print and empty the queue
    //read from compileJobOutput.json file and fill content variable with output
     //Generic file path for errors.json
    std::ifstream inputFile("Data/compileJobOutput.json");
    json compileJobOutput = json::parse(inputFile);
    inputFile.close();

    //fill content with output from compileJobOutput.json
    for (const auto& line : compileJobOutput.at("outputLines")) {
        content.append(line.get<std::string>() + "\n");
    }

    // Check if it's a linker error
    std::regex mainLinkerErrorRegex(R"(duplicate symbol '(.*)' in:((?:.*\s*)+))"); //REGEX FOR MULT. MAIN DEC. LINKER ERROR PARSING
    //std::regex forwardDeclarationErrorRegex(R"(Undefined symbols:\s+_(.*), referenced from:)"); //REGEX FOR FORWARD DECLARATION ERROR PARSING
    std::regex forwardDeclarationErrorRegex(R"(Undefined symbols:\s+(.*), referenced from:)");



    std::regex errorRegex; // Declare errorRegex here for scope reasons 

    if (std::regex_search(content, mainLinkerErrorRegex) || std::regex_search(content, forwardDeclarationErrorRegex)) {//TODO - boolean not being entered, why? 
        isLinkerError = true;  
        //std::cout << "BOOL CHANGED: " << isLinkerError << std::endl;
    }
    //isLinkerError = true; //TODO - for testing remove later 
    StringParsing(content, parsedStrings); //parse string for file path, line number, column number, error type, and error description
   
int count = 0;
while(count < parsedStrings.size()){ 

    content = parsedStrings[count]; //take string from vector and put into content string
    std::smatch matches;
//std::cout << "ISLINK: " << isLinkerError << std::endl;
if(isLinkerError == 1) {
    //std::regex errorRegex(R"(duplicate symbol '(.*)' in:((?:.*\s*)+))"); //REGEX FOR LINKER ERRROR PARSING 
    if(std::regex_search(content, matches, mainLinkerErrorRegex)){//main linker error parsing
        std::string duplicateSymbol = matches[1].str(); //TODO - differentiate between content from main linker error and forward declaration error
        std::string filePaths = matches[2].str();
        
        // Split file paths
        std::istringstream stream(filePaths);
        std::string path;
        while (std::getline(stream, path)) {
            nlohmann::json errorJson;
            errorJson["Error Description"] = "duplicate symbol";
            errorJson["Error Detail"] = duplicateSymbol;
            errorJson["File Path"] = path; 
            //LINES, COL., SOURCE CODE CONTENT --> NOT INCLUDED FOR LINKER ERRORS, WRITTEN AS NULL IN OUTPUTJOB.CPP 
            errorJsonArray.push_back(errorJson);
            }
    }else if(std::regex_search(content, matches, forwardDeclarationErrorRegex)){//forward declaration linker error parsing 
        // handling forward declaration error
        //std::string errorDetail = matches[1].str(); // capturing just the undefined symbol name
        nlohmann::json errorJson;
        std::string errorDetail = content; 
        
        errorJson["Error Description"] = "unidentified symbols";
        errorJson["Error Detail"] = errorDetail;
        errorJson["File Path"] = "NULL - not listed for linker error"; 
        //TODO - Line number and column number added in output.cpp

        errorJsonArray.push_back(errorJson);
    }
   
}
else {//for non-linker error parsing 
    errorRegex = std::regex(R"((.*):(\d+):(\d+): (\w+): (.+))");
    if (std::regex_search(content, matches, errorRegex)) {
        std::string filePath = matches[1].str();
        int lineNumber = std::stoi(matches[2].str());
        int columnNumber = std::stoi(matches[3].str());
        std::string errorType = matches[4].str();
        std::string errorDescription = matches[5].str();
        
        nlohmann::json errorJson;
        errorJson["File Path"] = filePath;
        errorJson["Line Number"] = lineNumber;
        errorJson["Column Number"] = columnNumber;
        errorJson["Error Type"] = errorType;
        errorJson["Error Description"] = errorDescription;
        
        errorJsonArray.push_back(errorJson);
    }
}

    //END OF FILE PARSING & WRITING
    count++; 
}
    // Write JSON to a file
    std::ofstream outputFile("Data/errors.json");
    outputFile << errorJsonArray.dump(4); // 4 spaces for pretty printing
    outputFile.close();

    std::cout << "ParsingJob [ID: " << this->GetUniqueID() << "] has been executed." << std::endl;
    JobCompletedCallback();
}

void ParsingJob::JobCompletedCallback(){//TODO - report errors and warnings back to main thread. Main thread should then pass these to Parsingjob and OutputJob.
    std::cout << "ParsingJob callback" << std::endl;
    signalCompletion(); //TODO - encapsulated version of thread control with condvar
}

void ParsingJob::StringParsing(std::string &content, std::vector<std::string> &parsedStrings){

    std::string errorLog = content; 

    std::string delimiter = "./";
    size_t pos = 0;

    if(isLinkerError == 0){//not a linker error so parse ./ delimiter out 
        while ((pos = errorLog.find(delimiter)) != std::string::npos) {
            std::string token = errorLog.substr(0, pos);
            parsedStrings.push_back(token);
            errorLog.erase(0, pos + delimiter.length());
        }
    }
    parsedStrings.push_back(errorLog);

}