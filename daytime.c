#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

int main(int argc,char *argv[])
{
    int sockfd,len,ret;
    struct sockaddr_in saddr;
    char *hname,buff[256];
    struct hostent *hostinfo;
    struct servent *servinfo;
    if(argc == 1)
        hname = "localhost";
    else
        hname = argv[1];
   
    //Getting host info
    hostinfo = gethostbyname(hname);
    if(!hostinfo) {
        fprintf(stderr,"No host: %s\n ",hname);
        exit(1);
    }
   
    //Getting daytime server info
    servinfo = getservbyname("daytime","tcp");
    if(!servinfo) {
        fprintf(stderr,"Daytime server not found! \n");
        exit(1);
    }

    //Using daytime port 13
    printf("Daytime Protocol Port: %d\n", ntohs(servinfo->s_port));

    // Creating socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = servinfo->s_port;
    saddr.sin_addr = *(struct in_addr *) *(hostinfo->h_addr_list);
    len = sizeof(saddr);
   
    //Error message if failed to connect
    ret = connect(sockfd,(struct sockaddr *)&saddr,len);
    if(ret == -1) {
        perror("[X] CONNECTION FAILED [X] ");
        exit(1);
    }
   
    //Getting reply from server
    ret = read(sockfd,buff,sizeof(buff));
    buff[ret] = '\0';
    printf("Time received = %s",buff);
    printf("Bytes read = %d byte(s) \n",ret);
   
    //Closing socket
    close(sockfd);

return 0;
}
