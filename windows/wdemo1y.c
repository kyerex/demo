#include "demo.h"

int main()
{
    out_open();

    out_cursor_address(3,0);
    out_enter_standout_mode();
    out_str("The window below was created with the sm32 mnemonic window(10,5,60,15) ");
    out_exit_standout_mode();

    sm32_out("window(10,5,60,15)");

    sm32_out("backgr"); //next color becomes back ground color
    sm32_out("red");
    sm32_out("default");//make it the default so CS clears to red

    out_clear_screen();
    out_close();

}
