CXXFLAGS=-std=c++17
ANTLR_INCLUDE_DIR=/usr/local/include/antlr4-runtime
ANTLR_LIB_DIR=/usr/local/lib

CXXFLAGS += -I$(ANTLR_INCLUDE_DIR) -I./Code

compile: libLinux buildLinux

libLinux: 
	clang++ $(CXXFLAGS) -shared -o ./Code/lib/libjobsystem.so -fPIC -I./Code/lib -I$(ANTLR_INCLUDE_DIR) ./Code/lib/*.cpp 

buildLinux: 
	clang++ $(CXXFLAGS) -o program ./Code/main.cpp ./Code/interpreter.cpp ./Code/factory.cpp ./Code/antlr/grammar-files/FlowscriptGrammarLexer.cpp ./Code/customerrorlistener.cpp ./Code/antlr/grammar-files/FlowscriptGrammarParser.cpp ./Code/JobSystemAPI.cpp ./Code/customjob.cpp ./Code/customvisitor.cpp -I$(ANTLR_INCLUDE_DIR) -L./Code/lib -L$(ANTLR_LIB_DIR) -ljobsystem -lantlr4-runtime

run: 
	DYLD_LIBRARY_PATH=/usr/local/lib ./program

automated: 
	clang++ -g -std=c++14 -I$(ANTLR_INCLUDE_DIR) ./test-code/*.cpp -o test-output -L$(ANTLR_LIB_DIR) -lantlr4-runtime
	./test-output

antlr: 
	antlr4 -Dlanguage=Cpp -visitor -listener -o ../Code/antlr/grammar-files FlowscriptGrammar.g4
	# must: cd ./Data first and run from Data dir to avoid making a copy data dir in grammar-files dir
