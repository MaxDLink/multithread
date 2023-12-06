#include "customjob.h"
#include "fstream"
#include "./lib/json.hpp" //for json manipulation
#include <iostream> 
#include <string> 
#include <array> 
#include <sstream> //for stringstream to split output into words by spaces 

//For antlr4 lexical and syntactical parsing 
#include "antlr4-runtime/antlr4-runtime.h"
#include "antlr/grammar-files/FlowscriptGrammarLexer.h"
#include "antlr/grammar-files/FlowscriptGrammarParser.h"

#include "JobSystemAPI.h"  //for kicking off jobs with the parsed flowscript.... 

#include "customvisitor.h" //for visiting the node_definitions in the tree

#include "customerrorlistener.h" //for flowscript error logging 

Job* CustomJob::CreateCustomJob() {
    return new CustomJob();
}

//execute function 
void CustomJob::Execute(){

    std::cout << "EXECUTING PARSING FROM CUSTOMJOB" << std::endl;

    CustomErrorListener errorListener; //create error listener object

    //TODO -  add parsing here in customJobs execute function 

    // Path to flowscript input file taken in 
    std::ifstream stream("./Data/fsp3.txt"); // Adjust the path to the location of your .txt file
    if (!stream) {
        std::cerr << "Cannot open file: ../Data/fsp#.txt" << std::endl;
        return; // Handle the error as you see fit
    }
    antlr4::ANTLRInputStream input(stream);

    // Create a lexer that feeds off of the input stream
    FlowscriptGrammarLexer lexer(&input);

    // Create a buffer of tokens pulled from the lexer
    antlr4::CommonTokenStream tokens(&lexer);

    // Create a parser that feeds off the tokens buffer
    FlowscriptGrammarParser parser(&tokens);

    //attach the customerror listener to the parser 
    parser.removeErrorListeners(); //remove default error listener
    parser.addErrorListener(&errorListener); //add custom error listener

    //attach the custom listener to the lexer 
    lexer.removeErrorListeners(); //remove default error listener
    lexer.addErrorListener(&errorListener); //add custom error listener

    // Begin parsing at the root rule (replace 'script' with your actual root rule name)
    antlr4::tree::ParseTree *tree = parser.flowscript();

    //parsing now complete, so write errors to json file if there are any errors 
    //errorListener.writeErrorsToFile("./Data/flowscript-errors.json");


    // Now you can use the tree however you need to
    //std::cout << tree->toStringTree(&parser) << std::endl; //TODO - use this tree to run the jobs in interpreter situationally based on what is in the tree..... 

    std::cout << "visiting tree!" << std::endl; 

    //TODO - use visitor design pattern to visit tree 

    //TODO - JobQUEUE is holding info, but jobLabels is not... why?
   CustomVisitor visitor; //create visitor object
   visitor.visit(tree); //visit tree. Will call visitNode_definition function in customvisitor.cpp and push back the strings "Job A", "Job B", and "Job C" to the jobQueue vector in customvisitor.cpp

// Aggregate errors from errorListener and visitor
json combinedErrors = json::array(); // Initialize as an empty JSON array

for (const auto& error : errorListener.getErrors()) {
       combinedErrors.push_back(error);
      
}

//TODO - commented out because customerrorlistener class gets both errors. Left in for future reference & feature implementation
// for (const auto& error : visitor.getSemanticErrors()) {
//        combinedErrors.push_back(error);
// }

// Write to file
std::ofstream errorFile("./Data/flowscript-error-output.json");
if (errorFile.is_open()) {
    errorFile << combinedErrors.dump(4);
    errorFile.close();
} else {
    std::cerr << "Unable to open error log file." << std::endl;
}

   //TODO - jobLabels holds "outputjob", "compilejob", "parsingjob", "outputjob"... this out of order is from grabbing only 4 of the 6 strings from the customvisitor jobqueue because customjob is a thread that finishes before the customvisitor class is done running... make a control structure for customjob to wait for costumvisitor to finish and make sure that jobQueue only holds three string values, not 6
   jobLabels = visitor.getJobLabels(); // Get the job labels

    //iterate through jobLabels to check if they are correct
    // for(const auto& label : jobLabels){
    //     std::cout << "\n\nCUSTOMJOB JOB LABELS: \n\n" << label << std::endl;
    // }
    // Print the job labels (optional)
    //write lablel to a file 
    std::ofstream file("./Data/jobprocessflow.txt"); //open file to write to
    for (const std::string& label : jobLabels) {
        file << label << std::endl;
        //TODO - printing labels for testing only... 
        //std::cout << label << std::endl; //jobs original naming convention in the fsp1.txt file was "Job A", "Job B", "Job C", but they were changed to "compilejob", "parsingjob", and "outputjob" respectfully for testing purposes. 
    } //TODO - get labels vector into intepreter and run jobs based on those strings. Here the strings are "Job A", "Job B", "Job C" but for testing purposes I should change these strings in the fsp1.txt file to be "compilejob", "parsejob", "outputjob" to ensure I can run the jobs in the jobsystem. Then I can adopt the jobsystem's string identifiers it uses to run the native jobs to match the flowscript name conventions later. ASK HIM ABOUT THIS NAMING CONVENTION FOR STRING IDENTIFIERS.  
    file.close(); //close file
    std::cout << "CustomJob [ID: " << this->GetUniqueID() << "] has been executed." << std::endl;
    //call jobcompletedCallback 

    JobCompletedCallback(); 
}

//callback function
void CustomJob::JobCompletedCallback() {
    std::cout << "CustomJob callback is done!" << std::endl;
    
    //getJobLabels(); //return job labels to interpreter
    signalCompletion(); //signal completion


}
