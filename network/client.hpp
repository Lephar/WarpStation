#ifndef ZERO_SERVER_NETWORK_CLIENT_HPP
#define ZERO_SERVER_NETWORK_CLIENT_HPP

#include "base.hpp"

namespace zero::network {
    class Client {
    private:
        int32_t client;
        in_addr_t ip;
        uint16_t port;
    public:
        Client(int32_t client, in_addr_t ip, uint16_t port);
    };
}

#endif //ZERO_SERVER_NETWORK_CLIENT_HPP
