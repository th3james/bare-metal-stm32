MEMORY 
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (rwx) : ORIGIN = 0x02000000, LENGTH = 96K
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
    /* The whole interrupt table is 384 bytes long. Advance to that position. */
    . = 384;
    /* The rest of the code */
    *(.text*)
  } > FLASH /* put the code in the FLASH section */
}
