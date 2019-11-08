#include <iostream>
#include "../common/socket.h"
#include "EnqueuedConnection.h"
#include <string>

int main(int argc, char **argv) {
  Listener listener("1234");
  EnqueuedConnection connection(listener.Accept());
  std::string str;
  while (connection.Pop(&str)) {
    std::cout << str;
  }
}
