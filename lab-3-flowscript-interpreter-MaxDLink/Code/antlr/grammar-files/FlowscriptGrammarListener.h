
// Generated from FlowscriptGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "FlowscriptGrammarParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by FlowscriptGrammarParser.
 */
class  FlowscriptGrammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFlowscript(FlowscriptGrammarParser::FlowscriptContext *ctx) = 0;
  virtual void exitFlowscript(FlowscriptGrammarParser::FlowscriptContext *ctx) = 0;

  virtual void enterGraph_content(FlowscriptGrammarParser::Graph_contentContext *ctx) = 0;
  virtual void exitGraph_content(FlowscriptGrammarParser::Graph_contentContext *ctx) = 0;

  virtual void enterSubgraph(FlowscriptGrammarParser::SubgraphContext *ctx) = 0;
  virtual void exitSubgraph(FlowscriptGrammarParser::SubgraphContext *ctx) = 0;

  virtual void enterSubgraph_content(FlowscriptGrammarParser::Subgraph_contentContext *ctx) = 0;
  virtual void exitSubgraph_content(FlowscriptGrammarParser::Subgraph_contentContext *ctx) = 0;

  virtual void enterLabel_statement(FlowscriptGrammarParser::Label_statementContext *ctx) = 0;
  virtual void exitLabel_statement(FlowscriptGrammarParser::Label_statementContext *ctx) = 0;

  virtual void enterNode_definition(FlowscriptGrammarParser::Node_definitionContext *ctx) = 0;
  virtual void exitNode_definition(FlowscriptGrammarParser::Node_definitionContext *ctx) = 0;

  virtual void enterEdge_definition(FlowscriptGrammarParser::Edge_definitionContext *ctx) = 0;
  virtual void exitEdge_definition(FlowscriptGrammarParser::Edge_definitionContext *ctx) = 0;

  virtual void enterEdge_label(FlowscriptGrammarParser::Edge_labelContext *ctx) = 0;
  virtual void exitEdge_label(FlowscriptGrammarParser::Edge_labelContext *ctx) = 0;


};

