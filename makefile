ifeq ($(OS),Windows_NT)
	flag := -lws2_32
endif

build:
	g++ -o client client.cpp $(flag)
	g++ -o server server.cpp $(flag)
