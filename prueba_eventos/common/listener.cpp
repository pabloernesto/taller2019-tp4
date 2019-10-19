#include "socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>   // close
#include <stdexcept>  // runtime_error

using std::runtime_error;
using std::move;

#define BACKLOG 10

Listener::Listener(const char *port) {
  struct addrinfo hints = {};
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  struct addrinfo *addr;
  if (getaddrinfo(NULL, port, &hints, &addr))
    throw runtime_error("getaddrinfo returned an error");

  struct addrinfo *addr_p;
  for (addr_p = addr; addr_p; addr_p = addr_p->ai_next) {
    fd = socket(addr_p->ai_family, addr_p->ai_socktype,
      addr_p->ai_protocol);
    if (fd == -1)
      continue; // try again, coundn't create socket
    if (!bind(fd, addr_p->ai_addr, addr_p->ai_addrlen))
      break;    // successful bind
    close(fd);  // try again, couldn't bind
  }

  freeaddrinfo(addr);
  // No address succeeded
  if (!addr_p)
    throw runtime_error("no address succeeded");

  if (listen(fd, BACKLOG) < 0)
    throw runtime_error("listen failed");
}

Listener::~Listener() {
  if (!fd) return;
  close(fd);
  fd = 0;
}

Connection Listener::Accept() {
  int ret = accept(fd, NULL, NULL);
  if (ret == -1)
    throw runtime_error("accept failed");
  Connection c(ret);
  return move(c);
}

void Listener::Shutdown() {
  if (shutdown(fd, SHUT_RDWR) == -1)
    throw runtime_error("shutdown failed");
}
