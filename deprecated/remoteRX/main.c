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
char buf[32]; //define a buffer

//named pipe init

int nPipeD; //named pipe device
char * myfifo = "../transfer_file";







void dump(){
	//main loop
  	n = read(fd, buf, 32);

	//print serial output
	printf("\e[1;1H\e[2J"); //clear screen
 	printf("%s\n", buf);

	
	//write pipe


	nPipeD = open(myfifo, O_WRONLY);


        // Write buf on FIFO
        // and close it
        write(nPipeD, buf, 32);
        close(nPipeD);










	dump();
}

int main(){
	//named pipe

	mkfifo(myfifo, 0666); //permission 666

	
				



	struct termios toptions;

 	 /* open serial port */
  	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
  	printf("fd opened as %i\n", fd);
  
 	 /* wait for the Arduino to reboot */
  	usleep(3500000);
  
  	/* get current serial port settings */
  	tcgetattr(fd, &toptions);
  	/* set 9600 baud both ways */
  	cfsetospeed(&toptions, B115200);
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


	dump();

	return 0;


}
