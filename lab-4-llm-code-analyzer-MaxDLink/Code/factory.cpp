#include "factory.h"
#include "customjob.h"
#include "JobSystemAPI.h"

void JobFactory::Register(JobFactoryFunction factoryFunction, const std::string& jobTypeName) {
    m_registeredJobs[jobTypeName] = factoryFunction;
}

Job* JobFactory::Create(const std::string& jobTypeName) {
    auto it = m_registeredJobs.find(jobTypeName);
    if (it != m_registeredJobs.end()) { 
        return it->second(); //TODO - how is this pulling out the filepath and returning it? How is the filepath put in the map? From the register function? 
    }
    return nullptr;  // or handle error appropriately
}


