#include "../common/Event.h"
#include "../common/socket.h"

int main(int argc, char **argv) {
  Connection connection("localhost", "1234");
  KeyEvent e("up");
  connection.SendStr(e.ToStr().c_str());
}
