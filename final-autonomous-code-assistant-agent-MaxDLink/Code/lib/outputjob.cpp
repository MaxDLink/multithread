#include "outputjob.h"
#include <iostream>
#include <string> 
#include <array> 
#include <fstream> //for reading and writing to files
#include <cstdio> //for removing files
#include "json.hpp" //for creating output json 

using json = nlohmann::json; 

std::vector<std::string> getSurroundingLines(const std::string& filePath, int errorLine) {
    std::vector<std::string> lines;
    std::ifstream file(filePath);
    std::string line;
    int lineNumber = 1;

    while (std::getline(file, line)) {
        if (lineNumber >= errorLine - 2 && lineNumber <= errorLine + 2) {
            lines.push_back(line);
        }
        lineNumber++;
    }

    file.close();
    return lines;
}

void OutputJob::Execute(){
    //Generic file path for errors.json
    std::ifstream inputFile("Data/parsed-errors.json");
    json errors = json::parse(inputFile);
    inputFile.close();

    //if errors is empty, then write "No errors/warnings" to output.json
    if (errors.empty()) {
        json outputJson = json::array();
        json errorJson;
        errorJson["Error Description"] = "No errors or warnings - compiled successfully";
        outputJson.push_back(errorJson);

        std::ofstream outputFile("Data/output.json");
        outputFile << outputJson.dump(4); // 4 spaces for pretty printing
        outputFile.close();

        // //delete errors.json file 
        //std::remove("Data/errors.json");
        return;
    }

    for (const auto& error : errors) {
            // Check if "Error Description" key exists in the json object
            if (error.contains("Error Description")) {
                std::string errorDescription = error.at("Error Description").get<std::string>();

                // Check if it's a linker error.
                if (errorDescription == "duplicate symbol" || errorDescription == "unidentified symbols") {
                    //std::cout << "KICKING OFF LINKER ERROR FUNCTION FOR MAIN LINKER ERROR" << std::endl; 
                    LinkerError(errors); //handle linker error

                }
                else{//handle linker error 
                    NonLinkerError(errors); //handle writing errors that are not linker errors

                 }
            }
        
    }

    std::cout << "OutputJob [ID: " << this->GetUniqueID() << "] has been executed." << std::endl;
    JobCompletedCallback();

}


void OutputJob::JobCompletedCallback(){
    signalCompletion(); //TODO - encapsulated version of thread control with condvar
}

void OutputJob::LinkerError(json & errors){//TODO - take out input file 
   //std::cout << "LINKER ERROR BEING WRITTEN TO OUTPUT FILE" << std::endl; 

    // Using a map to organize errors by file path.
    std::map<std::string, json> outputMap;

    for (json& error : errors) {
        std::string filePath = error["File Path"];
        std::string detail = error["Error Detail"];
        std::string errorDescription = error["Error Description"]; 

        json errorOutput;
        errorOutput["File Path"] = filePath;
        errorOutput["Error Type"] = error["Error Description"];
        errorOutput["Error Description"] = error["Error Detail"];
        //if the error is a linker error, will not have these 
        errorOutput["Line Number"] = "NULL - not listed for linker error";
        errorOutput["Column Number"] = "NULL - not listed for linker error";
        errorOutput["Source Code Causing Error"] = "NULL - not listed for linker error"; 

        // Inserting errorOutput into the map.
        outputMap[filePath].push_back(errorOutput);
    }

    // Convert the map to a json array.
    json outputJson = json::array();
    for (auto& pair : outputMap) {
        outputJson.push_back(pair.second);
    }

    // Write JSON to a file
    std::ofstream outputFile("Data/output.json");
    outputFile << outputJson.dump(4); // 4 spaces for pretty printing
    outputFile.close();

    //delete errors.json file 
    //std::remove("Data/errors.json");

}

void OutputJob::NonLinkerError(json & errors){//TODO - take out input file 

    // Using a map to organize errors by file path.
    std::map<std::string, json> outputMap;

    for (json& error : errors) {
        std::string filePath = error["File Path"];
        int lineNumber = error["Line Number"];
        int columnNumber = error["Column Number"];
        auto surroundingLines = getSurroundingLines(filePath, lineNumber);

        json errorOutput;
        errorOutput["File Path"] = filePath;
        errorOutput["Line Number"] = lineNumber;
        errorOutput["Column Number"] = columnNumber;
        errorOutput["Error Description"] = error["Error Description"];
        errorOutput["Source Code Causing Error"] = surroundingLines;

        // Inserting errorOutput into the map.
        outputMap[filePath].push_back(errorOutput);
    }

    // Convert the map to a json array.
    json outputJson = json::array();
    for (auto& pair : outputMap) {
        outputJson.push_back(pair.second);
    }

    //write JSON to a file 
    std::ofstream outputFile("Data/output.json");
    outputFile << outputJson.dump(4); // 4 spaces for pretty printing
    outputFile.close();

    //delete errors.json file
    //std::remove("Data/errors.json");
}   
