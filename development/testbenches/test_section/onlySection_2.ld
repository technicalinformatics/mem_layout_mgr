SECTIONS {
  .bss :  { *(.bss)  *(COMMON) }
  .text : { *("1" "2" "3" "4") }
  
  //.data : {
  //  *("13" "14")
  //}
}