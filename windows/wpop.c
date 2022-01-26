
#include "demo.h"

int main()
{
    out_open();

    sm32_out("pop");

    out_cursor_address(3,0);
    out_clr_eos();
    out_close();

}

