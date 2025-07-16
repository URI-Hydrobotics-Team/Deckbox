#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h> //include fentanyl
#include <bits/stdc++.h>

#include "config.h"
#include "connections.h"
#include "controller.h"
#include "controller_maps/sixaxis.h"
#include "controller_maps/f710.h"
#include "vt100.h"
/* AUV HUB */

/* 
	message buffer:
	holds all recieved messages and prints them in a certian location
	input buffer:
	holds current controller input
*/

std::string status_string;


std::string input_string;
char inputBuffer[256];
char inputTemp[128];



/* device definitions */
auv_rx_socket input_hub, input_controller_backend; 
auv_tx_socket output_hub, output_log;



controller_t test_controller; // new controller
controller_generic_raw sixaxis_raw; // new virtual raw device

controller_generic_raw f710_raw; // new virtual raw device
controller_generic_profile deckbox_input;


/* variables of interest */

float pressure, temperature, depth, altitude;

int autopilot = 0;


void sendInputData(){

	/* send input buffer to AUV */
	
	input_string = "";
	input_string += "!DBX CTL ";
	fillControllerBuffer(deckbox_input, inputTemp, 128);
	input_string += inputTemp;
	strncpy(inputBuffer, input_string.c_str(), 256);
	output_hub.transmit(inputBuffer);
	usleep(1000);
}


void initDevices(){
	
	input_hub.init(HUB_PORT_RX); // setup hub socket
	output_hub.init(HUB_IP, HUB_PORT_TX);
	//input_controller_backend.init(CONTROLLER_BACKEND_IP, CONTROLLER_BACKEND_PORT_RX, MULTICASTGROUP);
	test_controller.setDevice("/dev/input/js0");
	test_controller.init();



	std::cout << "Devices Initialized\n";
}

void readFromDevices(){
	
	//causing slowdowns, needs to be addressed
	if (input_hub.probe() > 0){
		strncpy(inputBuffer, input_hub.rec(1), 256); // rec. data from hub socket
	}
	
	

	test_controller.poll(&f710_raw);
	convertToF710(&deckbox_input, f710_raw);
	//sixaxis_raw.print();
	usleep(1000);

}

void processInput(){
	/* process input_buffer contents */


	if (inputBuffer[0] == '!'){ //is legit

		//HUB STATUS PRESSURE
		if (inputBuffer[1] == 'H' &&
		    inputBuffer[2] == 'S' &&
	            inputBuffer[3] == 'P'){
			int index = 5;
			std::string press_str, temp_str, depth_str, alt_str;

			for (int i = 0; i < 4; i ++){
				while (inputBuffer[index] != ' '){
					if (i == 0){
						press_str += inputBuffer[index];
					}
					if (i == 1){
						temp_str += inputBuffer[index];
					}
					
					if (i == 2){
						depth_str += inputBuffer[index];
					}
				
					if (i == 3 && index < 32){
						alt_str += inputBuffer[index];
					}
					index++;
					
				}
				index++;

			}
			
			std::cout << press_str << ' ' << temp_str << ' ' << depth_str << ' ' << alt_str << '\n';
			pressure = std::stof(press_str);
			temperature = std::stof(temp_str);
			depth = std::stof(depth_str);
			//altitude = std::stof(alt_str);
			
		}




	}
	

	initStr(inputBuffer, 256);

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

	std::cout << "\n--- ONBOARD STATUS ---\n";
	std::cout << "Temperature: " << temperature << " degrees celsius\n";
	std::cout << "Pressure: " << pressure << " \n";
	std::cout << "Depth: " << depth << " \n";
	std::cout << "Altitude: " << altitude << " \n";
	std::cout << "\n--- MESSAGE CENTER ---\n";
	//sixaxis_raw.print();
	f710_raw.print();
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
			processInput();
			printElements();
			sendInputData();

		}
	//do other things

    	//vtClear(); //clear screen
	


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
