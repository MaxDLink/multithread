CXXFLAGS=-std=c++11  # Or c++14, c++17, etc.
compile: libLinux buildLinux

libLinux: 
	clang++ $(CXXFLAGS) -shared -o ./Code/lib/libjobsystem.so -fPIC -I./Code/lib ./Code/lib/*.cpp 

buildLinux: 
	clang++ $(CXXFLAGS) -o program ./Code/main.cpp ./Code/factory.cpp ./Code/JobSystemAPI.cpp ./Code/customjob.cpp -L./Code/lib -ljobsystem

run: 
	./program

automated: 
	clang++ -g -std=c++14 ./test-code/*.cpp -o test-output
	./test-output

