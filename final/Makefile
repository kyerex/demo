CC=	gcc
CFLAGS= -g -O0 -Wall -I. -I../common

LIBS=	../common/out.a

OBJS=	demo1.o \
	helloworld.o \
	demo2x.o \
	demo3x.o \
	demoiframe.o \
	menuhw.o \
	demo2.o \
	demo3.o \
	democss.o \
	demo2y.o \
	demo3y.o \
	window_open.o \
	jsData.o \
	alldemof.o

all:	$(OBJS) $(LIBS) 
	gcc -o alldemof $(OBJS) html/html_files.o $(LIBS) -lcurses  

clean:
	@rm -f *.o
	@rm -f html/html_files.*
	@rm -f alldemof
