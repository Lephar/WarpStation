#pragma once

#include "pch.h"

struct connection {
    int32_t fd;
    struct in_addr ip;
    in_port_t port;
    uuid_t uuid;
    pthread_t thread;
} typedef Connection;

void setConnReuseOpts(Connection *conn);
void setConnOptimOpts(Connection *conn);

Connection *createConn(int32_t fd, struct sockaddr_in addr);
void destroyConn(Connection *connection);
