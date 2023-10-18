#include <stdint.h>

// See Table 19. STM32L475xx memory map and peripheral register boundary addresses in Datasheet STM32L475xx
#define RCC_BASE 0x40021000
// See AHB2 peripheral clock enable register (RCC_AHB2ENR) in Reference Manual rm0351-stm32l47xxx....
#define RCC_APB2ENR_REGISTER (*(volatile uint32_t *)(RCC_BASE + 0x4C))
// GPIOBEN - enable GPIO port B clock (bit 1) - see rm0351-stm32l47xxx....
#define RCC_APB2ENR_GPIOBEN (1 << 1)



int main(void) {
  // Enable Port B clock
  RCC_APB2ENR_REGISTER |= RCC_APB2ENR_GPIOBEN;
}
