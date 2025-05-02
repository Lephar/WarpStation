#include "database/database.hpp"
#include "network/network.hpp"

#include <string>
#include <iostream>

int main() {
    zero::database::Database database;


    zero::network::Network network;
    auto &server = network.createServer("Game", 7076);
    server.start();

    while(true) {
        std::string command;
        std::cin >> command;

        if(command == "quit")
            break;
    }

    return 0;
}
