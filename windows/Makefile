CC=	gcc
CFLAGS= -g -O0 -Wall -I. -I../common

LIBS=	../common/out.a

all:	wdemo1 wdemo1x wdemo1y wdemo2 wdemo2x wpop

wdemo1:	wdemo1.o $(LIBS) 
	gcc -o wdemo1 wdemo1.o $(LIBS) -lcurses  

wdemo1x: wdemo1x.o $(LIBS) 
	gcc -o wdemo1x wdemo1x.o $(LIBS) -lcurses  

wdemo1y: wdemo1y.o $(LIBS) 
	gcc -o wdemo1y wdemo1y.o $(LIBS) -lcurses  

wdemo2:	wdemo2.o $(LIBS) 
	gcc -o wdemo2 wdemo2.o $(LIBS) -lcurses  

wdemo2x:	wdemo2x.o $(LIBS) 
	gcc -o wdemo2x wdemo2x.o $(LIBS) -lcurses  

wpop:	wpop.o $(LIBS) 
	gcc -o wpop wpop.o $(LIBS) -lcurses  

clean:
	@rm -f *.o
	@rm -f wdemo1
	@rm -f wdemo1x
	@rm -f wdemo1y
	@rm -f wdemo2
	@rm -f wdemo2x
	@rm -f wpop
	@rm -f wpop

