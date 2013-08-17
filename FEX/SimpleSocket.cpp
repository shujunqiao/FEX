//
//  SimpleSocket.cpp
//  FEX
//
//  Created by FancyZero on 13-8-15.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "SimpleSocket.h"

bool SimpleSocket::connect(std::string addr, int port)
{
    sockaddr_in serv_addr;
    hostent *server;
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(addr.c_str());
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(port);

    if (::connect(socketfd,(sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        return false;
    return true;
}

bool SimpleSocket::disconnect()
{
    return close(socketfd) >= 0;
}

int  SimpleSocket::send(std::string data)
{
    return write( socketfd, (void*)data.c_str(), (size_t)data.length() );
}

std::string SimpleSocket::recv( int max)
{
    bzero(buff, 1024);
    read(socketfd, buff, max);
    return std::string((char*)buff);
    
}
