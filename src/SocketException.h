/*
 * SocketException.h
 *
 *  Created on: 2020. 2. 21.
 *      Author: yw
 *
 *   참고 : http://coffeenix.net/doc/lg/issue74/tougher.html#4
 */

#ifndef SOCKETEXCEPTION_H_
#define SOCKETEXCEPTION_H_

#include <string>

class SocketException {
public:
	SocketException(std::string str) :
			m_str(str) {
	}
	;
	virtual ~SocketException() {
	}
	;

	std::string description() {
		return m_str;
	}
private:
	std::string m_str;
};

#endif /* SOCKETEXCEPTION_H_ */
