all:server client tcp_server tcp_client udp_server udp_client udp_connect_client

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
udp_server:udp_server.c
	gcc -g udp_server.c -o $@
udp_client:udp_client.c
	gcc -g udp_client.c -o $@
nonblock_udp_server:nonblock_udp_server.c
	gcc -g nonblock_udp_server.c -o $@
nonblock_udp_client:nonblock_udp_client.c
	gcc -g nonblock_udp_client.c -o $@
udp_connect_client:udp_connect_client.c iolib.o
	gcc -g udp_connect_client.c iolib.o -o $@

unix_sock_server:unix_sock_server.c
	gcc -g unix_sock_server.c -o $@
unix_sock_client:unix_sock_client.c
	gcc -g unix_sock_client.c -o $@

clean:
	rm -rf server client tcp_server tcp_client udp_server udp_client nonblock_udp_server nonblock_udp_client *.o udp_connect_client
	rm -rf unix_sock_server unix_sock_client
