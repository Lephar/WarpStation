#include "server.h"

#include "client.h"

#include "helper.h"
#include "logger.h"

int32_t server;

void initialize() {
    // Open IPv4 / TCP socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    assert(server != -1);

#if DEBUG
    // Set socket close on exec
    setFileDescriptorOptionInt(server, FD_CLOEXEC);

    // Enable socket address reuse
    setSocketOptionInt(server, SOL_SOCKET, SO_REUSEADDR, 1);

    // Enable socket port reuse
    setSocketOptionInt(server, SOL_SOCKET, SO_REUSEPORT, 1);
#endif

    // Set type of service to low delay
    setSocketOptionInt(server, IPPROTO_IP, IP_TOS, IPTOS_LOWDELAY);

    // Disable Nagle's Algorithm
    setSocketOptionInt(server, IPPROTO_TCP, TCP_NODELAY, 1);

    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(5316),
        .sin_addr = {
            .s_addr = INADDR_ANY
        },
        .sin_zero = {}
    };

    int32_t retval = 0;

    // Bind socket
    retval = bind(server, (struct sockaddr *) &address, sizeof(struct sockaddr_in));
    assert(retval == 0);

    // Listen for connection
    retval = listen(server, SOMAXCONN);
    assert(retval == 0);
}

void loop() {
    while(1) {
        struct sockaddr_in addr = {};
        socklen_t addrlen = sizeof(addr);

        int32_t fd = accept(server, (struct sockaddr *) &addr, &addrlen);
        assert(fd != -1);

        Client client = {
            .fd = fd,
            .ip = addr.sin_addr,
            .port = addr.sin_port,
        };

        debug("IP:   %s", inet_ntoa(client.ip));
        debug("Port: %d", ntohs(client.port));
    }
}

void quit() {
    close(server);
}
