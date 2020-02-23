/*
=====================
Name		: Member.cpp
Author		: LYW
Version		: 0.0.1
Desciption	: socket chat server Member class
=====================
*/

#include "Member.h"

const std::string& Member::GetId() const
{
    return mId;
}
void Member::SetId(const std::string& id)
{
    mId = id;
    fprintf(stdout, "'%s' complete ID setup\n");
}

const std::string& Member::GetPw() const
{
    return mPw;
}
void Member::SetPw(const std::string& pw)
{
    mPw = pw;
    fprintf(stdout, "complete Password setup\n");
}

int Member::GetMemberSocket() const
{
    return this->msocket.GetSocketFd();
}
void Member::SetSocket(ServerSocket& _socket)
{
    msocket = _socket;
    fprintf(stdout, "'%d' complete File Descriptor setup\n", msocket.GetSocketFd());
}
