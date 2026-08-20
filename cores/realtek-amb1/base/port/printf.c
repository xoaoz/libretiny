/* Copyright (c) Kuba Szczodrzyński 2022-06-19. */

#include <libretiny.h>

#include <printf/printf.h>

#include <serial_api.h>
#include <PinNames.h>

static serial_t log_uart;
static bool log_uart_ready;

uint8_t lt_uart_port = 2;

void putchar_(char c) {
	putchar_p(c, lt_uart_port);
}

void putchar_p(char c, unsigned long port) {
	if (!log_uart_ready) {
		if (port == 0)
			serial_init(&log_uart, PA_23, PA_18);
		else
			serial_init(&log_uart, PA_30, PA_29);
		serial_baud(&log_uart, 115200);
		log_uart_ready = true;
	}
	serial_putc(&log_uart, c);
}

WRAP_PRINTF(rtl_printf);
WRAP_SPRINTF(rtl_sprintf);
WRAP_SNPRINTF(rtl_snprintf);
WRAP_VSNPRINTF(rtl_vsnprintf);
WRAP_VSNPRINTF(rtl_vsnprintf_r);
WRAP_VPRINTF(rtl_vprintf);
WRAP_PRINTF(DiagPrintf);
WRAP_SPRINTF(DiagSPrintf);
WRAP_SNPRINTF(DiagSnPrintf);
WRAP_PRINTF(prvDiagPrintf);
WRAP_SPRINTF(prvDiagSPrintf);
WRAP_VSPRINTF(VSprintf);
WRAP_PRINTF(LOG_PRINTF);
