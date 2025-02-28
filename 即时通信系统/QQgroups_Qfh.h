
#pragma once
#include <string>
#include <vector>

using namespace std;

class QQ_Qfh; // 前向声明

//QQ群类（组合：友元）
class QQgroups_Qfh
{

public:
	friend class QQ_Qfh;
	QQgroups_Qfh(string id, string name, string userid) :GroupID(id), GroupName(name), CreatUserID(userid), TypeID(0) {};
	vector<string>& ReturnGroupMembers() { return GroupMembers; }
	vector<string>& Return_Admins_ID() { return AdminsList; }
	string Return_Group_ID() { return GroupID; }
	string Return_Group_Name() { return GroupName; }
	string ReturnCreatUserID() { return CreatUserID; }
	void ChangeTypeID(int id) { TypeID = id; }

protected:
	int TypeID;
	string GroupID;//群号
	string GroupName;//群名称
	string CreatUserID;//群主
	vector<string> GroupMembers;//群成员列表
	vector<string> AdminsList;//管理员列表
};
