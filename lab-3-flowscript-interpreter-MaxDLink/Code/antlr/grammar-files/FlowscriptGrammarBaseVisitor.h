
// Generated from FlowscriptGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "FlowscriptGrammarVisitor.h"


/**
 * This class provides an empty implementation of FlowscriptGrammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  FlowscriptGrammarBaseVisitor : public FlowscriptGrammarVisitor {
public:

  virtual std::any visitFlowscript(FlowscriptGrammarParser::FlowscriptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGraph_content(FlowscriptGrammarParser::Graph_contentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubgraph(FlowscriptGrammarParser::SubgraphContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubgraph_content(FlowscriptGrammarParser::Subgraph_contentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabel_statement(FlowscriptGrammarParser::Label_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNode_definition(FlowscriptGrammarParser::Node_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEdge_definition(FlowscriptGrammarParser::Edge_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEdge_label(FlowscriptGrammarParser::Edge_labelContext *ctx) override {
    return visitChildren(ctx);
  }


};

