//
//  msghandler.cpp
//  Server-9-17
//
//  Created by Ruiyao Luo on 14/12/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#include "msghandler.h"

void msgHandler::loginHdl(int _fromID, int _type, string _content, clients _fromCli) {
    loginVeri(_fromID, _fromCli);
}

bool msgHandler::loginVeri(int _ID, clients _cli) {
    
    return false;
}