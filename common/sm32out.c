#include "demo.h"

#define osc_start "\033]99;"
#define osc_end "\033\\"

void sm32_out (char *bp)
{
    out_str(osc_start); // start of operating system command 99
    out_str(bp); // sm32 mnemonic
    out_str(osc_end); // end of operating system command 99
    out_flush();
}

