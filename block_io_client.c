#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("%s: input IP & port\n", argv[0]);
        return 1;
    }

    int sockfd, numbytes;
    char buff[100] = "hi, there";
    struct hostent *he;
    struct sockaddr_in their_addr;

    he = gethostbyname(argv[1]);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(atoi(argv[2]));
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8);

    if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect error");
        exit(1);
    }

    if (send(sockfd, buff, strlen(buff), 0) == -1)
    {
        perror("send error");
        exit(1);
    }

    memset(buff, 0, sizeof(buff));

    if ((numbytes = recv(sockfd, buff, 100, 0)) == -1)
    {
        perror("recv error");
        exit(1);
    }

    close(sockfd);

    return 0;
}