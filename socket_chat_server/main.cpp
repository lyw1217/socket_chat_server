/*
=====================
Name		: main.cpp
Author		: LYW
Version		: 0.0.1
Desciption	: socket chat server main func
=====================
*/

#include "main.h"

int main() {
	Member m("abcd","1234",55);

	m.SetId("abc");
	m.SetPw("123");
	m.SetFd(44);

	cout << m.GetId() << m.GetPw() << m.GetFd() << endl;

	return 0;
}