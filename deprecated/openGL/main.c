/*DECKBOX INTERFACE*/
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>


#define GLT_IMPLEMENTATION


#include "assets/glToolkit.h"	//toolkit lib 
#include "assets/interface.h"	//interface element definitions
#include "assets/glText.h"	//text rendering library
#include "assets/hydro_small.ppm"

/* named pipe definitions*/
//remoteRX
int fd;
char rxStream[32];
char * myfifo = "../transfer_file";
//takeControl
int takeControl = 0; //local variable 

int takeControlD; //takeControl device
char takeControl_stream[2];
char *takeControlPipe = "../control_status_pipe";


void takeControl_set(int mode){

	takeControlD = open(takeControlPipe, O_WRONLY);
	if (mode == 1){
		//manual mode
		takeControl_stream[0] = '1';
		takeControl_stream[1] = '\0';
		
	}else if (mode == 0){
		takeControl_stream[0] = '0';
		takeControl_stream[1] = '\0';
		
	}

	write(takeControlD, takeControl_stream, 2);
	close(takeControlD);
	

}




void remoteRX_capture(){
		
	//printf ("pipe status %i\n", access(myfifo, F_OK));
/*
	if(myfifo == NULL) {
    		//file not found
		printf("transfer_file not found\n");
		exit(1);
	} 		
	
*/


	fd = open(myfifo,O_RDONLY);
       	read(fd, rxStream, 32);
       	close(fd);
	//printf("%s\n", rxStream);

	for (int i = 0; i < 30; i++){
		printf("rxStream[%i] = %c\n", i, rxStream[i]);
	}
	

}

long sticks[6];

void remoteRX_parse(){

	char stick1[4];
	char stick2[4];
	char stick3[4] = "0000";
	char stick4[4];
	char stick5[4];
	char stick6[4];


	//get values from rxStream

	for (int i = 0; i < 4; i++){
		//stick1
		stick1[i] = rxStream[i];
		
	}

	for (int i = 5; i < 9; i++){
		//stick1
		stick2[i - 5] = rxStream[i];
		
	}



	for (int i = 10; i < 14; i++){
		//stick1
		stick3[i - 10] = rxStream[i];
		
	}

	for (int i = 15; i < 19; i++){
		//stick1
		stick4[i - 15] = rxStream[i];
		
	}




	printf("%s\n", stick3);

	//convert and store values
	sticks[0] = strtol(stick1, NULL, 10);
	sticks[1] = strtol(stick2, NULL, 10);
	sticks[2] = strtol(stick3, NULL, 10);
	sticks[3] = strtol(stick4, NULL, 10);


	for (int i = 0; i < 6; i++){
		printf("STICK (INT) %i: %i\n",i , sticks[i]);
	}

}


//definitions
int statusBox[] = {440, 10, 340, 240, 2, 1};

char mode_string[10] = "MANUAL";



void display(){
	//clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//DEFINE CONTROLS
	if(Keys.wB == 1){panY = panY - 2;}
	if(Keys.aB == 1){panX = panX - 2;}
	if(Keys.sB == 1){panY = panY + 2;}
	if(Keys.dB == 1){panX = panX + 2;}

	//reset pan
	if(Keys.rB == 1){panX = 0; panY = 0;}
	glutPostRedisplay();
	//MAIN LOOP CODE

	//draw gui elements
	updateRectObject(buttonBox);
	updateRectObject(inputStatusBox);
	updateRectObject(statusBox);

	//draw sticks
		drawStatusBar(240, 50, 100, 20, sticks[0], 0, 1000, 'h');
		drawStatusBar(240, 80, 100, 20, sticks[1], 1000, 2000, 'h');
		drawStatusBar(240, 110, 100, 20, sticks[2], 1000, 2000, 'h');
		drawStatusBar(240, 140, 100, 20, sticks[3], 1000, 2000, 'h');
		drawStatusBar(240, 170, 100, 20, sticks[4], 1000, 2000, 'h');
		drawStatusBar(240, 200, 100, 20, sticks[5], 1000, 2000, 'h');


	//text
	renderString(20, 20, 1, "BUTTONS");
	renderString(240, 20, 1, "INPUT VISUAL");
	takeControl_set(0);
	if (takeControl_stream[0] == '1'){
		
		strcpy(mode_string, "MANUAL");
	}else{
		strcpy(mode_string, "AUTO");
	}


	//status information
	renderString(460, 20, 1, "STATUS");
		renderString(460, 50, 1, "LEAK SENSOR:");
			renderString(560, 50, 1, "NO LEAK");
		renderString(460, 70, 1, "CONTROL MODE:");
			renderString(580, 70, 1, mode_string);





	//deckBox Logo

	renderString(550, 540, 3, "DECKBOX GL");

	renderTexture(logo, 620, 440, 96, 96);

	remoteRX_capture();
	remoteRX_parse();
	glutSwapBuffers();
}

void init(){
	glClearColor(1,1,1,0);
	gluOrtho2D(0,800,600,0);
}


int main(int argc, char* argv[]){
	//deckbox

	mkfifo(myfifo, 0666);
	



 	//opengl
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(200,200);
 	glutCreateWindow("deckBox_GL");
 	init();
 	glutDisplayFunc(display);
 	glutKeyboardFunc(ButtonsDown);
	glutKeyboardUpFunc(ButtonsUp);
	glutMainLoop();
}

