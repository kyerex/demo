
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "demo.h"
#include "html/html_files.h"

void check_fatal();
void dmessage(char *);


void demo3y()
{
    char *bp;
    char buf[128];
    time_t t;
    char message[1024];

    html_init();
    set_value("protocol","8");
    set_value("type","dialog_open");
    set_value("params","left=200,top=200,width=500,height=350");
    html_out();

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
        check_fatal();
        get_value("type",&bp);
	    if (0 == strcmp(bp,"dialogclosed")) {
            strcpy(message,\
            "user closed dialog box - no form information available\n\n");
            dmessage(message);
            return;
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

    html_init();
    set_value("protocol","8");
    set_value("type","dialog_close");
    html_out();
    html_in();
    // type=dialogclosed will be returned
    dmessage(message);
}
