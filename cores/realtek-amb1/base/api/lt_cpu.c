/* Copyright (c) Kuba Szczodrzyński 2026. */

#include <libretiny.h>
#include <sdk_private.h>

lt_cpu_model_t lt_cpu_get_model() {
	return CPU_MODEL_ENUM(FAMILY, 0);
}

uint32_t lt_cpu_get_mac_id() {
	uint8_t efuse[512] = {0};
	EFUSE_LogicalMap_Read(efuse);
	uint32_t id = 0;
	memcpy(&id, efuse + 0x11A + 3, 3);
	return id;
}

const char *lt_cpu_get_core_type() {
	return "ARM Cortex-M3 (ARMv7-M)";
}

uint32_t lt_cpu_get_freq() {
	return CPU_ClkGet(false);
}
