default: prog

hashMap.o: hashMap.c hashMap.h
	gcc -g -Wall -ansi -pedantic-errors -c hashMap.c

linkedList.o: linkedList.h linkedList.c
	gcc -g -Wall -ansi -pedantic-errors -c linkedList.c

prog: hashMap.o linkedList.o main.c
	gcc -g -Wall -ansi -pedantic-errors -o prog hashMap.o  main.c

clean:
	rm hashMap.o
	rm linkedList.o

cleanall: clean
	rm prog
