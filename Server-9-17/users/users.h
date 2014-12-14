//
//  users.h
//  Server-9-17
//
//  Created by Ruiyao Luo on 13/12/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#ifndef __Server_9_17__users__
#define __Server_9_17__users__

#include <map>
#include <stdio.h>
#include <fstream>
#include "../defination.h"

class users {
    map<clients, int> _ClientsIDMap;
    map<int, clients> _IDClientsMap;
    
    map<int, string> _existUsers;
    map<int, string> _userNickname;
    
public:
    users();
    ~users();
    
    int     getIDFromClient(clients _cli);
    clients     getClientFromID(int _ID);

    
    void    addUser(clients _cli, int _ID);
    void    addUser(int _ID, clients _cli);
    
    void    rmUser(clients _cli);
    void    rmUser(int _ID);
    
    void    showAllConn();
    void    showExistUsers();
    void    registerUser(string _content);

    
private:
    void    getUserList();
    fstream  _fstream;
};

#endif /* defined(__Server_9_17__users__) */
