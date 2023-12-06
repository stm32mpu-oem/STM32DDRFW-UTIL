Release Notes for STM32DDRFW-UTIL
=================================

Copyright © 2023 STMicroelectronics  

<a href="https://www.st.com" class="logo"><img src="_htmresc/st_logo_2020.png" alt="ST logo" /></a>

Purpose
=======

<span style="font-weight: bold;">The STM32DDRFW-UTIL is the firmware
package for DDR configuration and test.</span>

This firmware contains a minimal set of drivers based on STM32CubeMP2xx
Firmware package:

-   HAL drivers
-   CMSIS Device
-   Cortex-A CMSIS Core
-   BSP for STM32MP2 Series MPUs
-   imageheader
-   resourcemanager

The DDR\_Tool directory includes STM32CubeIDE Projects for all ST
supported boards

Update history
==============

**V0.3.0 / 04-December-2023**

STM32MP2 beta release of STM32DDRFW-UTIL.

-   Rename legacy STM32MP257F board support with _CUT1 suffix.
-   Add STM32MP257F-EV1 (MB1936C) and STM32MP257F-VALID3 (MB1706C) board support with up to 4GB size support in aarch64 build environment (local toolchain) with STM32 V2.2 header.
-   Add resourcemanager to solve STM32MP257F-EV1 BSP dependencies.
-   Rebase all elements.

**V0.2.0 / 14-April-2023**

STM32MP2 alpha release of STM32DDRFW-UTIL.

-   Support of STM32MP257F-EV1 (MB1936) board.
-   Improve board customization capability.
-   Add imageheader to generate stm32 files with STM32CubeIDE.
-   Rebase all elements.

**V0.1.0 / 03-December-2022**

STM32MP2 pre-alpha release of STM32DDRFW-UTIL.

-   First STM32MP2 release.
-   Support of STM32MP257F-VALID3 (MB1706) board.

For complete documentation, visit: <span style="background-color: yellow;">[&lt;here&gt;](http://www.st.com/en/microcontrollers-microprocessors/stm32-arm-cortex-mpus.html)</span>
