#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "ChatBase_Qfh.h"

using namespace std;
class QQ_Qfh; // ǰ������
class QQgroups_Qfh; // ǰ������

//QQ����ģ����ࣨ�̳У�
class QQChatBase_Qfh : public ChatBase_Qfh
{

public:
	virtual void Apply();//����ע��
	virtual void Menu();//�˵�
	virtual void Login();//��¼
	virtual void QQMenu();//QQ�˵�
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
	virtual void SaveQQ();//����QQ
	virtual void GetQQ();//��ȡQQ
	virtual void ShowQQ();//չʾQQ

//�һ�����
    virtual void Find_PassWord();
	// ���º����ļ�
	virtual void UpdateFriendFile(int sub);

	//����QQ������
	int FindQQIndex(const string& qqid);
	//���뷵��
	void WaitForUserInput();

	//����Ա�˵�
	void HandleMenuSelection(int select);

	int FindGroup(const string& groupID, int sub);
	bool IsFriend(const string& friendID, int sub);
	bool IsMemberInGroup(const string& memberID, int groupIndex, int sub);
	void AddMemberToGroup(const string& groupID, const string& memberID);

	virtual void AddFriend();//�Ӻ���
	virtual void SaveFriends();//�������
	virtual void Get_Friends();//��ȡ����
	virtual void ShowFriends();//չʾ�����б�
	virtual void DeleteFriend();
	void SortFriendList();
	//ɾ��
	virtual void AgreeFriend();

	void UpdateFriendApplication(const string& filename, const string& prefix, const string& id);

	void UpdateFriendFile(const string& filename, const string& userId);

	void RemoveFriendApplication(const string& filename, const string& id);

	void ProcessAgreeFriend(const string& fdqq, const string& friendqqfilename);

	void ProcessRejectFriend(const string& fdqq, const string& subfilename, const string& friendqqfilename);

	//ͬ������
	virtual void ShowMyInformation();//չʾ������Ϣ

	virtual void Change_PassWord();//������
	virtual void Change_Name();//����
	virtual void Change_AutoGraph();//�ĸ���ǩ��
	virtual void Change_Area();//��IP



	void DisplayCommonFriends(bool shouldReturn);
	virtual void Get_Links();//��ȡ����
	virtual void LinkWeiChat();
	void UnlinkWeiChat();
	void UnlinkQQFromWeChat(int thisQQ, const string& linkedWeChat);
	void UnlinkWeChatFromQQ(int thisQQ, const string& linkedWeChat);
	void RemoveLinkRecord(const string& service, const string& serviceID, const string& linkLine);
	//����΢��

	virtual void InviteGroupMember();//�����Ⱥ
	virtual void CreatQQgroup();//����Ⱥ
	virtual void SaveQQGroup();//����Ⱥ
	virtual void ShowQQGroup();//չʾȺ�б�
	virtual void GetQQGroup();//��ȡȺ
	virtual void AddInGroupMember();//�����Ⱥ
	virtual void AgreeMember();//ͬ���Ⱥ
	virtual void DeleteGroupMember();//ɾ��Ⱥ��Ա����returnmember������
	virtual void AddGroupAdmin();//��ΪȺ����Ա
	virtual void QuitGroup();//�˳�Ⱥ



	void removeGroupFromFile(const string filename, const string& groupid);

	virtual void removeUserFromGroupFile(const string& filename, const string& userID);//ɾ��Ⱥ��Ա�ļ�
	virtual void removeUserFromAdminFile(const string& filename, const string& userID, const string& groupid);//ɾ��Ⱥ����Ա�ļ�

	virtual void SaveChange();//�����޸�
	virtual void ShowFriendInformation();
	//չʾ���Ѿ�����Ϣ
	virtual void ShowFriendNoReturn();//չʾ���ѣ������أ�
	virtual void ChangeFriendRemarks();//�޸ĺ��ѱ�ע
	virtual void ShowGroupInformation();//չʾȺ������Ϣ
	virtual void ShowQQGroupNoReturn();//չʾȺ�������أ�
	virtual void ShowWeiChatCommonFriends();//չʾ΢�Ź�ͬ����
	virtual void CreateWeiBo();//����΢��(�����ļ�������
	virtual void CreateWeChat();
	virtual string& Returnqqnumber() { return qqnumber; }//����QQ��
	virtual vector<QQ_Qfh*>& ReturnQQ() { return QQ; }//����QQ�б�������



	virtual void Show_WeiChat_Common_FriendsNo_Return();//չʾ΢�Ź�ͬ���ѣ������أ�
	virtual void AddWeiChatCommonFriend();//���΢�Ź�ͬ����
	// ���������������û�����
	int findUserIndex(const string& userId);
	
	bool isTemporaryGroupValid(const string& groupId);
	int findTemporaryGroupIndex(const string& groupId);
	void DisplayLog(const string& userId);
	void ShowUserLog(const string& userId);
	void displayTemporaryGroups(const vector<QQgroups_Qfh*>& groups);
	virtual void CreatTemporaryGroup();//������ʱ��
	virtual void JoinTemporaryGroup();//������ʱ��

	virtual void Show_Group_InformationNo_Return(string groupId);//չʾȺ������Ϣ�������أ�
	vector<QQgroups_Qfh*>ReturnAllQQTemporaryGroup() { return AllQQTemporaryGroup; }//����������ʱ��

	//���Ӵ���
	void SwitchToWeChat(const string& linkweichat);


	vector<QQ_Qfh*>QQ;
	string qqnumber; //��½��QQ��
	string QQgroup;//������Ⱥ��;
	string GroupMember; //�����Ⱥ��QQ��
	vector<QQgroups_Qfh*>AllQQTemporaryGroup;//��ʱ������


private:
	//��־��¼(����T)
	template <typename T>
	void LogOperation(const T& operation, const string& userId);

};

class QQChat_Qfh : public QQChatBase_Qfh
{
public:
	
    // ����ʵ��...void SwitchToWeChat(const string& wechatid);
};