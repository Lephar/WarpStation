#include <iostream>
#include "server.hpp"

namespace zero::network {
    void optimizeSocket(int32_t socket) {
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

        optimizeSocket(server);

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

        return value;
    }

    void Server::setActive(bool value) {
        pthread_rwlock_wrlock(&lock);
        active = value;
        pthread_rwlock_unlock(&lock);
    }

    void *startReceiver(void *context) {
        auto server = reinterpret_cast<Server *>(context);

        while (server->isActive()) {
            // Process updates here
        }

        return nullptr;
    }

    void *startSender(void *context) {
        auto server = reinterpret_cast<Server *>(context);

        while (server->isActive()) {
            // Send updates here
        }

        return nullptr;
    }

    void Server::start() {
        listen(server, SOMAXCONN);

        setActive(true);

        pthread_create(&receiver, nullptr, startReceiver, this);
        pthread_create(&sender, nullptr, startSender, this);
    }

    void Server::stop() {
        setActive(false);

        pthread_join(receiver, nullptr);
        pthread_join(sender, nullptr);

        close(server);
    }
}