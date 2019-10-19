#ifndef SOCKET_H_
#define SOCKET_H_

class Connection {
  int fd;

  public:
  // Object creation
  Connection() = delete;
  explicit Connection(int file_descriptor);
  Connection(const char *host, const char *port);
  ~Connection();

  // Non copyable
  Connection(const Connection& other) = delete;
  Connection operator=(const Connection& other) = delete;

  // Movable
  Connection(Connection&& other);
  Connection& operator=(Connection&& other);

  // Send some bytes through the socket
  int Send(const char *buffer, int n);

  // Receive some bytes through the socket
  int Get(void *buffer, int n);

  // Send a character string
  // Returns 0 on success, -1 on partial success, -2 on error
  int SendStr(const char *msg);

  // Receive a character string
  // Returns a heap-allocated character string, or nullptr on error
  char *GetStr();

  // Send shutdown for both read and write
  void Shutdown();
  void ShutdownWrite();
};

class Listener {
  int fd;

  public:
  // Object creation
  Listener() = delete;
  explicit Listener(const char *port);
  ~Listener();

  // Non copyable
  Listener(const Listener& other) = delete;
  Listener operator=(const Listener& other) = delete;

  Connection Accept();
  void Shutdown();
};

#endif  // SOCKET_H_
