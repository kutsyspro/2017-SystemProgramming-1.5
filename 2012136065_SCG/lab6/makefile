CC = gcc
CFLAGS = -g -DDEBUG -W -Wall
TARGET = mtest

$(TARGET) : mtest.o foo.o boo.o bar.o
	$(CC) $(CFLAGS) -o $(TARGET) mtest.o foo.o boo.o bar.o
mtest.o : mtest.c a.h
	$(CC) $(CFLAGS) -c -o mtest.o mtest.c
foo.o : foo.c a.h
	$(CC) $(CFLAGS) -c -o foo.o foo.c
boo.o : boo.c a.h
	$(CC) $(CFLAGS) -c -o boo.o boo.c
bar.o : bar.c a.h
	$(CC) $(CFLAGS) -c -o bar.o bar.c
clean : 
	rm *.o mtest
