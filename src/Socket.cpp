/*
 * Socket.cpp
 *
 *  Created on: 2020. 2. 20.
 *      Author: yw
 */

#include "Socket.h"
#include <string.h> // memset()

Socket::Socket() :
		m_sock(-1) {
	memset(&m_addr, 0, sizeof(m_addr));

}

Socket::~Socket() {
	if (is_valid()) {
		// close() -> 소켓 메모리 반환, file descriptor table 정리
		close(m_sock);
	}
}

// 서버 init
bool Socket::create() {
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET(IPv4), SOCK_STREAM(TCP), 0(protocol, IPPROTO_TCP도 가능)
	// 반환값 : 해당 소켓을 가리키는 소켓 디스크립터를 반환
	// 생성 실패 시 -1

	// 소켓 생성 실패하면 false 리턴
	if (is_valid()) {
		return false;
	}

	/* int setsockopt (int fd, int level, int optname,
	 const void *optval, socklen_t optlen);
	 소켓의 속성값 변경을 도와준다. 직접 할당해도 되지만..
	 이 함수는 사용하면 주소와 포트의 재활용을 도와준다.
	 https://www.it-note.kr/122
	 */
	int opt = 1;
	if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &opt,
			sizeof(opt)) < 0) {
		// SOL_SOCKET : 소켓 레벨에서 설정하는 옵션임을 명시
		// SO_RESUEADDR : bind(2) 시에 local 주소를 재사용 할 것인지 여부
		fprintf(stderr, "socket create error: %s\n", strerror(errno));
		return false;
	} else {
		return true;	// 소켓 생성 완료
	}
}

bool Socket::bind(const int _port) {
	if (!is_valid()) {
		return false;
	}

	m_addr.sin_family = AF_INET;				// IP_v4
	m_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// INADDR_ANY 상수로 인해 자신의 ip값을 자동으로 할당
	m_addr.sin_port = htonl(_port);				// 매개변수로 받은 port를 포트로 설정

	// 할당한 구조체를 가지고 소켓에 ip와 port를 묶는다
	/*
	 * int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	 * sockaddr 구조체와 sockaddr_in 구조체의 차이에 대해서도 알고있자
	 */
	if (::bind(m_sock, (struct sockaddr*) &m_addr, sizeof(m_addr)) < 0) {
		close(m_sock);
		fprintf(stderr, "socket bind error: %s\n", strerror(errno));
		return false;
	} else {
		return true;
	}
}

bool Socket::listen() const {
	if (!is_valid()) {
		return false;
	}

	// 소켓을 수동 대기모드로 설정, 파라미터(소켓 번호, 연결 대기하는 클라이언트 최대 수)
	// 클라이언트가 listen()을 호출해 둔 서버 소켓을 목적지로 connect()를 호출
	// (여기서 3-way 핸드쉐이크가 발생한다. 연결확인) , 성공시 0, 실패시 -1
	// 시스템이 핸드쉐이크를 마친 후에는 서버 프로그램이 설정된 연결을 받아들이는 과정으로 accept()가 사용됨
	if (::listen(m_sock, MAX_CONNECTIONS) < 0) {
		close(m_sock);
		fprintf(stderr, "socket listen error: %s\n", strerror(errno));
		return false;
	} else {
		return true;
	}
}

bool Socket::accept(Socket &new_socket) const {
	int addr_size = sizeof(new_socket);
	new_socket.m_sock = ::accept(m_sock, (struct sockaddr*) new_socket.m_addr,
			(socklen_t*) &addr_size);

	if (new_socket.m_sock < 0) {
		close(m_sock);
		fprintf(stderr, "socket accept error: %s\n", strerror(errno));
		return false;
	} else {
		return true;
	}
}

// 클라이언트 init
bool Socket::connect(const std::string host_ip, const int port) {
	if (!is_valid()) {
		return false;
	}

	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);

	// https://techlog.gurucat.net/317
	// inet_pton 함수 : text 형식의 IP 주소를 binary 형태로 변환
	// int inet_pton(int af, const char *src, void *dst);
	// 리턴값 : 0, str에 명시된 주소가 af의 유효한 값이 아닌 경우
	// -1 : af가 적절한 address family값이 아님, errno이 EAFNOSUPPORT로 설정됨
	if (::inet_pton(AF_INET, host_ip.c_str(), &m_addr.sin_addr) <= 0) {
		return false;
	}

	// https://www.it-note.kr/117?category=1068194
	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	// addr로 접속하여 connection을 유지.
	if (::connect(m_sock, (sockaddr*) &m_addr, sizeof(m_addr)) == -1) {
		return false;
	}else{
		return true;
	}

}

// 데이터 송수신
bool Socket::send(const std::string str) const {
	// send 함수 참고 : https://www.it-note.kr/125
	// int send(int socket, const void * msg, unsigned int msgLength, int flags)
	// flags : MSG_NOSIGNAL ; 다른 한쪽의 소켓의 연결이 끊겼을때, 소켓으로부터 발생하는 스트림상의 SIGPIPE를 보내지 않도록 요구한다. 그러나 EPIPE에러는 여전히 반환된다
	// flags 참고 : https://kldp.org/node/46561
	if (::send(m_sock, str.c_str(), str.size(), MSG_NOSIGNAL) < 0) {
		return false;
	} else {
		return true;
	}
}

int Socket::recv(std::string &str) const {
	// recv 함수 참고 : https://www.it-note.kr/123?category=1068194
	// int recv(int socket, void * rcvBuffer, unsigned int bufferLength, int flags);
	char buff[MAX_RECV + 1];
	memset(buff, 0, MAX_RECV + 1);
	str = "";

	int recv_length = ::recv(m_sock, buff, MAX_RECV + 1, MSG_NOSIGNAL);
	if (recv_length < 0) {
		fprintf(stderr, "socket recv error: %s\n", strerror(errno));
		return -1;
	} else if (recv_length == 0) {
		// 수신한 문자열의 길이가 0이면 길이만 반환
		return 0;
	} else {
		// 수신한 문자열(buff)를 string에 저장
		str = buff;
		// 수신한 문자열의 길이 반환
		return recv_length;
	}
}

bool Socket::is_valid() const {
	// 소켓이 생성 되어서 초기값(-1)이 아니면 true
	return (m_sock == -1);
}
