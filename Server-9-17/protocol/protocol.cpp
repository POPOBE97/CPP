//
//  protocol.cpp
//  Server-9-17
//
//  Created by Ruiyao Luo on 26/9/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#include "protocol.h"

protocol::protocol(string& _content, int _fromID, int _toID, int _type) {
    content = _content;
    fromID  = _fromID;
    toID    = _toID;
    type    = _type;
    pkgMake();
}

protocol::protocol(const string& _pkg) {
    if (_pkg.find('\xff') != 0) {
        content = _pkg;
        fromID  = 0;
        toID    = 0;
        type    = 0;
        pkgMake();
    } else {
        pkg = _pkg;
        pkgSolve();
    }
}

protocol::protocol(const protocol& _pkg) {
    content = _pkg.content;
    pkg     = _pkg.pkg;
    fromID  = _pkg.fromID;
    toID    = _pkg.toID;
    type    = _pkg.type;
}

protocol& protocol::operator+ (const protocol& _pkg) {
    content += _pkg.content;
    pkgMake();
    return *this;
}

protocol& protocol::operator= (const protocol& _pkg) {
    pkg     = _pkg.pkg;
    type    = _pkg.type;
    fromID  = _pkg.fromID;
    toID    = _pkg.toID;
    content = _pkg.content;
    return *this;
}

protocol& protocol::operator= (const string& _pkg) {
    if (_pkg.find('\xff') == -1) {
        content = _pkg;
        fromID  = 0;
        toID    = 0;
        type    = 0;
        pkgMake();
    } else {
        pkg.clear();
        pkg = _pkg;
        pkgSolve();
    }
    return *this;
}

void protocol::pkgMake() {
    pkg.clear();
    char sep = '\xff';
    stringstream stream;
    //               type           toID           formID           content
    stream << sep << type << sep << toID << sep << fromID << sep << content;
    stream >> pkg;
}

void protocol::pkgSolve() {
    content.clear();
    string _temp, _copy;
    stringstream stream;
    //get type
    {
        _temp = pkg.substr(pkg.find('\xff')+1);
        _copy = _temp;
        _temp = _temp.substr(0,_copy.find('\xff'));
        stream << _temp;
        stream >> type;
    }
    //get toID
    {
        _copy = _copy.substr(_copy.find('\xff')+1);
        _temp = _temp.substr(0,_copy.find('\xff'));
        stream << _temp;
        stream >> toID;
        _copy = _copy.substr(_copy.find('\xff')+1);
    }
    //get fromID
    {
        _copy = _copy.substr(_copy.find('\xff')+1);
        _temp = _temp.substr(0,_copy.find('\xff'));
        stream << _temp;
        stream >> fromID;
        _copy = _copy.substr(_copy.find('\xff')+1);
    }
    //get content
    {
        _copy = _copy.substr(_copy.find('\xff')+1);
        content = _copy;
    }
}