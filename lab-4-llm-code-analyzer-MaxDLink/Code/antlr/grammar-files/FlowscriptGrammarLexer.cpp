
// Generated from FlowscriptGrammar.g4 by ANTLR 4.13.1


#include "FlowscriptGrammarLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct FlowscriptGrammarLexerStaticData final {
  FlowscriptGrammarLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  FlowscriptGrammarLexerStaticData(const FlowscriptGrammarLexerStaticData&) = delete;
  FlowscriptGrammarLexerStaticData(FlowscriptGrammarLexerStaticData&&) = delete;
  FlowscriptGrammarLexerStaticData& operator=(const FlowscriptGrammarLexerStaticData&) = delete;
  FlowscriptGrammarLexerStaticData& operator=(FlowscriptGrammarLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag flowscriptgrammarlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
FlowscriptGrammarLexerStaticData *flowscriptgrammarlexerLexerStaticData = nullptr;

void flowscriptgrammarlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (flowscriptgrammarlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(flowscriptgrammarlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<FlowscriptGrammarLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "DIGRAPH", 
      "SUBGRAPH", "LABEL", "ID", "STRING", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,13,90,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,1,0,1,1,1,
  	1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	10,1,10,5,10,68,8,10,10,10,12,10,71,9,10,1,11,1,11,1,11,1,11,5,11,77,
  	8,11,10,11,12,11,80,9,11,1,11,1,11,1,12,4,12,85,8,12,11,12,12,12,86,1,
  	12,1,12,0,0,13,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,
  	12,25,13,1,0,4,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,4,
  	0,10,10,13,13,34,34,92,92,3,0,9,10,13,13,32,32,93,0,1,1,0,0,0,0,3,1,0,
  	0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,
  	1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,
  	0,0,1,27,1,0,0,0,3,29,1,0,0,0,5,31,1,0,0,0,7,33,1,0,0,0,9,35,1,0,0,0,
  	11,37,1,0,0,0,13,39,1,0,0,0,15,42,1,0,0,0,17,50,1,0,0,0,19,59,1,0,0,0,
  	21,65,1,0,0,0,23,72,1,0,0,0,25,84,1,0,0,0,27,28,5,123,0,0,28,2,1,0,0,
  	0,29,30,5,125,0,0,30,4,1,0,0,0,31,32,5,61,0,0,32,6,1,0,0,0,33,34,5,59,
  	0,0,34,8,1,0,0,0,35,36,5,91,0,0,36,10,1,0,0,0,37,38,5,93,0,0,38,12,1,
  	0,0,0,39,40,5,45,0,0,40,41,5,62,0,0,41,14,1,0,0,0,42,43,5,100,0,0,43,
  	44,5,105,0,0,44,45,5,103,0,0,45,46,5,114,0,0,46,47,5,97,0,0,47,48,5,112,
  	0,0,48,49,5,104,0,0,49,16,1,0,0,0,50,51,5,115,0,0,51,52,5,117,0,0,52,
  	53,5,98,0,0,53,54,5,103,0,0,54,55,5,114,0,0,55,56,5,97,0,0,56,57,5,112,
  	0,0,57,58,5,104,0,0,58,18,1,0,0,0,59,60,5,108,0,0,60,61,5,97,0,0,61,62,
  	5,98,0,0,62,63,5,101,0,0,63,64,5,108,0,0,64,20,1,0,0,0,65,69,7,0,0,0,
  	66,68,7,1,0,0,67,66,1,0,0,0,68,71,1,0,0,0,69,67,1,0,0,0,69,70,1,0,0,0,
  	70,22,1,0,0,0,71,69,1,0,0,0,72,78,5,34,0,0,73,77,8,2,0,0,74,75,5,92,0,
  	0,75,77,9,0,0,0,76,73,1,0,0,0,76,74,1,0,0,0,77,80,1,0,0,0,78,76,1,0,0,
  	0,78,79,1,0,0,0,79,81,1,0,0,0,80,78,1,0,0,0,81,82,5,34,0,0,82,24,1,0,
  	0,0,83,85,7,3,0,0,84,83,1,0,0,0,85,86,1,0,0,0,86,84,1,0,0,0,86,87,1,0,
  	0,0,87,88,1,0,0,0,88,89,6,12,0,0,89,26,1,0,0,0,5,0,69,76,78,86,1,6,0,
  	0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  flowscriptgrammarlexerLexerStaticData = staticData.release();
}

}

FlowscriptGrammarLexer::FlowscriptGrammarLexer(CharStream *input) : Lexer(input) {
  FlowscriptGrammarLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *flowscriptgrammarlexerLexerStaticData->atn, flowscriptgrammarlexerLexerStaticData->decisionToDFA, flowscriptgrammarlexerLexerStaticData->sharedContextCache);
}

FlowscriptGrammarLexer::~FlowscriptGrammarLexer() {
  delete _interpreter;
}

std::string FlowscriptGrammarLexer::getGrammarFileName() const {
  return "FlowscriptGrammar.g4";
}

const std::vector<std::string>& FlowscriptGrammarLexer::getRuleNames() const {
  return flowscriptgrammarlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& FlowscriptGrammarLexer::getChannelNames() const {
  return flowscriptgrammarlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& FlowscriptGrammarLexer::getModeNames() const {
  return flowscriptgrammarlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& FlowscriptGrammarLexer::getVocabulary() const {
  return flowscriptgrammarlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView FlowscriptGrammarLexer::getSerializedATN() const {
  return flowscriptgrammarlexerLexerStaticData->serializedATN;
}

const atn::ATN& FlowscriptGrammarLexer::getATN() const {
  return *flowscriptgrammarlexerLexerStaticData->atn;
}




void FlowscriptGrammarLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  flowscriptgrammarlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(flowscriptgrammarlexerLexerOnceFlag, flowscriptgrammarlexerLexerInitialize);
#endif
}
