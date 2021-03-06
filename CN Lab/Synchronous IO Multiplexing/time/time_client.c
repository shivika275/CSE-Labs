// ...

/**
 *	TCP from client side
 *	socket() -> connect() -> read() -> write()
 */

#include "common.h"

void commit_suicide(string message) {
	perror(message);
	exit(7);
}

int main (int argc, char const * argv []) {
	
	sockaddr_in_t server_address;
	
	int sockfd, i;
	socklen_t slen = sizeof(server_address);
	
	char buffer[BUFLEN];
	int ch;
	
	// create a TCP server
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		commit_suicide("socket()");
	}
	// zero out the structure
	memset((char *)&server_address, 0, slen);
	
	// set family and port
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = inet_addr(SERVER);
	
	// get address
	if (connect(sockfd, (sockaddr_p_t)&server_address, slen) < 0) {
		commit_suicide("connect()");
	}

	int pid = fork();
	if (pid == 0) {

		printf("Enter 'time' for time: ");
		while (YES) {
			scanf(" %s", buffer);

			if (strcmp(buffer, "time") != 0) {
				commit_suicide("Quitting...");
				exit(-1);
			}
			send(sockfd, buffer, BUFLEN, 0);
		}

	} else {

		while (YES) {
			if (recv(sockfd, buffer, BUFLEN, 0) != -1) {
				printf("Server said: %s\n", buffer);
			}
		}

	}

	return 0;
}