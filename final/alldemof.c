
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include "demo.h"
#include "html/html_files.h"

void helloworld();
void demo1();
void demo2x();
void demo3x();
void demoiframe();
void menuhw();
void demo2();
void demo3();
void democss();
void demo2y();
void demo3y();
void window_open();
void jsData();

void build_menu();
void check_fatal();
int to_int(char *bp);
void dmessage(char *);

void execute_from_menu(int x)
{
    switch (x-3000) {
        case 1:
            helloworld();
            return;
        case 2:
            demo1();
            return;

        case 3:
            demo2x();
            return;
        case 4:
            demo3x();
            return;
        case 5:
            demoiframe();
            return;
        case 6:
            menuhw();
            //menuhw turns off the ALLDEMO menu
            sm32_out("menu(\"show\",\"ALLDEMO\")");
            sm32_out("gwin(\"statuson\")");
            sm32_out("status(\"alldemo\")");
            return;        
        case 7:
            demo2();
            return;
        case 8:
            demo3();
            return;
        case 9:
            democss();
            return;
        case 10:
            demo2y();
            return;
        case 11:
            demo3y();
            return;
        case 12:
            window_open();
            return;
        case 13:
            jsData();
            return;
        default: return;
    }
}

int main()
{
    int x;
    char *v;

    out_open();
    build_menu();
    sm32_out("menu(\"show\",\"ALLDEMO\")");
    sm32_out("gwin(\"statuson\")");
    sm32_out("status(\"alldemo\")");
    sm32_out("window(-1,-1,-1,-1)");

    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");

    set_value("html",&allmenuf_html_start);              //place in output
    sm32_out("gwin(\"web\")");
    html_out();
    while (1) {
        sm32_out("menuon");
        html_in();
        sm32_out("menuoff");
        check_fatal();

        get_value("EXIT",&v);
        if (*v != '\0') {
            break;
        }
        get_value("MENU_CLICKED",&v);
        if (*v != '\0') {
            x=to_int(v);
            if (x==3014) break;
        }
        execute_from_menu(x);
        html_init();                        //init output
        set_value("protocol","0");
        set_value("type","load");

        set_value("html"," ");              //place in output
        sm32_out("gwin(\"web\")");
        html_out();
    }

    sm32_out("menu(\"show\",\"\")"); // do not show menu
    sm32_out("gwin(\"statusoff\")");
    sm32_out("gwin(\"console\")");
    sm32_out("pop");
    out_close();
}

void build_menu()
{
    sm32_out("menu(\"CREATE\",\"ALLDEMO\")");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"\",\"menu,&WINDOW Mnemonic\",\"Demos that use the WINDOW Mnemonic\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"\",\"menu,&FWINDOW Mnemonic\",\"Demos that use the FWINDOW Mnemonic\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"\",\"menu,&dialog_open\",\"Demos \
    that use protocol8 dialog_open for a dialog box\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"\",\"menu,&protocol 8\",\"Demos that use protocol 8 features\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"0\",\"item,3001,&helloworld\",\"Smallest html page with a button\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"0\",\"item,3002,demo&1\",\"return data from html page\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"0\",\"item,3003,demo&2x\",\"update html page with replace\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"0\",\"item,3004,demo&3x\",\"update html page with SETouterHTML\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"0\",\"item,3005,demo&iframe\",\"shows co-operating iframes\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"0\",\"item,3006,&menuhw\",\"helloworld with single menu item\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"0\",\"item,3014,&exit\",\"exit allmenuf\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"1\",\"item,3007,demo&2\",\"update html page with replace\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"1\",\"item,3008,demo&3\",\"update html page with SETouterHTML\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"1\",\"item,3009,demo&css\",\"demo embeded data\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"2\",\"item,3010,demo&2y\",\"update html page with replace\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"2\",\"item,3011,demo&3y\",\"update html page with SETouterHTML\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"3\",\"item,3012,&window_open\",\"demos disconnected pop up\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"3\",\"item,3013,&jsData\",\"demos send data to javascript function\",0)");
}

void check_fatal()
{
    char *bp;
    get_value("protocol",&bp);
    if (strcmp(bp,"999") == 0) { // is this an error return
        sm32_out("rm"); // kill all windows go back to console mode 
        out_enter_standout_mode();
        out_str("Error return - check google chrome console\n\n");
        out_exit_standout_mode();
        out_close();
        exit(1);
    }
}

int to_int(char *bp)
{
    int i;

    i=0;
    while (*bp != '\0') {
        i=i*10+*bp-'0';
        ++bp;
    }
    return i;
}

void dmessage(char *bp)
{
    char *html;

    html=malloc(message_html_len+1);
    strcpy(html,&message_html_start);
    sm32_out("fwindow(100,100,500,300,\
    \"Message\",\"background-color: #DEE1E6; color: #000000;\")"); 
    sm32_out("gwin(\"web\")");
    html_init();                        //init output
    set_value("protocol","0");
    set_value("type","load");
    html_replace(&html,"????MESSAGE",bp);
    set_value("html",html);  //place in output
    html_out();
    html_in();

    sm32_out("pop");
}