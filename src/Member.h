/*
=====================
Name		: Member.h
Author		: LYW
Version		: 0.0.1
Desciption	: socket chat server Member class header
=====================
*/

#pragma once

#include <iostream>
#include <string>
#include "ServerSocket.h"

constexpr int MAX_USER_LEN = 20;

class Member : private ServerSocket
{
public:
	Member(std::string id, std::string pw, ServerSocket& _socket)
		: mId(id), mPw(pw)
	{
		msocket = _socket;
		fprintf(stdout, "member %s complete setup\n", id);
	};

	Member(const Member& m)
		:mId(m.mId), mPw(m.mPw), msocket(m.msocket) {};

	const std::string& GetId() const;
	void SetId(const std::string& id);

	const std::string& GetPw() const;
	void SetPw(const std::string& pw);

	int GetMemberSocket() const;
	void SetSocket(ServerSocket&);

	virtual ~Member() {};

private:
	std::string mId;
	std::string mPw;
	ServerSocket msocket;
};
