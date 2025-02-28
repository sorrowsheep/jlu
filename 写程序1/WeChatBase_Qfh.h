#pragma once
#pragma once
#ifndef WEICHATBASE_QFH_H
#define WEICHATBASE_QFH_H
#include "ChatBase_Qfh.h"
#include <vector>
#include <string>
#include "Account.h"
using namespace std;

class Weixin_Qfh; // ǰ������

class WeChatBase_Qfh :public ChatBase_Qfh
{
public:

	virtual void Apply();//����ע��
	virtual void Menu();//�˵�
	virtual void WeChatMenu();//΢�Ų˵�
	//��ת��¼
	virtual void Login();//��¼

	virtual void SaveWeChat();//����΢��
	virtual void GetWeChat();//��ȡ΢��
	virtual void ShowWeChat();//չʾ΢��

	virtual void AddFriend();//�Ӻ���
	virtual void SaveFriends();//�������
	virtual void Get_Friends();//��ȡ����
	virtual void ShowFriends();//չʾ�����б�
	virtual void CreatGroup();//����Ⱥ
	virtual void SaveGroup();//����Ⱥ
	void FriendMenu();//���Ѳ˵�
	void GroupMenu();//Ⱥ�˵�
	void PersonalInfoMenu(); // ������Ϣ�˵�
	void ServiceMenu(); // �ͷ��˵�
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
	

	virtual vector<Weixin_Qfh*>GetWeChat(string qqid);
	
protected:

	vector<Weixin_Qfh*>WeiChatList;//����΢��

	string LoginedWeiChat;//��½��΢�ź�

	string WeiChatgroup;//������Ⱥ��;

	string WeiChatGroupMember; //�����Ⱥ��QQ��

private:


};

class WeiChat_Qfh :public WeChatBase_Qfh
{
public:
	//��ת��¼ʵ��
	void splogin(const string& ID) {
		system("CLS"); // ����
		cout << "���ڵ�¼ " << ID << "..." << endl;

		// ����΢��ID
		auto it = find_if(WeiChatList.begin(), WeiChatList.end(),
			[&](Weixin_Qfh* weixin) { return weixin->Return_ID() == ID; });

		// ����Ƿ��ҵ��˶�Ӧ��΢��
		if (it != WeiChatList.end()) {
			Weixin_Qfh* weixinObj = *it;

			// �����΢���Ѵ��ڵ�¼״̬��ֱ�ӻ�ȡ��Ϣ
			if (weixinObj->flag == 1) {
				LoginedWeiChat = ID; // �����ѵ�¼��΢�ź�
				Get_Friends(); // ��ȡ����
				GetGroup(); // ��ȡȺ��
				Get_Links(); // ��ȡ�󶨵� QQ
				cout << "��¼�ɹ�" << endl;
				cout << "���������ʼʹ��΢��" << endl;
				if (getchar() != EOF)
					WeChatMenu(); // ����΢�����˵�
				return;
			}

			// ���΢��δ��¼
			cout << "��΢����δ��¼��Ĭ�����������֤..." << endl;
			string defaultPassword = "1"; 
			cin >> defaultPassword;
			// ������һ��Ĭ�����룬ʵ�����������������
			if (weixinObj->Return_PassWord() == defaultPassword) {
				LoginedWeiChat = ID; // �����ѵ�¼��΢�ź�
				Get_Friends(); // ��ȡ����
				GetGroup(); // ��ȡȺ��
				Get_Links(); // ��ȡ�󶨵� QQ
				cout << "��¼�ɹ�" << endl;
				cout << "���������ʼʹ��΢��" << endl;
				if (getchar() != EOF)
					WeChatMenu(); // ����΢�����˵�
				return;
			}
			else {
				cout << "Ĭ��������֤ʧ�ܣ��޷���¼��" << endl;
				return;
			}
		}
		else {
			cout << "δ�ҵ���Ӧ��΢�źţ�" << ID << endl;
		}
	}
};
#endif // !WEICHATBASE_QFH_H
