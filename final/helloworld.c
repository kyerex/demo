
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"
#include "html/html_files.h"

void check_fatal();

void helloworld()
{
    sm32_out("window(-1,-1,-1,-1)");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");
    set_value("html",&helloworld_html_start);              //place in output
    sm32_out("gwin(\"web\")");
    html_out();
    html_in();
    check_fatal();

    sm32_out("pop");
}