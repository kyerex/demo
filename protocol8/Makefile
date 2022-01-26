CC=	gcc
CFLAGS= -g -O0 -Wall -I. -I../common

LIBS=	../common/out.a

all:	window_open jsData

window_open:	window_open.o $(LIBS) 
	gcc -o window_open window_open.o $(LIBS) -lcurses  

jsData:	 jsData.o $(LIBS) 
	gcc -o jsData jsData.o $(LIBS) -lcurses  

clean:
	@rm -f *.o
	@rm -f window_open
	@rm -f jsData
