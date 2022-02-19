
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"
#include "html/html_files.h"

void jsData()
{

    sm32_out("window(-1,-1,-1,-1)");
    sm32_out("gwin(\"web\")");
    
    html_init();
    set_value("protocol","8");
    set_value("type","SETjsData");
    set_value("key","page1");
    set_value("str",&window_open_page1_html_start);
    html_out();

    html_init();
    set_value("protocol","8");
    set_value("type","SETjsData");
    set_value("key","page2");
    set_value("str",&window_open_page2_html_start);
    html_out();

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");
    set_value("html",&jsData_html_start);              //place in output
    html_out();
    html_in();


    sm32_out("gwin(\"console\")");
    sm32_out("pop");
}