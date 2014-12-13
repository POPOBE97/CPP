//
//  msgque.h
//  Server-9-17
//
//  Created by Ruiyao Luo on 13/12/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#ifndef __Server_9_17__msgque__
#define __Server_9_17__msgque__

#include <list>
#include <pthread.h>
#include "../defination.h"

using namespace std;

class msgque{
    
    int                         queCount;
    list<protocol>              msgQueue;
    
public:
    msgque();
    ~msgque();
    
    void addMsg(protocol);
    
    virtual void msgDealer(protocol _pkg) = 0;

private:
    static void* queDealer(void* param);
    
    bool thread_stop;
    
    pthread_t thread_ID;
    
private:
    
};

#endif  /* defined(__Server_9_17__msgque__) */