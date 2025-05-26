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

#include "config.h"



void printHelp(){
	std::cout << "DeckBox-CLI version: " << version_string << "\n";
	std::cout << "\nUSAGE:\n";
	std::cout << "\t\tdeckbox-cli <mode> <arguments>\n"; 
	
	std::cout << "\tModes: help, listen\n";
	std::cout << "\tListen Arguments: <ip>\n";	




}


void listen(){
	std::cout << "DeckBox-CLI version: " << version_string << "\n";
		
	


    	printf("\033[H\033[J"); //clear screen
	listen();
}



int main(int argc, char *argv[]){
	
	std::string mode, arg1, arg2;
	if (argv[1] != NULL){
		mode = argv[1];
	}

	if (argv[2] != NULL){
		arg1 = argv[2];
	}
	if (argv[3] != NULL){
		arg2 = argv[3];
	}

	//display help
	if (mode == "help"){
		printHelp();
	}
	//display help
	if (mode == "listen"){
		listen();
	}


	return 0;
}
