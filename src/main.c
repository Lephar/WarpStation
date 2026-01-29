#include "server.h"

int main(const int argc, const char *argv[]) {
    (void) argc;
    (void) argv;

    dispatchServer();
    commandLoop();

    return EXIT_SUCCESS;
}
