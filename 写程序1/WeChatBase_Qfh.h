#pragma once
#pragma once
#ifndef WEICHATBASE_QFH_H
#define WEICHATBASE_QFH_H
#include "ChatBase_Qfh.h"
#include <vector>
#include <string>
#include "Account.h"
using namespace std;

class Weixin_Qfh; // 前向声明

class WeChatBase_Qfh :public ChatBase_Qfh
{
public:

	virtual void Apply();//申请注册
	virtual void Menu();//菜单
	virtual void WeChatMenu();//微信菜单
	//跳转登录
	virtual void Login();//登录

	virtual void SaveWeChat();//保存微信
	virtual void GetWeChat();//获取微信
	virtual void ShowWeChat();//展示微信

	virtual void AddFriend();//加好友
	virtual void SaveFriends();//保存好友
	virtual void Get_Friends();//获取好友
	virtual void ShowFriends();//展示好友列表
	virtual void CreatGroup();//创建群
	virtual void SaveGroup();//保存群
	void FriendMenu();//好友菜单
	void GroupMenu();//群菜单
	void PersonalInfoMenu(); // 个人信息菜单
	void ServiceMenu(); // 客服菜单
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
	

	virtual vector<Weixin_Qfh*>GetWeChat(string qqid);
	
protected:

	vector<Weixin_Qfh*>WeiChatList;//链接微信

	string LoginedWeiChat;//登陆的微信号

	string WeiChatgroup;//创建的群号;

	string WeiChatGroupMember; //申请加群的QQ号

private:


};

class WeiChat_Qfh :public WeChatBase_Qfh
{
public:
	//跳转登录实现
	void splogin(const string& ID) {
		system("CLS"); // 清屏
		cout << "正在登录 " << ID << "..." << endl;

		// 查找微信ID
		auto it = find_if(WeiChatList.begin(), WeiChatList.end(),
			[&](Weixin_Qfh* weixin) { return weixin->Return_ID() == ID; });

		// 检查是否找到了对应的微信
		if (it != WeiChatList.end()) {
			Weixin_Qfh* weixinObj = *it;

			// 如果该微信已处于登录状态，直接获取信息
			if (weixinObj->flag == 1) {
				LoginedWeiChat = ID; // 设置已登录的微信号
				Get_Friends(); // 获取好友
				GetGroup(); // 获取群组
				Get_Links(); // 获取绑定的 QQ
				cout << "登录成功" << endl;
				cout << "按任意键开始使用微信" << endl;
				if (getchar() != EOF)
					WeChatMenu(); // 进入微信主菜单
				return;
			}

			// 如果微信未登录
			cout << "该微信尚未登录，默认密码进行验证..." << endl;
			string defaultPassword = "1"; 
			cin >> defaultPassword;
			// 假设有一个默认密码，实际情况请根据需求调整
			if (weixinObj->Return_PassWord() == defaultPassword) {
				LoginedWeiChat = ID; // 设置已登录的微信号
				Get_Friends(); // 获取好友
				GetGroup(); // 获取群组
				Get_Links(); // 获取绑定的 QQ
				cout << "登录成功" << endl;
				cout << "按任意键开始使用微信" << endl;
				if (getchar() != EOF)
					WeChatMenu(); // 进入微信主菜单
				return;
			}
			else {
				cout << "默认密码验证失败，无法登录。" << endl;
				return;
			}
		}
		else {
			cout << "未找到对应的微信号：" << ID << endl;
		}
	}
};
#endif // !WEICHATBASE_QFH_H
