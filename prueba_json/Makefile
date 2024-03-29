# targets
#########

target=prueba.exe

# source files
sources=$(wildcard *.cpp)
headers=$(wildcard *.h)

# intermediate objects
objects=$(patsubst %.cpp, %.o, $(sources))

# opciones de compilador
########################

# Opciones para el compilador C/C++ para tratamiento de errores y warnings.
CFLAGS = -Wall -Werror -pedantic -pedantic-errors

# Para optimizar el binario resultante lo mejor posible
CFLAGS += -O3

# Para valgrind o debug
CFLAGS += -ggdb -DDEBUG -fno-inline

# Estandar de C++ a usar
CFLAGS += -std=c++11

CXXFLAGS = $(CFLAGS)

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

# Linkea a Box2D
LDFLAGS += -lBox2D

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
