
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

int main()
{
    char *hbp;
    char *v;
    out_open();

    sm32_out("window(-1,-1,-1,-1)");
    sm32_out("menu(\"CREATE\",\"TESTMENU\")");
    sm32_out("menu(\"APPEND\",\"TESTMENU\",\"\",\"item,12345,Okay\",\"Okay to quit\",0)");
    sm32_out("menu(\"show\",\"TESTMENU\")");
    sm32_out("gwin(\"statuson\")");
    sm32_out("status(\"Hello World menu demo\")");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");
    html_load("html/helloworld.html",&hbp);  //load html file as a single string
    if (hbp == NULL) {
        printf("HTML file not found\n");
        abort();    //can't happen
    }
    set_value("html",hbp);              //place in output
    free(hbp);                          //html_load used malloc
    sm32_out("gwin(\"web\")");
    html_out();
    sm32_out("menuon");
    html_in();
    sm32_out("menuoff");
    sm32_out("gwin(\"console\")");

    sm32_out("pop");
    sm32_out("menu(\"show\",\"\")"); // do not show menu
    sm32_out("gwin(\"statusoff\")");
    get_value("OKAY",&v);
    if (*v != '\0') {
        out_str("\nOkay button clicked\n\n");
    }
    get_value("MENU_CLICKED",&v);
    if (*v != '\0') {
        out_str("\nMenu Item #");
        out_str(v);
        out_str(" was clicked\n\n");
    }
    out_close();

}