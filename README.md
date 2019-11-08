# taller2019-tp4

## Dependencias

### SDL

Este proyecto usa [SDL2] como biblioteca gráfica. Los binarios se pueden instalar desde apt con `sudo apt install libsdl2-dev`

También usamos [SDL_image] versión 2 para cargar imágenes y [SDL_ttf] para el texto mostrado en pantalla. Los binarios se pueden instalar desde apt con `sudo apt install libsdl2-image-dev` y `sudo apt install libsdl2-ttf-dev`.

[SDL2]: http://wiki.libsdl.org/FrontPage
[SDL_image]: https://www.libsdl.org/projects/SDL_image/
[SDL_ttf]: https://www.libsdl.org/projects/SDL_ttf/

### Box2D

Este proyecto usa [Box2D] para su física. Los binarios se pueden instalar desde apt con `sudo apt install libbox2d-dev` y `sudo apt-get install g++ cmake libglu-dev libxi-dev`.

[Box2D]: https://github.com/erincatto/Box2D/wiki/FAQ

### RapidJSON

Este proyecto usa [RapidJSON] para leer y escribir archivos JSON. Los binarios se pueden instalar desde siguiendo los siguientes pasos:
  1. Descargar el archivo include/rapidjson del [repositorio][include/rapidjson].
  2. Descargar [CMake] y descomprimirlo en la carpeta descargada en (1).
  3. Ubicarse en la la carpeta descargada en (1) con la terminal y ejecutar el comando `git submodule update --init`.
  4. Crear una carpeta llamada "build" dentro de la misma carpeta.
  5. Ubicarse en la carpeta "build" con la terminal y ejecutar `cmake ..`.
  6. Ahora ejecutar `make`.
  7. Ejecutar `sudo make install` con la terminal ubicada en la carpeta descargada en (1).

[RapidJSON]: https://rapidjson.org/
[include/rapidjson]: https://github.com/Tencent/rapidjson
[CMake]: https://cmake.org/
