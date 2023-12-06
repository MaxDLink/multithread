
// Generated from FlowscriptGrammar.g4 by ANTLR 4.13.1


#include "FlowscriptGrammarListener.h"
#include "FlowscriptGrammarVisitor.h"

#include "FlowscriptGrammarParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct FlowscriptGrammarParserStaticData final {
  FlowscriptGrammarParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  FlowscriptGrammarParserStaticData(const FlowscriptGrammarParserStaticData&) = delete;
  FlowscriptGrammarParserStaticData(FlowscriptGrammarParserStaticData&&) = delete;
  FlowscriptGrammarParserStaticData& operator=(const FlowscriptGrammarParserStaticData&) = delete;
  FlowscriptGrammarParserStaticData& operator=(FlowscriptGrammarParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag flowscriptgrammarParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
FlowscriptGrammarParserStaticData *flowscriptgrammarParserStaticData = nullptr;

void flowscriptgrammarParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (flowscriptgrammarParserStaticData != nullptr) {
    return;
  }
#else
  assert(flowscriptgrammarParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<FlowscriptGrammarParserStaticData>(
    std::vector<std::string>{
      "flowscript", "graph_content", "subgraph", "subgraph_content", "label_statement", 
      "node_definition", "edge_definition", "edge_label"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "'='", "';'", "'['", "']'", "'->'", "'digraph'", 
      "'subgraph'", "'label'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "DIGRAPH", "SUBGRAPH", "LABEL", "ID", 
      "STRING", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,13,71,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,5,1,26,8,1,10,1,12,1,29,9,1,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,5,3,39,8,3,10,3,12,3,42,9,3,1,4,1,4,1,4,
  	1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,3,6,61,8,6,1,
  	6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,0,0,8,0,2,4,6,8,10,12,14,0,0,68,0,16,
  	1,0,0,0,2,27,1,0,0,0,4,30,1,0,0,0,6,40,1,0,0,0,8,43,1,0,0,0,10,48,1,0,
  	0,0,12,56,1,0,0,0,14,64,1,0,0,0,16,17,5,8,0,0,17,18,5,11,0,0,18,19,5,
  	1,0,0,19,20,3,2,1,0,20,21,5,2,0,0,21,1,1,0,0,0,22,26,3,4,2,0,23,26,3,
  	10,5,0,24,26,3,12,6,0,25,22,1,0,0,0,25,23,1,0,0,0,25,24,1,0,0,0,26,29,
  	1,0,0,0,27,25,1,0,0,0,27,28,1,0,0,0,28,3,1,0,0,0,29,27,1,0,0,0,30,31,
  	5,9,0,0,31,32,5,11,0,0,32,33,5,1,0,0,33,34,3,6,3,0,34,35,5,2,0,0,35,5,
  	1,0,0,0,36,39,3,8,4,0,37,39,3,10,5,0,38,36,1,0,0,0,38,37,1,0,0,0,39,42,
  	1,0,0,0,40,38,1,0,0,0,40,41,1,0,0,0,41,7,1,0,0,0,42,40,1,0,0,0,43,44,
  	5,10,0,0,44,45,5,3,0,0,45,46,5,12,0,0,46,47,5,4,0,0,47,9,1,0,0,0,48,49,
  	5,11,0,0,49,50,5,5,0,0,50,51,5,10,0,0,51,52,5,3,0,0,52,53,5,12,0,0,53,
  	54,5,6,0,0,54,55,5,4,0,0,55,11,1,0,0,0,56,57,5,11,0,0,57,58,5,7,0,0,58,
  	60,5,11,0,0,59,61,3,14,7,0,60,59,1,0,0,0,60,61,1,0,0,0,61,62,1,0,0,0,
  	62,63,5,4,0,0,63,13,1,0,0,0,64,65,5,5,0,0,65,66,5,10,0,0,66,67,5,3,0,
  	0,67,68,5,12,0,0,68,69,5,6,0,0,69,15,1,0,0,0,5,25,27,38,40,60
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  flowscriptgrammarParserStaticData = staticData.release();
}

}

FlowscriptGrammarParser::FlowscriptGrammarParser(TokenStream *input) : FlowscriptGrammarParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

FlowscriptGrammarParser::FlowscriptGrammarParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  FlowscriptGrammarParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *flowscriptgrammarParserStaticData->atn, flowscriptgrammarParserStaticData->decisionToDFA, flowscriptgrammarParserStaticData->sharedContextCache, options);
}

FlowscriptGrammarParser::~FlowscriptGrammarParser() {
  delete _interpreter;
}

const atn::ATN& FlowscriptGrammarParser::getATN() const {
  return *flowscriptgrammarParserStaticData->atn;
}

std::string FlowscriptGrammarParser::getGrammarFileName() const {
  return "FlowscriptGrammar.g4";
}

const std::vector<std::string>& FlowscriptGrammarParser::getRuleNames() const {
  return flowscriptgrammarParserStaticData->ruleNames;
}

const dfa::Vocabulary& FlowscriptGrammarParser::getVocabulary() const {
  return flowscriptgrammarParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView FlowscriptGrammarParser::getSerializedATN() const {
  return flowscriptgrammarParserStaticData->serializedATN;
}


//----------------- FlowscriptContext ------------------------------------------------------------------

FlowscriptGrammarParser::FlowscriptContext::FlowscriptContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FlowscriptGrammarParser::FlowscriptContext::DIGRAPH() {
  return getToken(FlowscriptGrammarParser::DIGRAPH, 0);
}

tree::TerminalNode* FlowscriptGrammarParser::FlowscriptContext::ID() {
  return getToken(FlowscriptGrammarParser::ID, 0);
}

FlowscriptGrammarParser::Graph_contentContext* FlowscriptGrammarParser::FlowscriptContext::graph_content() {
  return getRuleContext<FlowscriptGrammarParser::Graph_contentContext>(0);
}


size_t FlowscriptGrammarParser::FlowscriptContext::getRuleIndex() const {
  return FlowscriptGrammarParser::RuleFlowscript;
}

void FlowscriptGrammarParser::FlowscriptContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFlowscript(this);
}

void FlowscriptGrammarParser::FlowscriptContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFlowscript(this);
}


std::any FlowscriptGrammarParser::FlowscriptContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FlowscriptGrammarVisitor*>(visitor))
    return parserVisitor->visitFlowscript(this);
  else
    return visitor->visitChildren(this);
}

FlowscriptGrammarParser::FlowscriptContext* FlowscriptGrammarParser::flowscript() {
  FlowscriptContext *_localctx = _tracker.createInstance<FlowscriptContext>(_ctx, getState());
  enterRule(_localctx, 0, FlowscriptGrammarParser::RuleFlowscript);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(16);
    match(FlowscriptGrammarParser::DIGRAPH);
    setState(17);
    match(FlowscriptGrammarParser::ID);
    setState(18);
    match(FlowscriptGrammarParser::T__0);
    setState(19);
    graph_content();
    setState(20);
    match(FlowscriptGrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Graph_contentContext ------------------------------------------------------------------

FlowscriptGrammarParser::Graph_contentContext::Graph_contentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FlowscriptGrammarParser::SubgraphContext *> FlowscriptGrammarParser::Graph_contentContext::subgraph() {
  return getRuleContexts<FlowscriptGrammarParser::SubgraphContext>();
}

FlowscriptGrammarParser::SubgraphContext* FlowscriptGrammarParser::Graph_contentContext::subgraph(size_t i) {
  return getRuleContext<FlowscriptGrammarParser::SubgraphContext>(i);
}

std::vector<FlowscriptGrammarParser::Node_definitionContext *> FlowscriptGrammarParser::Graph_contentContext::node_definition() {
  return getRuleContexts<FlowscriptGrammarParser::Node_definitionContext>();
}

FlowscriptGrammarParser::Node_definitionContext* FlowscriptGrammarParser::Graph_contentContext::node_definition(size_t i) {
  return getRuleContext<FlowscriptGrammarParser::Node_definitionContext>(i);
}

std::vector<FlowscriptGrammarParser::Edge_definitionContext *> FlowscriptGrammarParser::Graph_contentContext::edge_definition() {
  return getRuleContexts<FlowscriptGrammarParser::Edge_definitionContext>();
}

FlowscriptGrammarParser::Edge_definitionContext* FlowscriptGrammarParser::Graph_contentContext::edge_definition(size_t i) {
  return getRuleContext<FlowscriptGrammarParser::Edge_definitionContext>(i);
}


size_t FlowscriptGrammarParser::Graph_contentContext::getRuleIndex() const {
  return FlowscriptGrammarParser::RuleGraph_content;
}

void FlowscriptGrammarParser::Graph_contentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGraph_content(this);
}

void FlowscriptGrammarParser::Graph_contentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGraph_content(this);
}


std::any FlowscriptGrammarParser::Graph_contentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FlowscriptGrammarVisitor*>(visitor))
    return parserVisitor->visitGraph_content(this);
  else
    return visitor->visitChildren(this);
}

FlowscriptGrammarParser::Graph_contentContext* FlowscriptGrammarParser::graph_content() {
  Graph_contentContext *_localctx = _tracker.createInstance<Graph_contentContext>(_ctx, getState());
  enterRule(_localctx, 2, FlowscriptGrammarParser::RuleGraph_content);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FlowscriptGrammarParser::SUBGRAPH

    || _la == FlowscriptGrammarParser::ID) {
      setState(25);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(22);
        subgraph();
        break;
      }

      case 2: {
        setState(23);
        node_definition();
        break;
      }

      case 3: {
        setState(24);
        edge_definition();
        break;
      }

      default:
        break;
      }
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubgraphContext ------------------------------------------------------------------

FlowscriptGrammarParser::SubgraphContext::SubgraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FlowscriptGrammarParser::SubgraphContext::SUBGRAPH() {
  return getToken(FlowscriptGrammarParser::SUBGRAPH, 0);
}

tree::TerminalNode* FlowscriptGrammarParser::SubgraphContext::ID() {
  return getToken(FlowscriptGrammarParser::ID, 0);
}

FlowscriptGrammarParser::Subgraph_contentContext* FlowscriptGrammarParser::SubgraphContext::subgraph_content() {
  return getRuleContext<FlowscriptGrammarParser::Subgraph_contentContext>(0);
}


size_t FlowscriptGrammarParser::SubgraphContext::getRuleIndex() const {
  return FlowscriptGrammarParser::RuleSubgraph;
}

void FlowscriptGrammarParser::SubgraphContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubgraph(this);
}

void FlowscriptGrammarParser::SubgraphContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubgraph(this);
}


std::any FlowscriptGrammarParser::SubgraphContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FlowscriptGrammarVisitor*>(visitor))
    return parserVisitor->visitSubgraph(this);
  else
    return visitor->visitChildren(this);
}

FlowscriptGrammarParser::SubgraphContext* FlowscriptGrammarParser::subgraph() {
  SubgraphContext *_localctx = _tracker.createInstance<SubgraphContext>(_ctx, getState());
  enterRule(_localctx, 4, FlowscriptGrammarParser::RuleSubgraph);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    match(FlowscriptGrammarParser::SUBGRAPH);
    setState(31);
    match(FlowscriptGrammarParser::ID);
    setState(32);
    match(FlowscriptGrammarParser::T__0);
    setState(33);
    subgraph_content();
    setState(34);
    match(FlowscriptGrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Subgraph_contentContext ------------------------------------------------------------------

FlowscriptGrammarParser::Subgraph_contentContext::Subgraph_contentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FlowscriptGrammarParser::Label_statementContext *> FlowscriptGrammarParser::Subgraph_contentContext::label_statement() {
  return getRuleContexts<FlowscriptGrammarParser::Label_statementContext>();
}

FlowscriptGrammarParser::Label_statementContext* FlowscriptGrammarParser::Subgraph_contentContext::label_statement(size_t i) {
  return getRuleContext<FlowscriptGrammarParser::Label_statementContext>(i);
}

std::vector<FlowscriptGrammarParser::Node_definitionContext *> FlowscriptGrammarParser::Subgraph_contentContext::node_definition() {
  return getRuleContexts<FlowscriptGrammarParser::Node_definitionContext>();
}

FlowscriptGrammarParser::Node_definitionContext* FlowscriptGrammarParser::Subgraph_contentContext::node_definition(size_t i) {
  return getRuleContext<FlowscriptGrammarParser::Node_definitionContext>(i);
}


size_t FlowscriptGrammarParser::Subgraph_contentContext::getRuleIndex() const {
  return FlowscriptGrammarParser::RuleSubgraph_content;
}

void FlowscriptGrammarParser::Subgraph_contentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubgraph_content(this);
}

void FlowscriptGrammarParser::Subgraph_contentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubgraph_content(this);
}


std::any FlowscriptGrammarParser::Subgraph_contentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FlowscriptGrammarVisitor*>(visitor))
    return parserVisitor->visitSubgraph_content(this);
  else
    return visitor->visitChildren(this);
}

FlowscriptGrammarParser::Subgraph_contentContext* FlowscriptGrammarParser::subgraph_content() {
  Subgraph_contentContext *_localctx = _tracker.createInstance<Subgraph_contentContext>(_ctx, getState());
  enterRule(_localctx, 6, FlowscriptGrammarParser::RuleSubgraph_content);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FlowscriptGrammarParser::LABEL

    || _la == FlowscriptGrammarParser::ID) {
      setState(38);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case FlowscriptGrammarParser::LABEL: {
          setState(36);
          label_statement();
          break;
        }

        case FlowscriptGrammarParser::ID: {
          setState(37);
          node_definition();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(42);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Label_statementContext ------------------------------------------------------------------

FlowscriptGrammarParser::Label_statementContext::Label_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FlowscriptGrammarParser::Label_statementContext::LABEL() {
  return getToken(FlowscriptGrammarParser::LABEL, 0);
}

tree::TerminalNode* FlowscriptGrammarParser::Label_statementContext::STRING() {
  return getToken(FlowscriptGrammarParser::STRING, 0);
}


size_t FlowscriptGrammarParser::Label_statementContext::getRuleIndex() const {
  return FlowscriptGrammarParser::RuleLabel_statement;
}

void FlowscriptGrammarParser::Label_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabel_statement(this);
}

void FlowscriptGrammarParser::Label_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabel_statement(this);
}


std::any FlowscriptGrammarParser::Label_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FlowscriptGrammarVisitor*>(visitor))
    return parserVisitor->visitLabel_statement(this);
  else
    return visitor->visitChildren(this);
}

FlowscriptGrammarParser::Label_statementContext* FlowscriptGrammarParser::label_statement() {
  Label_statementContext *_localctx = _tracker.createInstance<Label_statementContext>(_ctx, getState());
  enterRule(_localctx, 8, FlowscriptGrammarParser::RuleLabel_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(43);
    match(FlowscriptGrammarParser::LABEL);
    setState(44);
    match(FlowscriptGrammarParser::T__2);
    setState(45);
    match(FlowscriptGrammarParser::STRING);
    setState(46);
    match(FlowscriptGrammarParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Node_definitionContext ------------------------------------------------------------------

FlowscriptGrammarParser::Node_definitionContext::Node_definitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FlowscriptGrammarParser::Node_definitionContext::ID() {
  return getToken(FlowscriptGrammarParser::ID, 0);
}

tree::TerminalNode* FlowscriptGrammarParser::Node_definitionContext::LABEL() {
  return getToken(FlowscriptGrammarParser::LABEL, 0);
}

tree::TerminalNode* FlowscriptGrammarParser::Node_definitionContext::STRING() {
  return getToken(FlowscriptGrammarParser::STRING, 0);
}


size_t FlowscriptGrammarParser::Node_definitionContext::getRuleIndex() const {
  return FlowscriptGrammarParser::RuleNode_definition;
}

void FlowscriptGrammarParser::Node_definitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNode_definition(this);
}

void FlowscriptGrammarParser::Node_definitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNode_definition(this);
}


std::any FlowscriptGrammarParser::Node_definitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FlowscriptGrammarVisitor*>(visitor))
    return parserVisitor->visitNode_definition(this);
  else
    return visitor->visitChildren(this);
}

FlowscriptGrammarParser::Node_definitionContext* FlowscriptGrammarParser::node_definition() {
  Node_definitionContext *_localctx = _tracker.createInstance<Node_definitionContext>(_ctx, getState());
  enterRule(_localctx, 10, FlowscriptGrammarParser::RuleNode_definition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    match(FlowscriptGrammarParser::ID);
    setState(49);
    match(FlowscriptGrammarParser::T__4);
    setState(50);
    match(FlowscriptGrammarParser::LABEL);
    setState(51);
    match(FlowscriptGrammarParser::T__2);
    setState(52);
    match(FlowscriptGrammarParser::STRING);
    setState(53);
    match(FlowscriptGrammarParser::T__5);
    setState(54);
    match(FlowscriptGrammarParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Edge_definitionContext ------------------------------------------------------------------

FlowscriptGrammarParser::Edge_definitionContext::Edge_definitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> FlowscriptGrammarParser::Edge_definitionContext::ID() {
  return getTokens(FlowscriptGrammarParser::ID);
}

tree::TerminalNode* FlowscriptGrammarParser::Edge_definitionContext::ID(size_t i) {
  return getToken(FlowscriptGrammarParser::ID, i);
}

FlowscriptGrammarParser::Edge_labelContext* FlowscriptGrammarParser::Edge_definitionContext::edge_label() {
  return getRuleContext<FlowscriptGrammarParser::Edge_labelContext>(0);
}


size_t FlowscriptGrammarParser::Edge_definitionContext::getRuleIndex() const {
  return FlowscriptGrammarParser::RuleEdge_definition;
}

void FlowscriptGrammarParser::Edge_definitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdge_definition(this);
}

void FlowscriptGrammarParser::Edge_definitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdge_definition(this);
}


std::any FlowscriptGrammarParser::Edge_definitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FlowscriptGrammarVisitor*>(visitor))
    return parserVisitor->visitEdge_definition(this);
  else
    return visitor->visitChildren(this);
}

FlowscriptGrammarParser::Edge_definitionContext* FlowscriptGrammarParser::edge_definition() {
  Edge_definitionContext *_localctx = _tracker.createInstance<Edge_definitionContext>(_ctx, getState());
  enterRule(_localctx, 12, FlowscriptGrammarParser::RuleEdge_definition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(FlowscriptGrammarParser::ID);
    setState(57);
    match(FlowscriptGrammarParser::T__6);
    setState(58);
    match(FlowscriptGrammarParser::ID);
    setState(60);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == FlowscriptGrammarParser::T__4) {
      setState(59);
      edge_label();
    }
    setState(62);
    match(FlowscriptGrammarParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Edge_labelContext ------------------------------------------------------------------

FlowscriptGrammarParser::Edge_labelContext::Edge_labelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FlowscriptGrammarParser::Edge_labelContext::LABEL() {
  return getToken(FlowscriptGrammarParser::LABEL, 0);
}

tree::TerminalNode* FlowscriptGrammarParser::Edge_labelContext::STRING() {
  return getToken(FlowscriptGrammarParser::STRING, 0);
}


size_t FlowscriptGrammarParser::Edge_labelContext::getRuleIndex() const {
  return FlowscriptGrammarParser::RuleEdge_label;
}

void FlowscriptGrammarParser::Edge_labelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEdge_label(this);
}

void FlowscriptGrammarParser::Edge_labelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<FlowscriptGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEdge_label(this);
}


std::any FlowscriptGrammarParser::Edge_labelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FlowscriptGrammarVisitor*>(visitor))
    return parserVisitor->visitEdge_label(this);
  else
    return visitor->visitChildren(this);
}

FlowscriptGrammarParser::Edge_labelContext* FlowscriptGrammarParser::edge_label() {
  Edge_labelContext *_localctx = _tracker.createInstance<Edge_labelContext>(_ctx, getState());
  enterRule(_localctx, 14, FlowscriptGrammarParser::RuleEdge_label);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    match(FlowscriptGrammarParser::T__4);
    setState(65);
    match(FlowscriptGrammarParser::LABEL);
    setState(66);
    match(FlowscriptGrammarParser::T__2);
    setState(67);
    match(FlowscriptGrammarParser::STRING);
    setState(68);
    match(FlowscriptGrammarParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void FlowscriptGrammarParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  flowscriptgrammarParserInitialize();
#else
  ::antlr4::internal::call_once(flowscriptgrammarParserOnceFlag, flowscriptgrammarParserInitialize);
#endif
}
