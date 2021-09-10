#ifndef ZERO_SERVER_NETWORK_SERVER_HPP
#define ZERO_SERVER_NETWORK_SERVER_HPP

#include "base.hpp"

namespace zero::network {
    class Server {
    private:
        int32_t server;

        bool active;
        pthread_rwlock_t lock;

        pthread_t receiver;
        pthread_t sender;
    public:
        explicit Server(uint32_t port);

        bool isActive();

        void setActive(bool value);

        void start();

        void stop();
    };
}

#endif //ZERO_SERVER_NETWORK_SERVER_HPP
