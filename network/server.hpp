#ifndef ZERO_SERVER_NETWORK_SERVER_HPP
#define ZERO_SERVER_NETWORK_SERVER_HPP

#include "base.hpp"
#include "client.hpp"

namespace zero::network {
    class Server {
    private:
        int32_t server;

        bool active;
        pthread_rwlock_t lock; // TODO: Use atomics

        pthread_t listener;
        pthread_t receiver;
        pthread_t sender;

        std::vector<Client> clients; //TODO: Change to set
    public:
        explicit Server(uint32_t port);

        bool isActive();

        void setActive(bool value);

        void listenLoop();

        void receiveLoop();

        void sendLoop();

        void start();

        void stop();
    };
}

#endif //ZERO_SERVER_NETWORK_SERVER_HPP
