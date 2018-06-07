CC=cc -O -L. -Aa
CC=gcc -O3 -DPRINT
#PREFIX=sslittle-na-sstrix-
#CC=/ss/bin/$(PREFIX)gcc -I/ss/sslittle-na-sstrix/include -L/ss/sslittle-na-sstrix/lib

all:	libp.a  perm  # perm.dvi

libp.a:	perm.o
	$(PREFIX)ar r libp.a perm.o
	$(PREFIX)ranlib libp.a

perm:	libp.a main.o sc.o
	$(CC) -o perm main.o sc.o obj.c -lp -L.


perm.o:	perm.c
		$(CC)   -c perm.c

perm.c:	perm.w
		ctangle perm.w
		cweave  perm.w

perm.dvi:	perm.tex
		tex perm

perm.tex:	perm.w
		ctangle perm.w
		cweave  perm.w

main.c:	main.w
	ctangle main.w
	cweave  main.w

main.o:	main.c
	$(CC) -c main.c

#sc.c:	sc.w
#	ctangle sc.w
#	cweave  sc.w

sc.o:	sc.c
	$(CC) -c sc.c
