CORE_SYM( CSA_SIZE) = DEFINED(CORE_SYM( CSA_SIZE)) ? CORE_SYM( CSA_SIZE) : 2K ;

SECTIONS 
{
    CORE_SEC(.text) : ALIGN(8) FLAGS(axl) 
    {
      *(*.text) 
      *(*.text.*) 
    } > CODE_MEM = 0 

    CORE_SEC(.data) : ALIGN(8) FLAGS(awl) 
    {
      *(*.data)
      *(*.data.*)
    } > CORE_SYM(DATA) AT > CODE_MEM 
}
