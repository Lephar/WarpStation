#pragma once

#include "pch.h"

extern char ip[INET_ADDRSTRLEN];
extern uint16_t port;

void dispatchServer();
void commandLoop();
