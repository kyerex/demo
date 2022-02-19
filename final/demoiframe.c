
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"
#include "html/html_files.h"

void check_fatal();
void dmessage(char *);

void demoiframe()
{
    char *bp;
    char *left,*right;
    char message[1024];
    char buf[256];

    sm32_out("window(-1,-1,-1,-1)");

    left=alloca(left_html_len+64);
    strcpy(left,&left_html_start);

    right=alloca(right_html_len+64);
    strcpy(right,&right_html_start);

    sm32_out("gwin(\"web\")");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","loadform");
    set_value("html",&demoiframe_html_start);              //place in output
    html_out();

    html_init();
    set_value("protocol","8");
    set_value("type","SETouterHTML");
    set_value("ElementId","left");
    set_value("Text",left);
    html_out();

    html_init();
    set_value("protocol","8");
    set_value("type","SETouterHTML");
    set_value("ElementId","right");
    set_value("Text",right);
    html_out();

    html_in();
    check_fatal();
    sm32_out("pop");
    get_value("DONE",&bp);
    if (*bp != '\0') {
        strcpy(message,"Done clicked in main window\n");
    }
    get_value("DONE-LEFT",&bp);
    if (*bp != '\0') {
        strcpy(message,"Done clicked in left IFRAME\n");
    }
    get_value("DONE-RIGHT",&bp);
    if (*bp != '\0') {
        strcpy(message,"Done clicked in right IFRAME\n");
    }
    get_value("DATA1",&bp);
    sprintf(buf,"DATA1 from \"THEFORM\" = %s\n",bp);
    strcat(message,buf);
    get_value("DATA2",&bp);
    sprintf(buf,"DATA2 from \"THEFORM\" = %s\n\n",bp);
    strcat(message,buf);
    dmessage(message);
}
