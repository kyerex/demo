#
all:
	@rm -f loadhtml
	(make loadhtml)
	@./loadhtml final/html
	(cd common ; make )
	(cd demos ; make )
	(cd final ; make )
	(cd windows ; make )
	(cd protocol8 ; make )

clean:
	(cd common ; make clean )
	(cd demos ; make clean )
	(cd final ; make clean )
	(cd windows ; make clean )
	(cd protocol8 ; make clean )

loadhtml:
	gcc -g -O0 -Wall -o loadhtml loadhtml.c

