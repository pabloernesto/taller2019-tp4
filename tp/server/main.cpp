#include <iostream>
#include "../common/socket.h"
#include "EnqueuedConnection.h"
#include <string>

int main(int argc, char **argv) {
  Listener listener("1234");
  EnqueuedConnection connection(listener.Accept());
  while (connection.IsPopable()) {
    std::string&& str = connection.Pop();
    std::cout << str;
  }
}
