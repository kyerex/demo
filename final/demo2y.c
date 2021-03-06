
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "demo.h"
#include "html/html_files.h"

void check_fatal();
void dmessage(char *);

void demo2y()
{
    char *hbp,*bp;
    time_t t;
    char message[1024];

    html_init();
    set_value("protocol","8");
    set_value("type","dialog_open");
    set_value("params","left=200,top=200,width=500,height=350");
    html_out();

    while (1) {
        html_init();                        //init output
        set_value("protocol","0");
        set_value("type","loadform");
        hbp=malloc(demo2_html_len+1);
        strcpy(hbp,&demo2_html_start);

        t=time(0);
        bp=ctime(&t);
        html_replace(&hbp,"????time",bp);
        set_value("html",hbp);              //place in output
        free(hbp);                          //html_load used malloc

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
