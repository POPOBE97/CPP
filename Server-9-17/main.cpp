//
//  main.cpp
//  Server-9-17
//
//  Created by Ruiyao Luo on 26/9/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#include <iostream>
#include <string>
#include "protocol/protocol.h"
#include "socket/socket_server.h"
#include "users/users.h"
#include "msgque/msgque.h"
#include "msghandler/msghandler.h"
#include "defination.h"

using namespace std;

users       *_myUsers;
msgque      *_myMsgque;
protocol    *_myProtocol;
socket_c    *_mySocket;
msgHandler  *_myMsgHandler;

class mySocket : public socket_c {
public:
    void buffRecved(clients _cli, string _recv) {
        _myMsgque->addMsg(_recv, _cli);
    };
    void newConnEstablished(clients newClients) {
        _myUsers->addUser(newClients, 0);
        _myUsers->showAllConn();
    };
    void lostAConnection(clients lostClient) {
        _myUsers->rmUser(lostClient);
        _myUsers->showAllConn();
    };
};

class myMsgque : public msgque {
    void msgDealer(clipro _clipro) {
        *_myProtocol = _clipro._pkg;
        switch (_myProtocol->getType()) {
            case _PROTOCOL_TYPE_LOGIN_VERIFY_:
                _myMsgHandler->loginHdl(_myProtocol->getFromID(),
                                        _myProtocol->getType(),
                                        _myProtocol->getContent(),
                                        _clipro._cli);
                break;
                case _PROTOCOL_TYPE_CHATTING_:
                break;
                case _PROTOCOL_TYPE_REQUEST_:
                break;
                case _PROTOCOL_TYPE_REGIST_:
                cout << "Regist" << endl;
                _myUsers->registerUser(_myProtocol->getContent());
                break;
            default:
                break;
        }
    }
};

class myProtocol : public protocol {
};

int main(int argc, const char * argv[]) {
    _myMsgHandler = new msgHandler();
    _myUsers = new users();
    _myProtocol = new myProtocol();
    _myMsgque = new myMsgque();
    _mySocket = new mySocket();
    fflush(stdin);
    getchar();
    delete _myMsgHandler;
    delete (myMsgque*)_myMsgque;
    delete _myProtocol;
    delete (mySocket*)_mySocket;
    delete _myUsers;
    return 0;
}
