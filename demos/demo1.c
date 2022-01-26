
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

int main()
{
    char *hbp,*bp;
    out_open();

    sm32_out("backgr");
    sm32_out("red");
    sm32_out("default");
    sm32_out("cs");                     // set window 0 as red background
    sm32_out("window(12,6,56,14)");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","loadform");
    html_load("html/demo1.html",&hbp);  //load html file as a single string
    if (hbp == NULL) {
        abort();    //can't happen
    }
    set_value("html",hbp);              //place in output
    free(hbp);                          //html_load used malloc
    sm32_out("gwin(\"web\")");
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

    sm32_out("gwin(\"console\")");
    sm32_out("pop");
    sm32_out("backgr");
    sm32_out("black");
    sm32_out("default");
    sm32_out("cs");                     // set window 0 as black background

    out_str("\nThe html page returned because:\n\n");
    get_value("DOIT",&bp);
    if (*bp != '\0') out_str ("The \"DOIT\" button was clicked\n\n");
    get_value("CANCEL",&bp);
    if (*bp != '\0') out_str ("The \"CANCEL\" button was clicked\n\n");
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

    out_str("Terminal:");
    out_str(ttyname(0));
    out_str("\n\n");

    out_close();
}
