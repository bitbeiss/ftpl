/*
 * AUTHOR: Clemens J. Zuzan
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * YEAR: 2016
 * COMPILE: make all
 * ftp_server.c
 *
 *  Created on: 09. Juni 2016
 *      Author: clemens
 */

#include "socketlayer.h"
#define BUF (1024)

typedef struct Packet{
		size_t length;
		void *data;
	} packet;


int main(int argc, char *argv[]){
	socket_t sock1, sock2;
	int addrlen;

	int status;
	char cwd[1000]="\0";
	char cmd_buffer[BUF]="\0";

	sock1 = create_socket(AF_INET, SOCK_STREAM, 0);
	atexit(cleanup);
	bind_socket ( &sock1, INADDR_ANY, 15000 );
	listen_socket (&sock1);
	addrlen = sizeof(struct sockaddr_in);

	while(1) {
		accept_socket( &sock1, &sock2);
		do {
			TCP_recv (&sock2, cmd_buffer,BUF-1);
			printf("Received cmd: %s",cmd_buffer);

			TCP_send (&sock2, FTP_STATUS_OK, sizeof(FTP_STATUS_OK) );

			//switch je nachdem welches kommando empfangen wurde....


		} while (strcmp((char *) cmd_buffer, "quit\n") !=0);
	}

	return EXIT_SUCCESS;
}
