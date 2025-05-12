#pragma once

#include "pch.h"

void initClientList();
void dispatchClient(int32_t fd, struct sockaddr_in addr);
