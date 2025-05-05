#include "server.h"

#include "logger.h"

int32_t server;

void initialize() {
    // Open IPv4 / TCP socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    assert(server != -1);

    int32_t  retval = 0;
    int32_t  optval = 0;
    uint32_t optlen = sizeof(int32_t);

    // Set socket close on exit
    retval = fcntl(server, F_SETFD, FD_CLOEXEC);
    assert(retval == 0);

    // Enable socket address reuse
    optval  = 1;
    retval = setsockopt(server, SOL_SOCKET,  SO_REUSEADDR, &optval, optlen);
    assert(retval == 0);

    // Enable socket port reuse
    optval  = 1;
    retval = setsockopt(server, SOL_SOCKET,  SO_REUSEPORT, &optval, optlen);
    assert(retval == 0);

    // Set type of service to low delay
    optval = IPTOS_LOWDELAY;
    retval = setsockopt(server, IPPROTO_IP,  IP_TOS,       &optval, optlen);
    assert(retval == 0);

    // Disable Nagle's Algorithm
    optval  = 1;
    retval = setsockopt(server, IPPROTO_TCP, TCP_NODELAY,  &optval, optlen);
    assert(retval == 0);

    // Check if the values are properly set
    retval = fcntl(server, F_GETFD, FD_CLOEXEC);
    assert(retval == FD_CLOEXEC);

    retval = getsockopt(server, SOL_SOCKET,  SO_REUSEADDR, &optval, &optlen);
    assert(retval == 0 && optlen == 4 && optval == 1);

    retval = getsockopt(server, SOL_SOCKET,  SO_REUSEPORT, &optval, &optlen);
    assert(retval == 0 && optlen == 4 && optval == 1);

    retval = getsockopt(server, IPPROTO_IP,  IP_TOS,       &optval, &optlen);
    assert(retval == 0 && optlen == 4 && optval == IPTOS_LOWDELAY);

    retval = getsockopt(server, IPPROTO_TCP, TCP_NODELAY,  &optval, &optlen);
    assert(retval == 0 && optlen == 4 && optval == 1);

    // Bind socket
    const uint16_t port = 5316;

    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {
            .s_addr = INADDR_ANY
        },
        .sin_zero = {}
    };

    retval = bind(server, (struct sockaddr *) &address, sizeof(struct sockaddr_in));
    assert(retval == 0);
}

void loop() {

}

void quit() {
    close(server);
}
