#include "config.h"
#include "server.h"

int main(const int argc, const char *argv[]) {
    configure(argc, argv);

    dispatchServer();
    commandLoop();

    return EXIT_SUCCESS;
}
