#pragma once
#include "Account.h"
#include "QQFriends_Qfh.h"
#include "QQgroups_Qfh.h"
#include <vector>
#include <string>

using namespace std;
//΢����
class WeiBo_Qfh : public Account_Qfh
{
public:
	WeiBo_Qfh() {}
	WeiBo_Qfh(string id) { ID = id; LinkedQQ = id; }
	virtual int Return_Friend_Number() { return Friend_Number; }//���غ�������
	virtual int Return_Group_Number() { return Group_Number; }//����Ⱥ����
	virtual string Return_ID() { return ID; }//�����˺ŵ�ID
	virtual string Return_ApplyDate() { return ApplyDate; }//����ע��ʱ��
	virtual string  Return_PassWord() { return PassWord; }//�����˺ŵ�����
	virtual string  Return_Name() { return Name; }//�����˺ŵ��ǳ�
	virtual string  Return_Area() { return Area; }//����IP
	virtual string  Return_Autograph() { return Autograph; }//���ظ���ǩ��
	//
	virtual string Return_Sex() { return Sex; }//�����Ա�
	virtual string Return_bir() { return birthday; }//��������
	//
	virtual void Change_group_num(int num) { Group_Number = num; }//Ⱥ��������Ⱥʱ����
	virtual void Change_Friends_Number(int num) { Friend_Number = num; }//��������
	virtual void Change_PassWord(string pw) { PassWord = pw; }//������
	virtual void Change_Name(string newname) { Name = newname; }//����
	virtual void Change_AutoGraph(string newautograph) { Autograph = newautograph; }//�ĸ���ǩ��
	virtual void Change_Area(string newarea) { Area = newarea; }//��IP
	vector<QQFriends_Qfh*>& Return_Friend_List() { return FriendList; }//���غ���
	vector<QQgroups_Qfh*>& Return_group_List() { return GroupList; }//����Ⱥ

private:
	string LinkedQQ;//�󶨵�QQ
	vector<string>WeiBoContent;//΢������
	vector<QQFriends_Qfh*> FriendList;//�����б�
	vector<QQgroups_Qfh*> GroupList;//Ⱥ�б�
};
