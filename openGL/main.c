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



//#include "assets/youtube.ppm"
#include "assets/mapdata.h"
#include "assets/interface.h"
#include "assets/glText.h"
/*DECKBOX INTERFACE*/

//deckbox stuff
int fd;
char rxStream[32];
char * myfifo = "../transfer_file";


void remoteRX_capture(){


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






//TODO
/*
*/

//DOCUMENTATION
/*
	This software is becoming a basic 2D game engine based in C and OpenGL using the glut library
	audio is not implemented at the moment

	Each object is defined by two arrays, a "physical" one that defines position, velocity, size specifications. And a "map" array that can map a texture to the physical array.
	
	PHYSICAL ARRAY DEFINITIONS:

	-Rectangular Object Array

	float <rectObjectName>[9] = [<positionX>,<positionY>,<velocityX,<velocityY>,<accelerationX>,<accelerationY>,<mass>,<width>,<height>];

*/

	


//system vars
float panX = 0;
float panY = 0;




//int mapScale = 32;
int drawMapOn = 0;




	


//define controls

typedef struct{
	int aB, bB, cB, dB, eB, fB, gB, hB, iB, jB,lB, kB, mB, nB, oB, pB, qB, rB, sB, tB, uB, vB, wB, xB, yB, zB, backspaceB, enterB; //button state on off
} ButtonKeys; ButtonKeys Keys;



//Buttons

void ButtonsDown(unsigned char key, int x, int y){
	
	//alpha keys
	if(key=='a') {Keys.aB=1;}
	if(key=='b') {Keys.bB=1;}
	if(key=='c') {Keys.cB=1;}
	if(key=='d') {Keys.dB=1;}
	if(key=='e') {Keys.eB=1;}
	if(key=='f') {Keys.fB=1;}
	if(key=='g') {Keys.gB=1;}
	if(key=='h') {Keys.hB=1;}
	if(key=='i') {Keys.iB=1;}
	if(key=='j') {Keys.jB=1;}
	if(key=='k') {Keys.kB=1;}
	if(key=='l') {Keys.lB=1;}
	if(key=='m') {Keys.mB=1;}
	if(key=='n') {Keys.nB=1;}
	if(key=='o') {Keys.oB=1;}
	if(key=='p') {Keys.pB=1;}
	if(key=='q') {Keys.qB=1;}
	if(key=='r') {Keys.rB=1;}
	if(key=='s') {Keys.sB=1;}
	if(key=='t') {Keys.tB=1;}
	if(key=='u') {Keys.uB=1;}
	if(key=='v') {Keys.vB=1;}
	if(key=='w') {Keys.wB=1;}
	if(key=='x') {Keys.xB=1;}
	if(key=='y') {Keys.yB=1;}
	if(key=='z') {Keys.zB=1;}

	//other keys
	if(key==13) {Keys.enterB=1;} //enter
	if(key==8) {Keys.backspaceB=1;} //backspace

	glutPostRedisplay();

}
void ButtonsUp(unsigned char key, int x, int y){
	//alpha keys
	if(key=='a') {Keys.aB=0;}
	if(key=='b') {Keys.bB=0;}
	if(key=='c') {Keys.cB=0;}
	if(key=='d') {Keys.dB=0;}
	if(key=='e') {Keys.eB=0;}
	if(key=='f') {Keys.fB=0;}
	if(key=='g') {Keys.gB=0;}
	if(key=='h') {Keys.hB=0;}
	if(key=='i') {Keys.iB=0;}
	if(key=='j') {Keys.jB=0;}
	if(key=='k') {Keys.kB=0;}
	if(key=='l') {Keys.lB=0;}
	if(key=='m') {Keys.mB=0;}
	if(key=='n') {Keys.nB=0;}
	if(key=='o') {Keys.oB=0;}
	if(key=='p') {Keys.pB=0;}
	if(key=='q') {Keys.qB=0;}
	if(key=='r') {Keys.rB=0;}
	if(key=='s') {Keys.sB=0;}
	if(key=='t') {Keys.tB=0;}
	if(key=='u') {Keys.uB=0;}
	if(key=='v') {Keys.vB=0;}
	if(key=='w') {Keys.wB=0;}
	if(key=='x') {Keys.xB=0;}
	if(key=='y') {Keys.yB=0;}
	if(key=='z') {Keys.zB=0;}


	//other keys
	if(key==13) {Keys.enterB=0;} //enter
	if(key==8) {Keys.backspaceB=0;} //backspace
	glutPostRedisplay();

}

//declare render texture function
void renderTexture(int[], int, int);
void drawRect(int, int, int, int, int);
void drawMap(int[], int, int, int, int, int, int, int[]);
//declare object update functions
void updateRectObject(int[]);


void drawStatusBar(int , int , int , int , int , int, int, char);




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

	remoteRX_capture();

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
	//deckBox Logo

	renderString(550, 540, 3, "DECKBOX GL");


	remoteRX_parse();
	glutSwapBuffers();
}









void updateRectObject(int array[]){
	
	int x = array[0];
	int y = array[1];
	int w = array[2];
	int h = array[3];
	int border = array[4];
	int on = array[5];
	if (on == 1){
		drawRect(x, y, w, h, border);
	}

}


void drawRect(int x, int y, int w, int h, int border){
	if (border > 0){
		glColor3f(0,0,0);
   	glBegin(GL_QUADS); 
	glVertex2i(x, y); 
  	glVertex2i(x, y + h); 
  	glVertex2i(x + w, y + h);  
 	glVertex2i(x + w, y); 
 	glEnd();





	}
	if(border > 0){
		glColor3f(1,1,1);
	}else{

		glColor3f(0,0,0);
	}
   	glBegin(GL_QUADS); 
	glVertex2i(x + border, y + border); 
  	glVertex2i(x + border ,y + h - border); 
  	glVertex2i(x + w - border, y + h - border);  
 	glVertex2i(x + w - border, y + border); 
 	glEnd();
}




void drawStatusBar(int x, int y, int w, int h, int value, int min, int max, char orientation){

	if (value < min || value > max){
		//out of range

		value = min;
	}



	if (orientation == 'h'){
		drawRect(x, y, w, h, 0); //draw border

		float width = (w + 0.0) * (((value - min) + 0.0) / (max - min));
		drawRect(x, y, width, h, 1); //draw bar 



	}

	
}






void drawMap(int* map, int mapScale, int initX, int initY, int mapX, int mapY, int border, int* textureIn){
	int x,y,xo,yo;
 	for(x=0;x<mapX;x++){
		for(y=0;y<mapY;y++){
			//render main tiles
   			if(map[y*mapY+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
    			//render player
   				xo = x*mapScale + initX + panX; yo = y*mapScale + initY + panY; 
   				glBegin(GL_QUADS); 
  			 	glVertex2i(xo + border, yo + border); 
  				glVertex2i(xo + border ,yo+mapScale - border); 
  				glVertex2i(xo+mapScale - border,yo+mapScale -border);  
 				glVertex2i(xo+mapScale - border, yo + border); 
 			 	glEnd();
    			if(map[y*mapY+x]==3 && textureIn != 0){
   				renderTexture(textureIn, xo, yo);
  			}
  		}	 
	}	
}


void renderTexture(int* texture, int xOff, int yOff){
	int x, y;
	for (y=0;y<64;y++){
 		for(x=0; x<64;x++){
  			int pixel= (y*64+x)*3;
  			int red = texture[pixel +0];
  			int green = texture[pixel +1];
  			int blue = texture[pixel+2];
  			glPointSize(1); glColor3ub(red,green,blue); glBegin(GL_POINTS); glVertex2i(x+xOff,y+yOff); glEnd();

		}
	}
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

