# _*_ Makefile _*_

shell: shell.c myls mycat mymkdir myrm
	gcc -g shell.c -o shell

myls: ls.c
	gcc ls.c -o myls

mycat: cat.c
	gcc cat.c -o mycat

mymkdir: mkdir.c
	gcc mkdir.c -o mymkdir

myrm: rm.c
	gcc rm.c -o myrm

clean:
	rm -f shell myls mycat mymkdir myrm
