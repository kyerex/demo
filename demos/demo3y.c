
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "demo.h"

int main()
{
    char *hbp,*bp;
    char buf[128];
    time_t t;

    out_open();

    out_clear_screen();
    out_cursor_address(24,0);

    html_init();
    set_value("protocol","8");
    set_value("type","dialog_open");
    set_value("params","left=200,top=200,width=500,height=350");
    html_out();
    //this is window #1
    sm32_out("gwin(\"web\")");
    //better be error free we are in web mode

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","loadform");
    html_load("html/demo3.html",&hbp);  //load html file
    if (hbp == NULL) {
        abort();    //can't happen
    }

    set_value("html",hbp);              //place in output
    free(hbp);                          //html_load used malloc

    while (1) {
        html_out();
        t=time(0);
        bp=ctime(&t);
        sprintf(buf,"<span ID=\"TOD\">%s</span>",bp);
        html_init();
        set_value("protocol","8");
        set_value("type","SETouterHTML");
        set_value("ElementId","TOD");
        set_value("Text",buf);
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
        get_value("type",&bp);
	    if (0 == strcmp(bp,"dialogclosed")) {
               out_enter_standout_mode();
               out_str(\
               "user closed dialog box - no form information available\n\n");
               out_exit_standout_mode();
               out_close();
               exit(0);
        }
        get_value("Update",&bp);
        if (*bp == '\0') {
            break;
        }
        html_init();                        //init output
        set_value("protocol","0");
        set_value("type","loadform");
        set_value("html"," ");              // do not redisplay
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

    html_init();
    set_value("protocol","8");
    set_value("type","dialog_close");
    html_out();
    html_in();
    // type=dialogclosed will be returned
    out_close();
}
