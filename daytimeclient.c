#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

  //Conecting port
int main(int argc, char **argv){
  if(argc != 2){
    printf("Port Number: %s <port>\n", argv[0]);
    exit(0);
  }

  int port = atoi(argv[1]);
  printf("Port used: %d\n", port);

  //Connecting socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  char response[30];
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = inet_addr("192.168.56.106");
  serverAddress.sin_port = htons(port);

  //Connecting to server
  connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("[X] SUCCESSFULLY CONNECTED TO SERVER [X]\n");

  //Receiving time from server
  recv(sockfd, response, 29, 0);
  printf("Time received from server= %s", response);

  return 0;

  //Closing socket
  close(sockfd);

}
