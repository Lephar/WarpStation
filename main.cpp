#include "network/network.hpp"

int main() {
    zero::network::Network network;
    auto &server = network.createServer("Game", 7076);
    server.start();
    server.stop();
}
