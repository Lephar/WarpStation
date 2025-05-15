#include "server.h"

#include "connection.h"
#include "client.h"

#include "logger.h"

char ip[INET_ADDRSTRLEN];
uint16_t port;

Conn* server;

void commandLoop() {
    char command[UINT8_MAX];

    while(true) {
        scanf("%s", command);

        if( strcmp(command, "q") == 0    ||
            strcmp(command, "quit") == 0 ||
            strcmp(command, "e") == 0    ||
            strcmp(command, "exit") == 0) {
            debug("Server stopped:");
            destroyConn(server);
            destroyClientList();
            break;
        }
    }
}

void *serverLoop(void *param) {
    (void) param;

    while(true) {
        struct sockaddr_in addr = {};
        socklen_t addr_len = sizeof(addr);

        const int32_t retval = accept(server->fd, (struct sockaddr *) &addr, &addr_len);

        if(retval == -1) {
            debug("Failed to accept connection");
        } else {
            dispatchClient(retval, addr);
        }
    }

    return nullptr;
}

void dispatchServer() {
    // Open IPv4 / TCP socket
    int32_t retval = socket(AF_INET, SOCK_STREAM, 0);
    assert(retval != -1);
    debug("Server started:");

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(port),
        .sin_addr   = {
            .s_addr = inet_addr(ip),
        },
        .sin_zero   = {}
    };

    server = makeConn(retval, addr);

#if DEBUG
    setConnReuseOpts(server);
#endif

    // Bind socket
    retval = bind(server->fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
    assert(retval == 0);
    debug("\tAddress bound");

    setConnOptimOpts(server);

    // Listen for connection
    retval = listen(server->fd, SOMAXCONN);
    assert(retval == 0);
    debug("\tStarted listening");

    initClientList();
    pthread_create(&server->thread, nullptr, serverLoop, nullptr);
}
