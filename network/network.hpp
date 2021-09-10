#ifndef ZERO_SERVER_NETWORK_HPP
#define ZERO_SERVER_NETWORK_HPP

#include "base.hpp"
#include "server.hpp"

namespace zero::network {
    class Network {
    private:
        std::unordered_map<const char *, Server> servers;
    public:
        Server &createServer(const char *name, uint32_t port);
        ~Network();
    };
}

#endif //ZERO_SERVER_NETWORK_HPP
