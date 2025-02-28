#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "ChatBase_Qfh.h"

using namespace std;
class QQ_Qfh; // 前向声明
class QQgroups_Qfh; // 前向声明

//QQ功能模块基类（继承）
class QQChatBase_Qfh : public ChatBase_Qfh
{

public:
	virtual void Apply();//申请注册
	virtual void Menu();//菜单
	virtual void Login();//登录
	virtual void QQMenu();//QQ菜单
	void displayMainMenu(int menuWidth);
	void handleMainMenuSelection(int select, int menuWidth);

	void handleFriendMenu(int menuWidth);
	void displayFriendMenu(int menuWidth);

	void handleGroupMenu(int menuWidth);
	void displayGroupMenu(int menuWidth);
	void handleQQGroupMenu(int menuWidth);
	void displayQQGroupMenu(int menuWidth);
	void handleWeChatGroupMenu(int menuWidth);
	void displayWeChatGroupMenu(int menuWidth);

	void handlePersonalInfoMenu(int menuWidth);
	void displayViewPersonalInfoMenu(int menuWidth);
	void displayModifyPersonalInfoMenu(int menuWidth);
	void handleModifyPersonalInfoMenu(int menuWidth);

	void handleServiceMenu(int menuWidth);
	void displayServiceMenu(int menuWidth);
	virtual void SaveQQ();//保存QQ
	virtual void GetQQ();//获取QQ
	virtual void ShowQQ();//展示QQ

//找回密码
    virtual void Find_PassWord();
	// 更新好友文件
	virtual void UpdateFriendFile(int sub);

	//查找QQ的索引
	int FindQQIndex(const string& qqid);
	//输入返回
	void WaitForUserInput();

	//管理员菜单
	void HandleMenuSelection(int select);

	int FindGroup(const string& groupID, int sub);
	bool IsFriend(const string& friendID, int sub);
	bool IsMemberInGroup(const string& memberID, int groupIndex, int sub);
	void AddMemberToGroup(const string& groupID, const string& memberID);

	virtual void AddFriend();//加好友
	virtual void SaveFriends();//保存好友
	virtual void Get_Friends();//获取好友
	virtual void ShowFriends();//展示好友列表
	virtual void DeleteFriend();
	void SortFriendList();
	//删除
	virtual void AgreeFriend();

	void UpdateFriendApplication(const string& filename, const string& prefix, const string& id);

	void UpdateFriendFile(const string& filename, const string& userId);

	void RemoveFriendApplication(const string& filename, const string& id);

	void ProcessAgreeFriend(const string& fdqq, const string& friendqqfilename);

	void ProcessRejectFriend(const string& fdqq, const string& subfilename, const string& friendqqfilename);

	//同意申请
	virtual void ShowMyInformation();//展示个人信息

	virtual void Change_PassWord();//改密码
	virtual void Change_Name();//改名
	virtual void Change_AutoGraph();//改个性签名
	virtual void Change_Area();//改IP



	void DisplayCommonFriends(bool shouldReturn);
	virtual void Get_Links();//获取链接
	virtual void LinkWeiChat();
	void UnlinkWeiChat();
	void UnlinkQQFromWeChat(int thisQQ, const string& linkedWeChat);
	void UnlinkWeChatFromQQ(int thisQQ, const string& linkedWeChat);
	void RemoveLinkRecord(const string& service, const string& serviceID, const string& linkLine);
	//链接微信

	virtual void InviteGroupMember();//邀请加群
	virtual void CreatQQgroup();//创建群
	virtual void SaveQQGroup();//保存群
	virtual void ShowQQGroup();//展示群列表
	virtual void GetQQGroup();//获取群
	virtual void AddInGroupMember();//申请加群
	virtual void AgreeMember();//同意加群
	virtual void DeleteGroupMember();//删除群成员（改returnmember个数）
	virtual void AddGroupAdmin();//设为群管理员
	virtual void QuitGroup();//退出群



	void removeGroupFromFile(const string filename, const string& groupid);

	virtual void removeUserFromGroupFile(const string& filename, const string& userID);//删除群成员文件
	virtual void removeUserFromAdminFile(const string& filename, const string& userID, const string& groupid);//删除群管理员文件

	virtual void SaveChange();//保存修改
	virtual void ShowFriendInformation();
	//展示好友具体信息
	virtual void ShowFriendNoReturn();//展示好友（不返回）
	virtual void ChangeFriendRemarks();//修改好友备注
	virtual void ShowGroupInformation();//展示群具体信息
	virtual void ShowQQGroupNoReturn();//展示群（不返回）
	virtual void ShowWeiChatCommonFriends();//展示微信共同好友
	virtual void CreateWeiBo();//创建微博(链接文件创建）
	virtual void CreateWeChat();
	virtual string& Returnqqnumber() { return qqnumber; }//返回QQ号
	virtual vector<QQ_Qfh*>& ReturnQQ() { return QQ; }//返回QQ列表（容器）



	virtual void Show_WeiChat_Common_FriendsNo_Return();//展示微信共同好友（不返回）
	virtual void AddWeiChatCommonFriend();//添加微信共同好友
	// 辅助函数：查找用户索引
	int findUserIndex(const string& userId);
	
	bool isTemporaryGroupValid(const string& groupId);
	int findTemporaryGroupIndex(const string& groupId);
	void DisplayLog(const string& userId);
	void ShowUserLog(const string& userId);
	void displayTemporaryGroups(const vector<QQgroups_Qfh*>& groups);
	virtual void CreatTemporaryGroup();//创建临时组
	virtual void JoinTemporaryGroup();//加入临时组

	virtual void Show_Group_InformationNo_Return(string groupId);//展示群具体信息（不返回）
	vector<QQgroups_Qfh*>ReturnAllQQTemporaryGroup() { return AllQQTemporaryGroup; }//返回所有临时组

	//链接创建
	void SwitchToWeChat(const string& linkweichat);


	vector<QQ_Qfh*>QQ;
	string qqnumber; //登陆的QQ号
	string QQgroup;//创建的群号;
	string GroupMember; //申请加群的QQ号
	vector<QQgroups_Qfh*>AllQQTemporaryGroup;//临时讨论组


private:
	//日志记录(泛型T)
	template <typename T>
	void LogOperation(const T& operation, const string& userId);

};

class QQChat_Qfh : public QQChatBase_Qfh
{
public:
	
    // 具体实现...void SwitchToWeChat(const string& wechatid);
};