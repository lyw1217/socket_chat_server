/*
 * ServerSocket.h
 *
 *  Created on: 2020. 2. 21.
 *      Author: yw
 */

#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include "Socket.h"

class ServerSocket: private Socket {
public:
	ServerSocket(int port);
	ServerSocket(){};
	virtual ~ServerSocket(){};
	int GetFd() {return Socket::GetFd();};
	char* GetAddr() {return Socket::GetAddr();};

	const ServerSocket& operator << ( const std::string& s ) const;
	const ServerSocket& operator >> ( std::string& s ) const;

	void accept(ServerSocket&);
private:
};

#endif /* SERVERSOCKET_H_ */
