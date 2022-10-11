# _*_ Makefile _*_

shell: shell.c myls mycat mymkdir myrm
	gcc -g shell.c -o shell

myls: ls.o utils.o
	gcc ls.o utils.o -o myls

ls.o: ls.c
	gcc -c ls.c -o ls.o

mycat: cat.c
	gcc cat.c -o mycat

mymkdir: mkdir.c
	gcc mkdir.c -o mymkdir

myrm: rm.c
	gcc rm.c -o myrm

utils.o: utils.c
	gcc -c utils.c -o utils.o

clean:
	rm -f shell myls mycat mymkdir myrm ls.o utils.o
