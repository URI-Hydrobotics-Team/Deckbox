/* DeckBox Controller Backend */
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

std::string event_buffer = "!CBE TEL "; //buffer of input events to be sent to deckbox 


controller_t joystick;
auv_tx_socket output_deckbox;


void sendEventBuffer(const char *str){

	if(event_buffer.length() + strlen(str) > 256){
		event_buffer = "!CBE TEL "; //add header

	}

	event_buffer += str;
	

	output_deckbox.transmit(event_buffer.c_str());

}

int main(int argc, char *argv[]){

	/* controller init */
	joystick.setDevice(DEFAULT_CONTROLLER);
	joystick.init();
	/*network socket init*/


	output_deckbox.init(DECKBOX_PORT_TX, MULTICASTGROUP);

	

	

	while(1){

		sendEventBuffer(joystick.poll());
		usleep(CONTROLLER_TIMEOUT);	
			


	}







	return 0;
}

