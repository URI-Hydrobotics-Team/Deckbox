/*glTEXT alpha header version*/


//TODO
/*	
	combine all ppm files into one
	implement upper and lower case
	add all other ascii characters	
*/


#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <string.h>

#include "font/num.ppm"
#include "font/char.ppm"
#include "font/alpha.ppm"

int tileScale = 8; //default scale is 8

//declare functions
void render8Bit(int[], int, int);
void renderString(int, int, int, char[]);



void renderString(int xo, int yo, int size, char string[]){
	int saveScale = tileScale;
	tileScale = size;
	int length = strlen(string);
	for (int index = 0; index < length; index ++){
		//numbers and other characters
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
			//numbers


			case '0':
	 			render8Bit(zero, xo, yo);
				break;
			case '1':
	 			render8Bit(one, xo, yo);
				break;
			case '2':
	 			render8Bit(two, xo, yo);
				break;

			case '3':
	 			render8Bit(three, xo, yo);
				break;
			case '4':
	 			render8Bit(four, xo, yo);
				break;
			case '5':
	 			render8Bit(five, xo, yo);
				break;
	
			case '6':
	 			render8Bit(six, xo, yo);
				break;
			case '7':
	 			render8Bit(seven, xo, yo);
				break;
			case '8':
	 			render8Bit(eight, xo, yo);
				break;
	
			case '9':
	 			render8Bit(nine, xo, yo);
				break;
			//characters	

			case '@':
	 			render8Bit(address, xo, yo);
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


