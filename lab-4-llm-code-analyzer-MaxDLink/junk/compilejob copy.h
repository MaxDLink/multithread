#include "lib/Job.h"
#include "lib/nlohmann/json.hpp"
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <vector>
using json = nlohmann::json;

class CustomJob : public Job
{
public:
    CustomJob(json input);
    ~CustomJob(){};
    void Execute();
    static Job *CreateCustomJob(json input);
    void JobCompleteCallback();
    std::string output;
    int returnCode;
    std::string folder;
    std::string jobTypeName;
};
