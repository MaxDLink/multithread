
// Generated from FlowscriptGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "FlowscriptGrammarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by FlowscriptGrammarParser.
 */
class  FlowscriptGrammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by FlowscriptGrammarParser.
   */
    virtual std::any visitFlowscript(FlowscriptGrammarParser::FlowscriptContext *context) = 0;

    virtual std::any visitGraph_content(FlowscriptGrammarParser::Graph_contentContext *context) = 0;

    virtual std::any visitSubgraph(FlowscriptGrammarParser::SubgraphContext *context) = 0;

    virtual std::any visitSubgraph_content(FlowscriptGrammarParser::Subgraph_contentContext *context) = 0;

    virtual std::any visitLabel_statement(FlowscriptGrammarParser::Label_statementContext *context) = 0;

    virtual std::any visitNode_definition(FlowscriptGrammarParser::Node_definitionContext *context) = 0;

    virtual std::any visitEdge_definition(FlowscriptGrammarParser::Edge_definitionContext *context) = 0;

    virtual std::any visitEdge_label(FlowscriptGrammarParser::Edge_labelContext *context) = 0;


};

