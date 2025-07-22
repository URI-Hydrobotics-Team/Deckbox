#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h> //include fentanyl
#include <bits/stdc++.h>
#include <termios.h>


#include "config.h"
#include "keyboard.h"
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

keyboard_t kb;

/* variables of interest */

float pressure, temperature, depth, altitude; //pressure sensor
float eox, eoy, eoz, avx, avy, avz, acx, acy, acz, mfx, mfy, mfz, lax, lay, laz, gvx, gvy, gvz; //IMU

int sys_mode = 0;


void sendInputData(){

	/* send input buffer to AUV */
	
	input_string = "!DCI";
	fillControllerBuffer(deckbox_input, inputTemp, 128);
	input_string += inputTemp;
	strncpy(inputBuffer, input_string.c_str(), 256);
	output_hub.transmit(inputBuffer);
	usleep(1000);
	/* send sys_mode */

	input_string = "!DCM ";
	input_string += std::to_string(sys_mode);
	output_hub.transmit(input_string.c_str());
	usleep(1000);

}


void initDevices(){
	
	input_hub.init(HUB_PORT_RX); // setup hub socket
	output_hub.init(HUB_IP, HUB_PORT_TX);
	test_controller.setDevice("/dev/input/js0");
	test_controller.init();
	kb.init();


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
				
					if (i == 3 && index < 64){
						alt_str += inputBuffer[index];
					}
					index++;
					
				}
				index++;

			}
			
			//std::cout << press_str << ' ' << temp_str << ' ' << depth_str << ' ' << alt_str << '\n';
			pressure = std::stof(press_str);
			temperature = std::stof(temp_str);
			depth = std::stof(depth_str);
			altitude = std::stof(alt_str);
			
		}
		//HUB STATUS IMU
		if (inputBuffer[1] == 'H' &&
		    inputBuffer[2] == 'S' &&
	            inputBuffer[3] == 'I'){
			
			int index = 5;
			std::string eox_str, eoy_str, eoz_str, avx_str, avy_str, avz_str, acx_str, acy_str, acz_str, mfx_str, mfy_str, mfz_str, lax_str, lay_str, laz_str, gvx_str, gvy_str, gvz_str;

			for (int i = 0; i < 18; i ++){
				while (inputBuffer[index] != ' '){
					switch (i){
						case 0:
							eox_str += inputBuffer[index];
							break;
						case 1:
							eoy_str += inputBuffer[index];
							break;
						case 2:
							eoz_str += inputBuffer[index];
							break;
						case 3:	
							avx_str += inputBuffer[index];
							break;
						case 4:	
							avy_str += inputBuffer[index];
							break;
						case 5:
							avz_str +=  inputBuffer[index];
							break;
						case 6:	
							acx_str += inputBuffer[index];
							break;
						case 7:
							acy_str += inputBuffer[index];
							break;
						case 8:
							acz_str += inputBuffer[index];
							break;
						case 9:
							mfx_str += inputBuffer[index];
							break;
						case 10:
							mfy_str += inputBuffer[index];
							break;
						case 11:
							mfz_str += inputBuffer[index];
							break;
						case 12:
							lax_str += inputBuffer[index];
							break;
						case 13:	
							lay_str += inputBuffer[index];
							break;
						case 14:
							laz_str += inputBuffer[index];
							break;
				
						case 15:
							gvx_str += inputBuffer[index];
							break;
						case 16:
							gvy_str += inputBuffer[index];
							break;
						case 17:
							gvz_str += inputBuffer[index];
							break;
					}
					index++;
				}
				index++;
			}
			//std::cout << eox_str << ' ' << eoy_str << ' ' << eoz_str << ' ' << avx_str << ' ' << avy_str << ' ' << avz_str <<'\n';
			
			eox = std::stof(eox_str);
			eoy = std::stof(eoy_str);
			eoz = std::stof(eoz_str);

			avx = std::stof(avx_str);
			avy = std::stof(avy_str);
			avz = std::stof(avz_str);

			acx = std::stof(acx_str);
			acy = std::stof(acy_str);
			acz = std::stof(acz_str);

			mfx = std::stof(mfx_str);
			mfy = std::stof(mfy_str);
			mfz = std::stof(mfz_str);

			lax = std::stof(lax_str);
			lay = std::stof(lay_str);
			laz = std::stof(laz_str);

			gvx = std::stof(gvx_str);
			gvy = std::stof(gvy_str);
			gvz = std::stof(gvz_str);
		}
	}
	initStr(inputBuffer, 256);

}


void printElements(){

	//vtGoto(1,1);
	std::cout << "DeckBox-CLI version: " << version_string << "\n";

	std::cout << "--- SYSTEM STAUS ---\n";
	std::cout << "\tUse Keys 1 - 6 to select mode\n";
	std::cout << "\tMode: ";
	switch (sys_mode){
		case 0:
			std::cout << "Testing\n";
			break;
		case 1:
			std::cout << "Full Manual Control\n";
			break;
		case 2:
			std::cout << "Teleoperative (Debug)\n";
			break;
		case 3:
			std::cout << "Teleoperative\n";
			break;

		case 4:
			std::cout << "Teleoperative (with recording and playback)\n";
			break;
		case 5: 
			std::cout << "Full Autonomy (Tasks)\n";
			break;
		
	}
	std::cout << "--- INPUT STAUS ---\n";
	
	/* controller input*/
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

	std::cout << "\n--- ONBOARD TELEMETRY ---\n";
	std::cout << "Temperature: " << temperature << " degrees celsius\n";
	std::cout << "Pressure: " << pressure << " \n";
	std::cout << "Depth: " << depth << " \n";
	std::cout << "Altitude: " << altitude << " \n";
	std::cout << "Orientation: " << eox << ' '<< eoy << ' '<< eoz << '\n';
	std::cout << "Velocity: " << avx << ' '<< avy << ' '<< avz << '\n';
	std::cout << "Acceleration: " << acx << ' ' << acy << ' ' << acz << '\n';
	std::cout << "Mag. Field Strength: " << mfx << ' ' << mfy << ' ' << mfz << '\n';
	std::cout << "Linear Acceleration: " << lax << ' ' << lay << ' ' << laz << '\n';
	std::cout << "Gravity: " << gvx << ' ' << gvy << ' ' << gvz << '\n';
	std::cout << "\n--- MESSAGE CENTER ---\n";
	//sixaxis_raw.print();
	f710_raw.print();
}

void getKbInput(){
	int ch = kb.getCode();

	switch (ch){
		case 2: // '1'
			sys_mode = 0;
			break;
		case 3:
			sys_mode = 1;
			break;
		case 4:
			sys_mode = 2;
			break;
		case 5:
			sys_mode = 3;
			break;
		case 6:
			sys_mode = 4;
			break;
		case 7:
			sys_mode = 5;
			break;
	}
}

void printHelp(){
	std::cout << "DeckBox-CLI version: " << version_string << "\n";
	std::cout << "\nUSAGE:";
	std::cout << "\t\tdeckbox-cli <mode> <arguments>\n"; 
		
	std::cout << "\tModes: help, listen\n";
	std::cout << "\t[Listen] arguments: <controller (/dev/input/js*)>\n";	




}




int listen(){ 
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
			getKbInput();
		}
	//do other things
	return 1;
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
