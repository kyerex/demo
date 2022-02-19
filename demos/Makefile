CC=	gcc
CFLAGS= -g -O0 -Wall -I. -I../common

LIBS=	../common/out.a

all:	demo1 demo2 demo2x demo2y demo3 demo3x demo3y democss \
		demoiframe helloworld menuhw window_open jsData alldemo

demo1:	demo1.o $(LIBS) 
	gcc -o demo1 demo1.o $(LIBS) -lcurses  

demo2:	demo2.o $(LIBS) 
	gcc -o demo2 demo2.o $(LIBS) -lcurses  

demo2x:	demo2x.o $(LIBS) 
	gcc -o demo2x demo2x.o $(LIBS) -lcurses  

demo2y:	demo2y.o $(LIBS) 
	gcc -o demo2y demo2y.o $(LIBS) -lcurses  

demo3:	demo3.o $(LIBS) 
	gcc -o demo3 demo3.o $(LIBS) -lcurses  

demo3x:	demo3x.o $(LIBS) 
	gcc -o demo3x demo3x.o $(LIBS) -lcurses  

demo3y:	demo3y.o $(LIBS) 
	gcc -o demo3y demo3y.o $(LIBS) -lcurses  

democss:	democss.o $(LIBS) 
	gcc -o democss democss.o $(LIBS) -lcurses  

demoiframe:	demoiframe.o $(LIBS) 
	gcc -o demoiframe demoiframe.o $(LIBS) -lcurses  

helloworld:	helloworld.o $(LIBS) 
	gcc -o helloworld helloworld.o $(LIBS) -lcurses  

menuhw:	menuhw.o $(LIBS) 
	gcc -o menuhw menuhw.o $(LIBS) -lcurses  

window_open:	window_open.o $(LIBS) 
	gcc -o window_open window_open.o $(LIBS) -lcurses  

jsData:	 jsData.o $(LIBS) 
	gcc -o jsData jsData.o $(LIBS) -lcurses  

alldemo:	alldemo.o $(LIBS) 
	gcc -o alldemo alldemo.o $(LIBS) -lcurses  

clean:
	@rm -f *.o
	@rm -f demo1
	@rm -f demo2
	@rm -f demo2x
	@rm -f demo2y
	@rm -f demo3
	@rm -f demo3x
	@rm -f demo3y
	@rm -f democss
	@rm -f demoiframe
	@rm -f helloworld
	@rm -f menuhw
	@rm -f jsData
	@rm -f window_open
	@rm -f alldemo
