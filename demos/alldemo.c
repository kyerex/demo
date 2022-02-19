
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include "demo.h"


void build_menu();
int read_keyboard();

char keyboard_buf[32];

void execute(char *bp)
{
    int ret_val;

    ret_val=fork();
    if (ret_val == 0){
        execl("/bin/sh","/bin/sh","-c",bp,NULL);
    }
    else {
        wait(&ret_val);
    }

    out_cursor_address(23,0);
    out_clear_line();
    out_str("Enter to continue:");
    out_flush();
    read_keyboard();
}

int keyboard_to_int()
{
    char *bp;
    int i;
    keyboard_buf[8]='\0'; //just in case

    bp=keyboard_buf;
    i=0;
    while (*bp != '\0') {
        i=i*10+*bp-'0';
        ++bp;
    }
    return i;
}

void execute_from_menu()
{
    int x;
    char *bp;

    x=read_keyboard(); // menu is turned off
    x=keyboard_to_int();
    switch (x-3000) {
        case 1: bp="./helloworld";break;
        case 2: bp="./demo1";break;
        case 3: bp="./demo2x";break;
        case 4: bp="./demo3x";break;
        case 5: bp="./demoiframe";break;
        case 6: bp="./menuhw";break;
        case 7: bp="./demo2";break;
        case 8: bp="./demo3";break;
        case 9: bp="./democss";break;
        case 10: bp="./demo2y";break;
        case 11: bp="./demo3y";break;
        case 12: bp="./window_open";break;
        case 13: bp="./jsData";break;

        default: return;
    }
    execute(bp);
    //menuhw turns off the ALLDEMO menu
    sm32_out("menu(\"show\",\"ALLDEMO\")");
    sm32_out("gwin(\"statuson\")");
    sm32_out("status(\"alldemo\")");

}

int in_keyboard(char *bp) 
{
	int a;

	a=read(0,bp,1);
	if (a != 1) {
        abort();
    } 
    if (*bp =='\x18') {
        return 1;
    }
    return 0;
}

int read_keyboard()
{
    char *bp;

    bp=keyboard_buf;
    *bp='\0';
    while (1) {
        if (in_keyboard(bp)) {
            return 1;
        }
        if (*bp == '\n' || *bp == '\r') {
            break;
        }
        if (*bp == '\b') {
            if (bp == keyboard_buf) {
                continue;
            }
            --bp;
            write(1,"\e[D \e[D",7);
            continue;
        }
        if (*bp < '0' || *bp > '9') {
            continue; // only accept digits
        }
        write(1,bp,1);
        ++bp;
        if (bp == &keyboard_buf[31] ) {
            bp=keyboard_buf; // just wrap if 32 chars typed
        }
    }
    *bp='\0';
    return 0;
}


int main()
{
    int x;

    out_open();
    build_menu();
    sm32_out("menu(\"show\",\"ALLDEMO\")");
    sm32_out("gwin(\"statuson\")");
    sm32_out("status(\"alldemo\")");

    while (1) {
        out_clear_screen();
        out_cursor_address(3,5);
        out_enter_standout_mode();
        out_str("Main Menu");
        out_exit_standout_mode();
        out_cursor_address(5,5);
        out_str("1. Demos that use 'WINDOW' mnemonic");
        out_cursor_address(6,5);
        out_str("2. Demos that use 'FWINDOW' mnemonic");
        out_cursor_address(7,5);
        out_str("3. Demos that use dialog_open");
        out_cursor_address(8,5);
        out_str("4. Protocol 8 demos");
        out_cursor_address(10,5);
        out_str("1->4 or Enter to quit:");
        out_flush();

        sm32_out("menuon");
        x=read_keyboard();
        sm32_out("menuoff");
        if (x) {
            // menu selected
            execute_from_menu();
            continue;
        }
        if (keyboard_buf[0] == '\0') {
            break;
        }
        x=keyboard_to_int();
        switch (x) {
            case 1:
                while(1) {
                    out_clear_screen();
                    out_cursor_address(3,5);
                    out_enter_standout_mode();
                    out_str("WINDOW Mnemonic Menu");
                    out_exit_standout_mode();
                    out_cursor_address(5,5);
                    out_str("1. helloworld demo");
                    out_cursor_address(6,5);
                    out_str("2. demo1 - return data from html page");
                    out_cursor_address(7,5);
                    out_str("3. demo2x - update html page with replace");
                    out_cursor_address(8,5);
                    out_str("4. demo3x - update html page with SETouterHTML");
                    out_cursor_address(9,5);
                    out_str("5. demoiframe - shows co-operating iframes");
                    out_cursor_address(10,5);
                    out_str("6. menuhw - helloworld with a menu with a single item");
                    out_cursor_address(12,5);
                    out_str("1->6 (Enter back to main menu) :");
                    out_flush();

                    sm32_out("menuon");
                    x=read_keyboard();
                    sm32_out("menuoff");
                    if (x) {
                        execute_from_menu();
                        continue;
                    }
                    x=keyboard_to_int();
                    switch (x) {
                        case 1:
                            execute("./helloworld");
                            continue;
                        case 2:
                            execute("./demo1");
                            continue;
                        case 3:
                            execute("./demo2x");
                            continue;
                        case 4:
                            execute("./demo3x");
                            continue;
                        case 5:
                            execute("./demoiframe");
                            continue;
                        case 6:
                            execute("./menuhw");
                            continue;

                        default:
                            break;
                    }
                    break;
                }
                break;
            case 2:
                while(1) {
                    out_clear_screen();
                    out_cursor_address(3,5);
                    out_enter_standout_mode();
                    out_str("FWINDOW Mnemonic (preferred dialog window) Menu");
                    out_exit_standout_mode();
                    out_cursor_address(5,5);
                    out_str("1. demo2 - update html page with replace");
                    out_cursor_address(6,5);
                    out_str("2. demo3 - update html page with SETouterHTML");
                    out_cursor_address(7,5);
                    out_str("3. democss - demo embedded data");
                    out_cursor_address(9,5);
                    out_str("1->3 (Enter back to main menu) :");
                    out_flush();

                    sm32_out("menuon");
                    x=read_keyboard();
                    sm32_out("menuoff");
                    if (x) {
                        execute_from_menu();
                        continue;
                    }
                    x=keyboard_to_int();
                    switch (x) {
                        case 1:
                            execute("./demo2");
                            continue;
                        case 2:
                            execute("./demo3");
                            continue;
                        case 3:
                            execute("./democss");
                            continue;

                        default:
                            break;
                    }
                    break;
                }
                break;
            case 3:
                while(1) {
                    out_clear_screen();
                    out_cursor_address(3,5);
                    out_enter_standout_mode();
                    out_str("dialog_open demos Menu");
                    out_exit_standout_mode();
                    out_cursor_address(5,5);
                    out_str("1. demo2y - update html page with replace");
                    out_cursor_address(6,5);
                    out_str("2. demo3y - update html page with SETouterHTML");
                    out_cursor_address(8,5);
                    out_str("1->2 (Enter back to main menu) :");
                    out_flush();

                    sm32_out("menuon");
                    x=read_keyboard();
                    sm32_out("menuoff");
                    if (x) {
                        execute_from_menu();
                        continue;
                    }
                    x=keyboard_to_int();
                    switch (x) {
                        case 1:
                            execute("./demo2y");
                            continue;
                        case 2:
                            execute("./demo3y");
                            continue;

                        default:
                            break;
                    }
                    break;
                }
                break;
            case 4:
                while(1) {
                    out_clear_screen();
                    out_cursor_address(3,5);
                    out_enter_standout_mode();
                    out_str("Protocol8 demos Menu");
                    out_exit_standout_mode();
                    out_cursor_address(5,5);
                    out_str("1. window_open - demos disconnected pop up");
                    out_cursor_address(6,5);
                    out_str("2. jsData - demos send data to javascript function");
                    out_cursor_address(8,5);
                    out_str("1->2 (Enter back to main menu) :");
                    out_flush();

                    sm32_out("menuon");
                    x=read_keyboard();
                    sm32_out("menuoff");
                    if (x) {
                        execute_from_menu();
                        continue;
                    }
                    x=keyboard_to_int();
                    switch (x) {
                        case 1:
                            execute("./window_open");
                            continue;
                        case 2:
                            execute("./jsData");
                            continue;

                        default:
                            break;
                    }
                    break;
                }
                break;

            default:
                break;
        }
    }
    out_clear_screen();
    out_cursor_address(23,0);
    sm32_out("menu(\"show\",\"\")"); // do not show menu
    sm32_out("gwin(\"statusoff\")");
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
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"1\",\"item,3007,demo&2\",\"update html page with replace\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"1\",\"item,3008,demo&3\",\"update html page with SETouterHTML\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"1\",\"item,3009,demo&css\",\"demo embeded data\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"2\",\"item,3010,demo&2y\",\"update html page with replace\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"2\",\"item,3011,demo&3y\",\"update html page with SETouterHTML\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"3\",\"item,3012,&window_open\",\"demos disconnected pop up\",0)");
    sm32_out("menu(\"APPEND\",\"ALLDEMO\",\"3\",\"item,3013,&jsData\",\"demos send data to javascript function\",0)");
}