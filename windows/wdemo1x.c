
#include "demo.h"

int main()
{
    out_open();

    out_cursor_address(3,0);
    out_enter_standout_mode();
    out_str("The window below was created with the sm32 mnemonic window(10,5,60,15,\"Title\")");
    out_exit_standout_mode();

    sm32_out("blue");
    sm32_out("backgr");
    sm32_out("yellow");
    sm32_out("window(10,5,60,15,\"Title\")");
    sm32_out("white");
    sm32_out("backgr");
    sm32_out("black");

    out_close();

}
