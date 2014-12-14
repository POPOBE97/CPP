//
//  users.cpp
//  Server-9-17
//
//  Created by Ruiyao Luo on 13/12/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#include "users.h"

users::users() {
    _fstream.open("dat/6711f799eb9198a", ios::in|ios::out);
    if (!_fstream.is_open())
        cout << "failed" << endl;
    getUserList();
    _fstream.close();
}

users::~users() {
    _fstream.close();
}

int users::getIDFromClient(clients _cli) {
    return _ClientsIDMap[_cli];
}

clients users::getClientFromID(int _ID) {
    return _IDClientsMap[_ID];
}

void users::addUser(clients _cli, int _ID) {
    _ClientsIDMap.insert(pair<clients, int>(_cli, _ID));
    _IDClientsMap.insert(pair<int, clients>(_ID, _cli));
}

void users::rmUser(clients _cli) {
    _ClientsIDMap.erase(_cli);
    _IDClientsMap.erase(getIDFromClient(_cli));
}

void users::showAllConn() {
    map<clients, int>::iterator _it;
    for (_it=_ClientsIDMap.begin(); _it!=_ClientsIDMap.end(); _it++)
        cout << "ID: " << _it->second << "\tAddr: " << inet_ntoa(_it->first.cli_addr.sin_addr) << endl;
}

void users::showExistUsers() {
    map<int, string>::iterator _it;
    for (_it=_userNickname.begin(); _it!=_userNickname.end(); _it++)
        cout << "ID: " << _it->first << "\tNickname: " << _it->second << endl;
}

void users::getUserList() {
    string _username;
    string _password;
    int    _ID;
    while (_fstream >> _ID) {
        _fstream >> _username;
        _fstream >> _password;
        
        _existUsers.insert(pair<int, string>(_ID, _password));
        _userNickname.insert(pair<int, string>(_ID, _username));
    }
    showExistUsers();
}

void users::registerUser(string _content) {
    _fstream.open("dat/6711f799eb9198a", ios::app);
    if (!_fstream)
        cout << "failed" << endl;
    int _ID = _existUsers.begin()->first + 1;
    string _nickname = _content.substr(0,_content.find('\xfe'));
    string _password = _content.substr(_content.find('\xfe')+1);
    cout << _ID << _nickname << _password << endl;
    _fstream << _ID << " " << _nickname << " " << _password << "\n";
    _fstream.close();
}