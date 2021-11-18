#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define BACKLOG 10

  //Connecting port
int main(int argc, char **argv){
  if(argc != 2){
    printf("Port Number: %s <port>\n", argv[0]);
    exit(0);
  }

  int port = atoi(argv[1]);
  printf("Port used: %d\n", port);

  //Creating socket
  int n_client = 0;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = inet_addr("192.168.56.106");
  serverAddress.sin_port = htons(port);

  //Binding socket
  bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("[X] Binding... \n");

  //Listening to client
  listen(sockfd, BACKLOG);
  printf("[X] Waiting for client to connect... \n");

  int i = 1;
  while(i){
    //Counting the request from client
    int client_socket = accept(sockfd, NULL, NULL);
    n_client++;
    //Getting current time
    time_t currentTime;
    time(&currentTime);
    //Sending time to client
    printf("Sending Client %d current time = %s", n_client, ctime(&currentTime));
    send(client_socket, ctime(&currentTime), 30, 0);
  }

  return 0;
  //Closing socket
  close(sockfd);
}
