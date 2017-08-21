achiMS : list.o
	gcc list.o -g -o achiMS
list.o : list.h list.c
	gcc -c list.c -g
