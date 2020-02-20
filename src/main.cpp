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
	Member n("1234", "5678", 66);
	Member k("qwer", "asdf", 77);

	m.SetId("abc");
	m.SetPw("123");
	m.SetFd(44);

	cout << m.GetId() << m.GetPw() << m.GetFd() << endl;
	cout << n.GetId() << n.GetPw() << n.GetFd() << endl;
	cout << k.GetId() << k.GetPw() << k.GetFd() << endl;

	return 0;
}
