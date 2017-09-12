arithmeticTree.exe	:	arithmeticTree.o
	g++ arithmeticTree.o -std=c++11 -o arithmeticTree.exe

arithmeticTree.o	:	arithmeticTree.cpp arithmeticTree.h
	g++ -std=c++11 -c arithmeticTree.cpp
	