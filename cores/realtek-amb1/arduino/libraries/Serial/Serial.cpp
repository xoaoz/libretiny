#if LT_ARD_HAS_SERIAL || DOXYGEN

#include "SerialPrivate.h"

static void serialCallback(uint32_t id, SerialIrq event) {
    SerialData *data = reinterpret_cast<SerialData *>(id);
    if (event != RxIrq || !data || !data->buf)
        return;
    while (serial_readable(&data->uart))
        data->buf->store_char(static_cast<uint8_t>(serial_getc(&data->uart)));
}

void SerialClass::beginPrivate(unsigned long baudrate, uint16_t config) {
    if (!data)
        data = new SerialData;
    data->buf = rxBuf;
    serial_init(&data->uart, static_cast<PinName>(tx), static_cast<PinName>(rx));
    configure(baudrate, config);
    serial_irq_handler(&data->uart, serialCallback, reinterpret_cast<uint32_t>(data));
    serial_irq_set(&data->uart, RxIrq, 1);
}

void SerialClass::configure(unsigned long baudrate, uint16_t config) {
    if (!data)
        return;
    const int dataBits = (config & SERIAL_DATA_MASK) == SERIAL_DATA_7 ? 7 : 8;
    const SerialParity parity =
        (config & SERIAL_PARITY_MASK) == SERIAL_PARITY_EVEN ? ParityEven :
        (config & SERIAL_PARITY_MASK) == SERIAL_PARITY_ODD ? ParityOdd : ParityNone;
    const int stopBits = (config & SERIAL_STOP_BIT_MASK) == SERIAL_STOP_BIT_2 ? 2 : 1;
    serial_baud(&data->uart, baudrate);
    serial_format(&data->uart, dataBits, parity, stopBits);
}

void SerialClass::endPrivate() {
    if (!data)
        return;
    serial_irq_set(&data->uart, RxIrq, 0);
    serial_free(&data->uart);
    delete data;
    data = nullptr;
}

void SerialClass::flush() {
    if (data)
        while (!serial_writable(&data->uart)) {}
}

size_t SerialClass::write(uint8_t c) {
    if (!data)
        return 0;
    serial_putc(&data->uart, c);
    return 1;
}

#endif
