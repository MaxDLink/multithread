#include "antlr/grammar-files/FlowscriptGrammarVisitor.h"
#include <vector>
#include "./lib/json.hpp" //for json manipulation
#include "unordered_set" //for unordered set of legitimate node names
using json = nlohmann::json;
class CustomVisitor : public FlowscriptGrammarVisitor {
public:
    // Constructor and other methods can go here

    virtual std::any visitLabel_statement(FlowscriptGrammarParser::Label_statementContext *context) override;
    
    // Declarations for pure virtual functions
    virtual std::any visitFlowscript(FlowscriptGrammarParser::FlowscriptContext *context) override;
    virtual std::any visitGraph_content(FlowscriptGrammarParser::Graph_contentContext *context) override;
    virtual std::any visitSubgraph(FlowscriptGrammarParser::SubgraphContext *context) override;
    virtual std::any visitSubgraph_content(FlowscriptGrammarParser::Subgraph_contentContext *context) override;
    virtual std::any visitEdge_definition(FlowscriptGrammarParser::Edge_definitionContext *context) override;
    virtual std::any visitEdge_label(FlowscriptGrammarParser::Edge_labelContext *context) override;
    virtual std::any visitNode_definition(FlowscriptGrammarParser::Node_definitionContext *context) override;

    const std::vector<std::string>& getJobLabels() const {//Getter that returns jobQueue to customjob so that customjob can use the jobQueue to extract the joblabels //TODO - understand this relationship 
        // std::cout << "\n\n\n jobQueue HOLDS THIS: " << std::endl;
        // for(const auto& labels : jobQueue){//TODO - why are you holding duplicates of strings jobQueue? 
        //     std::cout << labels << std::endl;
        // }
        return jobQueue;
    }


    //TODO - commented out because customerrorlistener class gets both errors. Left in for future reference and feature implementation
    // std::vector<json> getSemanticErrors() const {
    //     std::vector<json> errors;
    //     if(!semanticErrors.empty()){
    //         for (const auto& error : semanticErrors) {
    //             errors.push_back(error);
    //         }
    //         return errors;
    //     }
    // }


    void logSemanticErrors(const std::string& filename);

    void collectDefinedNodes(FlowscriptGrammarParser::Graph_contentContext *context); //performs first pass to collect defined nodes first 


private:
    std::vector<std::string> jobQueue;  // This defines jobQueue

    //for cross referencing nodes that already exist for semantic analysis misspelling checks 
    std::set<std::string> definedNodes;
    std::vector<json> semanticErrors; // To store semantic errors

    // Any additional methods or attributes for your custom visitor

    // Hardcoded set of legitimate node names
    const std::unordered_set<std::string> legitimateNodeNames = {
        "compilejob", "parsingjob", "outputjob", "countingjob",
        "controlstatement", "loopstatement" // Assuming these are the correct node names
    };
};
