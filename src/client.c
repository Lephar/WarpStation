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

Client *addClient(Connection *conn) {
    Client *client = malloc(sizeof(Client));

    client->prev = tail->prev;
    client->conn = conn;
    client->next = tail;

    tail->prev->next = client;
    tail->prev = client;

    return client;
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

void printClientList() {
    debug("Client list:");

    Client *iter = head->next;

    while(iter != tail) {
        char uuid[UUID_STR_LEN];
        uuid_unparse_lower(iter->conn->uuid, uuid);
        debug("\t%s", uuid);
        iter = iter->next;
    }
}

void *clientLoop(void *param) {
    Client *client = param;

    while(true) {

    }

    removeClient(client->conn);

    return nullptr;
}

void dispatchClient(int32_t fd, struct sockaddr_in addr) {
    debug("Client connection accepted");

    Connection *conn = createConn(fd, addr);
    setConnOptimOpts(conn);

    Client *client = addClient(conn);
    printClientList();

    pthread_create(&conn->thread, nullptr, clientLoop, client);
}
