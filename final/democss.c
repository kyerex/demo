
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "demo.h"
#include "html/html_files.h"

void check_fatal();

void hload_base64(char *bp,int len,char **h)
{
	int lenx;

	*h=NULL;
    *h=malloc(len * 4/3 +16);
    do_hta64((unsigned char *)bp,len,(unsigned char *)*h,&lenx);
	*(*h+lenx)='\0';
}

void democss()
{
    char *hbp,*bp,*s;
    char *embed,*style0,*style1,*style2,*sound;

    sm32_out("fwindow(50,50,500,450,\
    \"Test Data url\",\"background-color: #DEE1E6; color: #000000;\")"); 
    //this is window #1

    hload_base64(&embed_html_start,embed_html_len,&bp);
    embed=alloca(strlen(bp)+64);
    strcpy(embed,"data:text/html;base64,");
    strcat(embed,bp);
    free(bp);

    style0=alloca(style0_css_len+64);
    strcpy(style0,"data:text/css,");
    strcat(style0,&style0_css_start);

    style1=alloca(style1_css_len+64);
    strcpy(style1,"data:text/css,");
    strcat(style1,&style1_css_start);

    style2=alloca(style2_css_len+64);
    strcpy(style2,"data:text/css,");
    strcat(style2,&style2_css_start);

    hload_base64(&sound_mp3_start,sound_mp3_len,&bp);
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
        hbp=malloc(democss_html_len+1);
        strcpy(hbp,&democss_html_start);
        html_replace(&hbp,"????style",s);
        html_replace(&hbp,"????embed",embed);
        html_replace(&hbp,"????sound",sound);
        set_value("html",hbp);              //place in output
        free(hbp);                          //html_load used malloc

        html_out();
        html_in();
        get_value("protocol",&bp);
        check_fatal();
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
}
