
// Generated from FlowscriptGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "FlowscriptGrammarListener.h"


/**
 * This class provides an empty implementation of FlowscriptGrammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  FlowscriptGrammarBaseListener : public FlowscriptGrammarListener {
public:

  virtual void enterFlowscript(FlowscriptGrammarParser::FlowscriptContext * /*ctx*/) override { }
  virtual void exitFlowscript(FlowscriptGrammarParser::FlowscriptContext * /*ctx*/) override { }

  virtual void enterGraph_content(FlowscriptGrammarParser::Graph_contentContext * /*ctx*/) override { }
  virtual void exitGraph_content(FlowscriptGrammarParser::Graph_contentContext * /*ctx*/) override { }

  virtual void enterSubgraph(FlowscriptGrammarParser::SubgraphContext * /*ctx*/) override { }
  virtual void exitSubgraph(FlowscriptGrammarParser::SubgraphContext * /*ctx*/) override { }

  virtual void enterSubgraph_content(FlowscriptGrammarParser::Subgraph_contentContext * /*ctx*/) override { }
  virtual void exitSubgraph_content(FlowscriptGrammarParser::Subgraph_contentContext * /*ctx*/) override { }

  virtual void enterLabel_statement(FlowscriptGrammarParser::Label_statementContext * /*ctx*/) override { }
  virtual void exitLabel_statement(FlowscriptGrammarParser::Label_statementContext * /*ctx*/) override { }

  virtual void enterNode_definition(FlowscriptGrammarParser::Node_definitionContext * /*ctx*/) override { }
  virtual void exitNode_definition(FlowscriptGrammarParser::Node_definitionContext * /*ctx*/) override { }

  virtual void enterEdge_definition(FlowscriptGrammarParser::Edge_definitionContext * /*ctx*/) override { }
  virtual void exitEdge_definition(FlowscriptGrammarParser::Edge_definitionContext * /*ctx*/) override { }

  virtual void enterEdge_label(FlowscriptGrammarParser::Edge_labelContext * /*ctx*/) override { }
  virtual void exitEdge_label(FlowscriptGrammarParser::Edge_labelContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

