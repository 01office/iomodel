#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int sockfd, new_fd;
    int sin_size, numbytes;
    struct sockaddr_in addr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("create socket error");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7092);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind error");
        return -1;
    }

    if (listen(sockfd, 10) == -1)
    {
        perror("listen error");
        return -1;
    }

    printf("server is running.\n");

    char buff[1024];

    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);

        if ((new_fd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&sin_size)) == -1)
        {
            perror("accept error");
            return -1;
        }

        if (!fork())
        {
            memset(buff, 0, sizeof(buff));
            if ((numbytes = recv(new_fd, buff, sizeof(buff), 0)) == -1)
            {
                perror("recv error");
                return -1;
            }
            printf("buff = %s\n", buff);

            if (send(new_fd, buff, strlen(buff), 0) == -1)
            {
                perror("send error");
            }

            close(new_fd);
            return 0;
        }

        close(new_fd);
    }

    close(new_fd);
}