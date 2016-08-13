#include <Arduino.h>
#include "MessageHandler.h"

void MessageHandler::onMessage(NMEASerial* serial, String message) {
    int pos = 0;
    String cmd;
    String params;
    if (message.indexOf(',') != -1) {
        cmd = message.substring(0, message.indexOf(','));
        params = message.substring(message.indexOf(',') + 1);
    } else {
        cmd = message;
        params = "";
    }

    for (int i = 0; i < m_numCommands; i++) {
        if (cmd == m_commands[i].command) {
            m_commands[i].callback(params);
            return;
        }
    }
}

void MessageHandler::registerCommand(const String& command, void(*callback)(const String&))
{
    if (m_numCommands >= MAX_COMMANDS)
        return;

    m_commands[m_numCommands].command = command;
    m_commands[m_numCommands].callback = callback;
    m_numCommands++;
}
