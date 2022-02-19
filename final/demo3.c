
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "demo.h"
#include "html/html_files.h"

void check_fatal();
void dmessage(char *);

void demo3()
{
    char *bp;
    char buf[128];
    time_t t;
    char message[1024];

    sm32_out("fwindow(100,100,500,300,\
    \"This is demo3\",\"background-color: #DEE1E6; color: #000000;\")"); 
    //this is window #1
    sm32_out("gwin(\"web\")");
    //better be error free we are in web mode

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","loadform");
    set_value("html",&demo3_html_start);              //place in output

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
    if (*bp != '\0') strcpy (message,"The \"Close Clicked\" \n\n");
    get_value("Okay",&bp);
    if (*bp != '\0') strcpy (message,"The \"Okay\" button was clicked\n\n");
    get_value("CHECKBOX",&bp);
    if (0 == strcmp("CHECKED",bp)) { //bp will be "" or "CHECKED"
        strcat(message,"The checkbox named \"CHECKBOX\" is checked\n");
    }
    else {
        strcat(message,"The checkbox named \"CHECKBOX\" is unchecked\n");
    }
    get_value("STRING",&bp);
    strcat(message,"The text box \"STRING\" contains: ");
    strcat(message,bp);
    strcat(message,"\n\n");
    dmessage(message);
}
