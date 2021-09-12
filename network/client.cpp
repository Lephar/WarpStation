#include "client.hpp"

namespace zero::network {
    Client::Client(int32_t client, in_addr_t ip, uint16_t port) : client(client), ip(ip), port(port) {}
}
