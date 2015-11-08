SOURCE = genetic.cpp


all: $(SOURCE)
	g++ -o genetic $(SOURCE) -std=c++11