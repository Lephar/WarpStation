#include "network/network.hpp"

int main() {
    zero::network::Network network;
    zero::network::Server &server = network.createServer("Game", 7076);
    server.start();
    server.stop();
}
