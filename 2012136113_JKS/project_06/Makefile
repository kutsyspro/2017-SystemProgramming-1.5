mtest : mtest.o foo.o boo.o bar.o
	gcc -g -o mtest -DDEBUG mtest.o foo.o boo.o bar.o

foo.o : foo.c
	gcc -c foo.c

boo.o : boo.c
	gcc -c boo.c

bar.o : bar.c
	gcc -c bar.c
