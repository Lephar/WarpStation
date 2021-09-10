#include "network.hpp"

namespace zero::network {
    Server &Network::createServer(const char *name, uint32_t port) {
        return servers.emplace(std::piecewise_construct, std::forward_as_tuple(name), std::forward_as_tuple(port)).first->second;
    }

    Network::~Network() {
        for(auto& server : servers)
            server.second.stop();
    }
}