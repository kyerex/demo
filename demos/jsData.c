
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

int main()
{
    char *hbp;
    out_open();

    sm32_out("window(-1,-1,-1,-1)");
    sm32_out("gwin(\"web\")");
    
    html_load("html/window_open_page1.html",&hbp);  //load html file as a single string
    if (hbp == NULL) {
        sm32_out("gwin(\"console\")");
        sm32_out("pop");
        printf("HTML file not found\n");
        abort();    //can't happen
    }
    html_init();
    set_value("protocol","8");
    set_value("type","SETjsData");
    set_value("key","page1");
    set_value("str",hbp);
    free(hbp);
    html_out();

    html_load("html/window_open_page2.html",&hbp);  //load html file as a single string
    if (hbp == NULL) {
        sm32_out("gwin(\"console\")");
        sm32_out("pop");
        printf("HTML file not found\n");
        abort();    //can't happen
    }
    html_init();
    set_value("protocol","8");
    set_value("type","SETjsData");
    set_value("key","page2");
    set_value("str",hbp);
    free(hbp);
    html_out();

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");
    html_load("html/jsData.html",&hbp);  //load html file as a single string
    if (hbp == NULL) {
        printf("HTML file not found\n");
        abort();    //can't happen
    }
    set_value("html",hbp);              //place in output
    free(hbp);                          //html_load used malloc
    html_out();
    html_in();


    sm32_out("gwin(\"console\")");
    sm32_out("pop");

    out_close();

}