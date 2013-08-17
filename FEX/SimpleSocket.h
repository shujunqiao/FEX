//
//  SimpleSocket.h
//  FEX
//
//  Created by FancyZero on 13-8-15.
//
//

#ifndef __FEX__SimpleSocket__
#define __FEX__SimpleSocket__

#include <string>
class SimpleSocket
{
public:
    bool connect(std::string addr, int port);
    bool disconnect();
    int     send(std::string data);
    std::string recv( int max);
protected:
    unsigned char buff[1024];
    int socketfd;
};

#endif /* defined(__FEX__SimpleSocket__) */
