#include <iostream>
#include <string> 
#include "job.h"
#include <fstream> //for writing to file 
#include <cstdio> //for removing file
#include <regex> //for parsing
#include "json.hpp" 
#include <sstream> //for linker error parsing 
#include "countingjob.h"
using json = nlohmann::json; 

void CountingJob::Execute(){

    int count = 0; 
    std::cout << "Countingjob is counting to five!" << std::endl; 

    for(int i = 0; i < 5; i++){
        count++; 
    }

    std::cout << "Counting job has counted to: " << count << std::endl; 

    std::cout << "Countingjob [ID: " << this->GetUniqueID() << "] has been executed." << std::endl;
    JobCompletedCallback();
}

void CountingJob::JobCompletedCallback(){//TODO - report errors and warnings back to main thread. Main thread should then pass these to Parsingjob and OutputJob.
    std::cout << "Countingjob callback" << std::endl;
    signalCompletion(); //TODO - encapsulated version of thread control with condvar
}