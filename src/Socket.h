/*
 * Socket.h
 *
 *  Created on: 2020. 2. 20.
 *      Author: yw
 *
 *  참고 주소
 *  https://www.geeksforgeeks.org/socket-programming-cc/
 *  https://www.it-note.kr/category/C%EC%96%B8%EC%96%B4%20header/sys%20%7C%20socket.h
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

const int MAX_CONNECTIONS = 10;
const int MAX_RECV = 512;

class Socket {
public:
	Socket();
	virtual ~Socket();

	// 서버 init
	bool create();					// 소켓 생성
	bool bind(const int port);	// IP/PORT
	bool listen() const;			// 요청 대기
	bool accept(Socket&) const;	// 수락

	// 클라이언트 init
	bool connect(const std::string host_ip, const int port);

	// 데이터 송수신
	bool send(const std::string) const;
	int recv(std::string&) const;

	// 소켓 생성 여부 확인
	bool is_valid() const;

private:
	int m_sock; // 각 소켓의 번호
	sockaddr_in m_addr; // 소켓의 주소 구조체

	/* sockaddr_in 구조체 참고
	 struct sockaddr_in{
	 sa_family_t	sin_family;		//주소체계 (Address Family)
	 uint16_t	sin_port;		//16비트 PORT번호 (TCP/UDP)
	 struct		in_addr;		//32비트 IP주소
	 char		sin_zero[8];	//---여기서는 사용되지 않음
	 }
	 */
};

#endif /* SOCKET_H_ */
