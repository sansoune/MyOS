#include "shell.h"

void shell(char* input) {
	if(strcmp(input, "help\n") == 0) {
		print("help is under construction please try again when the os is finished\n");
	}else if(strcmp(input, "clr\n") == 0){
		clear();
	}
	else {
		print("Unknown command: ");
		print(input);
	}
}
