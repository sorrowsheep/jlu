#pragma once
#pragma once
#ifndef WEICHATBASE_QFH_H
#define WEICHATBASE_QFH_H
#include "ChatBase_Qfh.h"
#include <vector>
#include <string>
using namespace std;

class Weixin_Qfh; // 前向声明

class WeiChatBase_Qfh :public ChatBase_Qfh
{
public:

	virtual void Apply();//申请注册
	virtual void Menu();//菜单
	virtual void WeiChatMenu();//微信菜单
	virtual void Login();//登录
	virtual void SaveWeiChat();//保存微信
	virtual void GetWeiChat();//获取微信
	virtual void ShowWeiChat();//展示微信

	virtual void AddFriend();//加好友
	virtual void SaveFriends();//保存好友
	virtual void Get_Friends();//获取好友
	virtual void ShowFriends();//展示好友列表
	virtual void CreatGroup();//创建群
	virtual void SaveGroup();//保存群
	virtual void GetGroup();//获取群
	virtual void DeleteFriend();//删除
	virtual void AgreeFriend();//同意好友申请
	virtual void ShowFriendInformation();//展示好友具体信息
	virtual void ShowFriendNoReturn();//展示
	virtual void ChangeFriendRemarks();//修改好友备注

	virtual void SaveChange();//保存修改

	virtual void ShowGroup();//展示群具体信息
	virtual void AgreeMember();//同意加群
	virtual void ShowGroupNoReturn();//展示群（不返回）
	virtual void AddGroupMember();//申请加群
	virtual void QuitGroup();//退出群

	virtual void DeleteGroupMember();//删除群成员（改returnmember个数）

	virtual void ShowGroupInformation();//展示群具体信息

	virtual void ShowMyInformation();//展示个人信息

	virtual void Change_PassWord();
	virtual void Change_Name();
	virtual void Change_AutoGraph();
	virtual void Change_Area();
	virtual void LinkQQ();

	virtual void Get_Links();

	virtual void ShowQQCommonFriends();
	virtual void ShowQQCommonFriendsNoReturn();
	virtual void ShowFriendsNoReturn();
	virtual void AddQQCommonFriend();//添加QQ共同好友

	virtual void InviteGroupMember();

	virtual void Show_Group_InformationNo_Return(string groupId);

	virtual vector<Weixin_Qfh*>& ReturnWeiChatList() { return WeiChatList; }

protected:

	vector<Weixin_Qfh*>WeiChatList;//链接微信

	string LoginedWeiChat;//登陆的微信号

	string WeiChatgroup;//创建的群号;

	string WeiChatGroupMember; //申请加群的QQ号

private:


};

class WeiChat_Qfh :public WeiChatBase_Qfh
{

};
#endif // !WEICHATBASE_QFH_H
