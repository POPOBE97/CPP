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
#include "defination.h"

using namespace std;
users       *_myUsers;
msgque      *_myMsgque;
socket_c    *_mySocket;
protocol    *_myProtocol;

class mySocket : public socket_c {
public:
    void buffRecved(clients _cli, string _recv) {
        _myMsgque->addMsg(_recv);
    };
    void newConnEstablished(clients newClients) {
        _myUsers->addUser(newClients.cli_socket, 0);
    };
    void lostAConnection(clients lostClient) {
        _myUsers->rmUser(lostClient.cli_socket);
    };
};

class myMsgque : public msgque {
    void msgDealer(protocol _pkg) {
        *_myProtocol = _pkg;
        cout << _myProtocol->getContent() << endl;
    }
};

class myProtocol : public protocol {
};

int main(int argc, const char * argv[]) {
    _myUsers = new users();
    _myMsgque = new myMsgque();
    _myProtocol = new myProtocol();
    _mySocket = new mySocket();
    fflush(stdin);
    getchar();
    return 0;
}
