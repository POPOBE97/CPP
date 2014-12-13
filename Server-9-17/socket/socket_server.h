//
//  socket_server.h
//  Server-9-17
//
//  Created by Ruiyao Luo on 1/10/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#ifndef __Server_9_17__socket_server__
#define __Server_9_17__socket_server__

#include <errno.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../defination.h"

struct clients {
    int         cli_socket;
    socklen_t   cli_addr_len;
    struct      sockaddr_in cli_addr;
};

class socket_c {
    
public:
    socket_c();
    ~socket_c();
    
public:
    virtual void buffRecved(clients fromClient, std::string recvStr) = 0;
    virtual void newConnEstablished(clients newClients)              = 0;
    virtual void lostAConnection(clients lostClient)                    = 0;
    
public:
    int         connCount;
    struct      clients     cli[32];
    
private:
    int         max_fd;
    int         listenSocket;
    
private:
    bool        thread_stop;
    
private:
    fd_set      rdfd;
    
private:
    struct      timeval     tv;
    
private:
    pthread_t   thread_ID;
    
private:
    void        init();
    void        debug();
    void        RecvAndVerify();
    int         BindAndListen();
    void        CheckAndAccept();
    char        recvBuff[1024];
    
private:
    static void* listenFucntion(void* param);
};

#endif /* defined(__Server_9_17__socket__) */
