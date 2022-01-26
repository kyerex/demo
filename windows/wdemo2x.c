
#include "demo.h"

int main()

{
    out_open();

    out_cursor_address(3,0);
    out_enter_standout_mode();
    out_str("The window below was created with sm32 mnemonic\n");
    out_str("fwindow(50,50,400,400,\"Hello\",\"font-size: 40px; background-color: #FF0000; color: #ffffff;\")");
    out_exit_standout_mode();

    sm32_out("fwindow(50,50,400,400,\"Hello\",\"font-size: 40px; background-color: #FF0000; color: #ffffff;\")");

    sm32_out("black");
    sm32_out("backgr");
    sm32_out("white");
    sm32_out("default");

    out_clear_screen();
    out_close();

}
