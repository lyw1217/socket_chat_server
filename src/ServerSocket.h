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

	void accept(ServerSocket&);
private:
};

#endif /* SERVERSOCKET_H_ */
