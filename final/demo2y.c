
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

int main()
{
    char *hbp,*bp;
    int next_flag,i;
    char buf[100];

    out_open();

    out_clear_screen();
    out_cursor_address(24,0);

    html_init();
    set_value("protocol","8");
    set_value("type","dialog_open");
    set_value("params","left=100,top=100,width=500,height=300");
    html_out();

    i=1;
    while (1) {
        html_init();                        //init output
        set_value("protocol","0");
        set_value("type","loadform");
        html_load("html/demo2.html",&hbp);  //load html file
        if (hbp == NULL) {
            abort();    //can't happen
        }

        if (i % 2 == 0) {
            html_replace(&hbp,"????CHECKED","");
            sprintf(buf,"This is iteration %d, Check box is unchecked",i);
            html_replace(&hbp,"????STRING",buf);
        }
        else {
            html_replace(&hbp,"????CHECKED","CHECKED");
            sprintf(buf,"This is iteration %d, Check box is checked",i);
            html_replace(&hbp,"????STRING",buf);
        }
        set_value("html",hbp);              //place in output
        free(hbp);                          //html_load used malloc
        html_out();
        html_in();
        get_value("protocol",&bp);
        if (0 ==strcmp(bp,"999")) { // is this an error return
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
        next_flag=0;
        out_str("\nThe html page returned because:\n\n");
        get_value("CLOSE_CLICKED",&bp);
        if (*bp != '\0') out_str ("The \"Close Clicked\" \n\n");
        get_value("DOIT",&bp);
        if (*bp != '\0') out_str ("The \"DOIT\" button was clicked\n\n");
        get_value("CANCEL",&bp);
        if (*bp != '\0') out_str ("The \"CANCEL\" button was clicked\n\n");
        get_value("NEXT",&bp);
        if (*bp != '\0') {
            out_str ("The \"NEXT\" button was clicked\n\n");
            next_flag=1;
        }
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
        if (next_flag == 0) {
            break;
        }
        i=i+1;
    }
    html_init();
    set_value("protocol","8");
    set_value("type","dialog_close");
    html_out();
    html_in();
    // type=dialogclosed will be returned
    out_close();
}
