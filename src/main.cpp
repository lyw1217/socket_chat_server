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

int main(int argc, char *argv[]) {
	std::cout << "Server Init..\n";

	//
	if (argc != 2) {
		// argv[0] : filename
		// argv[1] : 추가로 입력한 인자 -> 이게 없어서 argc가 2가 아니면 종료.
		std::cout << "Usage : " << argv[0] << "<port>\n";
		exit(1);
	}

	printf("port : %d\n", atoi(argv[1]));

	try {
		// Create server socket
		ServerSocket server_sock(atoi(argv[1]));
		while (true) {

			ServerSocket new_sock;
			server_sock.accept(new_sock);

			try {
				while (true) {
					std::string data;
					new_sock >> data;
					new_sock << data;
				}
			} catch (SocketException&) {
			}

		}

	} catch (SocketException &e) {
		std::cout << "Exception was caught:" << e.description() << "\n";
	}

	return 0;
}
