#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE (1024 * 32)
#define DEST_PORT 80

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cout << "usage: " << argv[0] << " hostToRetrieveIndex" << std::endl;
    return -1;
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct hostent *host;
  host = gethostbyname(argv[1]);

  struct sockaddr_in dest_addr;
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(DEST_PORT);
  dest_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr*) host->h_addr)));
  memset(&(dest_addr.sin_zero), '\0', 8);
  connect(sockfd, (struct sockaddr*) &dest_addr, sizeof(struct sockaddr));

  const char *command = "GET / HTTP/1.0\r\n\r\n";
  const int bytesSent = send(sockfd, command, strlen(command), 0);

  char buff[BUFFER_SIZE];
  int bytesRead;
  while ((bytesRead = recv(sockfd, buff, BUFFER_SIZE, 0))) {
    std::cout << buff;
    bzero(buff, BUFFER_SIZE);
  }
  std::cout << std::endl;

  close(sockfd);

  return 0;
}

