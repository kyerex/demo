
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

int main()
{
    char *hbp;
    out_open();

    sm32_out("window(-1,-1,-1,-1)");

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
    html_in();
    sm32_out("gwin(\"console\")");

    sm32_out("pop");

    out_close();

}