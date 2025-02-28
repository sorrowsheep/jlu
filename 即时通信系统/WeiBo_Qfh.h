#pragma once
#include "Account.h"
#include "QQFriends_Qfh.h"
#include "QQgroups_Qfh.h"
#include <vector>
#include <string>

using namespace std;
//微博类
class WeiBo_Qfh : public Account_Qfh
{
public:
	WeiBo_Qfh() {}
	WeiBo_Qfh(string id) { ID = id; LinkedQQ = id; }
	virtual int Return_Friend_Number() { return Friend_Number; }//返回好友数量
	virtual int Return_Group_Number() { return Group_Number; }//返回群数量
	virtual string Return_ID() { return ID; }//返回账号的ID
	virtual string Return_ApplyDate() { return ApplyDate; }//返回注册时间
	virtual string  Return_PassWord() { return PassWord; }//返回账号的密码
	virtual string  Return_Name() { return Name; }//返回账号的昵称
	virtual string  Return_Area() { return Area; }//返回IP
	virtual string  Return_Autograph() { return Autograph; }//返回个性签名
	//
	virtual string Return_Sex() { return Sex; }//返回性别
	virtual string Return_bir() { return birthday; }//返回生日
	//
	virtual void Change_group_num(int num) { Group_Number = num; }//群数量，退群时更改
	virtual void Change_Friends_Number(int num) { Friend_Number = num; }//好友数量
	virtual void Change_PassWord(string pw) { PassWord = pw; }//改密码
	virtual void Change_Name(string newname) { Name = newname; }//改名
	virtual void Change_AutoGraph(string newautograph) { Autograph = newautograph; }//改个性签名
	virtual void Change_Area(string newarea) { Area = newarea; }//改IP
	vector<QQFriends_Qfh*>& Return_Friend_List() { return FriendList; }//返回好友
	vector<QQgroups_Qfh*>& Return_group_List() { return GroupList; }//返回群

private:
	string LinkedQQ;//绑定的QQ
	vector<string>WeiBoContent;//微博内容
	vector<QQFriends_Qfh*> FriendList;//好友列表
	vector<QQgroups_Qfh*> GroupList;//群列表
};
