#include <stdint.h>

// See Table 1. STM32L47x/L48x devices memory map and peripheral register boundary addresses in Device Family Reference Manual rm0351-stm32l47xxx....
// Or Table 19. STM32L475xx memory map and peripheral register boundary addresses in Datasheet STM32L475xx
#define RCC_BASE 0x40021000
// See AHB2 peripheral clock enable register (RCC_AHB2ENR) in Device Family Reference Manual rm0351-stm32l47xxx....
#define RCC_APB2ENR_REGISTER (*(volatile uint32_t *)(RCC_BASE + 0x4C))
// GPIOBEN - enable GPIO port B clock (bit 1) - see rm0351-stm32l47xxx....
#define RCC_APB2ENR_GPIOBEN (1 << 1)

// ‘Device Family Reference Manual rm0351-stm32l47xxx….pdf’ - ‘Table 1. STM32L47x/L48x devices memory map and peripheral register boundary addresses’ - page 78
#define GPIO_PORTB_BASE 0x48000400
// GPIOx_MODER - GPIO port mode register offset - see 8.5.1 GPIO port mode register (GPIOx_MODER) in rm0351-stm32l47xxx...
#define GPIO_MODER_OFFSET 0x0
// Address of GPIOx_MODER for a given port x
#define GPIO_MODER_REGISTER(x) (*(volatile uint32_t *)(x + GPIO_MODER_OFFSET)) 
// Define a mode mask for a given pin n
#define GPIO_MODE_MASK(n) (0x3 << (0x2 * n))
// Set pin n to output mode
#define GPIO_MODE_OUTPUT(n) (0x1 << (0x2 * n))

// Address of GPIO Output Data Rigister
#define GPIO_ODR_OFFSET 0x14
#define GPIO_ODR_REGISTER(x) (*(volatile uint32_t *)(x + GPIO_ODR_OFFSET))
// Set pin n to high
#define GPIO_ODR_PIN(n) (1 << n)

#define GPIO_BLINK_PORT GPIO_PORTB_BASE
#define GPIO_BLINK_PIN 14


int main(void) {
  // Enable Port B clock
  RCC_APB2ENR_REGISTER |= RCC_APB2ENR_GPIOBEN;

  // Clear mode for LED pin
  GPIO_MODER_REGISTER(GPIO_BLINK_PORT) &= ~GPIO_MODE_MASK(GPIO_BLINK_PIN);
  // Set mode for LED pin to output
  GPIO_MODER_REGISTER(GPIO_BLINK_PORT) |= GPIO_MODE_OUTPUT(GPIO_BLINK_PIN);

  for (;;) {
    // Turn LED on
    GPIO_ODR_REGISTER(GPIO_BLINK_PORT) |= GPIO_ODR_PIN(GPIO_BLINK_PIN);
    // Delay
    for (int i = 0; i < 100000; i++) {
      __asm__ volatile("nop");
    }

    // Turn LED off
    GPIO_ODR_REGISTER(GPIO_BLINK_PORT) &= ~GPIO_ODR_PIN(GPIO_BLINK_PIN);
    // Delay
    for (int i = 0; i < 100000; i++) {
      __asm__ volatile("nop");
    }
  }
}
