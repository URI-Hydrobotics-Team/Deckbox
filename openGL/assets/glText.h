//glText ALPHA 1

//TODO
/*	
	combine all ppm files into one
	implement upper and lower case
	add all other ascii characters	
*/


#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "font/zero.ppm"
#include "font/alpha.ppm"
//map and system

int mapScale = 64;
//debugging
int verbose = 1; //debug mode (displays variables in terminal)
int globalCount;

//text
int tileScale = 8;

//process input
//declare functions
void render8Bit(int[], int, int);
void renderString(int, int, int, char[]);

/*

void display(){
//clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//temp code


	renderString(100, 100, 1, "THIS IS SOME SMALL ASS ONE POINT TEXT DAWG");

	renderString(50, 120, 2, "ABCDEFGHIJKLMNKOPQRSTUV");

	renderString(50, 140, 2, "abcdeFGHIJKLMNKOPQRSTUV");


	renderString(20, 200, 2, "LOOK HERE LOOK LISTEN APEEARING OFFLINE DOES NOT FUCKING STOP IT");

	renderString(100, 160, 4, "0FOIUREWHF 0");



//verbosity

	if (verbose == 1){

		//clear console
		printf("\e[1;1H\e[2J");
	}

	glutSwapBuffers();
}

*/
void renderString(int xo, int yo, int size, char string[]){
	int saveScale = tileScale;
	tileScale = size;
	int length = strlen(string);
	for (int index = 0; index < length; index ++){
		//numbers and other characters
		if(string[index] == '0'){
			render8Bit(zero, xo, yo); 

		}

		//letter
		switch (string[index]){
			case 'A':
	 			render8Bit(uA, xo, yo);
				break;
			case 'B':
	 			render8Bit(uB, xo, yo);
				break;
			case 'C':
	 			render8Bit(uC, xo, yo);
				break;
			case 'D':
	 			render8Bit(uD, xo, yo);
				break;
			case 'E':
	 			render8Bit(uE, xo, yo);
				break;
			case 'F':
	 			render8Bit(uF, xo, yo);
				break;
			case 'G':
	 			render8Bit(uG, xo, yo);
				break;
			case 'H':
	 			render8Bit(uH, xo, yo);
				break;
			case 'I':
	 			render8Bit(uI, xo, yo);
				break;
			case 'J':
	 			render8Bit(uJ, xo, yo);
				break;
			case 'K':
	 			render8Bit(uK, xo, yo);
				break;
			case 'L':
	 			render8Bit(uL, xo, yo);
				break;
			case 'M':
	 			render8Bit(uM, xo, yo);
				break;
			case 'N':
	 			render8Bit(uN, xo, yo);
				break;
			case 'O':
	 			render8Bit(uO, xo, yo);
				break;
			case 'P':
	 			render8Bit(uP, xo, yo);
				break;
			case 'Q':
	 			render8Bit(uQ, xo, yo);
				break;
			case 'R':
	 			render8Bit(uR, xo, yo);
				break;
			case 'S':
	 			render8Bit(uS, xo, yo);
				break;
			case 'T':
	 			render8Bit(uT, xo, yo);
				break;
			case 'U':
	 			render8Bit(uU, xo, yo);
				break;
			case 'V':
	 			render8Bit(uV, xo, yo);
				break;
			case 'W':
	 			render8Bit(uW, xo, yo);
				break;
			case 'X':
	 			render8Bit(uX, xo, yo);
				break;
			case 'Y':
	 			render8Bit(uY, xo, yo);
				break;
			case 'Z':
	 			render8Bit(uZ, xo, yo);
				break;
			//lower case
			case 'a':
	 			render8Bit(lA, xo, yo);
				break;
	
			case 'b':
	 			render8Bit(lB, xo, yo);
				break;
			case 'c':
	 			render8Bit(lC, xo, yo);
				break;
			case 'd':
	 			render8Bit(lD, xo, yo);
				break;
			case 'e':
	 			render8Bit(lE, xo, yo);
				break;
	
		}






		xo += 8*size ; //advance draw point
	}





	tileScale = saveScale;
}


void render8Bit(int* texture, int xOff, int yOff){
	int x, y, xo, yo;
	for (y=0;y<7;y++){
 		for(x=0; x<7;x++){
  			int pixel= (y*7+x);
  			if(texture[pixel] == 1){
         			glColor3ub(1,1,1); 
    				xo = x*tileScale; yo = y*tileScale; 
  				glBegin(GL_QUADS); 
  				glVertex2i(xOff+xo , yOff+yo ); 
				glVertex2i(xOff+xo  ,yOff+yo+tileScale ); 
   				glVertex2i(xOff+xo+tileScale ,yOff+yo+tileScale );  
   				glVertex2i(xOff+xo+tileScale, yOff+yo ); 
   				glEnd();

 			}
 		}
	}	
}

/*
void init(){
	glClearColor(0.8,0.8,0.8,0);
 	gluOrtho2D(0,800,600,0);
}


int main(int argc, char* argv[]){
 //memset(map, 22, 12);
 
 //system("timidity test/Quake_II_-_Descent_into_Cerberon.mid"); does indeed work
	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 	glutInitWindowSize(800,600);
 	glutInitWindowPosition(200,200);
	glutCreateWindow("GLTEXT");
 	init();
	glutDisplayFunc(display);
 	srand(time(NULL)); //seed random number
	glutMainLoop();
}
*/
