#pragma once

#include "pch.h"

void setFileDescriptorOptionInt(int32_t fd, int32_t val);
void setSocketOptionInt(int32_t fd, int32_t level, int32_t optname, int32_t optval);
