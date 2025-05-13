#include "connection.h"

#include "logger.h"

void setFd(int32_t fd, int32_t val) {
    int32_t retval = fcntl(fd, F_SETFD, val);
    assert(retval == 0);

#if DEBUG
    retval = fcntl(fd, F_GETFD, val);
    assert(retval == val);
#endif
}

void setSockOptInt(int32_t fd, int32_t level, int32_t optname, int32_t optval) {
    int32_t retval = setsockopt(fd, level, optname, &optval, sizeof(int32_t));
    assert(retval == 0);

#if DEBUG
    int32_t  retoptval = -1;
    uint32_t retoptlen = sizeof(int32_t);

    retval = getsockopt(fd, level, optname, &retoptval, &retoptlen);
    assert(retval == 0 && retoptlen == sizeof(int32_t) && retoptval == optval);
#endif
}

void setConnReuseOpts(Connection *conn)
{
    // Set socket close on exec
    setFd(conn->fd, FD_CLOEXEC);
    debug("\tSocket close on exec set");

    // Enable socket address reuse
    setSockOptInt(conn->fd, SOL_SOCKET,  SO_REUSEADDR, 1);
    debug("\tSocket address reuse enabled");

    // Enable socket port reuse
    setSockOptInt(conn->fd, SOL_SOCKET,  SO_REUSEPORT, 1);
    debug("\tSocket port reuse enabled");
}

void setConnOptimOpts(Connection *conn)
{
    // Set type of service to low delay
    setSockOptInt(conn->fd, IPPROTO_IP,  IP_TOS,      IPTOS_LOWDELAY);
    debug("\tType of service set to low delay");

    // Disable Nagle's Algorithm
    setSockOptInt(conn->fd, IPPROTO_TCP, TCP_NODELAY, 1);
    debug("\tNagle's Algorithm disabled");
}

void printConn(Connection *conn) {
    char uuid[UUID_STR_LEN];
    uuid_unparse_lower(conn->uuid, uuid);
    const char *ip = inet_ntoa(conn->ip);
    const uint16_t port = ntohs(conn->port);

    debug("\tUUID: %s",  uuid);
    debug("\tIP:   %s",  ip);
    debug("\tPort: %hu", port);
}

Connection *createConn(int32_t fd, struct sockaddr_in addr)
{
    Connection *conn = malloc(sizeof(Connection));

    conn->fd = fd;
    conn->ip = addr.sin_addr;
    conn->port = addr.sin_port;

    uuid_generate(conn->uuid);

    printConn(conn);

    return conn;
}

void destroyConn(Connection *conn)
{
    printConn(conn);

    pthread_cancel(conn->thread);
    pthread_join(conn->thread, nullptr);
    debug("\tThread cancelled");

    close(conn->fd);
    debug("\tConnection closed");

    free(conn);
    debug("\tMemory freed");
}
