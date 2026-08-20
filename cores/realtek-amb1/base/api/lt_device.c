/* Copyright (c) Kuba Szczodrzyński 2026. */

#include <libretiny.h>
#include <sdk_private.h>

void lt_get_device_mac(uint8_t *mac) {
	wifi_get_mac_address((char *)mac);
}

bool lt_reboot_download_mode() {
	NVIC_SystemReset();
	while (1) {}
	return true;
}

bool lt_set_debug_mode(lt_debug_mode_t mode) {
	// Ameba1 exposes SWD/JTAG through the ROM pinmux. Do not change the
	// debug pins from application code; J-Link/OpenOCD owns this state.
	return mode == DEBUG_MODE_OFF || mode == DEBUG_MODE_SWD;
}
