CC = g++
CFLAGS = -m32 -g -Wall -pthread -I. -lGL -lXrandr -llua --std=c++0x 

OBJ = \
src/Lua/LuaValue.o\
src/Lua/RedLua.o\
src/AABB.o\
src/Clock.o\
src/Color.o\
src/Context.o\
src/EventManager.o\
src/File.o\
src/Logger.o\
src/main.o

PLATFORM = 64

LIBS = \
ext/libglfw$(PLATFORM).a\
ext/GL/glew$(PLATFORM).o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o Red

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJ)
