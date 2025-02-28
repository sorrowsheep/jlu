#pragma once
#include "Account.h"
#include "QQFriends_Qfh.h"
#include "QQgroups_Qfh.h"
#include <vector>
#include <string>

using namespace std;

// 微信账号类
class Weixin_Qfh : public Account_Qfh
{
public:
	Weixin_Qfh(int size);
	Weixin_Qfh(string qqid);
	Weixin_Qfh(string qqid, string qage, string qqpw, string qqname, string wxsex, string qqpv, string ag, string bir);
	~Weixin_Qfh();
	virtual int Return_Friend_Number() { return Friend_Number; }
	virtual int Return_Group_Number() { return Group_Number; }
	virtual string Return_ID() { return ID; }
	virtual string  Return_PassWord() { return PassWord; }
	virtual string  Return_Name() { return Name; }
	virtual string  Return_Area() { return Area; }
	virtual string  Return_Autograph() { return Autograph; }
	virtual string Return_ApplyDate() { return ApplyDate; }
	//
	virtual string Return_Sex() { return Sex; }
	virtual string Return_bir() { return birthday; }
	//
	virtual void Change_group_num(int num) { Group_Number = num; }
	virtual void Change_Friends_Number(int num) { Friend_Number = num; }
	virtual void Change_PassWord(string pw) { PassWord = pw; }
	virtual void Change_Name(string newname) { Name = newname; }
	virtual void Change_AutoGraph(string newautograph) { Autograph = newautograph; }
	virtual void Change_Area(string newarea) { Area = newarea; }
	//
	vector<QQFriends_Qfh*>& Return_Friend_List() { return FriendList; }
	vector<QQgroups_Qfh*>& Return_group_List() { return GroupList; }
	string& Return_LinkedQQ() { return LinkedQQ; }
	void Change_LinkedQQ(string qq) { LinkedQQ = qq; }
	//
	void Get_Links();//获取链接QQ（文件）
	void Get_Friends();//获取好友列表
	int flag;
	


private:

	vector<QQFriends_Qfh*> FriendList;//好友列表
	vector<QQgroups_Qfh*> GroupList;//群列表
	string LinkedQQ;//绑定的QQ
};