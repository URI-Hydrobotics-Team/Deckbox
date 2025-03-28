//program recieves input from arduino PPM recivever and sends it to deckBox gui, deckbox logging software, the AUV and more

#include <stdlib.h>
#include <stdio.h>




int main(){

	//temporary run condition
	run = 1000;

	FILE *onlinePtr; //an "avalible file" will let the deckbox Gui and other client programs know that there is input to handle

	onlinePtr = fopen("is_Online", "w"); //open file

	//write "online" if running
	while (run > 0){
		fprintf(onlinePtr, "online"); 
		run--;
	}

	fprintf(onlinePtr, "offline"); 

	fclose(onlinePtr);





	return 0;


}
