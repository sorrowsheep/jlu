#include<iostream>
#include"Account.h"
#include<time.h>
#include"QQFriends_Qfh.h"
#include"QQgroups_Qfh.h"
#include"QQ_Qfh.h"
#include"WeiBo_Qfh.h"
#include"Weixin_Qfh.h"
#include<windows.h>
#include<stdlib.h>
#include<fstream>
#include"function.h"
#include"ChatBase_Qfh.h"
#include"QQChatBase_Qfh.h"
#include"WeiBoChatBase_Qfh.h"
#include"WeChatBase_Qfh.h"
#include"judge.h"
using namespace std;

QQ_Qfh::QQ_Qfh(int size)
{  
	int temp = size;
	stringstream ss;
	ss << temp;
	ss >> ID;
	cout << "现在进行QQ的注册：" << endl;
	cout << "请输入QQ昵称:" << endl;
	cin >> Name;
	judge_flush(stdin);
	cout << "请输入密码" << endl;
	string PassWordAgin;
	cin >> PassWord;
	judge_flush(stdin);
	cout << "请再次确认密码" << endl;
	cin >> PassWordAgin;
	judge_flush(stdin);
	while (1)
	{
		if (PassWord == PassWordAgin)
		{
			break;
		}
		else
		{
			cout << "密码不匹配，请重新输入" << endl;
			cout << "请输入密码" << endl;
			cin >> PassWord;
			judge_flush(stdin);
			cout << "请再次确认密码" << endl;
			cin >> PassWordAgin;
			judge_flush(stdin);
			continue;
		}
	}
	cout << "请输入您所在的地区" << endl;
	cin >> Area;
	judge_flush(stdin);
	cout << "请输入您的生日,格式：20050302" << endl;
	birthday = birthday_input();
	cout << "请选择您的性别" << endl;
	cout << "0.男性" << endl;
	cout << "1.女性" << endl;
	int select;
	string str;
	cin >> str;
	judge_flush(stdin);
	select = judge_count_menu(str, 1);
	switch (select)
	{
	case 0:
		Sex = Man.SexFlag;
		break;
	case 1:
		Sex = WoMan.SexFlag;
		break;
	default:
		Sex = WoMan.SexFlag;
		cout << "您的输入有误，默认为您设置为女性" << endl;
		break;
	}
	cout << "输入您的个性签名" << endl;
	cin >> Autograph;
	judge_flush(stdin);
	time_t t;
	t = time(NULL);
	char* time;
	time = ctime(&t);
	ApplyDate = time;
	cout << "QQ号申请成功" << endl;
	cout << "QQ号:" << ID << endl;
	cout << "QQ密码:" << PassWord << endl;
	cout << "QQ昵称:" << Name << endl;
	cout << "请妥善保存帐号密码" << endl;
	string QQ = "QQ\\" + ID;// str += "\\二级文件夹";
	CreateDirectory((LPCSTR)QQ.c_str(), NULL);//每个QQ创建一个文件夹目录
}
QQ_Qfh::QQ_Qfh(string qqid, string qage, string qqpw, string qqname, string qqsex, string qqpv, string ag, string bir)
{
	ID = qqid;
	PassWord = qqpw;
	Name = qqname;
	Area = qqpv;
	Sex = qqsex;
	Autograph = ag;
	ApplyDate = qage;
	birthday = bir;
	Friend_Number = 0;
	Group_Number = 0;
}

QQ_Qfh::~QQ_Qfh()
{
	for (int i = 0; i < FriendList.size(); i++)
	{
		delete FriendList[i];
	}
	for (int i = 0; i < GroupList.size(); i++)
	{
		delete GroupList[i];
	}
	for (int i = 0; i < TemporaryGroupList.size(); i++)
	{
		delete TemporaryGroupList[i];
	}
}
string QQ_Qfh::Return_bir()
{
	return birthday;
}
//获取QQ好友列表
void QQ_Qfh::Get_Friends()
{
	ifstream file;
	string qq = ID;
	string txt = ".txt";
	string filename = "QQ\\" + qq + "\\" + qq + "Friendlist.txt";
	string id;
	string name;
	string remarks;
	char c;
	int line = 0;
	file.open(filename, ios::app);
	while (file.get(c))
	{
		if (c == ' ')
		{
			line++;
		}
	}//检查有几个好友
	file.close();
	Friend_Number = line;
	FriendList.clear();
	file.open(filename, ios::app);
	for (int i = 0; i < line; i++)
	{
		file >> id;
		file >> name;
		file >> remarks;
		FriendList.push_back(new QQFriends_Qfh(name, id, remarks));
	}
	file.close();
}
//获取链接
void QQ_Qfh::Get_Links()
{
	fstream CheckFile;
	fstream GetLinksFile;
	string GetLinkFileName = "QQ\\" + ID + "\\Links.txt";
	CheckFile.open(GetLinkFileName, ios::in);
	if (!CheckFile)
	{
		CheckFile.close();
		CheckFile.open(GetLinkFileName, ios::out);
	}
	CheckFile.close();
	GetLinksFile.open(GetLinkFileName, ios::out | ios::in);
	vector<string> Links;
	string GetLinksFileTemp;
	while (!GetLinksFile.eof())
	{
		getline(GetLinksFile, GetLinksFileTemp);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		//erase微信：
		Links.push_back(GetLinksFileTemp);
	}
	if (Links.size() != 0)
	{
		LinkedWeiChat = Links[0];//默认第一个为微信号（有多个微信号时，默认第一个为微信号）
	}
}


//Weixin构造函数
Weixin_Qfh::Weixin_Qfh(int size)
{
	time_t ti;
	int temp = size+1;
	stringstream ss;
	ss << temp;
	string PassWordAgin;
	int select;
	ss >> ID;
	cout << "现在进行微信的注册:" << endl;
	cout << "请输入微信昵称:" << endl;
	cin >> Name;
	judge_flush(stdin);
	cout << "请输入密码" << endl;
	cin >> PassWord;
	judge_flush(stdin);
	cout << "请再次确认密码" << endl;
	cin >> PassWordAgin;
	judge_flush(stdin);
	while (1)
	{
		if (PassWord == PassWordAgin)
		{
			break;
		}
		else
		{
			cout << "密码不匹配，请重新输入" << endl;
			cout << "请输入密码" << endl;
			cin >> PassWord;
			judge_flush(stdin);
			cout << "请再次确认密码" << endl;
			cin >> PassWordAgin;
			judge_flush(stdin);
			continue;
		}
	}

	cout << "请输入您所在的地区" << endl;
	cin >> Area;
	judge_flush(stdin);
	cout << "请输入您的生日(格式：20050302)" << endl;
	birthday = birthday_input();
	cout << "请选择您的性别" << endl;
	cout << "0.男性" << endl;
	cout << "1.女性" << endl;
	string str;	cin >> str;
	judge_flush(stdin);
	select = judge_count_menu(str, 1);
	switch (select)
	{
	case 0:
		Sex = Man.SexFlag;
		break;
	case 1:
		Sex = WoMan.SexFlag;
		break;
	default:
		Sex = WoMan.SexFlag;
		cout << "输入有误，默认设置为女性" << endl;
		break;
	}

	cout << "输入您的个性签名" << endl;
	cin >> Autograph;
	judge_flush(stdin);
	time_t t;
	t = time(NULL);
	char* time;
	time = ctime(&t);
	ApplyDate = time;
	cout << "微信号申请成功" << endl;
	cout << "微信号:" << ID << endl;
	cout << "微信密码:" << PassWord << endl;
	cout << "请妥善保存帐号和密码" << endl;

	string WeChat = "WeChat\\" + ID;// str += "\\二级文件夹";
	CreateDirectory(WeChat.c_str(), NULL);//每个微信创建一个文件夹
}
Weixin_Qfh::Weixin_Qfh(string qqid) {
	ID = qqid;
	time_t t;
	t = time(NULL);
	char* time;
	time = ctime(&t);
	ApplyDate = time;
    PassWord = "0";
    Name = "0";
    Area = "0";
    Autograph = "0";
    Sex = "女";
    birthday = "20050302";
    Friend_Number = 0;
    Group_Number = 0;
}
Weixin_Qfh::Weixin_Qfh(string qqid, string qage, string qqpw, string qqname, string wxsex, string qqpv, string ag, string bir)
{
	ID = qqid;
	ApplyDate = qage;
	PassWord = qqpw;
	Name = qqname;
	Area = qqpv;
	Autograph = ag;
	Sex = wxsex;
	birthday = bir;
	Friend_Number = 0;
	Group_Number = 0;
}


//Weixin析构函数
Weixin_Qfh::~Weixin_Qfh()
{
	for (int i = 0; i < FriendList.size(); i++)
	{
		delete FriendList[i];
	}

	for (int i = 0; i < GroupList.size(); i++)
	{
		delete GroupList[i];
	}
}

//获取链接QQ号
void Weixin_Qfh::Get_Links()
{

	fstream GetLinksFile;
	fstream CheckFile;
	string GetLinkFileName = "WeChat\\" + ID + "\\Links.txt";

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
		LinkedQQ = Links[0];
	}
}
//获取微信好友列表
void Weixin_Qfh::Get_Friends()
{
	ifstream file;
	string qq = ID;
	string txt = ".txt";
	string filename = "WeChat\\" + qq + "\\" + qq + "Friendlist.txt";
	string id;
	string name;
	string remarks;
	char c;
	int line = 0;
	file.open(filename, ios::app);
	while (file.get(c))
	{
		if (c == ' ')
		{
			line++;
		}
	}
	file.close();
	Friend_Number = line;
	FriendList.clear();
	file.open(filename, ios::app);
	for (int i = 0; i < line; i++)
	{
		file >> id;
		file >> name;
		file >> remarks;
		FriendList.push_back(new QQFriends_Qfh(name, id, remarks));
	}
	file.close();
}



