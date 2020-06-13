#ifndef BLXR_SRC_NET_H_
#define BLXR_SRC_NET_H_

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT "3507"
#define BUFFER 4096

struct Client {
  SOCKET socket;
  int id;
  char recvMsg[BUFFER];
};

namespace Network {
int ProcessClient(Client &client);
int ClientControl();
}

#endif //BLXR_SRC_NET_H_
