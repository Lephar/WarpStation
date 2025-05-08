#include "client.h"

#include "logger.h"

void dispatchClient(const int32_t fd, const struct sockaddr_in addr) {
    const Client client = {
        .fd = fd,
        .ip = addr.sin_addr,
        .port = addr.sin_port,
    };

    debug("IP:   %s",  inet_ntoa(client.ip));
    debug("Port: %hu", ntohs(client.port));
}
