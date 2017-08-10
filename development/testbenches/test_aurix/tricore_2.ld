// file:///C:/Users/jester/Dropbox/mem_layout_mgr/thesis/latex/papers/tricore.pdf

SECTIONS 
{
    CORE_SEC(.text) 0 : 
    { 
      *(*.text) 
      *(*.text.*) 
    }

    CORE_SEC(.data) 0 : 
    { 
      *(.data) 
    } 
}
