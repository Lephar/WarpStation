#include "client.h"

#include "connection.h"

#include "logger.h"

struct client {
    struct client *prev;
    Connection *conn;
    struct client *next;
} typedef Client;

pthread_rwlock_t listLock;

Client *head;
Client *tail;

void initClientList() {
    pthread_rwlock_init(&listLock, NULL);
    pthread_rwlock_wrlock(&listLock);

    head = malloc(sizeof(Client));
    tail = malloc(sizeof(Client));

    head->prev = nullptr;
    head->conn = nullptr;
    head->next = tail;

    tail->prev = head;
    tail->conn = nullptr;
    tail->next = nullptr;

    pthread_rwlock_unlock(&listLock);
}

void printClientList() {
    pthread_rwlock_rdlock(&listLock);

    Client *iter = head->next;

    if(iter == tail) {
        debug("Client list empty");
    } else {
        debug("Client list:");
    }

    while(iter != tail) {
        char uuid[UUID_STR_LEN];
        uuid_unparse_lower(iter->conn->uuid, uuid);

        debug("\t%s", uuid);

        iter = iter->next;
    }

    pthread_rwlock_unlock(&listLock);
}

Client *addClient(Connection *conn) {
    Client *client = malloc(sizeof(Client));

    pthread_rwlock_wrlock(&listLock);

    client->prev = tail->prev;
    client->conn = conn;
    client->next = tail;

    tail->prev->next = client;
    tail->prev = client;

    pthread_rwlock_unlock(&listLock);

    printClientList();

    return client;
}

void removeClient(Connection *conn) {
    pthread_rwlock_wrlock(&listLock);

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

            break;
        }

        iter = iter->next;
    }

    pthread_rwlock_unlock(&listLock);

    printClientList();
}

void *clientLoop(void *param) {
    Client *client = param;

    sleep(5 + rand() % 10);

    debug("Client disconnected:");
    removeClient(client->conn);

    return nullptr;
}

void dispatchClient(int32_t fd, struct sockaddr_in addr) {
    debug("Client connected:");

    Connection *conn = createConn(fd, addr);
    setConnOptimOpts(conn);

    Client *client = addClient(conn);
    pthread_create(&conn->thread, nullptr, clientLoop, client);
}
