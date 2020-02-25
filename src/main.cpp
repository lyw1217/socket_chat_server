/*
 =====================
 Name		: main.cpp
 Author		: LYW
 Version		: 0.0.1
 Desciption	: socket chat server main func
 =====================
 */

#include <iostream>
#include <string>
#include "Member.h"
#include "ServerSocket.h"
#include "Epoll.h"

int main(int argc, char *argv[]) {
	int client_fd[MAX_CONNECTIONS] = { 0, };
	int client_index = 0;

	fprintf(stdout, "Server Init...\n");

	if (argc != 2) {
		// argv[0] : filename
		// argv[1] : 추가로 입력한 인자 -> 만약 이게 없어서 argc가 2가 아니면 종료.
		fprintf(stdout, "Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	fprintf(stdout, "port : %d\n", atoi(argv[1]));

	try {
		// Create server socket
		ServerSocket server_sock(atoi(argv[1]));

		while(true){
			ServerSocket new_sock;
			server_sock.accept(new_sock);
			try{
				while(true){
					std::string data;
					new_sock >> data;
					new_sock << data;
				}
			}catch(SocketException&){}
		}
		/*
		Epoll epoll(server_sock.GetSocketFd());

		while (true) {

			if (!epoll.Epoll_Wait()) {
				throw SocketException("epoll_wait() error\n");
			}

			for (int i = 0; i < epoll.GetEventCnt(); i++) {
				if (epoll.GetEventFd(i) == server_sock.GetSocketFd()) {
					ServerSocket client_sock;
					server_sock.accept(client_sock);
					epoll.Epoll_Ctl(client_sock);

					fprintf(stdout, "Server : Connected Client: %d, IP : %s\n",
							client_sock.GetSocketFd(), client_sock.GetSocketAddr());

					// 클라이언트 파일 디스크립터 번호 저장 및 예외처리
					int time_out = 0;
					while(client_fd[client_index] != 0){
						client_index++;
						if(client_index >= MAX_CONNECTIONS)
							client_index = 0;
						time_out++;
						if(time_out >= (MAX_CONNECTIONS * 2)){
							throw SocketException("Server : Client Index is Full!\n");
						}
					}
					client_fd[client_index] = client_sock.GetSocketFd();
				}else{

				}
			}
		}
		 */

	} catch (SocketException &e) {
		fprintf(stdout, "Exception was caught : %s\n", e.description());
	}

	return 0;
}
