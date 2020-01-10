all: 
	g++ -std=c++11 -o htable src/htable.cpp 
	g++ -std=c++11  -o generator src/generator.cpp 
clean:
	rm htable
	rm generator