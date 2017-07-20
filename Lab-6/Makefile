test: mtest.o foo.o boo.o bar.o
	gcc -g -DDEBUG -o test mtest.o foo.o boo.o bar.o
mtest: mtest.o
	gcc -c mtest.c
foo: foo.o
	gcc -c foo.c
boo: boo.o
	gcc -c boo.c
bar: bar.o
	gcc -c bar.c

clean:
	rm-f *.o test
