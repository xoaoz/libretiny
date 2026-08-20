/* Copyright (c) Kuba Szczodrzyński 2026. */

#include <libretiny.h>
#include <sdk_private.h>

lt_flash_id_t lt_flash_get_id() {
	// Ameba1's SDK does not expose the flash_read_id() helper used by
	// AmebaZ. Keep the API available and let the SDK own flash calibration.
	lt_flash_id_t id = {0};
	return id;
}
