//
//  udp_client.c
//  awesomecode
//
//  Created by heyong on 2016/11/20.
//  Copyright © 2016年 heyong. All rights reserved.
//

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define UDP_IP "127.0.0.1"
#define UDP_PORT 80001

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    int sockfd, len = 0;
    int addr_len = sizeof(struct sockaddr_in);
    char buffer[1024];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_PORT);
    addr.sin_addr.s_addr = inet_addr(UDP_IP);
    
    while (1) {
        bzero(buffer, sizeof(buffer));
        
        printf("enter string to send:\n");
        len = read(STDIN_FILENO, buffer, sizeof(buffer));
        
        sendto(sockfd, buffer, len, 0, (struct sockaddr *)&addr, sizeof(addr));
        
        len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addr_len);
        printf("Received from server: %s\n", buffer);
    }
    
    return 0;
}
