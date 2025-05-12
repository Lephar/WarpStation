#pragma once

#include "pch.h"

void initClientList();
void printClientList();
void dispatchClient(int32_t fd, struct sockaddr_in addr);
