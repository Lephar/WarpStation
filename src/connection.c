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

void setConnReuseOpts(Conn *conn) {
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

void setConnOptimOpts(Conn *conn) {
    // Set type of service to low delay
    setSockOptInt(conn->fd, IPPROTO_IP,  IP_TOS,      IPTOS_LOWDELAY);
    debug("\tType of service set to low delay");

    // Disable Nagle's Algorithm
    setSockOptInt(conn->fd, IPPROTO_TCP, TCP_NODELAY, 1);
    debug("\tNagle's Algorithm disabled");
}

Conn *makeConn(int32_t fd, struct sockaddr_in addr) {
    Conn *conn = malloc(sizeof(Conn));

    conn->prev = nullptr;

    uuid_generate(conn->uuid);

    conn->fd = fd;
    conn->addr = addr;

    conn->thread = ULONG_MAX;

    conn->next = nullptr;

    printConn(conn);

    return conn;
}

void printConn(Conn *conn) {
    char uuid[UUID_STR_LEN];
    uuid_unparse_lower(conn->uuid, uuid);

    char ip[INET_ADDRSTRLEN];
    inet_ntop(conn->addr.sin_family, &conn->addr.sin_addr, ip, INET_ADDRSTRLEN);

    const uint16_t port = ntohs(conn->addr.sin_port);

    debug("\tUUID: %s",  uuid);
    debug("\tIP:   %s",  ip);
    debug("\tPort: %hu", port);
}

void destroyConn(Conn *conn)
{
    printConn(conn);

    close(conn->fd);
    debug("\tSocket closed");

    free(conn);
    debug("\tMemory freed");
}
