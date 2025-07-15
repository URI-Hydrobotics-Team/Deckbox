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
#include "controller_maps/sixaxis.h"
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



controller_t test_controller; // new controller
controller_generic_raw sixaxis_raw; // new virtual raw device

controller_generic_profile deckbox_input;

int autopilot = 0;


void initDevices(){
	
	input_hub.init(HUB_IP, HUB_PORT_RX, MULTICASTGROUP); // setup hub socket
	//input_controller_backend.init(CONTROLLER_BACKEND_IP, CONTROLLER_BACKEND_PORT_RX, MULTICASTGROUP);
	test_controller.setDevice("/dev/input/js0");
	test_controller.init();



	std::cout << "Devices Initialized\n";
}

void readFromDevices(){
	
	
	if (input_hub.probe() > 0){
		input_hub.rec(1); // rec. data from hub socket
	}
	test_controller.poll(&sixaxis_raw);
	convertToSixaxis(&deckbox_input, sixaxis_raw);
	//sixaxis_raw.print();
	/*
	if (input_controller_backend.probe() > 0){


		input_controller_backend.rec(1); //rec. data from controller backend
	}

	*/

}

void printElements(){

	//vtGoto(1,1);
	std::cout << "DeckBox-CLI version: " << version_string << "\n";
	/* controller input*/

	std::cout << "--- CONTROL STAUS ---\n";
	if (autopilot){
		std::cout << "\tControl Scheme: AUTOMATIC\n";
	}else{

		std::cout << "\tControl Scheme: MANUAL\n";
	}
	
	std::cout << "\tButtons:\n";
	std::cout << "\t\tButton 1: " << deckbox_input.fc_1 << '\n';
	std::cout << "\t\tButton 2: " << deckbox_input.fc_2 << '\n';
	std::cout << "\t\tButton 3: " << deckbox_input.fc_3 << '\n';
	std::cout << "\t\tButton 4: " << deckbox_input.fc_4 << '\n';

	std::cout << "\t\tD-Pad Up: " << deckbox_input.dp_up << '\n';	
	std::cout << "\t\tD-Pad Down: " << deckbox_input.dp_down << '\n';
	std::cout << "\t\tD-Pad Left: " << deckbox_input.dp_left << '\n';
	std::cout << "\t\tD-Pad Right: " << deckbox_input.dp_right << '\n';

	std::cout << "\t\tLT1: " << deckbox_input.lt << '\n';
	std::cout << "\t\tRT1: " << deckbox_input.rt << '\n';

	std::cout << "\t\tLT2: " << deckbox_input.lt_a << '\n';
	std::cout << "\t\tRT2: " << deckbox_input.rt_a << '\n';

	std::cout << "\t\tStart: " << deckbox_input.start << '\n';
	std::cout << "\t\tSelect: " << deckbox_input.select << '\n';
	std::cout << "\t\tSuper: " << deckbox_input.super << '\n';

	std::cout << "\tSticks:\n";

	std::cout << "\t\tLeft Click: " << deckbox_input.sc_left << '\n';
	std::cout << "\t\tRight Click: " << deckbox_input.sc_right << '\n';

	std::cout << "\t\tLeft: " << deckbox_input.sll_x << ' ' << deckbox_input.sll_y << '\n';
	std::cout << "\t\tRight: " << deckbox_input.slr_x << ' ' << deckbox_input.slr_y << '\n';

	std::cout << "\n--- MESSAGE CENTER ---\n";
	sixaxis_raw.print();
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
			vtClear();
			readFromDevices();
			printElements();

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
