//
//  msghandler.h
//  Server-9-17
//
//  Created by Ruiyao Luo on 14/12/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#ifndef __Server_9_17__msghandler__
#define __Server_9_17__msghandler__

#include <stdio.h>
#include "../defination.h"

class msgHandler {
    
public:
    msgHandler()    {};
    ~msgHandler()   {};
    
    //void signUpHdl(int _fromID, int _toID, int _type, string _content, clients _fromCli);
    void loginHdl(int _fromID, int _type, string _content, clients _fromCli);
    
private:
    //void init();
    bool loginVeri(int _ID, clients _cli);
    
};

#endif /* defined(__Server_9_17__msghandler__) */
