all:
		gcc server.c -o server.o
server.o:
		gcc client.c -o client.o
clean:
		rm -f server.o
		rm -f client.o
