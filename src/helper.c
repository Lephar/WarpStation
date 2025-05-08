#include "helper.h"

#include "logger.h"

// TODO: Does this override previously set flags?
void setFileDescriptorOptionInt(const int32_t fd, const int32_t val) {
    int32_t retval = fcntl(fd, F_SETFD, val);
    assert(retval == 0);

#if DEBUG
    retval = fcntl(fd, F_GETFD, val);
    assert(retval == val);
#endif
}

void setSocketOptionInt(const int32_t fd, const int32_t level, const int32_t optname, const int32_t optval) {
    int32_t retval = setsockopt(fd, level, optname, &optval, sizeof(int32_t));
    assert(retval == 0);

#if DEBUG
    int32_t  retoptval = -1;
    uint32_t retoptlen = sizeof(int32_t);

    retval = getsockopt(fd, level, optname, &retoptval, &retoptlen);
    assert(retval == 0 && retoptlen == sizeof(int32_t) && retoptval == optval);
#endif
}
