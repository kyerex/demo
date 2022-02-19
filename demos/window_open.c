
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

int main()
{
    char *hbp,*bp;
    out_open();

    sm32_out("window(-1,-1,-1,-1)");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");
    html_load("html/window_open.html",&hbp);  //load html file as a single string
    if (hbp == NULL) {
        printf("HTML file not found\n");
        abort();    //can't happen
    }
    set_value("html",hbp);              //place in output
    free(hbp);                          //html_load used malloc
    sm32_out("gwin(\"web\")");
    while (1) {
        html_out();
        html_in();
        get_value("PAGE1",&bp);
        if (strcmp("CLICKED",bp) == 0) {
            html_init();
            html_load("html/window_open_page1.html",&hbp);  //load html file as a single string
            if (hbp == NULL) {
                sm32_out("gwin(\"console\")");
                sm32_out("pop");
                printf("HTML file not found\n");
                abort();    //can't happen
            }
            set_value("html",hbp);              //place in popup window
            free(hbp);                          //html_load used malloc
            set_value("name","MYHELP");
            set_value("params","width=600,height=400,top=20,left=20");
            set_value("protocol","8");
            set_value("type","window_open");
            html_out();
            // no input is returned
            html_init();
            set_value("protocol","0");
            set_value("type","load");
            set_value("html"," "); //leave main page as is 
            continue;
        }
        get_value("PAGE2",&bp);
        if (strcmp("CLICKED",bp) == 0) {
            html_init();
            html_load("html/window_open_page2.html",&hbp);  //load html file as a single string
            if (hbp == NULL) {
                sm32_out("gwin(\"console\")");
                sm32_out("pop");
                printf("HTML file not found\n");
                abort();    //can't happen
            }
            set_value("html",hbp);              //place in popup window
            free(hbp);                          //html_load used malloc
            set_value("name","MYHELP");
            set_value("params","width=600,height=400,top=20,left=20");
            set_value("protocol","8");
            set_value("type","window_open");
            html_out();
            html_init();
            set_value("protocol","0");
            set_value("type","load");
            set_value("html"," "); //leave main page as is 
            continue;
        }
        break; // must be done
    }
    sm32_out("gwin(\"console\")");

    sm32_out("pop");

    out_close();

}