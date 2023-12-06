#include "lib/job.h"
#include "json.hpp"
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <vector>
using json = nlohmann::json;

class CompileJob : public Job
{
public:
    //CompileJob(json input);
    ~CompileJob(){};
    void Execute();
    static Job *CreateCustomJob(json input);
    void JobCompleteCallback();
    std::string output;
    int returnCode;
    std::string folder;
    std::string jobTypeName;
};
