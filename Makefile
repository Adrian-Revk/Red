NAME = Red-Project
VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_PATCH = 10
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)

ARCH = 64


################################################################


CC = g++

CFLAGS = -Wall -g -Isrc/ -Iext/ -lX11 -lXrandr -lGL -llua --std=c++0x

OBJ = \
src/Lua/LuaValue.o\
src/Lua/RedLua.o\
src/AABB.o\
src/Clock.o\
src/Context.o\
src/EventManager.o\
src/File.o\
src/Logger.o\
src/main.o\
src/Mesh.o\
src/Renderer.o\
src/Scene.o\
src/Shader.o\
src/Shared.o\
src/Texture.o


LIB = \
ext/libglfw$(ARCH).a\
ext/libSOIL$(ARCH).a\
ext/GL/glew$(ARCH).o


.PHONY: all, clean, red

all: 
	@echo "---- Building $(NAME) $(VERSION) ----"
	@make red
	@echo "---- $(NAME) $(VERSION) built ----"
	
red: $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o bin/Red
	
%.o: %.cpp
	@ $(CC) $(CFLAGS) -c $< -o $@
	@echo "CC	$@"

clean:
	rm $(OBJ)
