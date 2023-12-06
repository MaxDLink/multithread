#include <vector> 
#include "job.h"

class RenderJob : public Job {
    public: 
        RenderJob(unsigned long jobChannels, int jobType) : Job(jobChannels, jobType) {}; //constructor 
        ~RenderJob(){}; //deconstructor 

        std::vector<int> data; 
        void Execute(); 
        void JobCompletedCallback(); //do not have to implement 
}; 