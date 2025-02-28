#pragma once
#include <string>

using namespace std;

class QQ_Qfh; // 前向声明

//QQ好友类（组合：友元）
class QQFriends_Qfh
{

public:
	friend class QQ_Qfh;//友元类
	QQFriends_Qfh(string name, string id, string newremarks) :FriendName(name), ID(id), Remarks(newremarks) {}
	QQFriends_Qfh(string name, string id) :FriendName(name), ID(id), Remarks("未备注") {}
	string ReturnFriendName() {
		return FriendName;
	}
	string Return_ID() {
		return ID;
	}
	string ReturnRemarks() { return Remarks; }
	void ChangeRemarks(string newremarks) { Remarks = newremarks; }
private:
	string FriendName;//好友姓名
	string ID;//好友ID
	string Remarks;//好友备注
};