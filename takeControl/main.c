//program recieves input from deckboxGui and remoteRX and sends that input data over a socket to the AUV's Pi

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


//control_status_pipe
int cspPipeD; //named pipe device
char * cspPipe = "../control_status_pipe";
char cspPipe_stream[2];
//remoteRX pipe (transfer_file)
int remoteRXpipeD;
char remoteRX_stream[32];
char *remoteRXpipe = "../transfer_file";




void remoteRX_capture(){


	//read data from remoteRX
	remoteRXpipeD = open(remoteRXpipe, O_RDONLY);
	read(remoteRXpipeD, remoteRX_stream, 32);
	printf("Test output from remoteRX:\n");
	for (int i = 0; i < 32; i++){
		printf("%c", remoteRX_stream[i]);
	}
	printf("\n");

}



void csp_capture(){

	cspPipeD = open(cspPipe, O_RDONLY);
	read(cspPipeD, cspPipe_stream, 2);


	printf("Control Status Pipe: %c\n", cspPipe_stream[0]);

}


int main(){


	mkfifo(cspPipe, 0666);
	mkfifo(remoteRXpipe, 0666);
	remoteRX_capture();
	csp_capture();






	

	return 0;
}
