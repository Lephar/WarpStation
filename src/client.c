#include "client.h"

#include "connection.h"
#include "logger.h"

struct client {
    struct client *prev;
    Connection *conn;
    struct client *next;
} typedef Client;

Client *head = nullptr;
Client *tail = nullptr;

void *clientLoop(void *param) {
    while (true) {

    }

    return nullptr;
}

void dispatchClient(int32_t fd, struct sockaddr_in addr) {
    debug("Client connection accepted");

    Connection *conn = createConn(fd, addr);
    setConnOptimOpts(conn);

    pthread_create(&conn->thread, nullptr, clientLoop, conn);
}
