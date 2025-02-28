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
	cout << "���ڽ���QQ��ע�᣺" << endl;
	cout << "������QQ�ǳ�:" << endl;
	cin >> Name;
	judge_flush(stdin);
	cout << "����������" << endl;
	string PassWordAgin;
	cin >> PassWord;
	judge_flush(stdin);
	cout << "���ٴ�ȷ������" << endl;
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
			cout << "���벻ƥ�䣬����������" << endl;
			cout << "����������" << endl;
			cin >> PassWord;
			judge_flush(stdin);
			cout << "���ٴ�ȷ������" << endl;
			cin >> PassWordAgin;
			judge_flush(stdin);
			continue;
		}
	}
	cout << "�����������ڵĵ���" << endl;
	cin >> Area;
	judge_flush(stdin);
	cout << "��������������,��ʽ��20050302" << endl;
	birthday = birthday_input();
	cout << "��ѡ�������Ա�" << endl;
	cout << "0.����" << endl;
	cout << "1.Ů��" << endl;
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
		cout << "������������Ĭ��Ϊ������ΪŮ��" << endl;
		break;
	}
	cout << "�������ĸ���ǩ��" << endl;
	cin >> Autograph;
	judge_flush(stdin);
	time_t t;
	t = time(NULL);
	char* time;
	time = ctime(&t);
	ApplyDate = time;
	cout << "QQ������ɹ�" << endl;
	cout << "QQ��:" << ID << endl;
	cout << "QQ����:" << PassWord << endl;
	cout << "QQ�ǳ�:" << Name << endl;
	cout << "�����Ʊ����ʺ�����" << endl;
	string QQ = "QQ\\" + ID;// str += "\\�����ļ���";
	CreateDirectory((LPCSTR)QQ.c_str(), NULL);//ÿ��QQ����һ���ļ���Ŀ¼
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
//��ȡQQ�����б�
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
	}//����м�������
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
//��ȡ����
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
		//erase΢�ţ�
		Links.push_back(GetLinksFileTemp);
	}
	if (Links.size() != 0)
	{
		LinkedWeiChat = Links[0];//Ĭ�ϵ�һ��Ϊ΢�źţ��ж��΢�ź�ʱ��Ĭ�ϵ�һ��Ϊ΢�źţ�
	}
}


//Weixin���캯��
Weixin_Qfh::Weixin_Qfh(int size)
{
	time_t ti;
	int temp = size+1;
	stringstream ss;
	ss << temp;
	string PassWordAgin;
	int select;
	ss >> ID;
	cout << "���ڽ���΢�ŵ�ע��:" << endl;
	cout << "������΢���ǳ�:" << endl;
	cin >> Name;
	judge_flush(stdin);
	cout << "����������" << endl;
	cin >> PassWord;
	judge_flush(stdin);
	cout << "���ٴ�ȷ������" << endl;
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
			cout << "���벻ƥ�䣬����������" << endl;
			cout << "����������" << endl;
			cin >> PassWord;
			judge_flush(stdin);
			cout << "���ٴ�ȷ������" << endl;
			cin >> PassWordAgin;
			judge_flush(stdin);
			continue;
		}
	}

	cout << "�����������ڵĵ���" << endl;
	cin >> Area;
	judge_flush(stdin);
	cout << "��������������(��ʽ��20050302)" << endl;
	birthday = birthday_input();
	cout << "��ѡ�������Ա�" << endl;
	cout << "0.����" << endl;
	cout << "1.Ů��" << endl;
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
		cout << "��������Ĭ������ΪŮ��" << endl;
		break;
	}

	cout << "�������ĸ���ǩ��" << endl;
	cin >> Autograph;
	judge_flush(stdin);
	time_t t;
	t = time(NULL);
	char* time;
	time = ctime(&t);
	ApplyDate = time;
	cout << "΢�ź�����ɹ�" << endl;
	cout << "΢�ź�:" << ID << endl;
	cout << "΢������:" << PassWord << endl;
	cout << "�����Ʊ����ʺź�����" << endl;

	string WeChat = "WeChat\\" + ID;// str += "\\�����ļ���";
	CreateDirectory(WeChat.c_str(), NULL);//ÿ��΢�Ŵ���һ���ļ���
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
    Sex = "Ů";
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


//Weixin��������
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

//��ȡ����QQ��
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
//��ȡ΢�ź����б�
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



