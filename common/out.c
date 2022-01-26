#include <string.h>
#include <errno.h>
#include <alloca.h>
#include <unistd.h>
#include <stdlib.h>
#include "demo.h"

#define osc_start2 "\033]98;"
#define gui_start "12351,0,0,0,0,9," //ascii len of ksa follows
#define osc_end2 "*\033\\"
#define osc_start "\033]99;"
#define osc_end "\033\\"

struct out_info oi;


void out_open()
{

oi.next_bp=&oi.out_buf[0];
oi.end_bp=oi.next_bp+sizeof(oi.out_buf);
setupterm((char *)0,1,(int *)0);
tcgetattr(0,&oi.tio);
oi.sav_tio=oi.tio;
oi.tio.c_lflag=ISIG;
oi.tio.c_cc[VMIN]=1;
oi.tio.c_cc[VTIME]=0;
tcsetattr(0,TCSAFLUSH,&oi.tio);
out_set_foreground();
out_str("\014htmltty Demos\n");
}

void out_close()
{
   out_set_background();
   out_flush();
   reset_shell_mode();
   tcsetattr(0,TCSAFLUSH,&oi.sav_tio);
}

int out_char(int tchar)
{

   *oi.next_bp=(char)tchar;
   ++oi.next_bp;
   if ( oi.next_bp == oi.end_bp ) {
      out_flush();
   }
   return 0;
}

void out_str(char *bp)
{
   while ( *bp != '\0' ) {
      if ( *bp == '\n') {
         out_line_feed();
      }
      else {
         if ( *bp == 0x0c) {
            out_clear_screen();
         }
         else {
            out_char(*bp);
         }
      }
      ++bp;
   }
}

void out_block(char *bp,int len)
{
   out_flush();
   memcpy(oi.out_buf,bp,len);
   oi.next_bp=&oi.out_buf[len];
   out_flush();
}

void out_set_foreground()
{
   tputs(enter_bold_mode,strlen(enter_bold_mode),out_char);
}
void out_set_background()
{
   tputs(exit_standout_mode,strlen(exit_standout_mode),out_char);
}
void out_set_tab()
{
   tputs(set_tab,strlen(set_tab),out_char);
}
void out_clear_tabs()
{
   tputs(clear_all_tabs,strlen(clear_all_tabs),out_char);
}
void out_cursor_home()
{
   tputs(cursor_home,strlen(cursor_home),out_char);
}
void out_enter_standout_mode()
{
   tputs(enter_standout_mode,strlen(enter_standout_mode),out_char);
}
void out_exit_standout_mode()
{
   tputs(exit_standout_mode,strlen(exit_standout_mode),out_char);
}
void out_move_left()
{
   tputs(cursor_left,strlen(cursor_left),out_char);
}
void out_move_right()
{
   tputs(cursor_right,strlen(cursor_right),out_char);
}
void out_clear_screen()
{
   tputs(clear_screen,strlen(clear_screen),out_char);
}
void out_clr_eos()
{
   tputs(clr_eos,strlen(clr_eos),out_char);
}
void out_line_insert()
{
   tputs(insert_line,strlen(insert_line),out_char);
}
void out_line_delete()
{
   tputs(delete_line,strlen(delete_line),out_char);
}
void out_clear_line()
{
   tputs(clr_eol,strlen(clr_eol),out_char);
}
void out_cursor_address(int row,int col)
{
char *bp;

bp=tparm(cursor_address,row,col);
tputs(bp,strlen(bp),out_char);
}
void out_ring_bell()
{
   tputs(bell,strlen(bell),out_char);
   out_flush();
}
void out_line_feed()
{
   out_char('\n');
}

void out_flush()
{
if ( oi.next_bp == oi.out_buf ) return;
if (-1 == write(1,oi.out_buf,oi.next_bp-oi.out_buf ) ) {
      printf ("Write Failed ???");
      abort();
   }
oi.next_bp=oi.out_buf;
return;
}
