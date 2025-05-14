#pragma once

#include "pch.h"

struct conn {
    struct conn *prev;
    uuid_t uuid;
    int32_t fd;
    struct sockaddr_in addr;
    pthread_t thread;
    struct conn *next;
} typedef Conn;

void setConnReuseOpts(Conn *conn);
void setConnOptimOpts(Conn *conn);

Conn *makeConn(int32_t fd, struct sockaddr_in addr);
void printConn(Conn *conn);
void destroyConn(Conn *conn);
