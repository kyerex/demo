
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"
#include "html/html_files.h"

void check_fatal();
void dmessage(char *);

void demo1()
{
    char *bp;
    char message[1024];

    sm32_out("window(12,6,56,14)");
    sm32_out("gwin(\"web\")");
    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","loadform");
    set_value("html",&demo1_html_start);
    html_out();
    html_in();
    check_fatal();

    sm32_out("pop");

    strcpy(message,"\nThe html page returned because:\n\n");
    get_value("DOIT",&bp);
    if (*bp != '\0') strcat (message,"The \"DOIT\" button was clicked\n\n");
    get_value("CANCEL",&bp);
    if (*bp != '\0') strcat (message,"The \"CANCEL\" button was clicked\n\n");
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
