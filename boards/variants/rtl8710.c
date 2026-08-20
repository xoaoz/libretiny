#include <Arduino.h>

#ifdef LT_VARIANT_INCLUDE
#include LT_VARIANT_INCLUDE
#endif

PinInfo lt_arduino_pin_info_list[PINS_COUNT] = {
    {PA_0, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PA_1, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PA_2, PIN_GPIO | PIN_IRQ | PIN_ADC, PIN_NONE, 0},
    {PA_3, PIN_GPIO | PIN_IRQ | PIN_ADC, PIN_NONE, 0},
    {PA_4, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PA_5, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PA_6, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PA_7, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PA_3, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PA_2, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PB_1, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PB_3, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PB_5, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PB_4, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PB_6, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PA_7, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PB_2, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PC_7, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
    {PB_7, PIN_GPIO | PIN_IRQ, PIN_NONE, 0},
};

PinInfo *lt_arduino_pin_gpio_map[PINS_GPIO_MAX + 1] = {
    [0] = &lt_arduino_pin_info_list[0], [1] = &lt_arduino_pin_info_list[1],
    [2] = &lt_arduino_pin_info_list[2], [3] = &lt_arduino_pin_info_list[3],
    [4] = &lt_arduino_pin_info_list[4], [5] = &lt_arduino_pin_info_list[5],
    [6] = &lt_arduino_pin_info_list[6], [7] = &lt_arduino_pin_info_list[7],
    [8] = &lt_arduino_pin_info_list[8], [9] = &lt_arduino_pin_info_list[9],
    [10] = &lt_arduino_pin_info_list[10], [11] = &lt_arduino_pin_info_list[11],
    [12] = &lt_arduino_pin_info_list[12], [13] = &lt_arduino_pin_info_list[13],
    [14] = &lt_arduino_pin_info_list[14], [15] = &lt_arduino_pin_info_list[15],
    [16] = &lt_arduino_pin_info_list[16], [17] = &lt_arduino_pin_info_list[17],
    [18] = &lt_arduino_pin_info_list[18],
};
