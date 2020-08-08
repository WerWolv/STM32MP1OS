#!/bin/bash

OPENOCD_SCRIPTS="/usr/share/openocd/scripts"

openocd -f $OPENOCD_SCRIPTS/board/stm32mp15x_dk2.cfg -c "gdb_flash_program enable"