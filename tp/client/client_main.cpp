#include "client.h"
#include <memory>   // unique_ptr
#include "../common/Configuration.h"

Configuration configuration("../common/Configuracion/config.json");

int main(int argc, char** argv){
  Client client;
  client.start();
}