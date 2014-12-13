//
//  users.h
//  Server-9-17
//
//  Created by Ruiyao Luo on 13/12/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#ifndef __Server_9_17__users__
#define __Server_9_17__users__

#include <stdio.h>
#include <map>
#include "../defination.h"

class users {
    map<int, int> _ClientsIDMap;
    
public:
    users()     {};
    ~users()    {};
    
    int     getIDFromClient(int _cli);
    
    void    addUser(int _cli, int _ID);
    
    void    rmUser(int _cli);
};

#endif /* defined(__Server_9_17__users__) */
