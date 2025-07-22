#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "../keyboard.h"


int main(){

	keyboard_t kb;
	kb.init();

	while (1){
		kb.getChar();
	}






	return 0;
}
