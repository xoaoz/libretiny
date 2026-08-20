#pragma once

#include <ArduinoPrivate.h>
#include <Serial.h>
#include <serial_api.h>

struct SerialData {
    serial_t uart{};
    SerialRingBuffer *buf{nullptr};
};
