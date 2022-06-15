OBJS = reciter.o sam.o
		
CC = gcc
CFLAGS =  -O2 -DUSESDL `sdl-config --cflags`
LFLAGS = `sdl-config --libs`

Sam: main.c $(OBJS)
	$(CC) $(CFLAGS) -osam $(OBJS) main.c $(LFLAGS)

reciter.o: reciter.c reciter.h
	$(CC) $(CFLAGS) -c reciter.c
	
sam.o: sam.c sam.h
	$(CC) $(CFLAGS) -c sam.c	
	
clean:
	rm *.o