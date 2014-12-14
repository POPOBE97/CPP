//
//  defination.h
//  Server-9-17
//
//  Created by Ruiyao Luo on 13/12/14.
//  Copyright (c) 2014 Ruiyao. All rights reserved.
//

#ifndef _DEFINATION_H_
#define _DEFINATION_H_

#include "protocol/protocol.h"
#include "socket/socket_server.h"

#ifndef _LISTENPORT_
#define _LISTENPORT_ 5555
#endif

#ifndef _PROTOCOL_TYPE_
#define _PROTOCOL_TYPE_
class   protocol;
struct  clipro;
//login verify package
#define _PROTOCOL_TYPE_LOGIN_VERIFY_	1
//chat package
#define _PROTOCOL_TYPE_CHATTING_ 		2
//request data from server
#define _PROTOCOL_TYPE_REQUEST_ 		3
//registeration
#define _PROTOCOL_TYPE_REGIST_          4
#endif

#ifndef _CLIENTS_
#define _CLIENTS_
struct clients;                 //server_9-17.cpp
#endif

#endif  /* defined(__Server_9_17__defination__) */