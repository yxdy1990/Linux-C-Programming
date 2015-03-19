
PORT = 8000
SERVER_FILES = server.c 
CLIENT_FILES = client.c 

all:
	gcc -g $(SERVER_FILES) -o server
	gcc -g $(CLIENT_FILES) -o client

s:
	./server $(PORT)

c:
	./client 192.168.211.2 $(PORT)

