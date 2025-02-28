#pragma once
#include<iostream>
#include"function.h"
#include"ChatBase_Qfh.h"
#include"QQChatBase_Qfh.h"
#include"WeiBoChatBase_Qfh.h"
#include"WeiChatBase_Qfh.h"
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


void WeiChatBase_Qfh::Menu()
{
	system("CLS");
	int select;
	cout << "\t\t\t\t|*------------΢�Ź��ܲ˵�------------*|" << endl;
	cout << "\t\t\t\t|*                                    *|" << endl;
	cout << "\t\t\t\t|*          1. ��½΢��               *|" << endl;
	cout << "\t\t\t\t|*          2. ע��΢��               *|" << endl;
	cout << "\t\t\t\t|*          3. �鿴��ע��΢��         *|" << endl;
	cout << "\t\t\t\t|*          0. ������һ���˵�         *|" << endl;
	cout << "\t\t\t\t|*                                    *|" << endl;
	cout << "\t\t\t\t|*------------------------------------*" << endl;
	cout << "����������ѡ��:" << endl;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 3);
	switch (select)
	{
	case 1:
		Login();
		break;
	case 2:
		Apply();
		break;
	case 3:
		ShowWeiChat();
		break;
	case 0:
		mainmenu.Menu();
		break;
	default:
		Menu();
		break;
	}
}

void WeiChatBase_Qfh::Apply()
{
	system("CLS");
	WeiChatList.push_back(new Weixin_Qfh());
	SaveWeiChat();
	cout << "�����������" << endl;
	if (getchar() != EOF)
		Menu();
	return;
}

void WeiChatBase_Qfh::SaveWeiChat()
{
	ofstream file;
	file.open("WeChat.txt", ios::app);
	int i = 0;
	i = WeiChatList.size();
	file << WeiChatList[i - 1]->Return_ID() << endl;
	file << WeiChatList[i - 1]->Return_ApplyDate();
	file << WeiChatList[i - 1]->Return_PassWord() << endl;
	file << WeiChatList[i - 1]->Return_Name() << endl;
	file << WeiChatList[i - 1]->Return_Sex() << endl;
	file << WeiChatList[i - 1]->Return_Area() << endl;
	file << WeiChatList[i - 1]->Return_Autograph() << endl;
	file << WeiChatList[i - 1]->Return_bir() << endl;
	file << " " << endl;
	file.close();
}

void WeiChatBase_Qfh::GetWeiChat()
{
	string wxage;
	string wxid;
	string wxpw, wxname, wxpv, wxag, wxbir, wxsex;
	ifstream file;
	int line = 0;
	char c;
	file.open("WeChat.txt");
	while (file.get(c))
	{
		if (c == ' ')
		{
			line++;
		}
	}
	line /= 5;
	string temp;
	file.close();
	file.open("WeChat.txt");
	for (int i = 0; i < line; i++)
	{
		file >> wxid;
		for (int i = 0; i < 4; i++)
		{
			file >> temp;
			wxage += temp;
			wxage += " ";
		}
		file >> temp;
		wxage += temp;
		file >> wxpw;
		file >> wxname;
		file >> wxsex;
		file >> wxpv;
		file >> wxag;
		file >> wxbir;
		WeiChatList.push_back(new Weixin_Qfh(wxid, wxage, wxpw, wxname, wxsex, wxpv, wxag, wxbir));
		wxage.clear();
	}
	file.close();
}

void WeiChatBase_Qfh::Login()
{
	system("CLS");
	string ID;
	bool flag = false;
	string PassWord;
	bool flag1 = true;
	int sub = 0;
	cout << "������Ҫ��½��΢��:" << endl;
	cin >> ID;
	judge_flush(stdin);
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == ID)
		{
			flag = true;
			break;
		}
	}
	if (flag == false)
	{
		while (1)
		{
			cout << "û�и�΢�źţ������������#�������˵�" << endl;
			cin >> ID;
			judge_flush(stdin);
			if (ID == "#")
			{
				Menu();
				return;
			}
			else
			{
				for (int i = 0; i < WeiChatList.size(); i++)
				{
					if (WeiChatList[i]->Return_ID() == ID)
					{
						flag = true;
						sub = i;
						break;
					}
				}
			}
			if (flag == true)
			{
				break;
			}
		}
	}
	if (WeiChatList[sub]->flag == 1)
	{
		LoginedWeiChat = ID;
		Get_Friends();//��ȡ����
		GetGroup();//��ȡȺ
		Get_Links();//��ȡ��
		cout << "��½�ɹ�" << endl;
		cout << "���������ʼʹ��΢��" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}
	cout << "�������΢�ŵ�����" << endl;
	cin >> PassWord;
	judge_flush(stdin);
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == ID && WeiChatList[i]->Return_PassWord() == PassWord)
		{
			LoginedWeiChat = ID;
			Get_Friends();//��ȡ����
			GetGroup();//��ȡȺ
			Get_Links();//��ȡ��
			cout << "��½�ɹ�" << endl;
			cout << "���������ʼʹ��΢��" << endl;
			if (getchar() != EOF)
				WeiChatMenu();
			return;
		}
		else if (WeiChatList[i]->Return_ID() == ID && WeiChatList[i]->Return_PassWord() != PassWord)
		{
			cout << "�����������" << endl;
			cout << "��������������,������#�������˵�" << endl;
			cin >> PassWord;
			judge_flush(stdin);
			if (PassWord == "#")
			{
				Menu();
				return;
			}
			while (1)
			{
				if (WeiChatList[i]->Return_PassWord() == PassWord)
				{
					cout << "��½�ɹ�" << endl;
					cout << "���������ʼʹ��WeChat" << endl;
					if (getchar() != EOF)
						WeiChatMenu();
					return;
				}
				else
				{
					cout << "�����������" << endl;
					cout << "��������������,������#�������˵�" << endl;
					cin >> PassWord;
					judge_flush(stdin);
					if (PassWord == "#")
					{
						Menu();
						return;
					}
					continue;
				}
			}
		}
	}
}
void WeiChatBase_Qfh::ShowWeiChat()
{
	system("CLS");
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		cout << "΢�ź�:" << WeiChatList[i]->Return_ID() << endl;
		cout << "΢��ע��ʱ��:" << WeiChatList[i]->Return_ApplyDate() << endl;
		cout << "΢������:" << WeiChatList[i]->Return_PassWord() << endl;
		cout << "΢����:" << WeiChatList[i]->Return_Name() << endl;
		cout << "IP��ַ:" << WeiChatList[i]->Return_Area() << endl;
		cout << "�û�����:" << WeiChatList[i]->Return_bir() << endl;
		cout << endl;

	}
	cout << "�����������" << endl;
	if (getchar() != EOF)
		Menu();
	return;
}

void WeiChatBase_Qfh::WeiChatMenu()
{
	const int menuWidth = 120;
	system("CLS");
	int select;
	int sub;
	printCentered("|*------------΢�Ž���----------*|", menuWidth);
	cout << "     ����΢�ź�Ϊ: " << LoginedWeiChat << endl; // ΢�źŲ������
	printCentered("|*          ��ѡ��ʹ�õĹ���        *|", menuWidth);
	printCentered("|*           1.���ѹ���             *|", menuWidth);
	printCentered("|*           2.Ⱥ����               *|", menuWidth);
	printCentered("|*           3.������Ϣ             *|", menuWidth);
	printCentered("|*           4.��ͨ����             *|", menuWidth);
	printCentered("|*           0.�������˵�           *|", menuWidth);
	printCentered("|*----------------------------------*|", menuWidth);
	cout << "����������ѡ��:" << endl;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 4);
	switch (select)
	{
	case 1:
	{
		system("cls");
		printCentered("|*---------���ѹ���-------*|", menuWidth);
		printCentered("|*            1.��ʾ���к���          *|", menuWidth);
		printCentered("|*            2.��Ӻ���              *|", menuWidth);
		printCentered("|*            3.ɾ������              *|", menuWidth);
		printCentered("|*            4.�鿴��������          *|", menuWidth);
		printCentered("|*            5.�鿴��������          *|", menuWidth);
		printCentered("|*            6.�޸ĺ��ѱ�ע          *|", menuWidth);
		printCentered("|*            7.�鿴QQ��ͬ����        *|", menuWidth);
		printCentered("|*            8.���QQ��ͬ����        *|", menuWidth);
		printCentered("|*            0.����΢�����˵�        *|", menuWidth);
		printCentered("|*------------------------------------*|", menuWidth);
		cout << "����������ѡ��:" << endl;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 8);
		switch (select)
		{
		case 1:
			 ShowFriends();
			break;
		case 2:
			AddFriend();
			break;
		case 3:
			DeleteFriend();
			break;
		case 4:
			AgreeFriend();
			break;
		case 5:
			ShowFriendInformation();
			break;
		case 6:
			ChangeFriendRemarks();
			break;
		case 7:
			ShowQQCommonFriends();
			break;
		case 8:
			AddQQCommonFriend();
			break;
		default:
			WeiChatMenu();
			break;

		}
		break;
	}
	case 2:

	{
		system("cls");
		printCentered("|*--------Ⱥ����--------*|", menuWidth);
		printCentered("|*          1.�˳�΢��Ⱥ            *|", menuWidth);
		printCentered("|*          2.����΢��Ⱥ            *|", menuWidth);
		printCentered("|*          3.�鿴�Ѽ����΢��Ⱥ    *|", menuWidth);
		printCentered("|*          4.�߳�Ⱥ��Ա            *|", menuWidth);
		printCentered("|*          5.�鿴Ⱥ��Ա��Ϣ        *|", menuWidth);
		printCentered("|*          6.������ѽ�Ⱥ          *|", menuWidth);
		printCentered("|*          0.�������˵�            *|", menuWidth);
		printCentered("|*----------------------------------*|", menuWidth);

		printCentered("����������ѡ��:", menuWidth);
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 6);
		switch (select)
		{
		case 1:
			QuitGroup();
			break;
		case 2:
			CreatGroup();
			break;
		case 3:
			ShowGroup();
			break;
		case 4:
			DeleteGroupMember();
			break;
		case 5:
			ShowGroupInformation();
			break;
		case 6:
			InviteGroupMember();
			break;
		default:
			WeiChatMenu();
			break;
		}
		break;
	}
	case 3:
	{
		system("cls");
		printCentered("|*---------����-------*|", menuWidth);
		printCentered("|*           1.�鿴������Ϣ           *|", menuWidth);
		printCentered("|*           2.�޸�����               *|", menuWidth);
		printCentered("|*           3.�޸�����               *|", menuWidth);
		printCentered("|*           4.�޸�ǩ��               *|", menuWidth);
		printCentered("|*           5.�޸����ڵ�             *|", menuWidth);
		printCentered("|*           0.����                   *|", menuWidth);
		printCentered("|*------------------------------------*|", menuWidth);
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 5);
		switch (select)
		{
		case 1:
			ShowMyInformation();
			break;
		case 2:
			Change_PassWord();
			break;
		case 3:
			Change_Name();
			break;
		case 4:
			Change_AutoGraph();
			break;
		case 5:
			Change_Area();
			break;
		default:
			WeiChatMenu();
			break;
		}
		break;
	}
	case 4:
	{
		system("cls");
		printCentered("|*-------����:------*|", menuWidth);
		printCentered("|*          1.��QQ           *|", menuWidth);
		printCentered("|*          0.����             *|", menuWidth);
		printCentered("|*-----------------------------*|", menuWidth);
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 1);
		switch (select)
		{
		case 1:
			LinkQQ();
			break;
		default:
			WeiChatMenu();
			break;
		}
		break;
	}
	case 0:
		mainmenu.Menu();
		break;

	default:
		WeiChatMenu();
		break;

	}
	if (getchar() != EOF)
		return;
}

void WeiChatBase_Qfh::AddFriend()
{
	system("CLS");
	int sub = 0, subfriend = 0;
	string id;
	string name, subname;
	bool flag = false;
	cout << "��������Ӻ��ѵ�΢�ź�" << endl;
	cin >> id;
	judge_flush(stdin);
	if (id == LoginedWeiChat)
	{
		cout << "����������Լ�Ϊ����" << endl;
		cout << "�����������΢����ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			subname = WeiChatList[i]->Return_Name();
			break;
		}
	}
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if (id == WeiChatList[sub]->Return_Friend_List()[i]->Return_ID())
		{
			cout << "������Ӵ˺���,�밴���������΢����ҳ" << endl;
			if (getchar() != EOF)
				WeiChatMenu();
			return;
		}
	}
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == id)
		{
			flag = true;
			subfriend = i;
			name = WeiChatList[i]->Return_Name();
			cout << "��������ɹ�����ȴ��Է�ȷ��" << endl;
		}
	}
	if (flag == false)
	{
		cout << "��΢�źŻ�û��ע�ᣬ���������������΢�ź�" << endl;
		cout << "1.��������΢�ź���Ӻ���" << endl;
		cout << "0.����΢����ҳ" << endl;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		int select;
		select = judge_count_menu(tempstr, 1);
		switch (select)
		{
		case 1:
			AddFriend();
			return;
		default:
			WeiChatMenu();
			return;
		}

	}
	string mark = "&";
	string ID = mark + id;//&��ʾ����������ĺ��ѵ���Ϣ�б�
	fstream file;
	string friendfilename = "WeChat\\" + LoginedWeiChat + "\\" + LoginedWeiChat + "Friendlist.txt";
	string remarks = "δ��ע";
	WeiChatList[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	file.open(friendfilename, ios::app);
	file << ID << endl;
	file << name << endl;
	file << remarks << endl;
	file << " " << endl;//�����жϼ�������
	file.close();
	//�����΢���ļ�����ӱ�ID
	friendfilename = "WeChat\\" + id + "\\" + id + "Friendlist.txt";
	subname = "$" + subname;
	WeiChatList[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subname, LoginedWeiChat));
	file.open(friendfilename, ios::app);
	file << "$" << WeiChatList[sub]->Return_ID() << endl;
	file << WeiChatList[sub]->Return_Name() << endl;
	file << remarks << endl;
	file << " " << endl;//�����жϼ�������
	file.close();
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::SaveFriends()
{
	int i = 0, sub, n;
	ofstream file;
	string qq = LoginedWeiChat;
	string txt = ".txt";
	string filename = "WeChat\\" + qq + "\\" + qq + "Friendlist.txt";
	file.open(filename, ios::app);
	for (i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	n = WeiChatList[sub]->Return_Friend_List().size();
	if (n > 0)
	{
		file << WeiChatList[sub]->Return_Friend_List()[n - 1]->Return_ID() << endl;
		file << WeiChatList[sub]->Return_Friend_List()[n - 1]->ReturnFriendName() << endl;
		file << WeiChatList[sub]->Return_Friend_List()[n - 1]->ReturnRemarks() << endl;
		file << " " << endl;
		file.close();
	}
	else
	{
		file.close();
		file.open(filename, ios::trunc | ios::out);//����ļ�����
		file.close();
	}
}

void WeiChatBase_Qfh::Get_Friends()
{
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			break;
		}
	}
	WeiChatList[sub]->Get_Friends();
}

void WeiChatBase_Qfh::ShowFriends()
{
	system("CLS");
	int friendsnum;
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	friendsnum = WeiChatList[sub]->Return_Friend_List().size();
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if ((WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//�ж���Ӻ��ѱ��
		{
			friendsnum--;
		}
	}
	cout << "����" << friendsnum << "������" << endl;
	int friends = 0;
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if ((WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
		{
			continue;
		}
		cout << "��" << friends + 1 << "λ����" << endl;
		cout << "����:" << WeiChatList[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "WeiChatList:" << WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "��ע:" << WeiChatList[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		cout << endl;
		friends++;
	}

	cout << "�����������WeiChatList��ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
}

void WeiChatBase_Qfh::ShowFriendsNoReturn()
{
	int friendsnum;
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	friendsnum = WeiChatList[sub]->Return_Friend_List().size();
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if ((WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//�ж���Ӻ��ѱ��
		{
			friendsnum--;
		}
	}

	cout << "����" << friendsnum << "������" << endl;
	int friends = 0;
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if ((WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
		{
			continue;
		}
		cout << "��" << friends + 1 << "λ����" << endl;
		cout << "����:" << WeiChatList[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "WeiChatList:" << WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << endl;
		friends++;
	}
}

void WeiChatBase_Qfh::CreatGroup()
{
	system("CLS");
	int sub;
	time_t ti;
	srand((unsigned)time(&ti));
	int temp = rand() % 99999999;
	stringstream ss;
	ss << temp;
	string ID;
	ss >> ID;
	cout << "������Ⱥ����" << endl;
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "����Ⱥ��Ϊ:" << ID << endl;
	WeiChatgroup = ID;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	WeiChatList[sub]->Return_group_List().push_back(new QQgroups_Qfh(ID, name, LoginedWeiChat));
	WeiChatList[sub]->Change_group_num(WeiChatList[sub]->Return_Group_Number() + 1);
	SaveGroup();
	//ÿ��WeiChatList�����Լ���Ⱥ�б�
	fstream FILE;
	string qq;
	qq = LoginedWeiChat;
	string txt1 = "Groupslist.txt";
	string FILEName = "WeChat\\" + LoginedWeiChat + "\\" + LoginedWeiChat + "Groupslist.txt";
	FILE.open(FILEName, ios::app);
	FILE << ID << endl;
	fstream GroupListFile;
	string GroupListFileName = "Groupslist.txt";
	GroupListFile.open(GroupListFileName, ios::app);
	GroupListFile << ID << endl;
	GroupListFile.close();
	cout << "�����������΢����ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::SaveGroup()
{
	system("CLS");
	int i = 0, sub, n;
	string ID;
	ID = WeiChatgroup;
	string txt = ".txt";
	string DirectoryName = "WeChat\\Groups\\" + ID;
	CreateDirectory(DirectoryName.c_str(), NULL);
	string GroupID = "WeChat\\Groups\\" + ID + "\\" + ID + ".txt";
	fstream file;
	file.open(GroupID, ios::app);
	for (i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	n = WeiChatList[sub]->Return_group_List().size();
	file << WeiChatList[sub]->Return_group_List()[n - 1]->Return_Group_ID() << endl;
	file << WeiChatList[sub]->Return_group_List()[n - 1]->Return_Group_Name() << endl;
	file << WeiChatList[sub]->Return_group_List()[n - 1]->ReturnCreatUserID() << endl;
	file << "*" << endl;
	file.close();
}

void WeiChatBase_Qfh::GetGroup()
{
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		for (int j = 0; j < WeiChatList[i]->Return_group_List().size(); j++)
		{
			WeiChatList[i]->Return_group_List()[j]->ReturnGroupMembers().clear();
		}
		WeiChatList[i]->Return_group_List().clear();
	}
	int sub, line = 0;
	char c;
	string txt1 = "Groupslist.txt";
	string txt = ".txt";
	ifstream listfile;
	ifstream groupfile;
	string qq = LoginedWeiChat;
	vector<string>group;
	string temp;
	string filename = "WeChat\\" + qq + "\\" + qq + "Groupslist.txt";
	string groupfilename;
	listfile.open(filename);
	while (listfile.get(c))
	{
		string x;
		x = c;
		temp += x;

		if (c == '\n')
		{
			line++;
			temp.pop_back();
			group.push_back(temp);
			temp.clear();
		}
	}
	listfile.close();
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	WeiChatList[sub]->Change_group_num(line);

	for (int i = 0; i < group.size(); i++)
	{
		temp = group[i];
		groupfilename = "WeChat\\Groups\\" + temp + "\\" + temp + ".txt";
		groupfile.open(groupfilename);
		string id;
		string name;
		string userid;
		groupfile >> id;
		groupfile >> name;
		groupfile >> userid;
		groupfile.close();
		WeiChatList[sub]->Return_group_List().push_back(new QQgroups_Qfh(id, name, userid));
	}
	//��ȡȺ��Ա
	fstream QQGroupMemberFile;
	string QQGroupMemberFileName;
	string QQGroupMemberFileTemp;
	string OwnerQQ;
	vector<string>QQGroupMemberFileContent;
	int ThisGroupID;
	string QQGroupID;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}

	for (int i = 0; i < group.size(); i++)
	{
		QQGroupMemberFileName = "WeChat\\Groups\\" + group[i] + "\\" + group[i] + ".txt";
		QQGroupMemberFile.open(QQGroupMemberFileName);

		while (!QQGroupMemberFile.eof())
		{
			getline(QQGroupMemberFile, QQGroupMemberFileTemp);

			QQGroupMemberFileContent.push_back(QQGroupMemberFileTemp);
		}
		QQGroupID = QQGroupMemberFileContent[0];
		OwnerQQ = QQGroupMemberFileContent[2];
		QQGroupMemberFileContent.erase(QQGroupMemberFileContent.begin());
		QQGroupMemberFileContent.erase(QQGroupMemberFileContent.begin());
		QQGroupMemberFileContent.erase(QQGroupMemberFileContent.begin());
		QQGroupMemberFileContent.erase(QQGroupMemberFileContent.begin());
		if (QQGroupMemberFileContent.size() != 0)
		{
			QQGroupMemberFileContent.pop_back();
		}

		for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
		{
			if (WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
			{
				ThisGroupID = i;
				break;
			}
		}
		WeiChatList[sub]->Return_group_List()[ThisGroupID]->ReturnGroupMembers().push_back(OwnerQQ);
		for (int i = 0; i < QQGroupMemberFileContent.size(); i++)
		{
			WeiChatList[sub]->Return_group_List()[ThisGroupID]->ReturnGroupMembers().push_back(QQGroupMemberFileContent[i]);
		}
		//BUG�޸�
		QQGroupMemberFileContent.clear();
		QQGroupMemberFile.close();
	}
	//��ȡȺ����ԱWeiChatList
	fstream adminfile;
	string adminfilename;
	string admintemp;
	string ThidGroupID;
	for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
	{
		ThidGroupID = WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID();

		fstream CheckGroupAdminFile;
		string GetLinkFileName = "WeChat\\Groups\\" + ThidGroupID + "\\" + ThidGroupID + "admin.txt";
		CheckGroupAdminFile.open(GetLinkFileName, ios::in);
		if (!CheckGroupAdminFile)
		{
			CheckGroupAdminFile.close();
			CheckGroupAdminFile.open(GetLinkFileName, ios::out);
		}
		CheckGroupAdminFile.close();
		adminfilename = "WeChat\\Groups\\" + ThidGroupID + "\\" + ThidGroupID + "admin.txt";
		adminfile.open(adminfilename);

		while (!adminfile.eof())
		{
			getline(adminfile, admintemp);
			WeiChatList[sub]->Return_group_List()[i]->Return_Admins_ID().push_back(admintemp);
		}
		if (WeiChatList[sub]->Return_group_List()[i]->Return_Admins_ID().size() != 0)
		{
			WeiChatList[sub]->Return_group_List()[i]->Return_Admins_ID().pop_back();
		}
		adminfile.close();
	}
}
void WeiChatBase_Qfh::DeleteFriend()
{
	system("CLS");

	//��ʾ���к���
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}//�ҵ���ǰ��¼��΢�Ŷ���
	cout << "�����б����£�" << endl;
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_Number(); i++)
	{
		if (WeiChatList[sub]->Return_Friend_List()[i]->ReturnFriendName()[0] == '$' || WeiChatList[sub]->Return_Friend_List()[i]->ReturnFriendName()[i] == '&')
			continue;
		cout << "����:" << WeiChatList[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "΢��:" << WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "��ע��" << WeiChatList[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		cout << endl;
	}

	//ɾ����΢���еĺ���
	string delq;
	cout << "��������ɾ�����ѵ�΢�źţ�������#����QQ��ҳ" << endl;
	cin >> delq;
	judge_flush(stdin);
	if (delq == "#")
	{
		WeiChatMenu();
		return;
	}
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			break;
		}
	}
	bool flag = false;
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() == delq)
		{
			flag = true;
			break;
		}
	}
	if (flag == false)
	{
		cout << "��û�д˺���" << endl;
		cout << "1.��������΢�ź�" << endl;
		cout << "0.����΢����ҳ" << endl;
		int select;
		string temp;
		cin >> temp;
		judge_flush(stdin);
		select = judge_count_menu(temp, 1);
		switch (select)
		{
		case 1:
			DeleteFriend();
			return;
		default:
			WeiChatMenu();
			return;
		}

	}
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			break;
		}
	}
	int num = WeiChatList[sub]->Return_Friend_List().size();
	for (int i = 0; i < num; i++)
	{
		if (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() == delq)
		{
			WeiChatList[sub]->Return_Friend_List().erase(WeiChatList[sub]->Return_Friend_List().begin() + i);
			WeiChatList[sub]->Change_Friends_Number(num - 1);
			break;
		}
	}
	int friendqq;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == delq)
		{
			friendqq = i;
			break;
		}
	}
	num = WeiChatList[friendqq]->Return_Friend_List().size();
	for (int i = 0; i < num; i++)
	{
		if (WeiChatList[friendqq]->Return_Friend_List()[i]->Return_ID() == LoginedWeiChat)
		{
			WeiChatList[friendqq]->Return_Friend_List().erase(WeiChatList[friendqq]->Return_Friend_List().begin() + i);
			WeiChatList[friendqq]->Change_Friends_Number(num - 1);
			break;
		}
	}
	//ɾ����QQ�еĺ���QQ,�����ĵ���Ҫɾ����һ�����Լ���һ���Ǻ���QQ
	ofstream subfile, outfile;
	string temp1;
	string content1;
	string subfilename = "WeChat\\" + LoginedWeiChat + "\\" + LoginedWeiChat + "Friendlist.txt";
	string friendqqfilename = "WeChat\\" + delq + "\\" + delq + "Friendlist.txt";
	subfile.open(subfilename, ios::ate);
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if (i > 0)
			subfile << endl;
		subfile << WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		subfile << WeiChatList[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		subfile << WeiChatList[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		subfile << " ";
	}
	subfile.close();
	outfile.open(friendqqfilename, ios::ate);
	for (int i = 0; i < WeiChatList[friendqq]->Return_Friend_List().size(); i++)
	{
		if (i > 0)
			subfile << endl;
		subfile << WeiChatList[friendqq]->Return_Friend_List()[i]->Return_ID() << endl;
		subfile << WeiChatList[friendqq]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		subfile << WeiChatList[friendqq]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		subfile << " ";
	}
	outfile.close();
	cout << "ɾ�����ѳɹ�" << endl;
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::AgreeFriend()
{
	system("CLS");
	fstream subfile;
	string subfilename = "WeChat\\" + LoginedWeiChat + "\\" + LoginedWeiChat + "Friendlist.txt";
	string friendwxfilename;
	subfile.open(subfilename);
	int sub, friendwx;
	string wx;
	vector<string> temp;
	string tempf;
	string fdwx;

	string name, id;

	char c;
	int line = 0;
	bool flag = false;
	while (subfile.get(c))//��ȡ������΢��
	{
		if (c == '$')
		{
			while (subfile.get(c))
			{
				tempf.push_back(c);
				if (c == '\n')
				{
					tempf.pop_back();
					temp.push_back(tempf);
					break;
				}
			}
			line++;
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "û�к�������" << endl;
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}
	subfile.close();
	for (int i = 0; i < temp.size(); i++) {
		fdwx = temp[i];
		friendwxfilename = "WeChat\\" + fdwx + "\\" + fdwx + "Friendlist.txt";
		cout << "���Ƿ�ͬ��" << temp[i] << "�ĺ�������?" << endl;
		cout << "1.ͬ��" << endl;
		cout << "0.�ܾ�" << endl;
		string FriendApplyWx = temp[i];
		int select;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 1);
		string content;
		string msg;
		fstream friendwxfile;
		int n = 0;
		int linefriend = 0;
		string contentfriend;
		string msgfriend;
		string myacepttemp;
		vector<string> myaceptcontent;
		string friendacepttemp;
		vector<string> friendaceptcontent;
		switch (select)
		{
		case 1:
			subfile.open(subfilename);
			while (!subfile.eof())
			{

				getline(subfile, myacepttemp);
				myaceptcontent.push_back(myacepttemp);
			}
			myaceptcontent.pop_back();//��������ķ�ʽ��ཨ��һ����Ҫ����
			for (int i = 0; i < myaceptcontent.size(); i++)
			{
				if (myaceptcontent[i] == ("$" + FriendApplyWx))
				{
					myaceptcontent[i] = FriendApplyWx;//�����к��ѱ�ǵı��ȥ��
				}
			}
			subfile.close();
			subfile.open(subfilename, ios::out | ios::trunc); //���ԭ���ļ�����
			for (int i = 0; i < myaceptcontent.size(); i++)//����д��
			{
				subfile << myaceptcontent[i] << endl;
			}
			subfile.close();
			friendwxfile.open(friendwxfilename);
			while (!friendwxfile.eof())//��ȡ�����ļ�����
			{
				getline(friendwxfile, friendacepttemp);
				friendaceptcontent.push_back(friendacepttemp);
			}
			friendaceptcontent.pop_back();
			for (int i = 0; i < friendaceptcontent.size(); i++)
			{
				if (friendaceptcontent[i] == ("&" + LoginedWeiChat))
				{
					friendaceptcontent[i] = LoginedWeiChat;
				}
			}
			friendwxfile.close();

			friendwxfile.open(friendwxfilename, ios::out | ios::trunc);//��պ����ļ�����
			for (int i = 0; i < friendaceptcontent.size(); i++)
			{
				friendwxfile << friendaceptcontent[i] << endl;
			}
			friendwxfile.close();

			for (int i = 0; i < WeiChatList.size(); i++)
			{
				if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
				{
					sub = i;
				}
			}
			for (int i = 0; i < WeiChatList.size(); i++)
			{
				if (WeiChatList[i]->Return_ID() == fdwx)
				{
					friendwx = i;
				}
			}
			name = WeiChatList[friendwx]->Return_Name();
			id = WeiChatList[friendwx]->Return_ID();
			WeiChatList[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, id));
			WeiChatList[sub]->Change_Friends_Number(WeiChatList[sub]->Return_Friend_Number() + 1);
			WeiChatList[friendwx]->Return_Friend_List().push_back(new QQFriends_Qfh(WeiChatList[sub]->Return_Name(), LoginedWeiChat));
			WeiChatList[friendwx]->Change_Friends_Number(WeiChatList[friendwx]->Return_Friend_Number() + 1);
			friendwxfile.close();
			cout << "ȷ������ɹ����������������һ��" << endl;
			if (getchar() != EOF)
				break;
		case 0:
		{
			cout << "���Ѿܾ������󣬰������������һ��" << endl;
			subfile.open(subfilename);

			string subfiletemp;
			vector<string> subfilecontent;

			while (!subfile.eof())
			{
				getline(subfile, subfiletemp);
				subfilecontent.push_back(subfiletemp);
			}
			subfilecontent.pop_back();

			for (int i = 0; i < size(subfilecontent); i++)
			{
				if (subfilecontent[i] == ("$" + FriendApplyWx))
				{
					subfilecontent.erase(subfilecontent.begin() + i);//����
					subfilecontent.erase(subfilecontent.begin() + i);//�ǳ�
					subfilecontent.erase(subfilecontent.begin() + i);//��ע
					subfilecontent.erase(subfilecontent.begin() + i);//���ļ��д洢������
					break;
				}
			}
			subfile.close();
			subfilecontent.shrink_to_fit();
			subfile.open(subfilename, ios::out | ios::trunc); //���ԭ���ļ�����

			for (int i = 0; i < subfilecontent.size(); i++)
			{
				subfile << subfilecontent[i] << endl;
			}
			subfile.close();

			//ɾ�������ļ��е�QQ
			friendwxfile.open(friendwxfilename);
			string friendfiletemp;
			vector<string> friendfilecontent;
			while (!friendwxfile.eof())
			{
				getline(friendwxfile, friendfiletemp);
				friendfilecontent.push_back(friendfiletemp);
			}
			friendfilecontent.pop_back();
			friendwxfile.close();
			for (int i = 0; i < friendfilecontent.size(); i++)
			{
				if (friendfilecontent[i] == ("&" + LoginedWeiChat))
				{
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);//ͬ��
				}
			}
			friendfilecontent.shrink_to_fit();//��������������������sizeƥ��

			friendwxfile.open(friendwxfilename, ios::out, ios::trunc);//���ԭ������

			for (int i = 0; i < friendfilecontent.size(); i++)
			{
				friendwxfile << friendfilecontent[i] << endl;
			}
			friendwxfile.close();
			if (getchar() != EOF)
				break;
		}
		default:
			WeiChatMenu();
			return;
		}
	}
	cout << "���е����봦����ϣ������������QQ���˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::ShowFriendInformation()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "�����������ѯ�ĺ���WeiChatList�ţ�������#����WeiChatList���˵�" << endl;
	string FriendQQ;
	cin >> FriendQQ;
	judge_flush(stdin);
	int sub;
	if (FriendQQ == "#")
	{
		WeiChatMenu();
		return;
	}

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}

	bool FriendCheckFlag = false;
	while (1)
	{
		for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
		{
			if (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() == FriendQQ)
			{
				FriendCheckFlag = true;
			}
		}
		if (FriendCheckFlag == true)
		{
			break;
		}
		else
		{
			cout << "��û�д˺��ѣ����������������#����WeiChatList���˵�" << endl;
			cin >> FriendQQ;
			judge_flush(stdin);
			if (FriendQQ == "#")
			{
				WeiChatMenu();
				return;
			}
			else
			{
				continue;
			}
		}
	}

	int friendid;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == FriendQQ)
		{
			friendid = i;
		}
	}

	int friendremarks;
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() == FriendQQ)
		{
			friendremarks = i;
		}
	}

	cout << "����Ϊ�˺�����Ϣ" << endl;
	cout << "�ʺ�:" << WeiChatList[friendid]->Return_ID() << endl;
	cout << "����:" << WeiChatList[friendid]->Return_Name() << endl;
	cout << "�Ա�:" << WeiChatList[friendid]->Return_Sex() << endl;
	cout << "�û�������:" << WeiChatList[friendid]->Return_bir() << endl;
	cout << "��ע:" << WeiChatList[sub]->Return_Friend_List()[friendremarks]->ReturnRemarks() << endl;
	cout << "����ǩ��:" << WeiChatList[friendid]->Return_Autograph() << endl;
	cout << "���ڵ���:" << WeiChatList[friendid]->Return_Area() << endl;
	cout << "ע��ʱ��:" << WeiChatList[friendid]->Return_ApplyDate();
	cout << endl;

	cout << "�����������WeiChatList���˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::ShowFriendNoReturn()
{
	system("CLS");
	int friendsnum;
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	friendsnum = WeiChatList[sub]->Return_Friend_List().size();
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if ((WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//�ж���Ӻ��ѱ��
		{
			friendsnum--;
		}
	}

	cout << "����" << friendsnum << "������" << endl;
	int friends = 0;
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if ((WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
		{
			continue;
		}
		cout << "��" << friends + 1 << "λ����" << endl;
		cout << "����:" << WeiChatList[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "WeiChatList:" << WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << endl;
		friends++;
	}
}

void WeiChatBase_Qfh::ChangeFriendRemarks()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "�����������ѯ�ĺ���WeiChatList�ţ�������#����WeiChatList���˵�" << endl;
	string FriendQQ;
	cin >> FriendQQ;
	judge_flush(stdin);
	int sub;
	if (FriendQQ == "#")
	{
		WeiChatMenu();
		return;
	}

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}

	bool FriendCheckFlag = false;
	while (1)
	{
		for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
		{
			if (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() == FriendQQ)
			{
				FriendCheckFlag = true;
			}
		}
		if (FriendCheckFlag == true)
		{
			break;
		}
		else
		{
			cout << "��û�д˺��ѣ����������������#����WeiChatList���˵�" << endl;
			cin >> FriendQQ;
			judge_flush(stdin);
			if (FriendQQ == "#")
			{
				WeiChatMenu();
				return;
			}
			else
			{
				continue;
			}
		}
	}

	cout << "�����������޸ĵı�ע" << endl;
	string NewRemarks;
	cin >> NewRemarks;
	judge_flush(stdin);
	int friendid;
	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if (WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() == FriendQQ)
		{
			friendid = i;
		}
	}

	WeiChatList[sub]->Return_Friend_List()[friendid]->ChangeRemarks(NewRemarks);
	SaveChange();

	cout << "�޸ı�ע�ɹ�" << endl;
	cout << "�����������WeiChatList���˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
}

void WeiChatBase_Qfh::SaveChange()
{
	fstream qqfile;
	string qqfilename = "WeChat.txt";
	qqfile.open(qqfilename, ios::trunc | ios::out);
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		qqfile << WeiChatList[i]->Return_ID() << endl;
		qqfile << WeiChatList[i]->Return_ApplyDate();
		qqfile << WeiChatList[i]->Return_PassWord() << endl;
		qqfile << WeiChatList[i]->Return_Name() << endl;
		qqfile << WeiChatList[i]->Return_Sex() << endl;
		qqfile << WeiChatList[i]->Return_Area() << endl;
		qqfile << WeiChatList[i]->Return_Autograph() << endl;
		qqfile << WeiChatList[i]->Return_bir() << endl;
		qqfile << " " << endl;
	}
	qqfile.close();


	fstream qqfriendlistfile;
	string qqfriendlistfilename = "WeiChatList\\" + LoginedWeiChat + "\\" + LoginedWeiChat + "Friendlist.txt";
	qqfriendlistfile.open(qqfriendlistfilename, ios::out | ios::trunc);

	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}

	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		qqfriendlistfile << WeiChatList[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		qqfriendlistfile << WeiChatList[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		qqfriendlistfile << WeiChatList[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		qqfriendlistfile << " " << endl;
	}
	qqfriendlistfile.close();
}

void WeiChatBase_Qfh::ShowGroup()
{
	system("CLS");
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	cout << "������" << WeiChatList[sub]->Return_Group_Number() << "��Ⱥ" << endl;
	for (int i = 0; i < WeiChatList[sub]->Return_Group_Number(); i++)
	{
		cout << "��" << i + 1 << "��Ⱥ" << endl;
		cout << "Ⱥ��:" << WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() << endl;
		cout << "Ⱥ����:" << WeiChatList[sub]->Return_group_List()[i]->Return_Group_Name() << endl;
		cout << "Ⱥ��:" << WeiChatList[sub]->Return_group_List()[i]->ReturnCreatUserID() << endl;
		cout << endl;
	}
	cout << "�����������WeiChatList��ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::AgreeMember()
{
	system("CLS");
	ShowGroupNoReturn();
	cout << "������Ҫ�����Ⱥ��" << endl;
	char c;
	int line = 0;
	bool flag = false;
	string id;
	string txt = ".txt";
	cin >> id;
	judge_flush(stdin);
	string filename = "WeChat\\Groups\\" + id + "\\" + id + ".txt";
	ifstream infile;
	infile.open(filename, ios::in);
	if (!infile)
	{
		cout << "û�д�Ⱥ,����������򷵻�΢����ҳ" << endl;
		cout << "1.��������" << endl;
		cout << "0.����WeiChatList��ҳ" << endl;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		int select;
		select = judge_count_menu(tempstr, 1);
		switch (select)
		{
		case 1:
			AgreeMember();
			return;

		case 2:
			WeiChatMenu();
			return;
		}
	}
	infile.close();
	fstream outfile;
	outfile.open(filename);

	string temp;
	while (outfile.get(c))
	{
		if (c == '\n')
		{
			line++;
			continue;
		}
		if (line == 2) //��ȡȺ��WeiChatList��
		{
			temp.push_back(c);
		}

	}
	string OwnerQQ = temp;
	fstream adminfile;
	string adminfilename;
	string admintemp;
	vector<string> AdminQQ;
	adminfilename = "WeiChatList\\Groups\\" + id + "\\" + id + "admin.txt";
	adminfile.open(adminfilename);
	while (!adminfile.eof())
	{

		getline(adminfile, temp);

		AdminQQ.push_back(temp);

	}
	AdminQQ.pop_back();
	bool Adminflag = false;
	for (int i = 0; i < AdminQQ.size(); i++)
	{
		if (AdminQQ[i] == LoginedWeiChat)
		{
			Adminflag = true;
			break;
		}
	}

	if (OwnerQQ == LoginedWeiChat)
	{
		cout << "Ⱥ�����ã���ӭ�鿴��Ⱥ����" << endl;

	}
	else if (Adminflag == true)
	{
		cout << "����Ա���ã���ӭ�鿴��Ⱥ����" << endl;
	}
	else
	{
		cout << "�����Ǹ�Ⱥ��Ⱥ�������Ա,�޷������Ⱥ" << endl;
		cout << "�����������WeiChatList��ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}

	outfile.close();
	temp.clear();
	line = 0;
	outfile.open(filename);
	while (outfile.get(c))
	{
		if (c == '$')
		{
			line++;
			flag = true;
			continue;
		}
		if (line == 1)
		{
			temp.push_back(c);
		}

	}

	if (flag == false)
	{
		cout << "û�м�Ⱥ����" << endl;
		cout << "�����������WeiChatList��ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}
	outfile.close();
	temp.pop_back();
	cout << "���Ƿ�ͬ��" << temp << "��Ⱥ?" << endl;
	cout << "1.ͬ��" << endl;
	cout << "0.�ܾ�" << endl;
	int select;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 1);
	string member = temp;
	string GroupList = "Groupslist.txt";
	string filename1 = "WeiChatList\\" + member + "\\" + member + "Groupslist.txt";
	string msg;
	vector<char> content;
	int n = 0;
	switch (select)
	{
	case 1:
		outfile.open(filename, ios::in | ios::out);

		while (!outfile.eof())
		{

			char ch[1000];
			outfile.getline(ch, 1000);
			for (int i = 0; i < strlen(ch); i++)
			{
				msg.push_back(ch[i]);//��ȡ�ļ�����
			}
			msg.push_back('\n');

		}
		for (int i = 0; i < size(msg); i++)//��δ������ɾ��
		{
			if (msg[i] == '$')
			{
				msg.erase(msg.begin() + i);
				break;
			}
		}
		msg.pop_back();
		outfile.close();
		outfile.open(filename, ios::out, ios::trunc); //���ԭ���ļ�����
		outfile << msg;
		cout << "ȷ������ɹ�" << endl;
		outfile.close();
		outfile.open(filename1, ios::app);
		outfile << id << endl;
		cout << "�����������WeiChatList��ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	case 0:

		cout << "���Ѿܾ�������" << endl;
		outfile.open(filename);

		while (!outfile.eof())
		{

			char ch[1000];

			outfile.getline(ch, 1000);
			for (int i = 0; i < strlen(ch); i++)
			{
				msg.push_back(ch[i]);//��ȡ�ļ�����
			}

			msg.push_back('\n');

		}
		outfile.close();

		for (int i = 0; i < size(msg); i++)
		{
			if (msg[i] == '$')
			{

				n = i;

				while (1)
				{
					msg.erase(msg.begin() + n); //ɾ��������WeiChatList


					if (msg[n] == '\n')
					{
						msg.erase(msg.begin() + n);
						break;
					}


				}

				break;
			}
		}
		msg.pop_back();

		outfile.open(filename, ios::out, ios::trunc);//���ԭ������

		outfile << msg;

		outfile.close();

		cout << "�����������WeiChatList��ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		break;
	default:
		WeiChatMenu();
		return;
	}
}

void WeiChatBase_Qfh::ShowGroupNoReturn()
{
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	cout << "������" << WeiChatList[sub]->Return_Group_Number() << "��Ⱥ" << endl;
	for (int i = 0; i < WeiChatList[sub]->Return_Group_Number(); i++)
	{
		cout << "��" << i + 1 << "��Ⱥ" << endl;
		cout << "Ⱥ��:" << WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() << endl;
		cout << "Ⱥ����:" << WeiChatList[sub]->Return_group_List()[i]->Return_Group_Name() << endl;
		cout << "Ⱥ��:" << WeiChatList[sub]->Return_group_List()[i]->ReturnCreatUserID() << endl;
		cout << endl;
	}

}

void WeiChatBase_Qfh::AddGroupMember()
{
	system("CLS");
	cout << "��������������Ⱥ" << endl;
	string groupid;
	cin >> groupid;
	judge_flush(stdin);
	WeiChatGroupMember = groupid;
	string id;
	int sub;
	id = WeiChatGroupMember;
	string txt = ".txt";

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			break;
		}
	}

	for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
	{
		if (WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() == groupid)
		{
			cout << "������Ӵ�Ⱥ" << endl;
			cout << "�����������΢����ҳ" << endl;
			if (getchar() != EOF)
				WeiChatMenu();
			return;
		}
	}

	fstream CheckGroupListFile;
	string GetLinkFileName = "Groupslist.txt";
	CheckGroupListFile.open(GetLinkFileName, ios::in);
	if (!CheckGroupListFile)
	{
		CheckGroupListFile.close();
		CheckGroupListFile.open(GetLinkFileName, ios::out);
	}
	CheckGroupListFile.close();

	bool IsGroupFlag = false;
	fstream IsGroupFile;
	string ISgroupFileName = "Groupslist.txt";
	vector<string>AllGroupIDList;
	string IsGroupTemp;
	IsGroupFile.open(ISgroupFileName);
	while (!IsGroupFile.eof())
	{
		getline(IsGroupFile, IsGroupTemp);

		AllGroupIDList.push_back(IsGroupTemp);
	}
	IsGroupFile.close();
	for (int i = 0; i < size(AllGroupIDList); i++)
	{
		if (AllGroupIDList[i] == groupid)
		{
			IsGroupFlag = true;
			break;
		}
	}

	if (IsGroupFlag == false)
	{
		cout << "û�д�Ⱥ�������������΢����ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}
	string filename = "WeChat\\Groups\\" + groupid + "\\" + groupid + ".txt";
	ofstream ofile;
	ofile.open(filename, ios::app);
	ofile << "$" << LoginedWeiChat << endl;
	ofile.close();
	cout << "������Ⱥ�ɹ�,��ȴ�Ⱥ��ͬ��" << endl;
	cout << "�����������΢����ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
}
void WeiChatBase_Qfh::QuitGroup()
{
	bool flag = false;
	int sub, select;
	string groupid;
	cout << "�����������˳���΢��Ⱥ" << endl;
	cin >> groupid;
	judge_flush(stdin);
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			break;
		}
	}

	for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
	{
		if (WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() == groupid)
		{
			flag = true;
		}
	}

	if (flag == false)
	{
		cout << "��û�м����Ⱥ" << endl;
		cout << "��ѡ����������򷵻�΢�����˵�" << endl;
		cout << "1.��������΢��Ⱥ" << endl;
		cout << "0.����΢�����˵�" << endl;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 1);
		switch (select)
		{
		case 1:
			QuitGroup();
			return;
		default:
			WeiChatMenu();
			return;
		}
	}


	//��WeiChatListȺ�б���ɾ����Ⱥ
	fstream subgrouplistfile;
	string temp;//��ȡ�ļ�ÿ������
	string content;//�����ļ���������
	string subgrouplistfilename = "WeChat\\" + LoginedWeiChat + "\\" + LoginedWeiChat + "Groupslist.txt";
	subgrouplistfile.open(subgrouplistfilename);

	while (!subgrouplistfile.eof())
	{
		getline(subgrouplistfile, temp);

		if (temp == groupid)
		{
			continue;
		}

		for (int i = 0; i < temp.size(); i++)
		{
			content.push_back(temp[i]);
		}
		content.push_back('\n');


	}
	content.pop_back();//ɾ������\n
	subgrouplistfile.close();

	subgrouplistfile.open(subgrouplistfilename, ios::out | ios::trunc);
	subgrouplistfile << content;
	subgrouplistfile.close();
	//�ӱ�Ⱥ�б���ɾ����WeiChatList
	fstream groupfile;
	string groupfilename = "WeChat\\Groups\\" + groupid + "\\" + groupid + ".txt";
	groupfile.open(groupfilename);
	string groupcontent;
	string grouptemp;
	vector<string> groupvec;

	while (!groupfile.eof())
	{
		getline(groupfile, grouptemp);
		groupvec.push_back(grouptemp);
		for (int i = 0; i < size(grouptemp); i++)
		{
			groupcontent.push_back(grouptemp[i]);
		}

		groupcontent.push_back('\n');
	}
	groupcontent.pop_back();//ɾ��ĩβ\n
	groupvec.pop_back();
	groupfile.close();
	groupvec.shrink_to_fit();

	groupfile.open(groupfilename, ios::out | ios::trunc);

	for (int i = 0; i < groupvec.size(); i++)
	{
		if (groupvec[i] == LoginedWeiChat)
		{
			groupvec.erase(groupvec.begin() + i);
			break;
		}
	}
	groupvec.shrink_to_fit();
	for (int i = 0; i < groupvec.size(); i++)
	{
		groupfile << groupvec[i] << endl;
	}
	groupfile.close();

	fstream groupadminfile;
	string groupadminfilename;
	string admincontent;
	string admintemp;
	vector<string> AdminQQ;
	groupadminfilename = "WeChat\\Groups\\" + groupid + "\\" + groupid + "admin.txt";
	groupadminfile.open(groupadminfilename);

	while (!groupadminfile.eof())
	{
		getline(groupadminfile, admintemp);
		AdminQQ.push_back(admintemp);
		for (int i = 0; i < size(admintemp); i++)
		{
			admincontent.push_back(admintemp[i]);
		}

		admincontent.push_back('\n');
	}
	admincontent.pop_back();
	AdminQQ.pop_back();
	groupadminfile.close();

	bool adminflag = false;
	for (int i = 0; i < AdminQQ.size(); i++)
	{
		if (AdminQQ[i] == LoginedWeiChat)
		{
			adminflag = true;
			break;
		}
	}


	if (adminflag == false)
	{
		cout << "�˳�Ⱥ" << groupid << "�ɹ�" << endl;
		cout << "�����������WeiChatList���˵�" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}

	groupadminfile.open(groupadminfilename, ios::out | ios::trunc);

	for (int i = 0; i < AdminQQ.size(); i++)
	{
		if (AdminQQ[i] == LoginedWeiChat)
		{
			AdminQQ.erase(AdminQQ.begin() + i);
		}
	}
	AdminQQ.shrink_to_fit();
	for (int i = 0; i < AdminQQ.size(); i++)
	{
		groupadminfile << AdminQQ[i] << endl;
	}

	groupadminfile.close();
	cout << "�˳�Ⱥ" << groupid << "�ɹ�" << endl;
	cout << "�����������WeiChatList���˵�" << endl;

	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::DeleteGroupMember()
{
	system("CLS");
	ShowGroupNoReturn();
	cout << "������Ҫ�����Ⱥ��" << endl;
	char c;
	int line = 0;
	bool flag = false;
	string id;
	string txt = ".txt";
	string GroupOwner;
	cin >> id;
	judge_flush(stdin);
	string filename = "WeChat\\Groups\\" + id + "\\" + id + ".txt";
	ifstream infile;
	infile.open(filename, ios::in);
	if (!infile)
	{
		cout << "û�д�Ⱥ,����������򷵻�WeiChatList��ҳ" << endl;
		cout << "1.��������" << endl;
		cout << "0.����WeiChatList��ҳ" << endl;
		int select;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 1);
		switch (select)
		{
		case 1:
			AgreeMember();
			return;

		case 2:
			WeiChatMenu();
			return;
		}
	}
	infile.close();
	//��ȡȺ��WeiChatList
	fstream outfile;
	outfile.open(filename);
	string temp;
	while (outfile.get(c))
	{
		if (c == '\n')
		{
			line++;
			continue;
		}
		if (line == 2) //��ȡȺ��WeiChatList��
		{
			temp.push_back(c);
		}

	}
	GroupOwner = temp;//Ⱥ��WeiChatList

	fstream adminfile;
	string adminfilename;
	string admintemp;
	vector<string> AdminQQ;
	adminfilename = "WeChat\\Groups\\" + id + "\\" + id + "admin.txt";
	adminfile.open(adminfilename);
	while (!adminfile.eof())
	{

		getline(adminfile, temp);

		AdminQQ.push_back(temp);

	}
	AdminQQ.pop_back();
	//�ж��Ƿ��ǹ���Ա��Ⱥ��
	bool Adminflag = false;
	for (int i = 0; i < AdminQQ.size(); i++)
	{
		if (AdminQQ[i] == LoginedWeiChat)
		{
			Adminflag = true;
			break;
		}
	}

	if (GroupOwner == LoginedWeiChat)
	{
		cout << "Ⱥ�����ã���ӭ����Ⱥ��Ա����" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "����Ա���ã���ӭ����Ⱥ��Ա����" << endl;
	}
	else
	{
		cout << "�����Ǹ�Ⱥ��Ⱥ�������Ա,�޷������Ⱥ" << endl;
		cout << "�����������WeiChatList��ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}
	outfile.close();
	temp.clear();
	//��ȡȺ��Ա
	fstream Groupfile;
	string Groupfilename = "WeChat\\Groups\\" + id + "\\" + id + ".txt";
	string GroupMembertemp;
	vector<string> GroupMember;
	Groupfile.open(Groupfilename);
	while (!Groupfile.eof())
	{
		getline(Groupfile, GroupMembertemp);

		GroupMember.push_back(GroupMembertemp);
	}
	GroupMember.pop_back();
	bool Ownerflag = false;
	Adminflag = false;
	if (LoginedWeiChat == GroupOwner)
	{
		cout << "��Ϊ��ȺȺ�������߳���������κ���" << endl;
		Ownerflag = true;
	}
	else
	{
		cout << "��Ϊ��Ⱥ����Ա�������߳���Ⱥ���͹���Ա�������" << endl;
		Adminflag = true;
	}
	Show_Group_InformationNo_Return(id);
	cout << "������Ҫ�߳��ĳ�Ա΢�ź�" << endl;
	string DeleteMemberQQ;
	cin >> DeleteMemberQQ;
	judge_flush(stdin);
	bool checkflag = false;//����Ƿ��д˳�Ա

	while (1)
	{
		if (DeleteMemberQQ == GroupOwner || DeleteMemberQQ == LoginedWeiChat)
		{
			cout << "�޷��߳�Ⱥ�����Լ�������������" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			continue;
		}

		for (int i = 0; i < GroupMember.size(); i++)//����Ƿ��д˳�Ա
		{
			if (DeleteMemberQQ == GroupMember[i])
			{
				checkflag = true;
				break;
			}
		}

		if (checkflag == false)
		{
			cout << "û�д˳�Ա����������" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			continue;
		}

		if (Adminflag == true)//������˺��ǹ���Ա�����߳���Ա�Ƿ��ǹ���Ա
		{
			for (int i = 0; i < AdminQQ.size(); i++)
			{
				if (AdminQQ[i] == DeleteMemberQQ)
				{
					cout << "����Ա�����߳���������Ա,����������" << endl;
					cin >> DeleteMemberQQ;
					judge_flush(stdin);
					continue;
				}
			}
		}


		//����Ƿ���Ⱥ�����Լ�
		if (DeleteMemberQQ != GroupOwner && DeleteMemberQQ != LoginedWeiChat)
		{
			break;
		}
		else
		{
			cout << "�޷��߳�Ⱥ�����Լ�������������" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			continue;
		}

	}
	//�Ӹó�ԱȺ�б���ɾ����Ⱥ
	fstream membergrouplistfile;
	string membergrouplistfilename = "WeChat\\" + DeleteMemberQQ + "\\" + DeleteMemberQQ + "Groupslist.txt";
	string membergrouplisttemp;
	vector<string> memebergrouplistcontent;
	membergrouplistfile.open(membergrouplistfilename);
	while (!membergrouplistfile.eof())
	{
		getline(membergrouplistfile, membergrouplisttemp);
		memebergrouplistcontent.push_back(membergrouplisttemp);
	}
	memebergrouplistcontent.pop_back();
	membergrouplistfile.close();

	for (int i = 0; i < memebergrouplistcontent.size(); i++)
	{
		if (memebergrouplistcontent[i] == id)
		{
			memebergrouplistcontent.erase(memebergrouplistcontent.begin() + i);
		}
	}
	membergrouplistfile.open(membergrouplistfilename, ios::trunc | ios::out);
	for (int i = 0; i < size(memebergrouplistcontent); i++)
	{
		membergrouplistfile << memebergrouplistcontent[i] << endl;
	}
	membergrouplistfile.close();

	//�ӱ�Ⱥ��Ա�б���ɾ���˳�Ա
	fstream GroupMemberListFile;
	string GroupMEmberListFileName = "WeChat\\Groups\\" + id + "\\" + id + ".txt";
	string GroupMEmberListTemp;
	vector<string> GroupMemberListContent;
	GroupMemberListFile.open(GroupMEmberListFileName);
	while (!GroupMemberListFile.eof())
	{
		getline(GroupMemberListFile, GroupMEmberListTemp);

		GroupMemberListContent.push_back(GroupMEmberListTemp);
	}
	GroupMemberListContent.pop_back();
	GroupMemberListFile.close();

	for (int i = 0; i < GroupMemberListContent.size(); i++)
	{
		if (GroupMemberListContent[i] == DeleteMemberQQ)
		{
			GroupMemberListContent.erase(GroupMemberListContent.begin() + i);
			break;
		}
	}
	GroupMemberListFile.close();
	GroupMemberListFile.open(GroupMEmberListFileName, ios::trunc | ios::out);
	for (int i = 0; i < GroupMemberListContent.size(); i++)
	{

		GroupMemberListFile << GroupMemberListContent[i] << endl;

	}
	GroupMemberListFile.close();
	int ThisGroup;
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			break;
		}
	}
	for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
	{
		if (WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() == id)
		{
			ThisGroup = i;
			break;
		}
	}
	for (int i = 0; i < WeiChatList[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers().size(); i++)
	{
		if (WeiChatList[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers()[i] == DeleteMemberQQ)
		{
			WeiChatList[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers().erase(WeiChatList[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers().begin() + i);
			break;
		}
	}
	//����ó�Ա�ǹ���Ա��ӹ���Ա�б���ɾ����WeiChatList
	for (int i = 0; i < AdminQQ.size(); i++)
	{
		if (DeleteMemberQQ == AdminQQ[i])
		{
			AdminQQ.erase(AdminQQ.begin() + i);
			adminfile.open(adminfilename, ios::trunc);
			for (int i = 0; i < AdminQQ.size(); i++)
			{
				adminfile << AdminQQ[i];
			}
			adminfile.close();

			cout << "�߳�" << DeleteMemberQQ << "�ɹ�" << endl;
			cout << "�����������WeiChatList���˵�" << endl;
			if (getchar() != EOF)
				WeiChatMenu();
			return;
		}

		else
		{
			cout << "�߳�" << DeleteMemberQQ << "�ɹ�" << endl;
			cout << "�����������WeiChatList���˵�" << endl;
			if (getchar() != EOF)
				WeiChatMenu();
			return;
		}
	}
}

void WeiChatBase_Qfh::ShowGroupInformation()
{
	system("CLS");
	ShowGroupNoReturn();

	cout << "��������Ҫ��ѯ��Ա��Ϣ��WeiChatListȺ,������#����WeiChatList���˵�" << endl;
	string  QQGroupID;
	cin >> QQGroupID;
	judge_flush(stdin);
	if (QQGroupID == "#")
	{
		WeiChatMenu();
		return;
	}
	int sub;
	int ThisQQGroupID;
	int ThisQQ;
	string ThisQQID;

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			break;
		}
	}

	bool CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
		{
			if (WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
			{
				CheckFlag = true;
				break;
			}

		}

		if (CheckFlag == true)
		{
			break;
		}
		else
		{
			cout << "��û�м����Ⱥ�����������������#����WeiChatList���˵�" << endl;
			cin >> QQGroupID;
			judge_flush(stdin);
			continue;
		}
	}


	system("CLS");
	bool AdminFlag = false;
	for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
	{
		if (WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
		{
			ThisQQGroupID = i;
			break;
		}
	}

	for (int i = 0; i < WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers().size(); i++)
	{
		int m = size(WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers());

		ThisQQID = WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers()[i];//��Ⱥ�б��ȡȺ��ԱWeiChatList
		for (int i = 0; i < WeiChatList.size(); i++)
		{
			if (WeiChatList[i]->Return_ID() == ThisQQID)
			{
				ThisQQ = i;
				break;
			}
		}
		for (int i = 0; i < size(WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->Return_Admins_ID()); i++)
		{
			if (WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->Return_Admins_ID()[i] == ThisQQID)
			{
				AdminFlag = true;
				break;
			}
		}
		if (ThisQQID == WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->ReturnCreatUserID())
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << WeiChatList[ThisQQ]->Return_ID() << endl;
			cout << "����:" << WeiChatList[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:Ⱥ��" << endl;
			cout << "���ڵ���:" << WeiChatList[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << WeiChatList[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
		else if (AdminFlag == true)
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << WeiChatList[ThisQQ]->Return_ID() << endl;
			cout << "����:" << WeiChatList[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:����Ա" << endl;
			cout << "���ڵ���:" << WeiChatList[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << WeiChatList[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
			AdminFlag = false;
		}

		else
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << WeiChatList[ThisQQ]->Return_ID() << endl;
			cout << "����:" << WeiChatList[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:��ͨ��Ա" << endl;
			cout << "���ڵ���:" << WeiChatList[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << WeiChatList[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
	}

	cout << endl;
	cout << "�����������WeiChatList���˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::ShowMyInformation()
{
	system("CLS");
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	cout << "����Ϊ���ĸ�����Ϣ:" << endl;
	cout << "�ʺ�:" << WeiChatList[sub]->Return_ID() << endl;
	cout << "����:" << WeiChatList[sub]->Return_PassWord() << endl;
	cout << "����:" << WeiChatList[sub]->Return_Name() << endl;
	cout << "�Ա�:" << WeiChatList[sub]->Return_Sex() << endl;
	cout << "����:" << WeiChatList[sub]->Return_Area() << endl;
	cout << "ע������:" << WeiChatList[sub]->Return_ApplyDate();
	cout << "����ǩ��:" << WeiChatList[sub]->Return_Autograph() << endl;
	cout << "��������:" << WeiChatList[sub]->Return_bir() << endl;
	cout << endl;
	cout << "�����������΢�����˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::Change_PassWord()
{
	system("CLS");
	cout << "��������������" << endl;
	string pw;
	string pwagin;
	cin >> pw;
	judge_flush(stdin);
	cout << "�ٴ�ȷ������������" << endl;
	cin >> pwagin;
	judge_flush(stdin);
	while (1)
	{
		if (pw != pwagin)
		{
			cout << "�������벻��������������" << endl;
			cin >> pw;
			judge_flush(stdin);
			cout << "�ٴ�ȷ������������" << endl;
			cin >> pwagin;
			judge_flush(stdin);
			continue;
		}
		else
		{
			break;
		}
	}

	int sub;

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}

	WeiChatList[sub]->Change_PassWord(pw);
	SaveChange();

	cout << "�޸�����ɹ�" << endl;
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::Change_Name()
{
	system("CLS");
	string newname;
	cout << "��������������" << endl;
	cin >> newname;
	judge_flush(stdin);
	int sub;

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}

	WeiChatList[sub]->Change_Name(newname);
	SaveChange();

	cout << "�޸����Ƴɹ�" << endl;
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::Change_AutoGraph()
{
	system("CLS");
	string autograph;
	cout << "����������ǩ��" << endl;
	cin >> autograph;
	judge_flush(stdin);
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}

	WeiChatList[sub]->Change_AutoGraph(autograph);
	cout << "�޸ĸ���ǩ���ɹ�" << endl;
	SaveChange();

	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::Change_Area()
{
	system("CLS");
	string Area;
	cout << "�������ĵ���" << endl;
	cin >> Area;
	judge_flush(stdin);
	int sub;
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
		}
	}
	WeiChatList[sub]->Change_Area(Area);
	SaveChange();

	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}


void WeiChatBase_Qfh::LinkQQ()
{
	string linkqq;
	string linkpw;
	int ThisQQ;
	int ThisWeiChat;
	system("CLS");

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			ThisWeiChat = i;
		}

	}



	if (WeiChatList[ThisWeiChat]->Return_LinkedQQ() != "")
	{
		cout << "���Ѿ���QQ:" << WeiChatList[ThisWeiChat]->Return_LinkedQQ() << endl;
		linkqq = WeiChatList[ThisWeiChat]->Return_LinkedQQ();
		for (int i = 0; i < QQFun.ReturnQQ().size(); i++)
		{
			if (QQFun.ReturnQQ()[i]->Return_ID() == linkqq)
			{
				QQFun.ReturnQQ()[i]->flag = 1;
				cout << "��QQ�Ѿ��Զ���¼" << endl;
				break;

			}
		}
		cout << "�����������΢����ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}
	cout << "��������Ҫ�󶨵�QQ��" << endl;
	cin >> linkqq;
	judge_flush(stdin);
	bool CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < QQFun.ReturnQQ().size(); i++)
		{
			if (QQFun.ReturnQQ()[i]->Return_ID() == linkqq)
			{
				CheckFlag = true;
				ThisQQ = i;
				break;

			}
		}

		if (CheckFlag == false)
		{
			cout << "û�д�QQ�����������������#����΢����ҳ" << endl;
			cin >> linkqq;
			judge_flush(stdin);
			if (linkqq == "#")
			{
				WeiChatMenu();
				return;
			}
			continue;
		}
		else
		{
			break;
		}
	}

	cout << "�������QQ�ŵ�����" << endl;
	cin >> linkpw;
	judge_flush(stdin);
	bool PWCheckFlag = false;
	while (1)
	{
		if (QQFun.ReturnQQ()[ThisQQ]->Return_PassWord() == linkpw)
		{
			PWCheckFlag = true;
			break;
		}

		if (PWCheckFlag == false)
		{
			cout << "��������������������������#����΢����ҳ" << endl;
			cin >> linkpw;
			judge_flush(stdin);
			if (linkpw == "#")
			{
				WeiChatMenu();
				return;
			}
			continue;
		}
	}

	fstream LinkFile;
	string LinkFileName = "WeChat\\" + LoginedWeiChat + "\\Links.txt";
	LinkFile.open(LinkFileName, ios::app);

	LinkFile << "QQ:" + linkqq;
	LinkFile.close();
	WeiChatList[ThisWeiChat]->Change_LinkedQQ(linkqq);


	fstream QQLinkFile;
	string QQLinkFileName = "QQ\\" + linkqq + "\\Links.txt";
	QQLinkFile.open(QQLinkFileName, ios::app);

	QQLinkFile << "΢��:" + LoginedWeiChat;
	QQLinkFile.close();
	QQFun.ReturnQQ()[ThisQQ]->Change_Linked_WeiChat(LoginedWeiChat);

	cout << "��QQ�ɹ�" << endl;
	cout << "�����������΢����ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::Get_Links()
{
	system("CLS");
	int ThisWeiChat;
	fstream GetLinksFile;
	fstream CheckFile;
	string GetLinkFileName = "WeChat\\" + LoginedWeiChat + "\\Links.txt";

	CheckFile.open(GetLinkFileName, ios::in);
	if (!CheckFile)
	{
		CheckFile.close();
		CheckFile.open(GetLinkFileName, ios::out);
	}
	CheckFile.close();

	GetLinksFile.open(GetLinkFileName);
	vector<string> Links;
	string GetLinksFileTemp;

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			ThisWeiChat = i;
		}
	}

	while (!GetLinksFile.eof())
	{
		getline(GetLinksFile, GetLinksFileTemp);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin());
		GetLinksFileTemp.erase(GetLinksFileTemp.begin());
		GetLinksFileTemp.erase(GetLinksFileTemp.begin());

		Links.push_back(GetLinksFileTemp);
	}

	if (Links.size() != 0)
	{
		WeiChatList[ThisWeiChat]->Change_LinkedQQ(Links[0]);
	}

}

void WeiChatBase_Qfh::ShowQQCommonFriends()
{
	system("CLS");
	int MyWeiChat;
	int LinkedQQ;
	int ThisWeiChat;

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			MyWeiChat = i;
			break;
		}
	}

	for (int i = 0; i < size(QQFun.ReturnQQ()); i++)
	{
		if (QQFun.ReturnQQ()[i]->Return_ID() == WeiChatList[MyWeiChat]->Return_LinkedQQ())
		{
			LinkedQQ = i;
			break;
		}
	}

	if (ReturnWeiChatList()[MyWeiChat]->Return_LinkedQQ() == "")
	{
		cout << "��û�а�QQ�����Ȱ�QQ" << endl;
		cout << "�����������΢����ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}

	cout << "���󶨵�QQ��Ϊ" << WeiChatList[MyWeiChat]->Return_LinkedQQ() << endl;
	cout << "���ʹ�QQ�Ĺ�ͬ����������" << endl;

	int FriendFlag = false;
	int CommonFriendNumber = 1;


	QQFun.ReturnQQ()[LinkedQQ]->Get_Friends();
	int fasd = QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List().size();
	for (int j = 0; j < QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List().size(); j++)
	{

		FriendFlag = false;

		for (int k = 0; k < WeiChatList.size(); k++)
		{
			WeiChatList[k]->Get_Links();
			//QQ�б����ҵ��˺���
			if (WeiChatList[k]->Return_LinkedQQ() == QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List()[j]->Return_ID())
			{
				ThisWeiChat = k;
				FriendFlag = true;
				break;
			}
		}

		if (FriendFlag == false)
		{
			continue;
		}

		for (int p = 0; p < WeiChatList[MyWeiChat]->Return_Friend_List().size(); p++)
		{
			if (WeiChatList[MyWeiChat]->Return_Friend_List()[p]->Return_ID() == WeiChatList[ThisWeiChat]->Return_ID())
			{
				cout << "��" << CommonFriendNumber << "����ͬ����" << endl;
				cout << "΢�ź�:" << WeiChatList[MyWeiChat]->Return_Friend_List()[j]->Return_ID();
				cout << "����:" << WeiChatList[MyWeiChat]->Return_Friend_List()[j]->ReturnFriendName();
				cout << "��ע:" << WeiChatList[MyWeiChat]->Return_Friend_List()[j]->ReturnRemarks();
				cout << endl;

				CommonFriendNumber++;
				break;
			}
		}


	}
	QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List().clear();
	QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List().shrink_to_fit();

	cout << "�����������΢����ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::ShowQQCommonFriendsNoReturn()
{
	system("CLS");
	int MyWeiChat;
	int LinkedQQ;
	int ThisWeiChat;

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			MyWeiChat = i;
			break;
		}
	}

	for (int i = 0; i < QQFun.ReturnQQ().size(); i++)
	{
		if (QQFun.ReturnQQ()[i]->Return_ID() == WeiChatList[MyWeiChat]->Return_LinkedQQ())
		{
			LinkedQQ = i;
			break;
		}
	}

	if (ReturnWeiChatList()[MyWeiChat]->Return_LinkedQQ() == "")
	{
		cout << "��û�а�QQ�����Ȱ�QQ" << endl;
		cout << "�����������΢����ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}

	cout << "���󶨵�QQ��Ϊ" << WeiChatList[MyWeiChat]->Return_LinkedQQ() << endl;
	cout << "���ʹ�QQ�Ĺ�ͬ����������" << endl;

	int FriendFlag = false;
	int CommonFriendNumber = 1;


	QQFun.ReturnQQ()[LinkedQQ]->Get_Friends();
	int fasd = QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List().size();
	for (int j = 0; j < QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List().size(); j++)
	{

		FriendFlag = false;
		for (int k = 0; k < WeiChatList.size(); k++)
		{
			WeiChatList[k]->Get_Links();
			//QQ�б����ҵ��˺���
			if (WeiChatList[k]->Return_LinkedQQ() == QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List()[j]->Return_ID())
			{
				ThisWeiChat = k;
				FriendFlag = true;
				break;
			}
		}

		if (FriendFlag == false)
		{
			continue;
		}

		for (int p = 0; p < WeiChatList[MyWeiChat]->Return_Friend_List().size(); p++)
		{
			if (WeiChatList[MyWeiChat]->Return_Friend_List()[p]->Return_ID() == WeiChatList[ThisWeiChat]->Return_ID())
			{
				cout << "��" << CommonFriendNumber << "����ͬ����" << endl;
				cout << "΢�ź�:" << WeiChatList[MyWeiChat]->Return_Friend_List()[j]->Return_ID();
				cout << "����:" << WeiChatList[MyWeiChat]->Return_Friend_List()[j]->ReturnFriendName();
				cout << "��ע:" << WeiChatList[MyWeiChat]->Return_Friend_List()[j]->ReturnRemarks();
				cout << endl;

				CommonFriendNumber++;
				break;
			}
		}


	}
	QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List().clear();
	QQFun.ReturnQQ()[LinkedQQ]->Return_Friend_List().shrink_to_fit();

}

void WeiChatBase_Qfh::AddQQCommonFriend()
{
	system("CLS");
	ShowQQCommonFriendsNoReturn();

	int sub, subfriend;
	string id;
	string name, subname;
	bool flag = false;
	cout << "���������QQ��ͬ���ѵ�΢�ź�" << endl;
	cin >> id;
	judge_flush(stdin);
	if (id == LoginedWeiChat)
	{
		cout << "����������Լ�Ϊ����" << endl;
		cout << "�����������΢����ҳ" << endl;
		if (getchar() != EOF)
			WeiChatMenu();
		return;
	}

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == id)
		{
			sub = i;
			subname = WeiChatList[i]->Return_Name();
			break;
		}
	}

	for (int i = 0; i < WeiChatList[sub]->Return_Friend_List().size(); i++)
	{
		if (id == WeiChatList[sub]->Return_Friend_List()[i]->Return_ID())
		{
			cout << "������Ӵ˺���,�밴���������΢����ҳ" << endl;
			if (getchar() != EOF)
				WeiChatMenu();
			return;
		}
	}

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == id)
		{
			flag = true;
			name = WeiChatList[i]->Return_Name();
			subfriend = i;
			cout << "��������ɹ�����ȴ��Է�ȷ��" << endl;
		}
	}

	if (flag == false)
	{
		cout << "��΢�źŻ�û��ע�ᣬ���������������΢�ź�" << endl;
		cout << "1.��������΢�ź���Ӻ���" << endl;
		cout << "0.����΢����ҳ" << endl;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		int select = judge_count_menu(tempstr, 1);
		switch (select)
		{
		case 1:
			AddFriend();
			return;

		case 0:
			WeiChatMenu();
			return;

		default:
			WeiChatMenu();
			return;
		}

	}

	string mark = "&";
	string ID = mark + id;//&��ʾ����������ĺ��ѵ���Ϣ�б�
	fstream file;
	string friendfilename = "WeChat\\" + LoginedWeiChat + "\\" + LoginedWeiChat + "Friendlist.txt";
	string remarks = "δ��ע";
	WeiChatList[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	file.open(friendfilename, ios::app);
	file << ID << endl;
	file << name << endl;
	file << remarks << endl;
	file << " " << endl;//�����жϼ�������
	file.close();
	//�����΢���ļ�����ӱ�ID
	friendfilename = "WeChat\\" + id + "\\" + id + "Friendlist.txt";
	subname = "$" + subname;
	WeiChatList[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subname, LoginedWeiChat));
	file.open(friendfilename, ios::app);
	file << "$" << WeiChatList[sub]->Return_ID() << endl;
	file << WeiChatList[sub]->Return_Name() << endl;
	file << remarks << endl;
	file << " " << endl;//�����жϼ�������
	file.close();
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::InviteGroupMember()
{
	system("CLS");
	int MyWeiChat;
	int ThisGroup;
	ShowGroupNoReturn();
	cout << "��������Ҫ������ѽ���Ⱥ��" << endl;
	string invitegroup;
	cin >> invitegroup;
	judge_flush(stdin);
	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			MyWeiChat = i;
		}
	}

	bool CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < WeiChatList[MyWeiChat]->Return_group_List().size(); i++)
		{
			if (WeiChatList[MyWeiChat]->Return_group_List()[i]->Return_Group_ID() == invitegroup)
			{
				CheckFlag = true;
				ThisGroup = i;
				break;
			}
			else
			{
				cout << "��û�м����Ⱥ�����������������#����΢����ҳ" << endl;
				cin >> invitegroup;
				judge_flush(stdin);
				if (invitegroup == "#")
				{
					WeiChatMenu();
					return;
				}
				continue;
			}
		}
		if (CheckFlag == true)
		{
			break;
		}
	}

	ShowFriendsNoReturn();
	cout << "��������Ҫ����ĺ���΢�ź�" << endl;
	string invitefriend;
	cin >> invitefriend;
	judge_flush(stdin);
	CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < WeiChatList[MyWeiChat]->Return_Friend_List().size(); i++)
		{
			if (WeiChatList[MyWeiChat]->Return_Friend_List()[i]->Return_ID() == invitefriend)
			{
				CheckFlag = true;
				break;
			}
			else
			{
				cout << "��û�д˺��ѣ����������������#����΢����ҳ" << endl;
				cin >> invitefriend;
				judge_flush(stdin);
				if (invitefriend == "#")
				{
					WeiChatMenu();
					return;
				}
				continue;
			}
		}
		if (CheckFlag == true)
		{
			break;
		}
	}

	CheckFlag = false;
	while (1)//���Ⱥ���Ƿ����г�Ա
	{
		for (int i = 0; i < WeiChatList[MyWeiChat]->Return_group_List()[ThisGroup]->ReturnGroupMembers().size(); i++)
		{
			if (WeiChatList[MyWeiChat]->Return_group_List()[ThisGroup]->ReturnGroupMembers()[i] == invitefriend)
			{
				cout << "�ú������ڸ�Ⱥ��,�������������΢�źŻ�����#����΢����ҳ" << endl;
				cin >> invitefriend;
				judge_flush(stdin);
				if (invitefriend == "#")
				{
					WeiChatMenu();
					return;
				}
				continue;
			}
			else
			{
				CheckFlag = true;
				break;
			}
		}
		if (CheckFlag == true)
		{
			break;
		}
	}

	fstream InviteGroupFile;
	string InviteGroupFileName = "WeChat\\Groups\\" + invitegroup + "\\" + invitegroup + ".txt";
	InviteGroupFile.open(InviteGroupFileName, ios::app);
	InviteGroupFile << invitefriend << endl;
	InviteGroupFile.close();

	fstream InviteFriendFile;
	string InviteFriendFileName = "WeChat\\" + invitefriend + "\\" + invitefriend + "Groupslist.txt";
	InviteFriendFile.open(InviteFriendFileName, ios::app);
	InviteFriendFile << invitegroup << endl;
	InviteFriendFile.close();


	cout << "������ѽ�Ⱥ�ɹ�" << endl;
	cout << "�����������΢����ҳ" << endl;
	if (getchar() != EOF)
		WeiChatMenu();
	return;
}

void WeiChatBase_Qfh::Show_Group_InformationNo_Return(string groupId)
{
	string  QQGroupID;
	QQGroupID = groupId;
	if (QQGroupID == "#")
	{
		WeiChatMenu();
		return;
	}
	int sub;
	int ThisQQGroupID;
	int ThisQQ;
	string ThisQQID;

	for (int i = 0; i < WeiChatList.size(); i++)
	{
		if (WeiChatList[i]->Return_ID() == LoginedWeiChat)
		{
			sub = i;
			break;
		}
	}

	bool CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
		{
			if (WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
			{
				CheckFlag = true;
				break;
			}

		}

		if (CheckFlag == true)
		{
			break;
		}
		else
		{
			cout << "��û�м����Ⱥ�����������������#����QQ���˵�" << endl;
			cin >> QQGroupID;
			judge_flush(stdin);
			continue;
		}
	}


	system("CLS");
	bool AdminFlag = false;
	for (int i = 0; i < WeiChatList[sub]->Return_group_List().size(); i++)
	{
		if (WeiChatList[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
		{
			ThisQQGroupID = i;
			break;
		}
	}

	for (int i = 0; i < size(WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers()); i++)
	{
		int m = size(WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers());

		ThisQQID = WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers()[i];//��Ⱥ�б��ȡȺ��ԱQQ
		for (int i = 0; i < WeiChatList.size(); i++)
		{
			if (WeiChatList[i]->Return_ID() == ThisQQID)
			{
				ThisQQ = i;
				break;
			}
		}
		for (int i = 0; i < size(WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->Return_Admins_ID()); i++)
		{
			if (WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->Return_Admins_ID()[i] == ThisQQID)
			{
				AdminFlag = true;
				break;
			}
		}
		if (ThisQQID == WeiChatList[sub]->Return_group_List()[ThisQQGroupID]->ReturnCreatUserID())
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << WeiChatList[ThisQQ]->Return_ID() << endl;
			cout << "����:" << WeiChatList[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:Ⱥ��" << endl;
			cout << "���ڵ���:" << WeiChatList[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << WeiChatList[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
		else if (AdminFlag == true)
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << WeiChatList[ThisQQ]->Return_ID() << endl;
			cout << "����:" << WeiChatList[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:����Ա" << endl;
			cout << "���ڵ���:" << WeiChatList[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << WeiChatList[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
			AdminFlag = false;
		}

		else
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << WeiChatList[ThisQQ]->Return_ID() << endl;
			cout << "����:" << WeiChatList[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:��ͨ��Ա" << endl;
			cout << "���ڵ���:" << WeiChatList[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << WeiChatList[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
	}

	cout << endl;
}