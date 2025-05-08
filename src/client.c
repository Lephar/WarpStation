#include "client.h"

#include "logger.h"

void processClient(const int32_t fd, const struct sockaddr_in addr) {
    Client *client = malloc(sizeof(Client));

    client->fd = fd;
    client->ip = addr.sin_addr;
    client->port = addr.sin_port;

    uuid_generate(client->uuid);
    pthread_create(&client->thread, NULL, dispatchClient, client);
}

void *dispatchClient(void *param)
{
    Client *client = param;

    char uuid[UUID_STR_LEN] = {};
    uuid_unparse_lower(client->uuid, uuid);

    debug("Accepted incoming connection:");
    debug("\tUUID: %s",  uuid);
    debug("\tIP:   %s",  inet_ntoa(client->ip));
    debug("\tPort: %hu", ntohs(client->port));

    free(client);

    return NULL;
}
