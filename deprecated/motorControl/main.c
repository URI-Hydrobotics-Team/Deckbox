//program recieves input from arduino PPM recivever and sends it to deckBox gui, deckbox logging software, the AUV and more

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define DEBUG 1



//serial init
int fd, n, i;
int delay = 0;
char servoPos[3];
int servoPosInt;

void testPrompt();

void sendToArduino(){
	//test function for writing to arduino


	//sprintf(servoPos, "%d", servoPosInt);
	write(fd, servoPos, 3);	
	//test prompt
	
		if (delay == 10){
			testPrompt();

		}else{
			delay++;
		}
	sendToArduino();

}

void testPrompt(){
		printf("Enter a position \n");
		scanf("%s", servoPos);

			delay = 0;
		sendToArduino();

}



int main(){
	//named pipe


	
				



	struct termios toptions;

 	 /* open serial port */
  	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
  	printf("fd opened as %i\n", fd);
  
 	 /* wait for the Arduino to reboot */
  	usleep(3500000);
  
  	/* get current serial port settings */
  	tcgetattr(fd, &toptions);
  	/* set 9600 baud both ways */
  	cfsetospeed(&toptions, B9600);
  	/* 8 bits, no parity, no stop bits */
  	toptions.c_cflag &= ~PARENB;
  	toptions.c_cflag &= ~CSTOPB;
  	toptions.c_cflag &= ~CSIZE;
  	toptions.c_cflag |= CS8;
  	/* Canonical mode */
  	toptions.c_lflag |= ICANON;
  	/* commit the serial port settings */
  	tcsetattr(fd, TCSANOW, &toptions);

  	/* Send byte to trigger Arduino to send string back */

  	/* Receive string from Arduino */
	sendToArduino();

	return 0;


}

