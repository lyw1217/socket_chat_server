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

using namespace std;

constexpr int MAX_USER_LEN = 20;

class Member
{
public:
	Member(string id, string pw, int fd)
		: mId(id), mPw(pw), mFd(fd) 
	{
		cout << "member " << id << " complete setup\n";
	};

	Member(const Member& m)
		:mId(m.mId), mPw(m.mPw), mFd(m.mFd) {};

	const string& GetId() const;
	void SetId(const string& id);

	const string& GetPw() const;
	void SetPw(const string& pw);

	int GetFd() const;
	void SetFd(const int fd);

	virtual ~Member() {};

private:
	string mId;
	string mPw;
	int mFd;
};
