#include "client.h"

#include "connection.h"
#include "logger.h"

struct client {
    struct client *prev;
    Connection *conn;
    struct client *next;
} typedef Client;

Client *head;
Client *tail;

void initClientList() {
    head = malloc(sizeof(Client));
    tail = malloc(sizeof(Client));

    head->prev = nullptr;
    head->conn = nullptr;
    head->next = tail;

    tail->prev = head;
    tail->conn = nullptr;
    tail->next = nullptr;
}

void addClient(Connection *conn) {
    Client *client = malloc(sizeof(Client));

    client->prev = tail->prev;
    client->conn = conn;
    client->next = tail;

    tail->next = client;
    tail->prev->next = client;
}

void removeClient(Connection *conn) {
    Client *iter = head->next;

    while(iter != tail) {
        if(uuid_compare(iter->conn->uuid, conn->uuid) == 0) {
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;

            destroyConn(iter->conn);

            iter->prev = nullptr;
            iter->conn = nullptr;
            iter->next = nullptr;

            free(iter);

            return;
        }
    }
}

void *clientLoop(void *param) {
    while(true) {

    }

    return nullptr;
}

void dispatchClient(int32_t fd, struct sockaddr_in addr) {
    debug("Client connection accepted");

    Connection *conn = createConn(fd, addr);
    setConnOptimOpts(conn);

    pthread_create(&conn->thread, nullptr, clientLoop, conn);
}
