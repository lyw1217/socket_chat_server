/*
=====================
Name		: Member.cpp
Author		: LYW
Version		: 0.0.1
Desciption	: socket chat server Member class
=====================
*/

#include "Member.h"

const string& Member::GetId() const
{
    return mId;
}
void Member::SetId(const string& id)
{
    mId = id;
    cout << "" << id << " complete ID setup\n";
}

const string& Member::GetPw() const
{
    return mPw;
}
void Member::SetPw(const string& pw)
{
    mPw = pw;
    cout << "" << pw << " complete Password setup\n";
}

int Member::GetFd() const
{
    return mFd;
}
void Member::SetFd(const int fd)
{
    mFd = fd;
    cout << "" << fd << " complete File Descriptor setup\n";
}