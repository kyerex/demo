CC=	gcc
CFLAGS=	-g -O0 -Wall -I. 

OBJS=   out.o html.o 

all:	common.a

common.a:  $(OBJS)
	ar r out.a $(OBJS)
	ranlib out.a

clean:
	@rm -f *.o
	@rm -f out.a

