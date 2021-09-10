#ifndef ZERO_SERVER_NETWORK_CLIENT_HPP
#define ZERO_SERVER_NETWORK_CLIENT_HPP

#include "base.hpp"

namespace zero::network {
    class Client {
    private:
        int32_t client;
        char ip[INET_ADDRSTRLEN];
        uint16_t port;
    public:
        Client(int32_t client, sockaddr_in address);
    };
}

#endif //ZERO_SERVER_NETWORK_CLIENT_HPP
