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
// ���ܳ����࣬����ʵ����������Ļ�������
class ChatBase_Qfh
{
public:
    virtual void Apply() = 0; // ����ע��
    virtual void Login() = 0; // ��¼
    virtual void Menu() = 0; // �˵�
    virtual void AddFriend() = 0; // �Ӻ���
    virtual void SaveFriends() = 0; // �������
    virtual void Get_Friends() = 0; // ��ȡ����
    virtual void ShowFriends() = 0; // չʾ�����б�
    virtual void DeleteFriend() = 0; // ɾ��
    virtual void AgreeFriend() = 0; // ͬ������
    virtual void ShowFriendInformation() = 0; // չʾ���Ѿ�����Ϣ
    virtual void ChangeFriendRemarks() = 0; // �޸ĺ��ѱ�ע
    virtual void SaveChange() = 0; // �����޸�
    virtual void AgreeMember() = 0; // ͬ���Ⱥ
    virtual void ShowMyInformation() = 0; // չʾ������Ϣ
    virtual void Change_PassWord() = 0; // ������
    virtual void Change_Name() = 0; // ����
    virtual void Change_AutoGraph() = 0; // �ĸ���ǩ��
    virtual void Change_Area() = 0; // ��IP
    virtual void Get_Links() = 0; // ��ȡ����
};

