# _*_ Makefile _*_

shell: shell.c myls mycat mymkdir myrm utils.o
	gcc -g shell.c utils.o -o shell

myls: ls.o utils.o
	gcc ls.o utils.o -o myls

ls.o: ls.c
	gcc -c ls.c -o ls.o

mycat: cat.o utils.o
	gcc cat.o utils.o -o mycat

cat.o: cat.c
	gcc -c cat.c -o cat.o

mymkdir: mkdir.o utils.o
	gcc mkdir.o utils.o -o mymkdir

mkdir.o: mkdir.c
	gcc -c mkdir.c -o mkdir.o

myrm: rm.o
	gcc rm.c utils.o -o myrm

rm.o: rm.c
	gcc -c rm.c -o rm.o

utils.o: utils.c
	gcc -c utils.c -o utils.o

clean:
	rm -f shell myls mycat mymkdir myrm 
	rm -f ls.o cat.o rm.o mkdir.o utils.o
