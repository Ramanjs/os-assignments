# _*_ Makefile _*_

shell: shell.c myls mycat mymkdir myrm
	gcc -g shell.c -o shell

myls: ls.o utils.o
	gcc ls.o utils.o -o myls

ls.o: ls.c
	gcc -c ls.c -o ls.o

mycat: cat.o
	gcc cat.o utils.o -o mycat

cat.o: cat.c
	gcc -c cat.c -o cat.o

mymkdir: mkdir.c
	gcc mkdir.c -o mymkdir

myrm: rm.o
	gcc rm.c utils.o -o myrm

rm.o: rm.c
	gcc -c rm.c -o rm.o

utils.o: utils.c
	gcc -c utils.c -o utils.o

clean:
	rm -f shell myls mycat mymkdir myrm 
	rm -f ls.o cat.o rm.o utils.o
