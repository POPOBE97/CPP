//
//  users.cpp
//  Server-9-17
//
//  Created by Ruiyao Luo on 13/12/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#include "users.h"

int users::getIDFromClient(int _cli) {
    return _ClientsIDMap[_cli];
}

void users::addUser(int _cli, int _ID) {
    _ClientsIDMap.insert(pair<int, int>(_cli, _ID));
}

void users::rmUser(int _cli) {
    _ClientsIDMap.erase(_cli);
}