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

const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
  if ( ! Socket::send ( s ) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
  if ( ! Socket::recv ( s ) )
    {
      throw SocketException ( "Could not read from socket." );
    }

  return *this;
}

void ServerSocket::accept(ServerSocket &sock) {
	if (!Socket::accept(sock)) {
		throw SocketException("Server : Could not accept socket.\n");
	}
}
