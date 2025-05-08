#include "server.h"

int main(const int argc, const char *argv[]) {
    (void) argc;
    (void) argv;

    initServer();
    loopServer();
    quitServer();

    return EXIT_SUCCESS;
}
