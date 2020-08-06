.syntax unified
.cpu cortex-a7
.fpu softvfp
.thumb

.global _start
.section .crt0
_start:
// Clear bss segment
   /*movs R0, #0x00
    ldr R1, =_bss_start_
    ldr R2, =_bss_end_

BssFillLoop:
    str R0, [R1, #4]!
    cmp R1, R2
    bne BssFillLoop*/

// Setup Stack pointer
    ldr R0, =StackPointerStart
    ldr R0, [R0]
    mov SP, R0

// Branch to main
    ldr R0, =main
    blx R0
    bx lr

.section .rodata

StackPointerStart:
    .word 0x30000000 // End of SYSRAM
