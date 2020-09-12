all: client server

client: client.cpp
	g++ -O3 $^ -o $@

server: server.cpp
	g++ -O3 $^ -o $@

clean: server client
	rm $^ 
