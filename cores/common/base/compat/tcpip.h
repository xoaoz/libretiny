/* Copyright (c) Kuba Szczodrzyński 2022-05-22. */

#pragma once

#if LT_RTL8710A
#include <lwip/lwip_timers.h>
typedef void (*sys_timeout_handler)(void *arg);
#endif
#include <lwip/tcpip.h>
