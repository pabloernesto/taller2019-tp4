#ifndef _MOD_H_
#define _MOD_H_
#include "../RaceModInterface.h"
// #include "../CarModInterface.h"
// ?? Me parece que la idea es definir mas una interfaz para que la gente del
// servidor pueda crear sus propios mods (y no revelar toda la API de Race)
// Pero habria que cambiar mas cosas...
// Lo clave seria preguntar por mail la verdad.
// Por ahora se hace con Race porque es mas facil. Pero a saber que probablemente
// este mal.
// #include "../RaceInterface.h"


class Mod {
  
  public:
    virtual void execute(Race* race) = 0;
    virtual ~Mod();  
};

#endif