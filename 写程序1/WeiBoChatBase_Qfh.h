#pragma once
#pragma once
#ifndef WEIBOCHATBASE_QFH_H
#define WEIBOCHATBASE_QFH_H
#include "ChatBase_Qfh.h"
#include <vector>
#include <string>
using namespace std;
class WeiBo_Qfh; // ǰ������

class WeiBoChatBase_Qfh : public ChatBase_Qfh
{

public:
	//΢������δʵ�ֳ��˵�¼
	virtual vector<WeiBo_Qfh*>& ReturnWeiBolist();
	virtual void SaveWeiBo();

	virtual void GetWeiBo();

	virtual void WeiBoMenu();

	virtual void Menu();

	virtual void Login();

	virtual void Apply();

	virtual void AddFriend();

	virtual void SaveFriends();

	virtual void Get_Friends();

	virtual void ShowFriends();

	virtual void DeleteFriend();

	virtual void AgreeFriend();

	virtual void ShowFriendInformation();

	virtual void ChangeFriendRemarks();

	virtual void SaveChange();

	virtual void AgreeMember();

	virtual void ShowMyInformation();

	virtual void Change_PassWord();

	virtual void Change_Name();

	virtual void Change_AutoGraph();

	virtual void Change_Area();

	virtual void Get_Links();

protected:

	vector<WeiBo_Qfh*> WeiBoList;

	string LoginedWeiBoID;

	
	
private:

};

class WeiBoChat_Qfh : public WeiBoChatBase_Qfh
{
public:
	
	//��ת��¼ʵ��
	void splogin(const string& ID) {
		system("CLS"); // ����
		cout << "���ڵ�¼ " << ID << "..." << endl;

		// ����΢��ID
		auto it = find_if(WeiBoList.begin(), WeiBoList.end(),
			[&](WeiBo_Qfh* weixin) { return weixin->Return_ID() == ID; });

		// ����Ƿ��ҵ��˶�Ӧ��΢��
		if (it != WeiBoList.end()) {
			WeiBo_Qfh* weixinObj = *it;

			// �����΢���Ѵ��ڵ�¼״̬��ֱ�ӻ�ȡ��Ϣ
			if (weixinObj->flag == 1) {
				LoginedWeiBoID = ID; // �����ѵ�¼��΢�ź�
				Get_Friends(); // ��ȡ����
				Get_Links(); // ��ȡ�󶨵� QQ
				cout << "��¼�ɹ�" << endl;
				cout << "���������ʼʹ��΢��" << endl;
				if (getchar() != EOF)
					WeiBoMenu(); // ����΢�����˵�
				return;
			}

			// ���΢��δ��¼
			cout << "��΢����δ��¼��Ĭ�����������֤..." << endl;
			string defaultPassword = "1";
			cin >> defaultPassword;
			// ������һ��Ĭ�����룬ʵ�����������������
			if (weixinObj->Return_PassWord() == defaultPassword) {
				LoginedWeiBoID = ID; // �����ѵ�¼��΢�ź�
				Get_Friends(); // ��ȡ����
				Get_Links(); // ��ȡ�󶨵� QQ
				cout << "��¼�ɹ�" << endl;
				cout << "���������ʼʹ��΢��" << endl;
				if (getchar() != EOF)
					WeiBoMenu(); // ����΢�����˵�
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
#endif // !WEIBOCHATBASE_QFH_H
