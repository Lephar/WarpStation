#include "server.h"

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    initServer();
    loopServer();
    quitServer();

    return EXIT_SUCCESS;
}
