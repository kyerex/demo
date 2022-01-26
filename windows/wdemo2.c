
#include "demo.h"

int main()
{
    out_open();

    out_cursor_address(3,0);
    out_enter_standout_mode();
    out_str("The window below was created with sm32 mnemonic fwindow(150,200,400,250,\"Title\")");
    out_exit_standout_mode();

    sm32_out("fwindow(150,200,400,250,\"Title\")");
    sm32_out("black");
    sm32_out("backgr");
    sm32_out("white");
    sm32_out("default");

    out_clear_screen();
    out_close();

}
