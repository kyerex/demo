CC=	gcc
CFLAGS= -g -O0 -Wall -I. -I../common

LIBS=	../common/out.a

all:	demo1 demo2 demo2x demo2y helloworld

demo1:	demo1.o $(LIBS) 
	gcc -o demo1 demo1.o $(LIBS) -lcurses  

demo2:	demo2.o html/html_files.o $(LIBS) 
	gcc -o demo2 demo2.o html/html_files.o $(LIBS) -lcurses  

demo2x:	demo2x.o $(LIBS) 
	gcc -o demo2x demo2x.o $(LIBS) -lcurses  

demo2y:	demo2y.o $(LIBS) 
	gcc -o demo2y demo2y.o $(LIBS) -lcurses  

helloworld:	helloworld.o $(LIBS) 
	gcc -o helloworld helloworld.o $(LIBS) -lcurses  

clean:
	@rm -f *.o
	@rm -f demo1
	@rm -f demo2
	@rm -f demo2x
	@rm -f demo2y
	@rm -f helloworld
