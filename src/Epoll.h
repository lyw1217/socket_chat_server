/*
 * Epoll.h
 *
 *  Created on: 2020. 2. 21.
 *      Author: yw
 *
		int epoll_create(int size);
		//size는 epoll_fd의 크기정보를 전달한다.
		// 반환 값 : 실패 시 -1, 일반적으로 epoll_fd의 값을 리턴

		int epoll_ctl(int epoll_fd,			// epoll_fd
				int operate_enum,			// 어떤 변경을 할지 결정하는 enum값
				int enroll_fd,				// 등록할 fd
				struct epoll_event* event	// 관찰 대상의 관찰 이벤트 유형
         );
		// 반환 값 : 실패 시 -1, 성공시 0

		int epoll_wait(int epoll_fd,		// epoll_fd
				struct epoll_event* event,	// event 버퍼의 주소
				int maxevents,				// 버퍼에 들어갈 수 있는 구조체 최대 개수
				int timeout					// select의 timeout과 동일 단위는 1/1000
		);
		// 성공시 이벤트 발생한 파일 디스크립터 개수 반환, 실패시 -1 반환
 */

#ifndef EPOLL_H_
#define EPOLL_H_

#include <sys/epoll.h>
#include "ServerSocket.h"
#include "SocketException.h"

const int EPOLL_SIZE = 50;

class Epoll :private ServerSocket{
public:
	Epoll(int _server_sock);
	virtual ~Epoll();
	bool Epoll_Wait();
	int GetEventCnt() const;
	int GetEventFd(int i) const;
	bool Epoll_Ctl(ServerSocket&);
	bool e_is_valid() const;

private:
	struct epoll_event m_ep_events[sizeof(struct epoll_event) * EPOLL_SIZE];
	struct epoll_event m_event;
	int m_epfd;
	int m_event_cnt;

};

#endif /* EPOLL_H_ */
