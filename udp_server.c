//
//  udp_server.c
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

#define UDP_PORT 80001

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    int sock_fd, len = 0;
    int addr_len = sizeof(struct sockaddr_in);
    char buff[1024];
    
    //
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("create socket.");
        exit(1);
    }
    
    //
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //
    if ((bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
        perror("bind.");
        exit(1);
    }
    
    while (1) {
        bzero(buff, sizeof(buff));
        len = recvfrom(sock_fd, buff, sizeof(buff), 0, (struct sockaddr *)&addr, &addr_len);
        
        printf("Received a string from client: %s, string is: %s\n", inet_ntoa(addr.sin_addr), buff);
        
        sendto(sock_fd, buff, sizeof(buff), 0, (struct sockaddr *)&addr, addr_len);
    }
    
    return 0;
}
