.syntax unified
.cpu cortex-a7
.fpu softvfp
.thumb

.global _start
.section .crt0
_start:

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
