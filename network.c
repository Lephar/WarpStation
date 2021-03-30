#include <unistd.h>
#include <pthread.h>
#include <uuid/uuid.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "network.h"

#define UUID_STRING_SIZE 37

#include <stdio.h>

struct client {

} clients[128];

int32_t server;
pthread_t listener, receiver, sender;

void initializeServer(void) {
	server = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &(int32_t) {1}, sizeof(int32_t));

	struct sockaddr_in serverAddress = {
			.sin_family = AF_INET,
			.sin_addr.s_addr = INADDR_ANY,
			.sin_port = htons(7076)
	};

	(void) bind(server, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr_in));
	listen(server, SOMAXCONN);
}

_Noreturn void* startListener(__attribute__((unused)) void* parameter) {
	while (1) {
		struct sockaddr_in clientAddress = {0};
		socklen_t addressLength = sizeof(struct sockaddr_in);
		int32_t client = accept(server, (struct sockaddr *) &clientAddress, &addressLength);

		char ipAddress[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(clientAddress.sin_addr), ipAddress, INET_ADDRSTRLEN);
		printf("%s %d: ", ipAddress, clientAddress.sin_port);

		setsockopt(client, IPPROTO_TCP, TCP_NODELAY, &(int32_t) {1}, sizeof(int32_t));
		setsockopt(client, IPPROTO_IP, IP_TOS, &(uint8_t) {IPTOS_LOWDELAY}, sizeof(uint8_t));

		uuid_t uuidBinary;
		uuid_generate(uuidBinary);
		send(client, uuidBinary, sizeof(uuid_t), 0);

		char uuidString[UUID_STRING_SIZE];
		uuid_unparse_upper(uuidBinary, uuidString);
		printf("%s\n", uuidString);

		close(client);
	}
}

void startServer(void) {
	initializeServer();

	pthread_create(&listener, NULL, startListener, NULL);
	//pthread_create(&receiver, NULL, startReceiver, NULL);
	//pthread_create(&sender, NULL, startSender, NULL);
}

void stopServer(void) {
	pthread_cancel(listener);
	//pthread_cancel(receiver);
	//pthread_cancel(sender);

	pthread_join(listener, NULL);
	//pthread_join(receiver, NULL);
	//pthread_join(sender, NULL);

	close(server);
}
