#pragma once
#include "Account.h"
#include "QQFriends_Qfh.h"
#include "QQgroups_Qfh.h"
#include <vector>
#include <string>

using namespace std;

//QQ帐号类（继承）
class QQ_Qfh : public Account_Qfh
{
public:
	QQ_Qfh(int size);
	QQ_Qfh(string qqid, string qage, string qqpw, string qqname, string sex, string qqpv, string ag, string bir);
	~QQ_Qfh();
	//返回值函数
	virtual int Return_Friend_Number() { return Friend_Number; }//返回好友数量
	virtual int Return_Group_Number() { return Group_Number; }//返回群数量
	virtual string Return_ID() { return ID; }//返回账号的ID
	virtual string  Return_PassWord() { return PassWord; }//返回账号的密码
	virtual string  Return_Name() { return Name; }//返回账号的昵称
	virtual string  Return_Area() { return Area; }//返回IP
	virtual string  Return_Autograph() { return Autograph; }//返回个性签名
	virtual string Return_ApplyDate() { return ApplyDate; }//返回注册时间
	virtual string Return_Sex() { return Sex; }//返回性别
	virtual void Change_group_num(int num) { Group_Number = num; }//群数量，退群时更改
	virtual void Change_Friends_Number(int num) { Friend_Number = num; }//好友数量
	virtual void Change_PassWord(string pw) { PassWord = pw; }//改密码
	virtual void Change_Name(string newname) { Name = newname; }//改名
	virtual void Change_AutoGraph(string newautograph) { Autograph = newautograph; }//改个性签名
	virtual void Change_Area(string newarea) { Area = newarea; }//改IP

	virtual string Return_bir();//返回生日
	//返回模板类函数
	vector<QQFriends_Qfh*>& Return_Friend_List() { return FriendList; }//返回好友
	vector<QQgroups_Qfh*>& Return_group_List() { return GroupList; }//返回群
	vector<QQgroups_Qfh*>& Return_Temporary_GroupList() { return TemporaryGroupList; }//返回临时讨论组
	void Change_Linked_WeiChat(string wechat) { LinkedWeiChat = wechat; }//改变链接的微信号
	string& Return_Linked_WeiChat() { return LinkedWeiChat; }//返回链接微信
	void Get_Friends();//获取好友列表
	void Get_Links();//获取链接微信（文件）
	int flag;
private:

	vector<QQFriends_Qfh*> FriendList;//好友列表
	vector<QQgroups_Qfh*> GroupList;//群列表
	vector<QQgroups_Qfh*> TemporaryGroupList;//临时讨论组列表
	string LinkedWeiChat;//链接的微信
};