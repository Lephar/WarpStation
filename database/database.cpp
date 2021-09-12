#include "database.hpp"

#include <iostream>

namespace zero::database {
    Database::Database() {
        connection = PQconnectdb("");

        std::cout << PQdb(connection) << std::endl;
        std::cout << PQuser(connection) << std::endl;
        std::cout << PQpass(connection) << std::endl;
        std::cout << PQhost(connection) << std::endl;
        std::cout << PQhostaddr(connection) << std::endl;
        std::cout << PQport(connection) << std::endl;
    }

    Database::~Database() {
        PQfinish(connection);
    }
}