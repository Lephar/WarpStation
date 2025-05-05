#pragma once

#ifndef NDEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbit.h>
#include <string.h>
#include <syslog.h>
#include <limits.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <uuid/uuid.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
