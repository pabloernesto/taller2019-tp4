# taller2019-tp4

## Dependencias

### SDL

Este proyecto usa [SDL2] como biblioteca gráfica. Los binarios se pueden instalar desde apt con `sudo apt install libsdl2-dev`

También usamos [SDL_image] versión 2 para cargar imágenes, [SDL_ttf] para el texto mostrado en pantalla y [SDL_mixer] para el sonido del juego. Los binarios se pueden instalar desde apt con `sudo apt install libsdl2-image-dev`, `sudo apt install libsdl2-ttf-dev` y `sudo apt install libsdl2-mixer-dev`.

[SDL2]: http://wiki.libsdl.org/FrontPage
[SDL_image]: https://www.libsdl.org/projects/SDL_image/
[SDL_ttf]: https://www.libsdl.org/projects/SDL_ttf/
[SDL_mixer]: https://www.libsdl.org/projects/SDL_mixer/

### Box2D

Este proyecto usa [Box2D] para su física. Los binarios se pueden instalar desde apt con `sudo apt install libbox2d-dev` y `sudo apt-get install g++ cmake libglu-dev libxi-dev`.

[Box2D]: https://github.com/erincatto/Box2D/wiki/FAQ

### RapidJSON

Este proyecto usa [RapidJSON] para leer y escribir archivos JSON.
Los binarios se pueden instalar de las siguientes formas:

[RapidJSON]: https://rapidjson.org/

#### apt install

`sudo apt install rapidjson-dev`

#### Build local

1. Descargar el archivo include/rapidjson del [repositorio][include/rapidjson].
2. Descargar [CMake] y descomprimirlo en la carpeta descargada en (1).
3. Ubicarse en la la carpeta descargada en (1) con la terminal y ejecutar el comando `git submodule update --init`.
4. Crear una carpeta llamada "build" dentro de la misma carpeta.
5. Ubicarse en la carpeta "build" con la terminal y ejecutar `cmake ..`.
6. Ahora ejecutar `make`.
7. Ejecutar `sudo make install` con la terminal ubicada en la carpeta descargada en (1).

[include/rapidjson]: https://github.com/Tencent/rapidjson
[CMake]: https://cmake.org/

### FFmpeg

Este proyecto usa [FFmpeg] version 4 para la grabación de video. Para esto se instalaron
las librerias libavutil-dev, libswresample-dev, libavformat-dev, libavcodec-dev 
y libswscale-dev con:

`sudo add-apt-repository ppa:jonathonf/ffmpeg-4`.
`sudo apt-get update`.
`sudo apt-get install ffmpeg`.
`sudo apt install libavutil-dev libswresample-dev libavformat-dev libavcodec-dev libswscale-dev`.

Para reproducir el video generado por el juego, se recomienda utilizar MPlayer.
Puede instalarse con `sudo apt install mplayer mplayer-gui` y ejecutar con 
`mplayer <path_to_video_file>`.

[FFmpeg]: https://www.ffmpeg.org/

### Lua

Este proyecto usa un interprete de Lua embebido en el programa cliente.
Los binarios se pueden instalar desde apt con `sudo apt install liblua5.3-dev`
