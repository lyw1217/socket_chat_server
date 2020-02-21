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

constexpr int MAX_USER_LEN = 20;

class Member
{
public:
	Member(std::string id, std::string pw, int fd)
		: mId(id), mPw(pw), mFd(fd) 
	{
		fprintf(stdout, "member %s complete setup\n", id);
	};

	Member(const Member& m)
		:mId(m.mId), mPw(m.mPw), mFd(m.mFd) {};

	const std::string& GetId() const;
	void SetId(const std::string& id);

	const std::string& GetPw() const;
	void SetPw(const std::string& pw);

	int GetFd() const;
	void SetFd(const int fd);

	virtual ~Member() {};

private:
	std::string mId;
	std::string mPw;
	int mFd;
};
