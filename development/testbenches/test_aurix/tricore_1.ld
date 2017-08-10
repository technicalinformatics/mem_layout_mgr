// c0, ... c6
// tricore page 279

MEMORY
{
    /* internal code ram */ 
    int_psprcpu0 (rx!c1): org = 0xc0000000, len = 24K
    int_psprcpu1 (rxc1): org = 0xc0000000, len = 24K 
    int_psprcpu2 (rxc2): org = 0xc0000000, len = 24K

    /* internal data ram */
    int_dsprcpu0 (wc0!x): org = 0xd0000000, len = 112K 
    int_dsprcpu1 (wc1!x): org = 0xd0000000, len = 120K 
    int_dsprcpu2 (wc2!x): org = 0xd0000000, len = 120K

    /* global view on internal memories */ 
    glb_int_psprcpu0 (rx):  org = 0x70100000, len =  24K
    glb_int_psprcpu1 (rx):  org = 0x60100000, len =  24K
    glb_int_psprcpu2 (rx):  org = 0x50100000, len =  24K
    glb_int_dsprcpu0 (w!x): org = 0x70000000, len = 112K
    glb_int_dsprcpu1 (w!x): org = 0x60000000, len = 120K
    glb_int_dsprcpu2 (w!x): org = 0x50000000, len = 120K

}

