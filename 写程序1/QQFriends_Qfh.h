#pragma once
#include <string>

using namespace std;

class QQ_Qfh; // ǰ������

//QQ�����ࣨ��ϣ���Ԫ��
class QQFriends_Qfh
{

public:
	friend class QQ_Qfh;//��Ԫ��
	QQFriends_Qfh(string name, string id, string newremarks) :FriendName(name), ID(id), Remarks(newremarks) {}
	QQFriends_Qfh(string name, string id) :FriendName(name), ID(id), Remarks("δ��ע") {}
	string ReturnFriendName() {
		return FriendName;
	}
	string Return_ID() {
		return ID;
	}
	string ReturnRemarks() { return Remarks; }
	void ChangeRemarks(string newremarks) { Remarks = newremarks; }
private:
	string FriendName;//��������
	string ID;//����ID
	string Remarks;//���ѱ�ע
};