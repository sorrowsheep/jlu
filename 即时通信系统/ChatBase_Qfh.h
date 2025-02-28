#pragma once
#include <vector>
#include <string>
#include"Account.h"
#include"QQFriends_Qfh.h"
#include"QQgroups_Qfh.h"
#include"QQ_Qfh.h"
#include"WeiBo_Qfh.h"
#include"Weixin_Qfh.h"
#include<deque>
#include<sstream>
#include<Windows.h>
#pragma warning( disable : 4996 )
class QQChat_Qfh;
class WeiBoChat_Qfh;
class WeiChat_Qfh;
class MainMenu_Qfh;
extern QQChat_Qfh QQFun;
extern WeiBoChat_Qfh WeiBoFun;
extern WeiChat_Qfh WeChatFun;
extern MainMenu_Qfh mainmenu;
// 功能抽象类，用于实现聊天软件的基本功能
class ChatBase_Qfh
{
public:
    virtual void Apply() = 0; // 申请注册
    virtual void Login() = 0; // 登录
    virtual void Menu() = 0; // 菜单
    virtual void AddFriend() = 0; // 加好友
    virtual void SaveFriends() = 0; // 保存好友
    virtual void Get_Friends() = 0; // 获取好友
    virtual void ShowFriends() = 0; // 展示好友列表
    virtual void DeleteFriend() = 0; // 删除
    virtual void AgreeFriend() = 0; // 同意申请
    virtual void ShowFriendInformation() = 0; // 展示好友具体信息
    virtual void ChangeFriendRemarks() = 0; // 修改好友备注
    virtual void SaveChange() = 0; // 保存修改
    virtual void AgreeMember() = 0; // 同意加群
    virtual void ShowMyInformation() = 0; // 展示个人信息
    virtual void Change_PassWord() = 0; // 改密码
    virtual void Change_Name() = 0; // 改名
    virtual void Change_AutoGraph() = 0; // 改个性签名
    virtual void Change_Area() = 0; // 改IP
    virtual void Get_Links() = 0; // 获取链接
};

