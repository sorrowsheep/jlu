#pragma once
#pragma once
#ifndef WEICHATBASE_QFH_H
#define WEICHATBASE_QFH_H
#include "ChatBase_Qfh.h"
#include <vector>
#include <string>
using namespace std;

class Weixin_Qfh; // ǰ������

class WeiChatBase_Qfh :public ChatBase_Qfh
{
public:

	virtual void Apply();//����ע��
	virtual void Menu();//�˵�
	virtual void WeiChatMenu();//΢�Ų˵�
	virtual void Login();//��¼
	virtual void SaveWeiChat();//����΢��
	virtual void GetWeiChat();//��ȡ΢��
	virtual void ShowWeiChat();//չʾ΢��

	virtual void AddFriend();//�Ӻ���
	virtual void SaveFriends();//�������
	virtual void Get_Friends();//��ȡ����
	virtual void ShowFriends();//չʾ�����б�
	virtual void CreatGroup();//����Ⱥ
	virtual void SaveGroup();//����Ⱥ
	virtual void GetGroup();//��ȡȺ
	virtual void DeleteFriend();//ɾ��
	virtual void AgreeFriend();//ͬ���������
	virtual void ShowFriendInformation();//չʾ���Ѿ�����Ϣ
	virtual void ShowFriendNoReturn();//չʾ
	virtual void ChangeFriendRemarks();//�޸ĺ��ѱ�ע

	virtual void SaveChange();//�����޸�

	virtual void ShowGroup();//չʾȺ������Ϣ
	virtual void AgreeMember();//ͬ���Ⱥ
	virtual void ShowGroupNoReturn();//չʾȺ�������أ�
	virtual void AddGroupMember();//�����Ⱥ
	virtual void QuitGroup();//�˳�Ⱥ

	virtual void DeleteGroupMember();//ɾ��Ⱥ��Ա����returnmember������

	virtual void ShowGroupInformation();//չʾȺ������Ϣ

	virtual void ShowMyInformation();//չʾ������Ϣ

	virtual void Change_PassWord();
	virtual void Change_Name();
	virtual void Change_AutoGraph();
	virtual void Change_Area();
	virtual void LinkQQ();

	virtual void Get_Links();

	virtual void ShowQQCommonFriends();
	virtual void ShowQQCommonFriendsNoReturn();
	virtual void ShowFriendsNoReturn();
	virtual void AddQQCommonFriend();//���QQ��ͬ����

	virtual void InviteGroupMember();

	virtual void Show_Group_InformationNo_Return(string groupId);

	virtual vector<Weixin_Qfh*>& ReturnWeiChatList() { return WeiChatList; }

protected:

	vector<Weixin_Qfh*>WeiChatList;//����΢��

	string LoginedWeiChat;//��½��΢�ź�

	string WeiChatgroup;//������Ⱥ��;

	string WeiChatGroupMember; //�����Ⱥ��QQ��

private:


};

class WeiChat_Qfh :public WeiChatBase_Qfh
{

};
#endif // !WEICHATBASE_QFH_H
