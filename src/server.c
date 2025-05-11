#include "server.h"

#include "connection.h"
#include "logger.h"

char ip[INET_ADDRSTRLEN];
uint16_t port;

Connection *server;

void initServer() {
    // Open IPv4 / TCP socket
    int32_t retval = socket(AF_INET, SOCK_STREAM, 0);
    assert(retval != -1);
    debug("Server socket created:");

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {
            .s_addr = inet_addr(ip)
        },
        .sin_zero = {}
    };

    server = createConn(retval, addr);

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
}

void loopServer() {
    while(1) {
        struct sockaddr_in addr = {};
        socklen_t addr_len = sizeof(addr);

        const int32_t retval = accept(server->fd, (struct sockaddr *) &addr, &addr_len);

        if(retval == -1) {
            debug("Failed to accept connection");
            continue;
        }

        debug("Client connection accepted:");
        Connection *client = createConn(retval, addr);
        setConnOptimOpts(client);
    }
}

void quitServer() {
    destroyConn(server);
}
