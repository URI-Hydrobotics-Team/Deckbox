#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h> //include fentanyl



/*
	Socket device setup 

*/


char rx_buffer[256];


/* for hub connection */
	struct sockaddr_in my_addr;	/* our address */
	struct sockaddr_in remote_addr;	/* remote address */
	socklen_t addrlen = sizeof(remote_addr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;				/* the socket */


void hubSocketRec(){

	/* Function for recieving from AUV HUB*/
	
	recvlen = recvfrom(fd,rx_buffer, 256, 0, (struct sockaddr *)&remote_addr, &addrlen);
	if (recvlen > 0) {
		/* 
		define how the message is handled 
		we would like to have a "message box" in the interface where raw message data is put
		*/
		printf("received %d bytes\n", recvlen);
		rx_buffer[recvlen] = 0;
		printf("received message: \"%s\"\n",rx_buffer);
	}

	shutdown(fd, 2);
	usleep(100000); //sleep for 100ms

	//hubSocketRec(); // recursive call for testing
}



void hubSocketInit(char *host, int port){
	//TODO move to another file
	/* Initialize a socket */
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	//set fd to non blocking
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	memset((char *)&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	//my_addr.sin_addr.s_addr = htonl(std::stoi(host));
	//TODO allow user to select ip
	my_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	my_addr.sin_port = htons(port);
	if (bind(fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
		//std::cout << "bind to " << host ":" << port << "failed\n";
		std::cout << "failed to bind socket\n";
	}

	std::cout << "HUB Socket Initialized\n";
}

