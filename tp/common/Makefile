# targets
#########

# source files
sources=$(wildcard *.cpp)
headers=$(wildcard *.h)

# intermediate objects
objects=$(patsubst %.cpp, %.o, $(sources))

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
LDFLAGS += $(shell sdl2-config --cXXflags --libs)

# Linkea a SDL_image
LDFLAGS += -lSDL2_image

# Linkea a Box2D
LDFLAGS += -lBox2D

# reglas
########

# targets
.PHONY: all
all: $(objects)

.PHONY: clean
clean:
	$(RM) $(objects) $(target)
