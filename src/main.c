#include "server.h"

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    initialize();
    loop();
    quit();

    return EXIT_SUCCESS;
}
