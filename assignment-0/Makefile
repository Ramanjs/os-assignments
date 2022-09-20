# _*_ MakeFile _*_

a1: a1.o
	gcc -no-pie -o a1 a1.o

a1.o: a1.asm
	yasm -f elf64 -o a1.o a1.asm

clean:
	rm -f a1 a1.o
