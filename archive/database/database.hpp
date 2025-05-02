#ifndef ZERO_SERVER_DATABASE_HPP
#define ZERO_SERVER_DATABASE_HPP

#include "base.hpp"

namespace zero::database {
    class Database {
    private:
        PGconn *connection;
    public:
        Database();
        ~Database();
    };
}

#endif //ZERO_SERVER_DATABASE_HPP
