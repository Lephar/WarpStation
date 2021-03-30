#include <stdio.h>
#include <string.h>

#include "game.h"
#include "network.h"
#include "database.h"

void commandLoop(void) {
	while(1) {
		char command[16] = {0};
		scanf("%s", command);

		if(!strcmp(command, "exit"))
			break;
	}
}

int main(void) {
	startServer();
	commandLoop();
	stopServer();

	return 0;
}
