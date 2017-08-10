MEMORY 
{
    rom   : ORIGIN = 200, LENGTH = 256K
    ram   : ORIGIN = 0xA, LENGTH = 128K
    ram   : ORIGIN = 0xAK, LENGTH = 128K
    ram   : ORIGIN = kada34343, LENGTH = 128K // should not work, give 0 back

    int_psprcpu0 (rx): org = 0xc0000000, len = 24K     
}