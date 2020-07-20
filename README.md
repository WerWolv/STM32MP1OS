# STM32MP1OS

A operating system to be running on the STM32MP157C-DK2 development board without the use of any of ST Microelectronic's proprietary binaries, code or tools.

## Overview
- /fsbl : The first stage bootlaoder, loaded by the bootROM

## Building an image
ARM32 gcc (arm-linux-gcc) and genimage is required to build a working image. Both of which come with buildroot.

1. Enter the fsbl folder and type `make`
2. Go back to the root directory and type `./genimage.sh -c genimage.cfg`
3. Flash the generated sdcard.img to your DK2's sdcard with for example `dd`, `rufus` or `balenaEtcher`.
