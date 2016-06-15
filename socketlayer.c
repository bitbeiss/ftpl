/*
 * AUTHOR: Clemens J. Zuzan
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * YEAR: 2016
 * COMPILE: make all
 *
 * socketlayer.c
 *
 *  Created on: 08. Juni 2016
 *      Author: clemens
 */

#include "socketlayer.h"

void error_exit(char *error_message) {
	fprintf(stderr, "%s: %s\n", error_message, strerror(errno));
	exit(EXIT_FAILURE);
}


//Serverseite Funktionen

int create_socket (int af, int type, int protocol){
	socket_t sock;
	const int y=1;
	sock=socket(af, type, protocol);
	if (sock <0) {
		error_exit(SOCKET_CREATION_ERROR_MESSAGE);
	}
	setsockopt( sock, SOL_SOCKET,
				SO_REUSEADDR, &y, sizeof(int));
	return sock;
}

void bind_socket(socket_t *sock, unsigned long address,
					unsigned short port) {
	struct sockaddr_in server;
	memset (&server,0,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(address); //konvertieren zu Netzwerk Byteorder
	server.sin_port = htons(port);
	if ( bind(*sock, (struct sockaddr*) &server, sizeof(server)) < 0) {
		error_exit(SOCKET_BINDING_ERROR_MESSAGE);
	}
}

void listen_socket( socket_t *sock ) {
	if( listen(*sock, 5) == -1 ) //5 ist Hinweis auf groesse der Listen-queue
		error_exit(SOCKET_LISTEN_ERROR_MESSAGE);
}

void accept_socket( socket_t *socket, socket_t *new_socket ){
					struct sockaddr_in client;
	unsigned int len;
	len = sizeof(client);
	*new_socket = accept(*socket,(struct sockaddr *) &client, & len);
	if (*new_socket == -1) {
		error_exit(SOCKET_ACCEPT_ERROR_MESSAGE);
	}
}

//Clientseite Funktionen

void connect_socket(socket_t *sock, char *serv_addr,
						unsigned short port) {
	struct sockaddr_in server;
	struct hostent *host_info;
	unsigned long addr;

	//Server Daten Struktur mit 0en initialisieren.
	memset( &server, 0, sizeof (server) );
	//server IP string in unsigned long wandeln
	if ( (addr = inet_addr( serv_addr) ) != INADDR_NONE ) {
		memcpy( (char *) &server.sin_addr, &addr, sizeof(addr));
	}
	else {
		//ggf. name zu IP aufloesen
		host_info = gethostbyname( serv_addr );
		if (NULL == host_info) {
			error_exit(SOCKET_SERVER_UNKNOWN_ERROR_MESSAGE);
		}
	memcpy( (char *) &server.sin_addr, host_info->h_addr,
			host_info->h_length);

	}
	server.sin_family = AF_INET;
	server.sin_port = htons (port);
	if (connect(
			*sock, (struct sockaddr *) &server, sizeof( server )) < 0) {
				error_exit(SOCKET_NO_CONNECTION_ERROR_MESSAGE);
			}
}

// Funktionen fuer Client und Sever

void TCP_send( socket_t *sock, char *data, size_t size) {
	if(send( *sock, data, size, 0) == -1) {
		error_exit(SOCKET_SEND_ERROR_MESSAGE);
	}
}

void TCP_recv (socket_t *sock, char *data, size_t size) {
	unsigned int len;
	len = recv (*sock, data, size, 0);
	if (len > 0 || len != -1 ) {
		data[len] = '\0';
	}
	else {
		error_exit(SOCKET_RECV_ERROR_MESSAGE);
	}
}

void close_socket(socket_t *sock ) {
	close(*sock);
}

void cleanup(void) {
	printf (SOCKET_CLEANUP_READY_MESSAGE);
}





