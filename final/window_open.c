
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"
#include "html/html_files.h"

void window_open()
{
    char *bp;

    sm32_out("window(-1,-1,-1,-1)");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");
    set_value("html",&window_open_html_start);

    sm32_out("gwin(\"web\")");
    while (1) {
        html_out();
        html_in();
        get_value("PAGE1",&bp);
        if (strcmp("CLICKED",bp) == 0) {
            html_init();
            set_value("html",&window_open_page1_html_start);              //place in popup window
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
            set_value("html",&window_open_page2_html_start);              //place in popup window
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
    sm32_out("pop");


}