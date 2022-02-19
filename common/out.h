
#ifndef _outh
#define _outh

#include "curses.h"
#include <term.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif 

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

void out_flush();
void out_open();
void out_close();

void out_clear_screen();
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

#ifdef __cplusplus
}
#endif


#endif /* _outh */
