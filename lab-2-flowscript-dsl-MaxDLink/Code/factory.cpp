#include "factory.h"
#include "customjob.h"

void JobFactory::Register(JobFactoryFunction factoryFunction, const std::string& jobTypeName) {
    m_registeredJobs[jobTypeName] = factoryFunction;
}

Job* JobFactory::Create(const std::string& jobTypeName) {
    auto it = m_registeredJobs.find(jobTypeName);
    if (it != m_registeredJobs.end()) {
        return it->second();
    }
    return nullptr;  // or handle error appropriately
}
