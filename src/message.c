#include "message.h"

#include "logger.h"

const char *messageTypeToString(MessageType type) {
    if(  type == AGENT_ADD) {
        return "AGENT_ADD";
    } if(type == AGENT_MOVE) {
        return "AGENT_MOVE";
    } if(type == AGENT_REMOVE) {
        return "AGENT_REMOVE";
    }

    return "UNKNOWN";
}

Message createMessage(uuid_t uuid, MessageType type) {
    Message message = {
        .header     = 0x05030106,
        .length     = sizeof(message),
        .dataLength = sizeof(message.data),
    };

    uuid_copy(message.sender, uuid);
    message.type = type;

    return message;
}

void printMessage(Message message) {
    debug("\tHeader:       0x%08X", message.header);
    debug("\tLength:       %u",     message.length);

    char uuid[UUID_STR_LEN] = {};
    uuid_unparse_lower(message.sender,  uuid);
    debug("\tSender:       %s",     uuid);
    debug("\tMessage Type: %s",     messageTypeToString(message.type));

    debug("\tData Length:  %d",     message.dataLength);
    for(int i = 0; i < message.dataLength / sizeof(uint32_t); i++) {
        debug("\t\t0x%08X", message.data[i]);
    }
}
