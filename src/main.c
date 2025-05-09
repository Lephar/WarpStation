#include "config.h"
#include "server.h"

int main(const int argc, const char *argv[]) {
    configure(argc, argv);

    initServer();
    loopServer();
    quitServer();

    return EXIT_SUCCESS;
}
