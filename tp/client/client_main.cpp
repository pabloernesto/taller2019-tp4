#include "client.h"
#include <memory>   // unique_ptr
#include "globals.h"

std::unique_ptr<ImageCache> image_cache;

int main(int argc, char** argv){
	Client client;
  client.start();
}