
#include"function.h"
#include"ChatBase_Qfh.h"
#include"QQChatBase_Qfh.h"
#include"WeiBoChatBase_Qfh.h"
#include"WeChatBase_Qfh.h"
#include"Account.h"
#include"QQFriends_Qfh.h"
#include"QQgroups_Qfh.h"
#include"QQ_Qfh.h"
#include"WeiBo_Qfh.h"
#include"Weixin_Qfh.h"
#include"judge.h"
#include<fstream>
#include<list> 
#include <cstring>
#include<stdlib.h>
#include<time.h>
#include "extend.h"
#pragma once
//���濪ͨ��΢��
void WeiBoChatBase_Qfh::SaveWeiBo()
{
	fstream WeiBoListFile;
	string WeiBoListFileName = "WeiBoList.txt";
	WeiBoListFile.open(WeiBoListFileName, ios::app);
	string m = QQFun.Returnqqnumber();
	WeiBoListFile << QQFun.Returnqqnumber() << endl;
	WeiBoListFile.close();
}
//��ȡ΢���б�
void WeiBoChatBase_Qfh::GetWeiBo()
{
	ofstream WeiBoListFileCheck;
	fstream WeiBoListFile;
	string WeiBoListFileName = "WeiBoList.txt";
	string WeiBoListTemp;
	WeiBoListFileCheck.open(WeiBoListFileName, ios::out | ios::app);
	WeiBoListFileCheck.close();
	WeiBoListFile.open(WeiBoListFileName);
	while (!WeiBoListFile.eof())
	{
		getline(WeiBoListFile, WeiBoListTemp);

		WeiBoFun.ReturnWeiBolist().push_back(new WeiBo_Qfh(WeiBoListTemp));
	}
	WeiBoFun.ReturnWeiBolist().pop_back();
	WeiBoListFile.close();
}
//��¼΢��
void WeiBoChatBase_Qfh::Login()
{
	system("CLS");
	string WeiBoID;
	string WeiBoPW;
	int ThisWeiBo;
	bool isCheckFlag = false;
	bool PWCheckFlag = false;
	cout << "����������΢��(QQ)��" << endl;
	cin >> WeiBoID;
	judge_flush(stdin);
	//�ж�΢���˺��Ƿ����
	while (1)
	{
		for (int i = 0; i < QQFun.ReturnQQ().size(); i++)
		{
			if (QQFun.ReturnQQ()[i]->Return_ID() == WeiBoID)
			{
				isCheckFlag = true;
				ThisWeiBo = i;
				WeiBoFun.LoginedWeiBoID = WeiBoID;
				break;
			}
		}

		if (isCheckFlag == false)
		{
			cout << "��������˺Ų����ڣ����������������#����΢�����˵�" << endl;
			cin >> WeiBoID;
			judge_flush(stdin);
			if (WeiBoID == "#")
			{
				Menu();
				return;
			}
			continue;
		}
		else
		{
			break;
		}
	}


	cout << "����������΢��(΢��)������" << endl;
	cin >> WeiBoPW;
	judge_flush(stdin);
	while (1)
	{
		if (QQFun.ReturnQQ()[ThisWeiBo]->Return_PassWord() == WeiBoPW)
		{
			cout << "��½�ɹ�,�����������΢����ҳ" << endl;
			if (getchar() != EOF)
				WeiBoMenu();
			break;
		}
		else
		{
			cout << "�����������,���������������#����΢�����˵�" << endl;
			cin >> WeiBoPW;
			judge_flush(stdin);
			if (WeiBoPW == "#")
			{
				Menu();
				return;
			}
			continue;
		}
	}


}

void WeiBoChatBase_Qfh::Menu()
{
	system("CLS");
	int select;
	cout << "\t\t\t\t|*------------΢�����ܲ˵�----------------*|" << endl;
	cout << "\t\t\t\t|*                                        *|" << endl;
	cout << "\t\t\t\t|*          1.��½΢��                    *|" << endl;
	cout << "\t\t\t\t|*          2.΢�����Ͷˣ�����������      *|"  << endl;
	cout << "\t\t\t\t|*          0.������һ���˵�              *|" << endl;
	cout << "\t\t\t\t|*                                        *|" << endl;
	cout << "\t\t\t\t|*----------------------------------------*|" << endl;
	cout << "����ѡ��:" << endl;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 2);

	switch (select)
	{
	case 1:
		Login();
		break;
	case 2:
		serve();
		break;
	case 0:
		mainmenu.Menu();
		return;
	default:
		Menu();
		return;
	}
}

void WeiBoChatBase_Qfh::WeiBoMenu()
{
	system("CLS");
	int select;
	cout << "\t\t\t\t|*----------��ӭ����΢��---------------*|" << endl;
	cout << "           ����΢����Ϊ" << WeiBoFun.LoginedWeiBoID << endl;
	cout << "\t\t\t\t|*          �޿��ù���             *|" << endl;
	cout << "\t\t\t\t|*         0.�������˵�            *|" << endl;
	cout << "\t\t\t\t|*---------------------------------*|" << endl;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 0);
	switch (select)
	{
	case 0:mainmenu.Menu();
		break;
	default:
		QQFun.Menu();
		break;
	}
}

void WeiBoChatBase_Qfh::Apply() { return; }
void WeiBoChatBase_Qfh::AddFriend() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::SaveFriends() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::Get_Friends() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::ShowFriends() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::DeleteFriend() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::AgreeFriend() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::ShowFriendInformation() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::ChangeFriendRemarks() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::SaveChange() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::AgreeMember() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::ShowMyInformation() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::Change_PassWord() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::Change_Name() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::Change_AutoGraph() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::Change_Area() { cout << "δʵ��" << endl; return; }
void WeiBoChatBase_Qfh::Get_Links() { cout << "δʵ��" << endl; return; }