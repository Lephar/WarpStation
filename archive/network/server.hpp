#ifndef ZERO_SERVER_NETWORK_SERVER_HPP
#define ZERO_SERVER_NETWORK_SERVER_HPP

#include "base.hpp"
#include "client.hpp"

namespace zero::network {
    class Server {
    private:
        int32_t server;

        bool active;
        pthread_rwlock_t statusLock; // TODO: Use atomics (maybe?)

        pthread_t listener;
        pthread_t receiver;
        pthread_t sender;

        std::list<Client> clients; // TODO: Add hashing and change to set
        pthread_rwlock_t listLock;
    public:
        explicit Server(uint32_t port);

        bool isActive();

        void setActive(bool value);

        void listenLoop();

        void receiveLoop();

        void sendLoop();

        void start();

        void stop();

        ~Server();
    };
}

#endif //ZERO_SERVER_NETWORK_SERVER_HPP
