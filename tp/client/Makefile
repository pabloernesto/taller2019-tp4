# targets
#########

target=client.exe

# source files
sources=$(wildcard *.cpp)
headers=$(wildcard *.h)

# intermediate objects
objects=$(patsubst %.cpp, %.o, $(sources))

# common objects
objects+=$(wildcard ../common/*.o)

# opciones de compilador
########################

# Opciones para el compilador C/C++ para tratamiento de errores y warnings.
CXXFLAGS = -Wall -Werror -pedantic -pedantic-errors

# Para optimizar el binario resultante lo mejor posible
CXXFLAGS += -O3

# Para valgrind o debug
CXXFLAGS += -ggdb -DDEBUG -fno-inline

# Estandar de C++ a usar
CXXFLAGS += -std=c++11

# opciones del enlazador
########################

# Usar el enlazador de C++
LD = $(CXX)

# Permite el uso de pthread en C y C++.
# Permite el uso de built-in threads en C++.
LDFLAGS += -pthread

# LDFLAGS += -static

# Linkea a SDL2
LDFLAGS += $(shell sdl2-config --cflags --libs)

# Linkea a SDL_image
LDFLAGS += -lSDL2_image

# Linkea a SDL_ttf
LDFLAGS += -lSDL2_ttf

# Linkea a SDL_mixer
LDFLAGS += -lSDL2_mixer

# Linkea a Box2D
LDFLAGS += -lBox2D

# Linkea librerias dinamicas
LDFLAGS += -ldl

# reglas
########

# targets
.PHONY: all
all: $(target)

$(target): $(objects)
	$(LD) -o $@ $(objects) $(LDFLAGS)

.PHONY: run
run: all
	./$(target)

valgrind: all
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(target)

.PHONY: clean
clean:
	$(RM) $(objects) $(target)
