# STM32MP1OS

A operating system to be running on the STM32MP157C-DK2 development board without the use of any of ST Microelectronic's proprietary binaries, code or tools.

## Overview

- /fsbl : The first stage bootlaoder, loaded by the bootROM

## Building an image

ARM32 gcc (e.g `arm-none-eabi-gcc` or `arm-linux-gcc`), a standard library such as `arm-none-eabi-newlib` and `genimage` is required to build a working image. They can be found either within buildroot or on the AUR.

The build process is as easy as typing `make` in the command line.

## Debugging

For debugging a very up-to-date version of `openocd` is required to support the stm32mp1. Easiest way to get this is through the `openocd-git` AUR package. Additionally ARM32 gdb (e.g `arm-none-eabi-gdb` or `arm-linux-gdb`) is needed. The project includes a VSCode launch script to make use of the integrated debugger tools.

To start debugging, start the openocd server by running

```sh
$ ./start_openocd.sh
Open On-Chip Debugger 0.10.0+dev-01372-gfa9a4d4db-dirty (2020-08-08-12:00)
Licensed under GNU GPL v2
...
```
