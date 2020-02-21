/*
 * ServerSocket.cpp
 *
 *  Created on: 2020. 2. 21.
 *      Author: yw
 */

#include "ServerSocket.h"

ServerSocket::ServerSocket(int _port) {

	if(!Socket::create()){
		throw SocketException("Server : Could not create socket.\n");
	}

	if(!Socket::bind(_port)){
		throw SocketException("Server : Could not bind to socket.\n");
	}

	if(!Socket::listen()){
		throw SocketException("Server : Could not listen to socket.\n");
	}
}

void ServerSocket::accept(ServerSocket &sock) {
	if (!Socket::accept(sock)) {
		throw SocketException("Server : Could not accept socket.\n");
	}
}
