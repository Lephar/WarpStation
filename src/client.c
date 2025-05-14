#include "client.h"

#include "connection.h"

#include "logger.h"

pthread_rwlock_t listLock;

Conn *head;
Conn *tail;

void initClientList() {
    pthread_rwlock_init(&listLock, NULL);
    pthread_rwlock_wrlock(&listLock);

    int32_t fd = INT32_MIN;

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = USHRT_MAX,
        .sin_addr   = {
            .s_addr = INADDR_NONE,
        },
        .sin_zero   = {}
    };

    debug("Created list head:");
    head = makeConn(fd, addr);

    debug("Created list tail:");
    tail = makeConn(fd, addr);

    head->next = tail;
    tail->prev = head;

    pthread_rwlock_unlock(&listLock);
}

void printClientList() {
    pthread_rwlock_rdlock(&listLock);

    Conn *iter = head->next;

    if(iter == tail) {
        debug("Client list empty");
    } else {
        debug("Client list:");
    }

    while(iter != tail) {
        char uuid[UUID_STR_LEN];
        uuid_unparse_lower(iter->uuid, uuid);

        debug("\t%s", uuid);

        iter = iter->next;
    }

    pthread_rwlock_unlock(&listLock);
}

void addClient(Conn *conn) {
    pthread_rwlock_wrlock(&listLock);

    conn->prev = tail->prev;
    conn->next = tail;

    tail->prev->next = conn;
    tail->prev = conn;

    pthread_rwlock_unlock(&listLock);

    printClientList();
}

void removeClient(Conn *conn) {
    pthread_rwlock_wrlock(&listLock);

    conn->prev->next = conn->next;
    conn->next->prev = conn->prev;

    conn->prev = nullptr;
    conn->next = nullptr;

    pthread_rwlock_unlock(&listLock);

    printClientList();
}

void *clientLoop(void *param) {
    Conn *conn = param;

    sleep(5 + rand() % 10);

    removeClient(conn);

    debug("Client disconnected:");
    destroyConn(conn);

    return nullptr;
}

void dispatchClient(int32_t fd, struct sockaddr_in addr) {
    debug("Client connected:");
    Conn *conn = makeConn(fd, addr);
    setConnOptimOpts(conn);

    addClient(conn);

    pthread_create(&conn->thread, nullptr, clientLoop, conn);
}
