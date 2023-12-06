#include "customvisitor.h"

std::any CustomVisitor::visitLabel_statement(FlowscriptGrammarParser::Label_statementContext *context) {
    // These lines should be commented out to avoid pushing the label statement to the job queue. We only want "Job A", "Job B", and "Job C" not "label="'Job Dependencies'"
    // std::string jobName = context->getText();
    // jobQueue.push_back(jobName);
    return visitChildren(context);
}

std::any CustomVisitor::visitFlowscript(FlowscriptGrammarParser::FlowscriptContext *context) {

    // First pass: Collect defined nodes
    collectDefinedNodes(context->graph_content());

    return visitChildren(context);
}

std::any CustomVisitor::visitGraph_content(FlowscriptGrammarParser::Graph_contentContext *context) {
    return visitChildren(context);
}

std::any CustomVisitor::visitSubgraph(FlowscriptGrammarParser::SubgraphContext *context) {
    return visitChildren(context);
}

std::any CustomVisitor::visitSubgraph_content(FlowscriptGrammarParser::Subgraph_contentContext *context) {
    return visitChildren(context);
}


void CustomVisitor::collectDefinedNodes(FlowscriptGrammarParser::Graph_contentContext *context) {
    // Visit each node_definition and add the node name to the definedNodes set
    for (auto *nodeDef : context->node_definition()) {
        definedNodes.insert(nodeDef->ID()->getText());
    }
}


std::any CustomVisitor::visitEdge_definition(FlowscriptGrammarParser::Edge_definitionContext *context) {
    std::string sourceNode = context->ID(0)->getText();
    std::string targetNode = context->ID(1)->getText();

    // Add source node to jobQueue if it is legitimate
    if (legitimateNodeNames.find(sourceNode) != legitimateNodeNames.end()) {
        if (std::find(jobQueue.begin(), jobQueue.end(), sourceNode) == jobQueue.end()) {
            jobQueue.push_back(sourceNode);
        }
    // } else { //TODO - commented out because customerrorlistener class gets both errors. Left in for future reference & feature implementation
    //     json error = {
    //         {"type", "Semantic Error"},
    //         {"description", "Undefined or invalid source node in edge"},
    //         {"node", sourceNode}
    //     };
    //   semanticErrors.push_back(error);
    }

    // Add target node to jobQueue if it is legitimate
    if (legitimateNodeNames.find(targetNode) != legitimateNodeNames.end()) {
        if (std::find(jobQueue.begin(), jobQueue.end(), targetNode) == jobQueue.end()) {
            jobQueue.push_back(targetNode);
        }
    // } else { //TODO - commented out because customerrorlistener class gets both error types. Left in for future reference and feature implementation
    //     json error = {
    //         {"type", "Semantic Error"},
    //         {"description", "Undefined or invalid target node in edge"},
    //         {"node", targetNode}
    //     };
    //     semanticErrors.push_back(error);
    }

    // Continue visiting other children nodes
    return visitChildren(context);
}



std::any CustomVisitor::visitEdge_label(FlowscriptGrammarParser::Edge_labelContext *context) {
    return visitChildren(context);
}

std::any CustomVisitor::visitNode_definition(FlowscriptGrammarParser::Node_definitionContext *context) {//TODO - understand how this fetched strings from flowscript... Running multiple times because I am getting multiple string duplicates in my jobQueue???? 
    // Add the node ID to the set of defined nodes
    definedNodes.insert(context->ID()->getText());
    return visitChildren(context);
}

//TODO - commented out because customerrorlistener class gets both error types. Left in for future reference and feature implementation
// void CustomVisitor::logSemanticErrors(const std::string& filename) {
//         std::ofstream file(filename, std::ios::app); // Open in append mode
//         if (file.is_open()) {
//             for (const auto& error : semanticErrors) {
//                 file << error.dump(4) << std::endl;
//             }
//             file.close();
//         } else {
//             std::cerr << "Unable to open file to log semantic errors." << std::endl;
//         }
// }


// Implement other methods of CustomVisitor if needed
