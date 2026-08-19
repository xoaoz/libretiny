/* Copyright (c) Kuba Szczodrzyński 2026. */

#include <libretiny.h>
#include <sdk_private.h>

void lt_get_device_mac(uint8_t *mac) {
	uint8_t efuse[512] = {0};
	EFUSE_LogicalMap_Read(efuse);
	memcpy(mac, efuse + 0x11A, 6);
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
