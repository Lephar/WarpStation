#include "client.h"

#include "logger.h"

void dispatchClient(int32_t fd, struct sockaddr_in addr) {
    Client client = {
        .fd = fd,
        .ip = addr.sin_addr,
        .port = addr.sin_port,
    };

    debug("IP:   %s",  inet_ntoa(client.ip));
    debug("Port: %hu", ntohs(client.port));
}
