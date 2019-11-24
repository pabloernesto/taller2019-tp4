#include "socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>   // close
#include <stdexcept>  // runtime_error
#include <string.h>   // strlen

using std::runtime_error;

Connection::Connection(int file_descriptor) : fd(file_descriptor) {}

Connection::Connection(const char *host, const char *port) {
  struct addrinfo hints = {};
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  struct addrinfo *addr;
  if (getaddrinfo(host, port, &hints, &addr))
    throw runtime_error("getaddrinfo returned an error");

  struct addrinfo *addr_p = addr;
  for (; addr_p; addr_p = addr_p->ai_next) {
    fd = socket(addr_p->ai_family, addr_p->ai_socktype,
      addr_p->ai_protocol);
    if (fd == -1)
      continue; // try again, couldn't create the socket
    if (!connect(fd, addr_p->ai_addr, addr_p->ai_addrlen))
      break;    // successful connect
    close(fd);  // try again, couldn't connect
  }

  freeaddrinfo(addr);
  if (!addr_p)
    throw runtime_error("no address succeeded");
}

Connection::Connection(Connection&& other) : fd(other.fd) {
  other.fd = 0;
}

Connection& Connection::operator=(Connection&& other) {
  fd = other.fd;
  other.fd = 0;
  return *this;
}

void Connection::Shutdown() {
  if (fd > 0) shutdown(fd, SHUT_RDWR);
}

void Connection::ShutdownWrite() {
  if (fd > 0) shutdown(fd, SHUT_WR);
}

void Connection::ShutdownRead() {
  if (fd > 0) shutdown(fd, SHUT_RD);
}

Connection::~Connection() {
  if (fd > 0) {
    Shutdown();
    close(fd);
  }
  fd = 0;
}

int Connection::Send(const char *buffer, int n) {
  int sent = 0;
  while (sent < n) {
    int r = send(fd, buffer, n - sent, MSG_NOSIGNAL);
    if (r <= 0)
      return sent;
    sent += r;
    buffer += sent;
  }
  return sent;
}

int Connection::Get(void *buffer, int n) {
  char *s = (char*) buffer;
  int received = 0;
  while (received < n) {
    int r = recv(fd, s, n - received, 0);
    if (r <= 0) return received;
    received += r;
    s += r;
  }
  return received;
}

int Connection::SendStr(const char *msg) {
  const int msg_len = strlen(msg);
  const __uint32_t msg_len_encoded = htonl(msg_len);
  int bytes_sent =
    Send((char*) &msg_len_encoded, (int) sizeof(msg_len_encoded));
  if (bytes_sent != (int) sizeof(msg_len_encoded))
    return -2;

  bytes_sent = Send(msg, msg_len);
  if (bytes_sent != msg_len)
    return -1;

  return 0;
}

char* Connection::GetStr() {
  __uint32_t len;
  if (Get(&len, 4) != 4) return nullptr;
  len = ntohl(len);

  char *s = new char[len + 1];
  s[len] = 0;
  if (Get(s, len) != (int) len) {
    delete s;
    return nullptr;
  }

  return s;
}
