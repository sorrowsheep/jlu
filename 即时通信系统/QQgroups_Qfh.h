
#pragma once
#include <string>
#include <vector>

using namespace std;

class QQ_Qfh; // ǰ������

//QQȺ�ࣨ��ϣ���Ԫ��
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
	string GroupID;//Ⱥ��
	string GroupName;//Ⱥ����
	string CreatUserID;//Ⱥ��
	vector<string> GroupMembers;//Ⱥ��Ա�б�
	vector<string> AdminsList;//����Ա�б�
};
