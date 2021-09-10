#include "client.hpp"

namespace zero::network {
    Client::Client(int32_t client, sockaddr_in address) : client(client){
        port = address.sin_port;
        inet_ntop(AF_INET, &(address.sin_addr), ip, INET_ADDRSTRLEN);
    }
}
