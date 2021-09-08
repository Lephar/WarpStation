#include "server.hpp"

namespace zero::network {
    void setSocketProperties(int32_t socket) {
        int32_t nodelayValue = 1;
        uint8_t tosValue = IPTOS_LOWDELAY;

        setsockopt(socket, IPPROTO_IP, IP_TOS, &tosValue, sizeof(uint8_t));
        setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, &nodelayValue, sizeof(int32_t));
    }

    Server::Server(uint32_t port) : lock(), receiver(), sender() {
        active = false;
        pthread_rwlock_init(&lock, nullptr);

        server = socket(AF_INET, SOCK_STREAM, 0);

        int32_t reuseaddrValue = 1;
        setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &reuseaddrValue, sizeof(int32_t));

        setSocketProperties(server);

        sockaddr_in serverAddress = {
                .sin_family = AF_INET,
                .sin_port = htons(port),
                .sin_addr = {
                        .s_addr = INADDR_ANY
                }
        };

        static_cast<void>(bind(server, reinterpret_cast<sockaddr *>(&serverAddress), sizeof(sockaddr_in)));
    }

    bool Server::isActive() {
        pthread_rwlock_rdlock(&lock);
        bool value = active;
        pthread_rwlock_unlock(&lock);

        return value; // TODO: Synchronization
    }

    void *startReceiver(void *context) {
        auto server = reinterpret_cast<Server *>(context);

        while (server->isActive()) {

        }

        return nullptr;
    }

    void *startSender(void *context) {
        auto server = reinterpret_cast<Server *>(context);

        while (server->isActive()) {

        }

        return nullptr;
    }

    void Server::start() {
        listen(server, SOMAXCONN);

        pthread_rwlock_wrlock(&lock);
        active = true;
        pthread_rwlock_unlock(&lock);


        pthread_create(&receiver, nullptr, startReceiver, this);
        pthread_create(&sender, nullptr, startSender, this);
    }

    void Server::stop() {
        pthread_rwlock_wrlock(&lock);
        active = false;
        pthread_rwlock_unlock(&lock);

        pthread_join(receiver, nullptr);
        pthread_join(sender, nullptr);

        close(server);
    }
}