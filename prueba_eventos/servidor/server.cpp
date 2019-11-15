#include "../common/socket.h"
#include <iostream>
#include <memory>   // unique_ptr

int main(int argc, char **argv) {
  Listener listener("1234");
  Connection connection = listener.Accept();

  while (char *c_str = connection.GetStr()) {
    std::string str(c_str);
    delete[] c_str;

    std::unique_ptr<Event> e(Event::FromStr(str));
    std::cout << e->ToStr() << "\n";
  }
}
