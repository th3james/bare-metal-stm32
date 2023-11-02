MEMORY 
{
  /* Device Flash start as documented in the Device Family Reference Manual rm0351-stm32l47xxx ... */
  /* Board has 1MB flash, see Board User Manual - STM32L4 Disco - DM00347848.pdf */
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M
  /* Device SRAM1 start and capacity as documented in the Device Family Reference Manual rm0351-stm32l47xxx ... */
  /* Board has 96k SRAM1, see Board User Manual - STM32L4 Disco - DM00347848.pdf */
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}
__reset_stack_pointer = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  .text : {
    /* set initial address to 0 */
    . = 0;
    /* 
     * first entry in vector table is start value for stack pointer,
     * which is the last RAM address
     */
    LONG(__reset_stack_pointer);
    /* 
     * next entry in the vector table is the value the program counter is set to after reset
     * Note: OR with 1 is used to set the LSB to 1, which enables Thumb mode
     */
    LONG(main | 1);
    /* The interrupt table is 384 bytes long
     * 4 * 16 channels for Cortex-M4 core
     * + 4 * 82 channels for STM32L47x/L48x devices 
     *  Advance to that position. */
    . = . + (4 * (16 + 82));
    /* The rest of the code */
    *(.text*)
  } > FLASH /* put the code in the FLASH section */
}
