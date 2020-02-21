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
		while (true) {

			ServerSocket client_sock;
			server_sock.accept(client_sock);

			try {
				while (true) {
					std::string data;
					client_sock >> data;
					client_sock << data;
				}
			} catch (SocketException&) {
			}

		}

	} catch (SocketException &e) {
		fprintf(stdout, "Exception was caught : %s\n", e.description());
	}

	return 0;
}
