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
    Message message;

    uuid_copy(message.sender, uuid);
    message.type = type;
    message.agent = UINT32_MAX;

    return message;
}

void printMessage(Message message) {
    debug("\tHeader: %x", message.header);
    debug("\tLength: %u", message.length);

    char uuid[UUID_STR_LEN] = {};
    uuid_unparse_lower(message.sender, uuid);
    debug("\tSender: %s", uuid);

    debug("\tMessage Type: %s", messageTypeToString(message.type));
    debug("\tAgent ID: %u",     message.agent);

    debug("\tVector 1: [%g %g %g]", message.vecs[0][0], message.vecs[0][1], message.vecs[0][2]);
    debug("\tVector 2: [%g %g %g]", message.vecs[1][0], message.vecs[1][1], message.vecs[1][2]);

    debug("\tPlaceholder: %x", message.placeholder);
    debug("\tFooter: %x",      message.footer);
}
