#pragma once

#include "pch.h"

struct client {
    uuid_t id;
    int32_t fd;
    struct in_addr ip;
    in_port_t port;
    pthread_t thread;
} typedef Client;
