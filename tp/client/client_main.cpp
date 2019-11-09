#include "client.h"
#include <memory>   // unique_ptr
#include "Configuration.h"

Configuration configuration("Configuracion/config.json");

int main(int argc, char** argv){
	Client client;
  client.start();
}