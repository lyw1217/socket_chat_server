/*
 * Epoll.cpp
 *
 *  Created on: 2020. 2. 21.
 *      Author: yw
 */

#include "Epoll.h"

Epoll::Epoll(int _server_sock) :
		m_event_cnt(0) {
	// 커널이 관리하는 epoll 인스턴스라 불리는 파일 디스크립터의 저장소 생성
	// 성공 시 epoll 파일 디스크립터, 실패시 -1 반환
	m_epfd = epoll_create(EPOLL_SIZE);
	if (m_epfd == -1) {
		throw SocketException("Server : could not create epoll\n");
	}

	m_event.events = EPOLLIN;
	m_event.data.fd = _server_sock;

	// 파일 디스크립터(server_sock)를 epoll 인스턴스에 등록한다
	// 관찰 대상의 관찰 이벤트 유형은 EPOLLIN
	if (::epoll_ctl(m_epfd, EPOLL_CTL_ADD, _server_sock, &m_event) == -1) {
		throw SocketException("Server : epoll_ctl() error\n");
	}
}

Epoll::~Epoll() {
	if(e_is_valid()){
		close(m_epfd);
	}
}

bool Epoll::Epoll_Wait(){
	m_event_cnt = ::epoll_wait(m_epfd, m_ep_events, EPOLL_SIZE, -1);
	if(m_event_cnt == -1){
		return false;
	}else{
		return true;
	}
}

int Epoll::GetEventCnt() const{
	return m_event_cnt;
}

int Epoll::GetEventFd(int i) const{
	return m_ep_events[i].data.fd;
}

bool Epoll::Epoll_Ctl(ServerSocket& socket) {
	m_event.events = EPOLLIN;
	m_event.data.fd = socket.GetSocketFd();

	// 파일 디스크립터(server_sock)를 epoll 인스턴스에 등록한다
	// 관찰 대상의 관찰 이벤트 유형은 EPOLLIN
	if (::epoll_ctl(m_epfd, EPOLL_CTL_ADD, socket.GetSocketFd(), &m_event) == -1) {
		throw SocketException("Server : epoll_ctl() error\n");
		return false;
	}

	return true;
}

bool Epoll::e_is_valid() const{
	return (m_epfd > -1) ? true : false;
}

