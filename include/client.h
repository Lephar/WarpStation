#pragma once

#include "pch.h"

struct client {
    int32_t fd;
    struct in_addr ip;
    in_port_t port;
    uuid_t uuid;
    pthread_t thread;
} typedef Client;

void processClient(int32_t fd, struct sockaddr_in addr);
void *dispatchClient(void *param);
