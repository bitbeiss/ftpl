/*
 * AUTHOR: Clemens J. Zuzan
 * REFERENCES: "C von A bis Z", Juergen Wolf
 * YEAR: 2016
 * COMPILE: make all
 * ftp_client.c
 *
 *  Created on: 09. Juni 2016
 *      Author: clemens
 */

#include "socketlayer.h"

#define BUF (1024)

void echo(char* arg, socket_t sock2){
	signed short status;

	//Kommando senden
	char kommando[]="echo";
	TCP_send (&sock2, kommando, sizeof(kommando));
	//Auf ok warten
	TCP_recv (&sock2, status, sizeof(status));
	if (status == FTP_STATUS_ERROR) {
		fprintf(stderr,"%s",FTP_STATUS_ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	//Auf Daten warten bzw. empfangen (ev. mit timeout)
	TCP_recv (&sock2, buffer, BUF-1);

}

void help(){
	fprintf(stderr,"%s",USAGE_MESSAGE_SERVER);
}

void ls(char* arg) {
}

void upload(){
	//Kommando senden (upload)
}


int main(int argc, char *argv[] ){
	socket_t sock;
	void *buffer = (void *)malloc (BUF);
	char cwd[1000]="\0";

	if (argc < 2) {
		printf("%s",USAGE_MESSAGE_CLIENT);
		exit(EXIT_FAILURE);
	}

	sock = create_socket(AF_INET, SOCK_STREAM,0);
	atexit(0);
	connect_socket(&sock,argv[1],15000);

	do {
		strcpy((char *) buffer,"\n");
		TCP_recv (&sock, buffer, BUF-1);
		printf("%s\n",(char *) buffer);
		printf("%s>",(char *) cwd);
		fgets(buffer, BUF, stdin);
		//ToDo: parse commands (fkt here)
		TCP_send(&sock, buffer, BUF);
	} while (strcmp((char *) buffer, "quit\n") != 0);
	close_socket(&sock);
	printf("Leaving the FTP client... bye!\n");
	return EXIT_SUCCESS;
}
