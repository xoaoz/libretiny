/* Copyright (c) Kuba Szczodrzyński 2026. */

#include <libretiny.h>

lt_ota_type_t lt_ota_get_type() {
	return OTA_TYPE_NONE;
}

bool lt_ota_is_valid(uint8_t index) {
	(void)index;
	return false;
}

uint8_t lt_ota_dual_get_current() {
	return 0;
}

uint8_t lt_ota_dual_get_stored() {
	return 0;
}

bool lt_ota_switch(bool revert) {
	(void)revert;
	return false;
}
