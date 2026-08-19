# Copyright (c) Kuba Szczodrzyński 2026.
#
# RTL8710AF / Ameba1 support based on xoaoz/ameba-arduino-1.

from os.path import join

from platformio.platform.board import PlatformBoardConfig
from SCons.Script import Builder, DefaultEnvironment, Environment

env: Environment = DefaultEnvironment()
board: PlatformBoardConfig = env.BoardConfig()
queue = env.AddLibraryQueue("realtek-amb1")
env.ConfigureFamily()

# The Ameba1 SDK is an Arduino package.  Keep the package itself outside
# LibreTiny and consume the SDK's prebuilt RTL8710AF libraries.
env.Replace(
    SDK_SYSTEM_DIR=join("$FRAMEWORK_DIR", "Arduino_package", "hardware", "system"),
    SDK_VARIANT_DIR=join("$FRAMEWORK_DIR", "Arduino_package", "hardware", "variants", "rtl8710"),
    SDK_DIR=join("$FRAMEWORK_DIR", "Arduino_package", "hardware", "variants", "rtl8710"),
)

queue.AppendPublic(
    CCFLAGS=[
        "-mcpu=cortex-m3",
        "-mthumb",
        "-Os",
        "-fno-short-enums",
        "-fno-common",
        "-ffunction-sections",
        "-fdata-sections",
        "-fomit-frame-pointer",
        "-fno-exceptions",
    ],
    CPPDEFINES=[
        "M3",
        "ARDUINO_SDK",
        "BOARD_RTL8710",
        "CONFIG_PLATFORM_8195A",
        ("ERRNO", "1"),
        "MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED",
    ],
    LINKFLAGS=[
        "-mcpu=cortex-m3",
        "-mthumb",
        "-Os",
        "--specs=nano.specs",
        "-Wl,--gc-sections",
        "-Wl,--cref",
        "-Wl,--entry=Reset_Handler",
        "-Wl,--undefined=InfraStart",
        "-Wl,-wrap,rom_psk_CalcGTK",
        "-Wl,-wrap,rom_psk_CalcPTK",
    ],
)

queue.AppendPrivate(
    CFLAGS=[
        "-Wno-implicit-function-declaration",
        "-Wno-incompatible-pointer-types",
        "-Wno-int-conversion",
        "-Wno-pointer-sign",
    ],
)

# Headers from Arduino_package/hardware/platform.txt.
queue.AppendPublic(
    CPPPATH=[
        join("$SDK_SYSTEM_DIR", "project", "realtek_ameba1_va0_example", "inc"),
        join("$SDK_SYSTEM_DIR", "component", "soc", "realtek", "common", "bsp"),
        join("$SDK_SYSTEM_DIR", "component", "os", "freertos"),
        join("$SDK_SYSTEM_DIR", "component", "os", "freertos", "freertos_v8.1.2", "Source", "include"),
        join("$SDK_SYSTEM_DIR", "component", "os", "freertos", "freertos_v8.1.2", "Source", "portable", "GCC", "ARM_CM3"),
        join("$SDK_SYSTEM_DIR", "component", "os", "os_dep", "include"),
        join("$SDK_SYSTEM_DIR", "component", "soc", "realtek", "8195a", "misc", "driver"),
        join("$SDK_SYSTEM_DIR", "component", "common", "api", "network", "include"),
        join("$SDK_SYSTEM_DIR", "component", "common", "api"),
        join("$SDK_SYSTEM_DIR", "component", "common", "api", "platform"),
        join("$SDK_SYSTEM_DIR", "component", "common", "api", "wifi"),
        join("$SDK_SYSTEM_DIR", "component", "common", "api", "wifi", "rtw_wpa_supplicant", "src"),
        join("$SDK_SYSTEM_DIR", "component", "common", "application"),
        join("$SDK_SYSTEM_DIR", "component", "common", "mbed", "api"),
        join("$SDK_SYSTEM_DIR", "component", "common", "mbed", "hal"),
        join("$SDK_SYSTEM_DIR", "component", "common", "mbed", "hal_ext"),
        join("$SDK_SYSTEM_DIR", "component", "common", "mbed", "targets", "hal", "rtl8195a"),
        join("$SDK_SYSTEM_DIR", "component", "common", "network"),
        join("$SDK_SYSTEM_DIR", "component", "common", "network", "lwip", "lwip_v1.4.1", "src", "include"),
        join("$SDK_SYSTEM_DIR", "component", "common", "network", "lwip", "lwip_v1.4.1", "port", "realtek"),
        join("$SDK_SYSTEM_DIR", "component", "soc", "realtek", "8195a", "cmsis"),
        join("$SDK_SYSTEM_DIR", "component", "soc", "realtek", "8195a", "cmsis", "device"),
        join("$SDK_SYSTEM_DIR", "component", "soc", "realtek", "8195a", "fwlib"),
        join("$SDK_SYSTEM_DIR", "component", "soc", "realtek", "8195a", "fwlib", "rtl8195a"),
        join("$SDK_SYSTEM_DIR", "component", "soc", "realtek", "8195a", "misc", "rtl_std_lib", "include"),
        join("$SDK_SYSTEM_DIR", "component", "common", "drivers", "wlan", "realtek", "include"),
        join("$SDK_SYSTEM_DIR", "component", "common", "drivers", "wlan", "realtek", "src", "osdep"),
        join("$SDK_SYSTEM_DIR", "component", "common", "network", "ssl", "polarssl-1.3.8", "include"),
        join("$SDK_SYSTEM_DIR", "component", "common", "network", "ssl", "mbedtls-2.16.1", "include"),
        join("$SDK_SYSTEM_DIR", "component", "common", "network", "ssl", "mbedtls-2.4.0", "include"),
        join("$SDK_SYSTEM_DIR", "component", "common", "network", "ssl", "ssl_ram_map", "rom"),
        join("$SDK_SYSTEM_DIR", "component", "common", "utilities"),
        join("$SDK_SYSTEM_DIR", "component", "common", "file_system", "fatfs"),
        join("$SDK_SYSTEM_DIR", "component", "common", "file_system", "fatfs", "r0.10c", "include"),
    ]
)

# FreeRTOS/LwIP are kept as external LibreTiny packages; the SDK itself
# provides the Ameba1-specific headers and prebuilt application libraries.
env.Replace(FREERTOS_PORT="amb1", FREERTOS_PORT_DEFINE="REALTEK_AMB1")
queue.AddExternalLibrary("freertos")
queue.AddExternalLibrary("freertos-port")
queue.AddExternalLibrary("lwip", port="amb1")

# RTL8710AF SDK libraries from hardware/variants/rtl8710.
queue.AppendPublic(
    LIBPATH=["$SDK_VARIANT_DIR"],
    LIBS=[
        "_ameba",
        "_mmf",
        "_p2p",
        "_platform",
        "_rtlstd",
        "_rtsp",
        "_sdcard",
        "_usbd",
        "_usbh",
        "_websocket",
        "_wlan",
        "_wps",
        "_xmodem",
        "_mdns",
        "_http",
        "_codec",
        "_arduino_alexa",
        "_google_cloud_iot",
        "m",
        "c",
        "nosys",
        "gcc",
    ],
)

# Use the SDK's linker script. It references export-rom_v03.txt and
# sdram_obj_list.txt in the same linker_scripts/gcc directory.
env.GenerateLinkerScript(board, board.get("build.ldscript"))

# Keep the standard LibreTiny ELF output. The Ameba1 post-build image
# conversion is intentionally left to the SDK-specific uploader stage.
env.Replace(
    SIZEPROGREGEXP=r"^(?:bootloader|image2|image3)\s+([0-9]+).*",
    SIZEDATAREGEXP=r"^(?:bootloader|image2|image3)\s+([0-9]+).*",
    SIZECHECKCMD="$SIZETOOL -A -d $SOURCES",
    SIZEPRINTCMD="$SIZETOOL -B -d $SOURCES",
)

queue.BuildLibraries()
