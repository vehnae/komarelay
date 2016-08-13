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
#include <Arduino.h>
#include "MultiRelay.h"

MultiRelay::MultiRelay(int pin) :
    m_isOn(false) {
    addPin(pin);
}

MultiRelay::MultiRelay(int pin1, int pin2) :
    m_isOn(false) {
    addPin(pin1);
    addPin(pin2);
}

void MultiRelay::addPin(int pin) {
    m_pins[m_numPins++] = pin;
    pinMode(pin, OUTPUT);
}

void MultiRelay::on() {
    for (int i = 0; i < m_numPins; i++)
        digitalWrite(m_pins[i], HIGH);
    m_isOn = true;
}

void MultiRelay::off() {
    for (int i = 0; i < m_numPins; i++)
        digitalWrite(m_pins[i], LOW);
    m_isOn = false;
}

bool MultiRelay::isOn() const {
    return m_isOn;
}
