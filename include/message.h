#pragma once

#include "pch.h"

enum messageType {
    AGENT_ADD,
    AGENT_MOVE,
    AGENT_REMOVE,
} typedef MessageType;

struct message {            // Size | Offset
    const uint32_t header;  // 4    | 0
    const uint32_t length;  // 4    | 4
    uuid_t sender;          // 16   | 8
    MessageType type;       // 4    | 24
    uint32_t agent;         // 4    | 28
    union {
        float vecs[2][3];   // 24   | 32
        uint8_t data[24];   // 24   | 32
    };
    uint32_t placeholder;   // 4    | 56
    const uint32_t footer;  // 4    | 60
} typedef Message;

Message createMessage(uuid_t uuid, MessageType type);
void printMessage(Message message);
