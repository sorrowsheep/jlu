#include<iostream>
#include"Account.h"
#include"QQFriends_Qfh.h"
#include"QQgroups_Qfh.h"
#include"QQ_Qfh.h"
#include"WeiBo_Qfh.h"
#include"Weixin_Qfh.h"
#include<string>
#include<fstream>
#include"function.h"
#include"ChatBase_Qfh.h"
#include"QQChatBase_Qfh.h"
#include"WeiBoChatBase_Qfh.h"
#include"WeChatBase_Qfh.h"
#include"judge.h"

using namespace std;
#pragma comment(lib,"ws2_32.lib")
#ifndef NOMINMAX
#define NOMINMAX 1// prevent windows redefining min/max
#endif
#include <Windows.h>
#undef far
#undef near
QQChat_Qfh QQFun;
WeiBoChat_Qfh WeiBoFun;
WeiChat_Qfh WeChatFun;
MainMenu_Qfh mainmenu;
static int menuWidth = 80;
int main()
{
	SetConsoleTitle("��ʱͨ��ϵͳ");
	system("CLS");
	string QQ = "QQ";
	string WeChat = "WeChat";
	string WeiBo = "WeiBo";
	string Groups = "QQ\\Groups";
	CreateDirectory(QQ.c_str(), NULL);//����QQ�ļ���
	CreateDirectory(WeChat.c_str(), NULL);//����΢�ŵ��ļ���
	CreateDirectory(WeiBo.c_str(), NULL);//����΢�����ļ���
	CreateDirectory(Groups.c_str(), NULL);//����QQȺ����ļ���
	string Groups1 = "WeChat\\Groups";
	CreateDirectory(Groups1.c_str(), NULL);//����΢��Ⱥ����ļ���
	QQFun.GetQQ();
	WeiBoFun.GetWeiBo();
	
	WeChatFun.GetWeChat();
	mainmenu.Menu();
	return 0;
}

void MainMenu_Qfh::Menu()
{
	system("CLS");
	int select, key = 1;
	string str;
	bool flag = false;
	cout << "\t\t\t\t|*--------------------ģ��ͨ��ϵͳ-------------------*|" << endl;
	cout << "\t\t\t\t|*                      1.����QQ                   *|" << endl;
	cout << "\t\t\t\t|*                      2.����΢��                 *|" << endl;
	cout << "\t\t\t\t|*                      3.����΢��                 *|" << endl;
	cout << "\t\t\t\t|*                      0.�˳�ϵͳ                 *|" << endl;
	cout << "\t\t\t\t|*---------------------------------------------------*|" << endl;
	cout << "��������Ҫ������罻���:" << endl;
	cin >> str;
	judge_flush(stdin);
	select = judge_count_menu(str, 3);
	switch (select)
	{
	case 1:
	{
		QQFun.Menu();
		break;
	case 2:
		WeChatFun.Menu();

		break;

	case 3:
		WeiBoFun.Menu();
		break;
	case 0:system("cls"); break;
	}
	default:
	{
		Menu();
		break;
	}
	}
}