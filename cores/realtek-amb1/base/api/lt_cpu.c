/* Copyright (c) Kuba Szczodrzyński 2026. */

#include <libretiny.h>
#include <sdk_private.h>

lt_cpu_model_t lt_cpu_get_model() {
	return CPU_MODEL_ENUM(FAMILY, 0);
}

uint32_t lt_cpu_get_mac_id() {
	uint8_t mac[6] = {0};
	wifi_get_mac_address((char *)mac);
	uint32_t id = 0;
	memcpy(&id, mac + 3, 3);
	return id;
}

const char *lt_cpu_get_core_type() {
	return "ARM Cortex-M3 (ARMv7-M)";
}

uint32_t lt_cpu_get_freq() {
	return 83333333;
}
