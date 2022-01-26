
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

#include "html/html_files.h"

void get_demo2_html(char **bp);

int main()
{
    char *hbp,*bp;
    int next_flag,i;
    char buf[100];

    out_open();

    out_clear_screen();
    out_cursor_address(24,0);

    sm32_out("fwindow(100,100,500,300,\
    \"This is demo2\",\"background-color: #DEE1E6; color: #000000;\")"); 
    //this is window #1
    sm32_out("gwin(\"web\")");
    //better be error free we are in web mode

    i=1;
    while (1) {
        html_init();                        //init output
        set_value("protocol","0");
        set_value("type","loadform");
        //get_demo2_html(&hbp);
        //html_load("html/demo2.html",&hbp);  //load html file
        hbp=malloc(strlen(demo2_html));
        strcpy(hbp,demo2_html);
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
        if (strcmp(bp,"999") == 0) { // is this an error return
            sm32_out("rm"); // kill all windows go back to console mode 
            out_enter_standout_mode();
            out_str("Error return - check google console\n\n");
            out_exit_standout_mode();
            out_close();
            exit(1);
        }

        sm32_out("goto(0)");

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
            sm32_out("drop(1)");
            break;
        }
        i=i+1;
        sm32_out("goto(1)");
    }

    out_close();
}
