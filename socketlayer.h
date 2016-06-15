/*
 * AUTHOR: Clemens J. Zuzan
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * YEAR: 2016
 * COMPILE: make all
 * socketlayer.h
 *
 *  Created on: 09. Juni 2016
 *      Author: clemens
 */

#ifndef SOCKETPRX_H_
#define SOCKETPRX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define socket_t int

//Fehlermedlungen
#define SOCKET_CREATION_ERROR_MESSAGE		"Fehler beim Anlegen eines Sockets"
#define SOCKET_BINDING_ERROR_MESSAGE		"Kann das Socket nicht binden"
#define SOCKET_LISTEN_ERROR_MESSAGE			"Fehler beim Lauschen am Socket"
#define SOCKET_ACCEPT_ERROR_MESSAGE			"Fehler bei Socket accept"
#define SOCKET_SERVER_UNKNOWN_ERROR_MESSAGE	"Server unbekannt"
#define SOCKET_NO_CONNECTION_ERROR_MESSAGE	"Verbindung nicht herstellbar"
#define SOCKET_SEND_ERROR_MESSAGE			"Fehler bei send()"
#define SOCKET_RECV_ERROR_MESSAGE			"Fehler bei recv()"

#define FTP_STATUS_ERROR_MESSAGE			"FTP Kommunikationsstatus Fehler"

//Fehler Codes
#define SOCKET_CREATION_ERROR_NUMBER			1
#define SOCKET_BINDING_ERROR_NUMBER				2
#define SOCKET_LISTEN_ERROR_NUMBER 				3
#define SOCKET_ACCEPT_ERROR_NUMBER				4
#define SOCKET_SERVER_UNKNOWN_ERROR_NUMBER 		5
#define SOCKET_NO_CONNECTION_ERROR_NUMBER		6
#define SOCKET_SEND_ERROR_NUMBER				7
#define SOCKET_RECV_ERROR_NUMBER				8

//Status Meldungen SOCKET
#define SOCKET_CLEANUP_READY_MESSAGE		"Aufraeumen abgeschlossen.\n"

//Status Meldungen Client/Server
#define FTP_STATUS_OK 0
#define	FTP_STATUS_ERROR -1

//Usage Meldungen
#define USAGE_MESSAGE_SERVER 				"Kommandos: echo [Nachricht]\n help\n ls\n cd [.. | Verzeichnis]\nget [Dateiname]\n"
#define USAGE_MESSAGE_CLIENT 				"myftp ServerAdresse\n"

//Funktionsdeklarationen
void error_exit( char *error_messages );
int create_socket( int af, int type, int protocol );
void bind_socket ( socket_t *sock, unsigned long adress, unsigned short port);
void listen_socket (socket_t *sock);
void accept_socket (socket_t *new_socket, socket_t *socket );
void connect_socket(socket_t *sock, char *server_addr, unsigned short port);
void TCP_send ( socket_t *sock, char *data, size_t size );
void TCP_recv ( socket_t *sock, char *data, size_t size );
void close_socket( socket_t *sock);
void cleanup(void);

#endif


