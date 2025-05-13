build:
	g++ -o client client.cpp -lws2_32
	g++ -o server server.cpp -lws2_32