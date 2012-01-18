
build_gnu:
	g++ -std=c++0x -o ipvx IPV4Address.cpp main.cpp

default: build_gnu
