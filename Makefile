#
all:
	@rm -f loadhtml
	(make loadhtml)
	@./loadhtml final/html
	as final/html/html_files.s -o final/html/html_files.o
	(cd common ; make )
	(cd demos ; make )
	(cd final ; make )
	(cd windows ; make )

clean:
	(cd common ; make clean )
	(cd demos ; make clean )
	(cd final ; make clean )
	(cd windows ; make clean )

	@rm -f loadhtml

loadhtml:
	gcc -g -O0 -Wall -o loadhtml loadhtml.c

