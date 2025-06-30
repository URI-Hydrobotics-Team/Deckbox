#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h> //include fentanyl


#include "config.h"
#include "connections.h"
#include "controller.h"
#include "vt100.h"
/* AUV HUB */

/* 
	message buffer
	holds all recieved messages and prints them in a certian location
*/

char msgBuffer[MSG_BUFF_SIZE];
std::string status_string;

/* device definitions */
auv_rx_socket input_hub, input_controller_backend; 
auv_tx_socket output_hub, output_log;
//controller_t test_controller; // new controller



void initDevices(){
	
	input_hub.init(HUB_IP, HUB_PORT_RX, MULTICASTGROUP); // setup hub socket
	input_controller_backend.init(CONTROLLER_BACKEND_IP, CONTROLLER_BACKEND_PORT_RX, MULTICASTGROUP);
	//test_controller.setDevice("/dev/input/js0"); //defaults to "/dev/input/js0"
	//test_controller.init();


	//test_controller.poll();


	std::cout << "Devices Initialized\n";
}

void readFromDevices(){
	
	
	if (input_hub.probe() > 0){
		input_hub.rec(1); // rec. data from hub socket
	}

	if (input_controller_backend.probe() > 0){


		input_controller_backend.rec(1); //rec. data from controller backend
	}

}

void printMessages(){
	


}

void addMessage(char *msg){

}



void printElements(){

	vtGoto(1,1);
	std::cout << "DeckBox-CLI version: " << version_string << "\n";
	
	vtGoto(40,1);
	std::cout << "STATUS >>>" << status_string << "\n";
	vtGoto(1,2);
	std::cout << "--- MESSAGE CENTER ---\n";
	vtGoto(1,3);
	std::cout << "[INTERNAL]\n";
	vtGoto(1,27);
	std::cout << "[EXTERNAL]\n";

}

/*function declerations */


void printHelp(){
	std::cout << "DeckBox-CLI version: " << version_string << "\n";
	std::cout << "\nUSAGE:";
	std::cout << "\t\tdeckbox-cli <mode> <arguments>\n"; 
		
	std::cout << "\tModes: help, listen\n";
	std::cout << "\t[Listen] arguments: <controller (/dev/input/js*)>\n";	




}




void listen(){ 
	
	vtClear();	
	/* 
		Main function for defining which sockets to listen to
	*/
	initDevices();
	printElements();	
		/* Initialize controller input */
		while (1){	
		/* loop for testing */
			readFromDevices();

		}
	//do other things

    	vtClear(); //clear screen
	


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
