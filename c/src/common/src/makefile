all:server client tcp_server tcp_client

server:server.c iolib.c
	gcc -g server.c iolib.c -o $@
client:client.c iolib.o
	gcc -g client.c iolib.o -o $@
iolib.o: iolib.c
	gcc -g -c iolib.c

tcp_server:tcp_server.c
	gcc -g tcp_server.c -o $@
tcp_client:tcp_client.c
	gcc -g tcp_client.c -o $@

clean:
	rm -rf server client tcp_server tcp_client *.o
