
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "demo.h"

int main()
{
    char *hbp,*bp;
    time_t t;

    out_open();

    out_clear_screen();
    out_cursor_address(24,0);

    sm32_out("fwindow(100,100,500,300,\
    \"This is demo2\",\"background-color: #DEE1E6; color: #000000;\")"); 
    //this is window #1
    sm32_out("gwin(\"web\")");
    //better be error free we are in web mode

    while (1) {
        html_init();                        //init output
        set_value("protocol","0");
        set_value("type","loadform");
        html_load("html/demo2.html",&hbp);  //load html file
        if (hbp == NULL) {
            abort();    //can't happen
        }

        t=time(0);
        bp=ctime(&t);
        html_replace(&hbp,"????time",bp);
        set_value("html",hbp);              //place in output
        free(hbp);                          //html_load used malloc

        html_out();
        html_in();
        get_value("protocol",&bp);
        if (strcmp(bp,"999") == 0) { // is this an error return
            sm32_out("rm"); // kill all windows go back to console mode 
            out_enter_standout_mode();
            out_str("Error return - check google console\n\n");
            out_exit_standout_mode();
            out_close();
            exit(1);
        }

        get_value("Update",&bp);
        if (*bp == '\0') {
            break;
        }
    }

    sm32_out("pop");

    get_value("CLOSE_CLICKED",&bp);
    if (*bp != '\0') out_str ("The \"Close Clicked\" \n\n");
    get_value("Okay",&bp);
    if (*bp != '\0') out_str ("The \"Okay\" button was clicked\n\n");
    get_value("CHECKBOX",&bp);
    if (0 == strcmp("CHECKED",bp)) { //bp will be "" or "CHECKED"
        out_str("The checkbox named \"CHECKBOX\" is checked\n");
    }
    else {
        out_str("The checkbox named \"CHECKBOX\" is unchecked\n");
    }
    get_value("STRING",&bp);
    out_str("The text box \"STRING\" contains: ");
    out_str(bp);
    out_str("\n\n");

    out_close();
}
