
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"

int main()
{
    char *hbp,*bp,*s;
    char *embed,*style0,*style1,*style2,*sound;

    out_open();

    out_clear_screen();
    out_cursor_address(24,0);

    sm32_out("fwindow(50,50,500,450,\
    \"Test Data url\",\"background-color: #DEE1E6; color: #000000;\")"); 
    //this is window #1

    html_load_base64("html/embed.html",&bp);
    if (bp == NULL) {
        abort();    //can't happen
    }
    embed=alloca(strlen(bp)+64);
    strcpy(embed,"data:text/html;base64,");
    strcat(embed,bp);
    free(bp);

    html_load("html/style0.css",&bp);
    if (bp == NULL) {
        abort();    //can't happen
    }
    style0=alloca(strlen(bp)+64);
    strcpy(style0,"data:text/css,");
    strcat(style0,bp);
    free(bp);

    html_load("html/style1.css",&bp);
    if (bp == NULL) {
        abort();    //can't happen
    }
    style1=alloca(strlen(bp)+64);
    strcpy(style1,"data:text/css,");
    strcat(style1,bp);
    free(bp);

    html_load("html/style2.css",&bp);
    if (bp == NULL) {
        abort();    //can't happen
    }
    style2=alloca(strlen(bp)+64);
    strcpy(style2,"data:text/css,");
    strcat(style2,bp);
    free(bp);

    html_load_base64("html/sound.mp3",&bp);
    if (bp == NULL) {
        abort();    //can't happen
    }
    sound=alloca(strlen(bp)+64);
    strcpy(sound,"data:audio/mpeg;base64,");
    strcat(sound,bp);
    free(bp);

    sm32_out("gwin(\"web\")");

    s=style1;
    while (1) {
        html_init();                        //init output
        set_value("protocol","0");
        set_value("type","load");
        html_load("html/democss.html",&hbp);  //load html file
        if (hbp == NULL) {
            abort();    //can't happen
        }
        html_replace(&hbp,"????style",s);
        html_replace(&hbp,"????embed",embed);
        html_replace(&hbp,"????sound",sound);
        set_value("html",hbp);              //place in output
        free(hbp);                          //html_load used malloc

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
        get_value("DONE",&bp);
        if (*bp != '\0') {
            break;
        }
        get_value("CLOSE_CLICKED",&bp);
        if (*bp != '\0'){
            break;
        } 
        get_value("STYLE0",&bp);
        if (*bp != '\0'){
            s=style0;
        }
        get_value("STYLE1",&bp);
        if (*bp != '\0'){
            s=style1;
        }
        get_value("STYLE2",&bp);
        if (*bp != '\0'){
            s=style2;
        }
    }

    sm32_out("pop");
    out_close();
}
