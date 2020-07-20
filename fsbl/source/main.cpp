#include <stdint.h>

#define BIT(bit) (1 << bit) 
#define REGISTER(base, offset) *(base + offset)



int main() {

    uint32_t *RCC_BASE = (uint32_t*)(0x5000'0000);
    uint32_t AHB4ENSETR = 0xA28; 

    uint32_t *GPIOD_BASE = (uint32_t*)(0x5000'5000);
    uint32_t *GPIOH_BASE = (uint32_t*)(0x5000'9000);

    uint32_t GPIO_MODER = 0x00;
    uint32_t GPIO_ODR = 0x14;
        
    REGISTER(RCC_BASE, AHB4ENSETR) |= BIT(3) | BIT(7); // Enable clocks for GPIOD and GPIOH

    REGISTER(GPIOD_BASE, GPIO_MODER) &= ~(0b11 << 22);
    REGISTER(GPIOH_BASE, GPIO_MODER) &= ~(0b11 << 14);

    REGISTER(GPIOD_BASE, GPIO_MODER) |= 0b01 << 22;
    REGISTER(GPIOH_BASE, GPIO_MODER) |= 0b01 << 14;

    REGISTER(GPIOD_BASE, GPIO_ODR) |= BIT(11);
    REGISTER(GPIOH_BASE, GPIO_ODR) |= BIT(7);

    // AHB4
    // PD11 : LED_B
    // PH7 : LED_Y

    while(true);
}