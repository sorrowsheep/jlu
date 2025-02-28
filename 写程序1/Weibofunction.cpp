
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
//保存开通的微博
void WeiBoChatBase_Qfh::SaveWeiBo()
{
	fstream WeiBoListFile;
	string WeiBoListFileName = "WeiBoList.txt";
	WeiBoListFile.open(WeiBoListFileName, ios::app);
	string m = QQFun.Returnqqnumber();
	WeiBoListFile << QQFun.Returnqqnumber() << endl;
	WeiBoListFile.close();
}
//获取微博列表
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
//登录微博
void WeiBoChatBase_Qfh::Login()
{
	system("CLS");
	string WeiBoID;
	string WeiBoPW;
	int ThisWeiBo;
	bool isCheckFlag = false;
	bool PWCheckFlag = false;
	cout << "请输入您的微博(QQ)号" << endl;
	cin >> WeiBoID;
	judge_flush(stdin);
	//判断微博账号是否存在
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
			cout << "您输入的账号不存在，请重新输入或输入#返回微博主菜单" << endl;
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


	cout << "请输入您的微博(微信)号密码" << endl;
	cin >> WeiBoPW;
	judge_flush(stdin);
	while (1)
	{
		if (QQFun.ReturnQQ()[ThisWeiBo]->Return_PassWord() == WeiBoPW)
		{
			cout << "登陆成功,按任意键进入微博主页" << endl;
			if (getchar() != EOF)
				WeiBoMenu();
			break;
		}
		else
		{
			cout << "密码输入错误,请重新输入或输入#返回微博主菜单" << endl;
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
	cout << "\t\t\t\t|*------------微博功能菜单----------------*|" << endl;
	cout << "\t\t\t\t|*                                        *|" << endl;
	cout << "\t\t\t\t|*          1.登陆微博                    *|" << endl;
	cout << "\t\t\t\t|*          2.微博推送端（主服务器）      *|"  << endl;
	cout << "\t\t\t\t|*          0.返回上一级菜单              *|" << endl;
	cout << "\t\t\t\t|*                                        *|" << endl;
	cout << "\t\t\t\t|*----------------------------------------*|" << endl;
	cout << "您的选择:" << endl;
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
	cout << "\t\t\t\t|*----------欢迎来到微博---------------*|" << endl;
	cout << "           您的微博号为" << WeiBoFun.LoginedWeiBoID << endl;
	cout << "\t\t\t\t|*          无可用功能             *|" << endl;
	cout << "\t\t\t\t|*         0.返回主菜单            *|" << endl;
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
void WeiBoChatBase_Qfh::AddFriend() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::SaveFriends() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::Get_Friends() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::ShowFriends() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::DeleteFriend() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::AgreeFriend() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::ShowFriendInformation() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::ChangeFriendRemarks() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::SaveChange() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::AgreeMember() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::ShowMyInformation() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::Change_PassWord() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::Change_Name() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::Change_AutoGraph() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::Change_Area() { cout << "未实现" << endl; return; }
void WeiBoChatBase_Qfh::Get_Links() { cout << "未实现" << endl; return; }