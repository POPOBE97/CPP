//
//  protocol.h
//  Server-9-17
//
//  Created by Ruiyao Luo on 26/9/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#ifndef __Server_9_17__protocol__
#define __Server_9_17__protocol__

#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include "../defination.h"

using namespace std;

class protocol {
    
public:
    
    protocol(string& _content, int _fromID, int _toID, int _type);
    protocol(const string& _package);
    
    protocol(const protocol& _pkg);
    
    protocol& operator+ (const protocol&);
    protocol& operator= (const protocol&);
    protocol& operator= (const string&);
    
    string  getPkg()        { return pkg; };
    string  getContent()    { return content; };
    int     getFromID()     { return fromID; };
    int     getToID()       { return toID; };
    int     getType()       { return type; };
    void    showAll()       { cout  << "pkg:" << pkg << "\n" << "content:" << content << "\n" << "fromID:" << fromID << "\n" << "toID:" << toID << "\n" << "type:" << type << endl; };
    
    protocol(){};
    ~protocol(){};
    
private:
    //functions
    void pkgSolve();
    void pkgMake();
    
    //vars
    string              content;
    string              pkg;
    
    int                 type;
    
    int                 fromID;
    int                 toID;
};

#endif /* defined(__Server_9_17__protocol__) */
