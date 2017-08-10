MEMORY 
{ 
    rom (rx)  : ORIGIN = 0, LENGTH = 256K 
    ram (!rx) : org = 0x40000000, l = 4M
}
