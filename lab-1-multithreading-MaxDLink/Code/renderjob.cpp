#include "renderjob.h"
#include <iostream> 
//basic example of a job -- looping through a for loop 
void RenderJob::Execute() {
    int total = 0; 

    std::vector<int>::iterator it = data.begin(); //created & processed inside child threads 

    for(; it != data.end(); ++it) {//loop through and accumulate total 
        total += *it; 
    }

    it = data.begin(); //reset iterator
    for(; it != data.end(); ++it) {//loop through and accumulate total 
        total += *it; 
    }
    
    data[0] = total; //store total in first element of vector
    std::cout << "Job " << this->GetUniqueID() << " has been executed" << std::endl; 
}

void RenderJob::JobCompletedCallback() {
    std::cout << "Job " << this->GetUniqueID() << " calculated sum: " << this->data[0] << std::endl; //prints out sum 
}

//have to create a class for that type of job and write execute function for jobs to be done 
//everything in jobcompletedcallback will be executed in the main thread -- not in child 
//everything that executes executes in the child thread running in parallel 