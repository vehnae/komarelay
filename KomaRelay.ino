/*
 * Copyright (c) 2016 Jari Saukkonen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "MessageHandler.h"
#include "MultiRelay.h"
#include "NMEASerial.h"
#include "Version.h"

#define NUM_RELAYS 4
#define BOARD_NAME "KOMARELAY"

static MultiRelay relays[NUM_RELAYS] = {
    MultiRelay(2, 3),
    MultiRelay(4, 5),
    MultiRelay(6, 7),
    MultiRelay(13)
};

static MessageHandler handler;
static NMEASerial serial(&handler);

void setup() {
    Serial.begin(9600);
    handler.registerCommand("TEST", test);
    handler.registerCommand("SET", set);
    handler.registerCommand("STATUS", status);
    test("");
}

void loop() {
}

void serialEvent() {
    serial.onSerialEvent();
}

void test(const String&) {
    serial.print(String(BOARD_NAME) + String(",VER=") + String(KOMARELAY_VERSION));
}

void status(const String&) {
    String message = "STATUS,";
    for (int i = 0; i < NUM_RELAYS; i++) {
        message += "R";
        message += (i+1);
        message += "=";
        message += relays[i].isOn() ? "ON" : "OFF";
        message += ",";
    }
    serial.print(message.substring(0, message.length()-1));
}

void set(const String& params) {
    int pos = 0, next = 0;
    do {
        next = params.indexOf(',', pos);
        int end = (next == -1 ? params.length() : next);
        String cmd = params.substring(pos, next);
        int eq = cmd.indexOf('=');
        if (eq == -1)
            return;
        bool state = cmd.substring(eq+1) == "ON";
        cmd = cmd.substring(0, eq);
        if (cmd.length() == 2 && cmd[0] == 'R') {
            int relay = atoi(&cmd[1])-1;
            if (relay >= 0 && relay < NUM_RELAYS) {
                if (state)
                    relays[relay].on();
                else
                    relays[relay].off();
            }
        } else {
            serial.print("SET,ERR");
            return;
        }
        pos = next+1;
    } while (next != -1);

    serial.print("SET,OK");
}
