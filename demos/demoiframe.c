
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

int main()
{
    char *hbp,*bp;
    char *left,*right;

    out_open();

    out_clear_screen();
    out_cursor_address(24,0);

    sm32_out("window(-1,-1,-1,-1)");
    //this is window #1

    html_load("html/left.html",&bp);
    if (bp == NULL) {
        abort();    //can't happen
    }
    left=alloca(strlen(bp)+64);
    strcpy(left,bp);
    free(bp);

    html_load("html/right.html",&bp);
    if (bp == NULL) {
        abort();    //can't happen
    }
    right=alloca(strlen(bp)+64);
    strcpy(right,bp);
    free(bp);

    sm32_out("gwin(\"web\")");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","loadform");
    html_load("html/demoiframe.html",&hbp);  //load html file
    if (hbp == NULL) {
        abort();    //can't happen
    }
    set_value("html",hbp);              //place in output
    free(hbp);                          //html_load used malloc

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
    get_value("protocol",&bp);
    if (strcmp(bp,"999") == 0) { // is this an error return
        sm32_out("rm"); // kill all windows go back to console mode 
        out_enter_standout_mode();
        out_str("Error return - check google console\n\n");
        out_exit_standout_mode();
        out_close();
        exit(1);
    }
    sm32_out("pop");
    get_value("DONE",&bp);
    if (*bp != '\0') {
        printf("Done clicked in main window\n");
    }
    get_value("DONE-LEFT",&bp);
    if (*bp != '\0') {
        printf("Done clicked in left IFRAME\n");
    }
    get_value("DONE-RIGHT",&bp);
    if (*bp != '\0') {
        printf("Done clicked in right IFRAME\n");
    }
    get_value("DATA1",&bp);
    printf("DATA1 from \"THEFORM\" = %s\n",bp);
    get_value("DATA2",&bp);
    printf("DATA2 from \"THEFORM\" = %s\n\n",bp);

    out_close();
}
