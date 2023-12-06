
// Generated from FlowscriptGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  FlowscriptGrammarParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    DIGRAPH = 8, SUBGRAPH = 9, LABEL = 10, ID = 11, STRING = 12, WS = 13
  };

  enum {
    RuleFlowscript = 0, RuleGraph_content = 1, RuleSubgraph = 2, RuleSubgraph_content = 3, 
    RuleLabel_statement = 4, RuleNode_definition = 5, RuleEdge_definition = 6, 
    RuleEdge_label = 7
  };

  explicit FlowscriptGrammarParser(antlr4::TokenStream *input);

  FlowscriptGrammarParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~FlowscriptGrammarParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class FlowscriptContext;
  class Graph_contentContext;
  class SubgraphContext;
  class Subgraph_contentContext;
  class Label_statementContext;
  class Node_definitionContext;
  class Edge_definitionContext;
  class Edge_labelContext; 

  class  FlowscriptContext : public antlr4::ParserRuleContext {
  public:
    FlowscriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DIGRAPH();
    antlr4::tree::TerminalNode *ID();
    Graph_contentContext *graph_content();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FlowscriptContext* flowscript();

  class  Graph_contentContext : public antlr4::ParserRuleContext {
  public:
    Graph_contentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SubgraphContext *> subgraph();
    SubgraphContext* subgraph(size_t i);
    std::vector<Node_definitionContext *> node_definition();
    Node_definitionContext* node_definition(size_t i);
    std::vector<Edge_definitionContext *> edge_definition();
    Edge_definitionContext* edge_definition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Graph_contentContext* graph_content();

  class  SubgraphContext : public antlr4::ParserRuleContext {
  public:
    SubgraphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUBGRAPH();
    antlr4::tree::TerminalNode *ID();
    Subgraph_contentContext *subgraph_content();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubgraphContext* subgraph();

  class  Subgraph_contentContext : public antlr4::ParserRuleContext {
  public:
    Subgraph_contentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Label_statementContext *> label_statement();
    Label_statementContext* label_statement(size_t i);
    std::vector<Node_definitionContext *> node_definition();
    Node_definitionContext* node_definition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Subgraph_contentContext* subgraph_content();

  class  Label_statementContext : public antlr4::ParserRuleContext {
  public:
    Label_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LABEL();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Label_statementContext* label_statement();

  class  Node_definitionContext : public antlr4::ParserRuleContext {
  public:
    Node_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LABEL();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Node_definitionContext* node_definition();

  class  Edge_definitionContext : public antlr4::ParserRuleContext {
  public:
    Edge_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    Edge_labelContext *edge_label();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Edge_definitionContext* edge_definition();

  class  Edge_labelContext : public antlr4::ParserRuleContext {
  public:
    Edge_labelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LABEL();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Edge_labelContext* edge_label();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

