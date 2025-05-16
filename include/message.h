#pragma once

#include "pch.h"

enum messageType {
    AGENT_ADD,
    AGENT_MOVE,
    AGENT_REMOVE,
} typedef MessageType;

struct message {                // Size | Offset
    const uint32_t header;      // 4    | 0
    const uint32_t length;      // 4    | 4
    uuid_t sender;              // 16   | 8
    MessageType type;           // 4    | 24
    const uint32_t dataLength;  // 4    | 28
    union {
        uint32_t data[8];       // 32   | 32
        float     vec[8];       // 32   | 32
    };
} typedef Message;

Message createMessage(uuid_t uuid, MessageType type);
void printMessage(Message message);
