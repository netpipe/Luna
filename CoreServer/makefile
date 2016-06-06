CC=g++
GCC=gcc
C_FLAGS=-ffast-math -Wall -g
COMPILE = $(CC) $(C_FLAGS) -c
CCOMPILE = $(GCC) $(C_FLAGS) -c

L_FLAGS=-lIrrlicht -lz -lenet -lsqlite3 -lGL  -lirrnet -lXxf86vm
L_INCLUDES=-L/home/Dev/libs/Irrlicht/lib/Linux/ -L../../libs/irrNetLite2 -I../../libs/irrNetLite2 -I../../libs/Irrlicht/include -I../..libs/sqlite/src -I../../libs/enet/include/enet -L../..libs/sqlite/.libs -L../../libs/enet 

OBJS := $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))


OBJECTS = $(OBJS) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5)

all: $(OBJECTS)
	$(CC) -g -o LunaServer $(OBJECTS) $(L_FLAGS)

%.obj: %.c
	$(CCOMPILE) $(L_INCLUDES) $< -o $@

%.o: %.cpp
	$(COMPILE) $(L_INCLUDES) $< -o $@

clean:
	rm $(OBJECTS)
	rm LunaServer
