#include "compilejob.h"

#include <iostream> 
#include <string>
#include <sstream> 

// CompileJob::CompileJob(json input)
// {
//    //Assuming m_jobType is a protected or public member in the Job class
//     m_jobType = input["jobType"].get<int>();
//     m_jobChannels = input["jobChannel"].get<unsigned long>();
//     folder = input["folder"].get<std::string>();
//     jobTypeName = input["newJobType"].get<std::string>();
// }

Job *CompileJob::CreateCustomJob(json input)
{
    return (Job *)(new CompileJob(input));
}

void CompileJob::Execute()
{
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

void CompileJob::JobCompleteCallback()
{
    // Return error output to the main thread and stores the output in error.json if the returnCode is not 0
    if (this->returnCode == 0)
    {
        // shows the file does not have compile errors to the main user interface
        std::cout << "Compile Job " << this->GetUniqueID() << " Return Code: " << this->returnCode << std::endl;
        std::cout << "No Errors detected while compiling " << folder << " folder" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Compile Job " << this->GetUniqueID() << " Return Code: " << this->returnCode << std::endl;
        std::cout << "Errors detected while compiling " << folder << " folder and errors has been parsed to errors.json" << std::endl;
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
        std::ofstream o("Data/alex-errors.json");
        o << std::setw(4) << parsejob << std::endl;
    }
}
