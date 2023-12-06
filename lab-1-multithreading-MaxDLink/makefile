#TODO - make this makefile dynamic so that it can take as many test-set-# files as the user needs 
#TODO - can the testing code "test-set-one" and "test-set-two" be treated as two different executables in the makefile??? or should they be one exec? 
compile: 
	clang++ -g -std=c++14 ./Code/*.cpp -o output
	./output

automated: 
	clang++ -g -std=c++14 ./test-code/*.cpp -o test-output
	./test-output

	