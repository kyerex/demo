#include "curses.h"
#include <term.h>
#include <stdio.h>

#ifndef _demoh
#define _demoh

struct out_info
{
   struct termios sav_tio;
   struct termios tio;
   char *next_bp;
   char *end_bp;
   char out_buf[8192];
};


void out_str(char *bp);
int out_char(int);
void out_block(char *bp ,int len);

void out_clear_screen();
void out_flush();
void out_open();
void out_close();
void out_clr_eos();
void out_clear_line();
void out_cursor_home();
void out_inc_col();
void out_insert_in_string();
void out_line_delete();
void out_line_feed();
void out_line_insert();
void out_move_left();
void out_ring_bell();
void out_enter_standout_mode();
void out_exit_standout_mode();
void out_set_foreground();
void out_set_background();
void out_set_tab();
void out_clear_tab();
void out_move_right();
void out_cursor_address(int row,int col);
void out_ring_bell();
void out_line_feed();

void sm32_out(char *bp);
void html_load(char *fname,char **h);
void html_load_base64(char *fname,char **h);
void html_init();
void html_out ();
void html_in();
void html_replace(char **,char *,char *);
void set_value(char *key,char *value);
void get_value(char *key,char **value);


#endif /* _demoh */
