/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

// NOTE: this file has the default main() function removed.

#include "rtl8195a.h"
#include "build_info.h"

#if (defined(CONFIG_POST_SIM))
void Simulation_Init(void);
#endif

#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
extern void init_rom_wlan_ram_map(void);
extern VOID wlan_network(VOID);
#endif

#ifdef CONFIG_MBED_ENABLED
extern void __libc_fini_array (void);
extern void __libc_init_array (void);
extern  void SVC_Handler (void);
extern  void PendSV_Handler (void);
extern  void SysTick_Handler (void);

void APP_StartMbed(void)
{
	InterruptForOSInit((VOID*)SVC_Handler,
		(VOID*)PendSV_Handler,
		(VOID*)SysTick_Handler);
	__asm (
		"ldr   r0, =SystemInit\n"
		"blx   r0\n"
		"ldr   r0, =_start\n"
		"bx    r0\n"
	);

	for(;;);

}
#endif

void APP_InitTrace(void) {}

extern void lt_main(void);

// The Main App entry point
void APP_Start(void)
{
	lt_main();
}
