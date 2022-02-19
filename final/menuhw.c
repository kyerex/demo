
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"
#include "html/html_files.h"

void check_fatal();
void dmessage(char *);

void menuhw()
{
    char *v;
    char message[1024];

    sm32_out("window(-1,-1,-1,-1)");
    sm32_out("menu(\"CREATE\",\"TESTMENU\")");
    sm32_out("menu(\"APPEND\",\"TESTMENU\",\"\",\"item,12345,Okay\",\"Okay to quit\",0)");
    sm32_out("menu(\"show\",\"TESTMENU\")");
    sm32_out("gwin(\"statuson\")");
    sm32_out("status(\"Hello World menu demo\")");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");
    set_value("html",&helloworld_html_start);              //place in output
    sm32_out("gwin(\"web\")");
    html_out();
    sm32_out("menuon");
    html_in();
    sm32_out("menuoff");

    sm32_out("pop");
    sm32_out("menu(\"show\",\"\")"); // do not show menu
    sm32_out("gwin(\"statusoff\")");
    get_value("OKAY",&v);
    if (*v != '\0') {
        strcpy(message,"\nOkay button clicked\n\n");
    }
    get_value("MENU_CLICKED",&v);
    if (*v != '\0') {
        strcpy(message,"\nMenu Item #");
        strcat(message,v);
        strcat(message," was clicked\n\n");
    }
    dmessage(message);
}