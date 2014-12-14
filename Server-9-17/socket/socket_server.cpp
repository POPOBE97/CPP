//
//  socket_server.cpp
//  Server-9-17
//
//  Created by Ruiyao Luo on 1/10/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#include "socket_server.h"
#include <string.h>

#ifndef THIS
#define THIS ptr_this
#endif

using namespace std;

socket_c::socket_c() {
    memset(recvBuff, 0, sizeof(recvBuff));
    thread_stop = false;
    connCount   = 0;
    tv.tv_sec   = 0;
    tv.tv_usec  = 10;
    string socket_err = "cannot create socket";
    try {
        listenSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (listenSocket < 0)
            throw socket_err;
    } catch (string err) {
        cout << "socket setup\t[FAILD]" << endl;
        cout << err << endl;
    }
    cout << "socket setup\t[OK]" << endl;
    max_fd      = listenSocket;
    for (int _loop = 0; _loop < 32; _loop++) {
        cli[_loop].cli_socket = 0;
        memset(&cli[_loop].cli_addr, 0, sizeof(sockaddr_in));
    }
    init();
}

socket_c::~socket_c() {
    thread_stop = true;
    for (int _loop = 0; _loop < connCount; _loop ++) {
        close(cli[_loop].cli_socket);
    }
    close(listenSocket);
    while (thread_stop) {
        sleep(1);
    }
    cout << "~socket\t\t\t[OK]" << endl;
}

int socket_c::BindAndListen() {
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(_LISTENPORT_);
    addr.sin_addr.s_addr    = INADDR_ANY;
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
    
    string err = "cannot bind on the socket";
    int yes = 1;
    
    try {
        bind(listenSocket, (struct sockaddr*)&addr, sizeof(addr));
        if (listenSocket < 0)
            throw err;
    } catch (string _err) {
        cout << "bind\t\t\t[FAILD]" << endl;
        cout << err << endl;
        return -1;
    }
    cout << "bind\t\t\t[OK]" << endl;
    
    try {
        if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
            throw err;
    } catch (string _err) {
        cout << "set socket\t\t[FAILD]" << endl;
    }
    
    err = "cannot listen to the socket";
    try {
        if (listen(listenSocket, 32) < 0)
            throw err;
    } catch (string _err) {
        cout << "bind\t\t\t[listen]" << endl;
        cout << _err << endl;
        return -1;
    }
    cout << "listen\t\t\t[OK]" << endl;
    
    return 0;
}

void socket_c::init() {
    if (BindAndListen() != 0)
        exit(-1);
    
    string err = "cannot start the accpet thread";
    try {
        if (pthread_create(&thread_ID, NULL, listenFucntion, this) != 0)
            throw err;
    } catch (string _err) {
        cout << "thread create\t[FAILD]" << endl;
        cout << _err << endl;
    }
    
    cout << "thread create\t[OK]" << endl;
}

void socket_c::CheckAndAccept() {
    if (connCount < 32) {
        if (FD_ISSET(listenSocket, &rdfd)) {
            cli[connCount].cli_addr_len = sizeof(sockaddr);
            cli[connCount].cli_socket   = accept(listenSocket, (struct sockaddr*)&cli[connCount].cli_addr, &cli[connCount].cli_addr_len);
            newConnEstablished(cli[connCount]);
            connCount ++;
        } else {
            return;
        }
    } else {
        send(listenSocket, "Sorry. Connection amount has reached the limination.", sizeof(char)*52, 0);
    }
}

void socket_c::RecvAndVerify() {
    for (int _loop = 0; _loop < connCount; _loop ++) {
        if (cli[_loop].cli_socket != 0) {
            if (FD_ISSET(cli[_loop].cli_socket, &rdfd)) {
                int ret = static_cast<int>(recv(cli[_loop].cli_socket, recvBuff, sizeof(recvBuff), 0));
                if ( ret <= 0) {
                    close(cli[_loop].cli_socket);
                    lostAConnection(cli[_loop]);
                    memset(&cli[_loop], 0, sizeof(clients));
                    _loop --;
                    connCount --;
                } else {
                    recvBuff[ret] = '\0';
                    buffRecved(cli[_loop], recvBuff);
                }
            }
        } else {
            cli[_loop] = cli[_loop +1];
            memset(&cli[_loop +1], 0, sizeof(clients));
            _loop --;
        }
    }
}

void socket_c::debug() {
    for (int _loop = 0; _loop < connCount; _loop ++) {
        cout << cli[_loop].cli_socket << ": " << inet_ntoa(cli[_loop].cli_addr.sin_addr) << endl;
    }
}

void* socket_c::listenFucntion(void* param) {
    socket_c* ptr_this = static_cast<socket_c *>(param);
    cout << "listen thread\t[OK]" << endl;

    while (!ptr_this->thread_stop) {
        FD_ZERO(&THIS->rdfd);
        FD_SET(THIS->listenSocket, &THIS->rdfd);
        THIS->max_fd = THIS->listenSocket;
        for (int _loop = 0; _loop < 32; _loop ++) {
            if (THIS->cli[_loop].cli_socket > THIS->max_fd)
                THIS->max_fd = THIS->cli[_loop].cli_socket;
            FD_SET(THIS->cli[_loop].cli_socket, &THIS->rdfd);
        }
        switch (select(THIS->max_fd + 1 , &THIS->rdfd, 0, 0, &THIS->tv)) {
            case 0:
                //cout << "time out\t\t[Warning]" << endl;
                break;
            case -1:
                cout << "an error occurred\t[FAILD]" << endl;
                break;
            default:
                THIS->CheckAndAccept();
                THIS->RecvAndVerify();
                //THIS->debug();
                break;
        }
    }
    
    cout << "thread quit\t\t[OK]" << endl;
    ptr_this->thread_stop = false;
    return nullptr;
}
