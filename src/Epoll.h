/*
 * Epoll.h
 *
 *  Created on: 2020. 2. 21.
 *      Author: yw
 */

#ifndef EPOLL_H_
#define EPOLL_H_

#include "ServerSocket.h"

class Epoll: public ServerSocket {
public:
	Epoll();
	virtual ~Epoll();
};

#endif /* EPOLL_H_ */
