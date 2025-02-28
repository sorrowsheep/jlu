#include<iostream>
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
#include <string>
#include<stdlib.h>
#include<time.h>
#include<chrono>
#include<iomanip>
#include <tchar.h>
#include <algorithm> // ���� std::sort
#include <locale>   // ���� std::tolower
#include <unordered_set>
using namespace std;
int Grouptype;
//�º�����hashcode�Ľ�ϣ�ͨѶ¼��
bool CompareFriends(QQFriends_Qfh* a,  QQFriends_Qfh* b) {
	// ת��ΪСд��ȷ���Ƚϲ��ܴ�СдӰ��
	return std::tolower(a->ReturnFriendName()[0]) < std::tolower(b->ReturnFriendName()[0]);
}
// quitgroup�����ã�ɾ��Ⱥ�б��еĸ�Ⱥ
void QQChatBase_Qfh::removeGroupFromFile(const string
	filename, const string& groupid) {
	fstream file(filename);
	string temp, content;

	while (getline(file, temp))
	{
		if (temp != groupid) {
			content += temp + '\n';
		}
	}
	file.close();
	file.open(filename, ios::out | ios::trunc);
	file << content;
	file.close();
}
// quitgroup�����ã���Ⱥ��Ա�ļ���ɾ����ǰ�û�
void QQChatBase_Qfh::removeUserFromGroupFile(const string& filename, const string& userID) {
	fstream file(filename);
	string temp, content;
	vector<string> groupvec;

	while (getline(file, temp))
	{
		if (temp != userID) {
			groupvec.push_back(temp);
			content += temp + '\n';
		}
	}
	file.close();

	file.open(filename, ios::out | ios::trunc);
	for (const auto& member : groupvec) {
		file << member << endl;
	}
	file.close();
}
// quitgroup�����ã��ӹ���Ա�ļ���ɾ����ǰ�û�
void QQChatBase_Qfh::removeUserFromAdminFile(const string& filename, const string& userID, const string& groupid) {
	fstream file(filename);
	string temp, content;
	vector<string> AdminQQ;

	while (getline(file, temp)) {
		AdminQQ.push_back(temp);
		content += temp + '\n';
	}
	file.close();

	auto it = find(AdminQQ.begin(), AdminQQ.end(), userID);
	if (it != AdminQQ.end()) {
		AdminQQ.erase(it);
	}

	// ����û����ǹ���Ա
	if (AdminQQ.size() == 0 || it == AdminQQ.end()) {
		cout << "�˳�Ⱥ" << groupid << "�ɹ�" << endl;
		cout << "�������������һ��" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	file.open(filename, ios::out | ios::trunc);
	for (const auto& admin : AdminQQ) {
		file << admin << endl;
	}
	file.close();

	cout << "�˳�Ⱥ" << groupid << "�ɹ�" << endl;
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		QQMenu();
}
// agree�����ã���ȡ�ļ����ݵ�������


	// ��ȡ�ļ�������
	static void ReadFileToVector(const string& filename, vector<string>& content) {
		ifstream file(filename);
		string line;
		while (getline(file, line)) {
			content.push_back(line);
		}
		if (!content.empty()) {
			content.pop_back(); // ɾ�����һ������
		}
	}

	// д�������ݵ��ļ�
	static void WriteVectorToFile(const string& filename, const vector<string>& content) {
		ofstream file(filename, ios::trunc); // ����ļ�����
		for (const auto& line : content) {
			file << line << endl;
		}
	}

//delete�����ã����º����ļ��б�
void QQChatBase_Qfh::UpdateFriendFile(int sub) {
	string filename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	ofstream file(filename, ios::trunc);
	for (const auto& friendObj : QQ[sub]->Return_Friend_List()) {
		file << friendObj->Return_ID() << endl;
		file << friendObj->ReturnFriendName() << endl;
		file << friendObj->ReturnRemarks() << endl;
		file << " ";
	}
	file.close();
}

// delete�����ã�����QQ���ѵ�����
int QQChatBase_Qfh::FindQQIndex(const string& qqid) {
	for (int i = 0; i < QQ.size(); i++) {
		if (QQ[i]->Return_ID() == qqid) {
			return i;
		}
	}
	return -1; // δ�ҵ�
}


//ͨ�ã����ؽ���
void QQChatBase_Qfh::WaitForUserInput() {
	cout << "�������������һ��" << endl;
	if (getchar() != EOF) {
		QQMenu();
	}
}
//����Ա��С�˵�
void QQChatBase_Qfh::HandleMenuSelection(int select) {
	switch (select) {
	case 1:
		AddGroupAdmin();
		return;
	default:
		handleQQGroupMenu(130);
		return;
	}
}
//����Ա�����Ⱥ����Ա
void ShowMenu(const string& message, const vector<string>& options) {
	cout << message << endl;
	for (const auto& option : options) {
		cout << option << endl;
	}
}
//����
vector<WeiBo_Qfh*>& WeiBoChatBase_Qfh::ReturnWeiBolist() {
	return WeiBoList;
}
void WeiBoChatBase_Qfh����Apply() {
	std::cout << "���¼QQ��ͨ΢��" << endl;
}
//����QQ��Ϣ
void QQChatBase_Qfh::SaveQQ()
{
	ofstream file;
	string filename = "QQ.txt";
	file.open("QQ.txt", ios::app);
	int i = 0;
	i = QQ.size();
	if (i > 0)
	{
	  //QQ��:2
		//ע������ : Mon Dec 16 13 : 00 : 05 2024
		//QQ���� : 1
		//QQ���� : 1
		// QQ�Ա� : 1
		//���ڵ��� : 1
		//�û����� : 20000505
		//����ǩ�� : 1
		file << QQ[i - 1]->Return_ID() << endl;
		file << QQ[i - 1]->Return_ApplyDate() << endl;
		file << QQ[i - 1]->Return_PassWord() << endl;
		file << QQ[i - 1]->Return_Name() << endl;
		file << QQ[i - 1]->Return_Sex() << endl;
		file << QQ[i - 1]->Return_Area() << endl;
		file << QQ[i - 1]->Return_Autograph() << endl;
		file << QQ[i - 1]->Return_bir() << endl;
		file << " " << endl;
	}
	else
	{
		file.close();
		file.open(filename, ios::trunc | ios::out);//����ļ�����
		file.close();
	}

	file.close();
}
//����QQ������Ϣ
	void QQChatBase_Qfh::SaveFriends()
	{
		int i = 0, sub, n;
		ofstream file;
		string filename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
		file.open(filename, ios::trunc);
		for (i = 0; i < QQ.size(); i++)
		{
			if (QQ[i]->Return_ID() == qqnumber)
			{
				sub = i;
				break;
			}
		}
		n = QQ[sub]->Return_Friend_List().size();
		for (int j = 0; j < n; j++)
		{
			file << QQ[sub]->Return_Friend_List()[j]->Return_ID() << endl;
			file << QQ[sub]->Return_Friend_List()[j]->ReturnFriendName() << endl;
			file << QQ[sub]->Return_Friend_List()[j]->ReturnRemarks() << endl;
			file << " "; // ���һ��������Ϊ�ָ���
		}
		file.close();
	}

//��QQ��Ϣ���ļ��ж�ȡ
void QQChatBase_Qfh::GetQQ()
{
	QQ.clear();
	QQ.shrink_to_fit();
	string qage;
	string qqnumber;
	string qqpw, qqname, qqpv, qqag, qqbir, qqsex;
	ifstream file;
	int line = 0;
	char c;
	file.open("QQ.txt");
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

	file.open("QQ.txt");
	for (int i = 0; i < line; i++)
	{
		file >> qqnumber;
		//��ȡע��������Ϣ
		for (int i = 0; i < 4; i++)
		{
			file >> temp;
			qage += temp + " ";

		}
		//��ȡ������Ϣ
		file >> temp;
		qage += temp;
		file >> qqpw >> qqname >> qqsex >> qqpv >> qqag >> qqbir;
		QQ.push_back(new QQ_Qfh(qqnumber, qage, qqpw, qqname, qqsex, qqpv, qqag, qqbir));
		qage.clear();
	}
	file.close();
}
//չʾ��ע��qq
void QQChatBase_Qfh::ShowQQ()
{
	system("CLS");
	GetQQ();
	
	for (int i = 0; i < QQ.size(); i++)
	{
		string applydate = QQ[i]->Return_ApplyDate();
		cout << "QQ��:" << QQ[i]->Return_ID() << endl;
		cout << "QQ����:" << QQ[i]->Return_PassWord() << endl;
		cout << "QQ����:" << QQ[i]->Return_Name() << endl;
		cout << "IP��ַ:" << QQ[i]->Return_Area() << endl;
		cout << "�û�����:" << QQ[i]->Return_bir() << endl;
		calculateAge(applydate);
		cout << "����ǩ��:" << QQ[i]->Return_Autograph() << endl;
		cout << endl;
	}
	cout << "�����������" << endl;
	if (getchar() != EOF)
		Menu();
}
//QQҳ��˵�
void QQChatBase_Qfh::Menu()
{
	const int menuWidth = 130;
	system("CLS");
	int  key = 1;
	bool flag = false;
	printCentered("|*---------QQҳ��˵�--------------*|", menuWidth);
	printCentered("|*          1.��½QQ               *|", menuWidth);
	printCentered("|*          2.ע��QQ               *|", menuWidth);
	printCentered("|*          3.�һ�����             *|", menuWidth);
	printCentered("|*          4.�鿴������QQ��       *|", menuWidth);
	printCentered("|*          0.�������˵�           *|", menuWidth);
	printCentered("|*---------------------------------*|", menuWidth);
	cout << "ѡ����Ҫִ�еĲ���:" << endl;
	int choice;
	string str;
	cin >> str;
	judge_flush(stdin);
	choice = judge_count_menu(str, 4);
	switch (choice)
	{
	case 1:Login(); break;
	case 2:Apply(); break;
	case 3:Find_PassWord(); break;
	case 4:ShowQQ(); break;
	case 0:mainmenu.Menu(); return;
	default:
	{
		Menu();
		return;
	}
	}
}

//ע��QQ
void QQChatBase_Qfh::Apply()
{
	system("CLS");
	QQ.push_back(new QQ_Qfh(QQ.size() + 1));//ͨ�����캯������
	SaveQQ();				   //����QQ��Ϣ
	cout << "�����������" << endl;
	if (getchar() != EOF)
		Menu();
	return;
}
//��¼QQ
void QQChatBase_Qfh::Login()
{
	system("CLS");
	string ID;
	bool flag = false;//�����û�����Ҫ��½��QQ��
	string PassWord;
	int sub = 0;//��¼�±�
	cout << "������Ҫ��½��QQ:" << endl;
	cin >> ID;
	judge_flush(stdin);
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == ID)
		{
			flag = true;
			sub = i;
			break;
		}
	}
	if (flag != true)
	{

		cout << "û�и�QQ�ţ��������룬�����������" << endl;
		if (getchar() != EOF)
			Menu();
		return;
	}
	if (QQ[sub]->flag != 1)
	{
		cout << "�������QQ������" << endl;
		cin >> PassWord;
		judge_flush(stdin);
		while (PassWord != QQ[sub]->Return_PassWord())
		{
			cout << "�����������,��������������(�򰴡�#��������һ���˵�)" << endl;
			cin >> PassWord;
			if (PassWord == "#") { Menu(); return; }
			judge_flush(stdin);
		}
	}
	qqnumber = ID;
	Get_Friends();//��ȡ����
	GetQQGroup();//��ȡȺ
	Get_Links();//��ȡ�󶨵�΢��
	LogOperation("�û���¼", ID);
	cout << "��½�ɹ�" << endl;
	cout << "���������ʼʹ��QQ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
//��������
void QQChatBase_Qfh::Find_PassWord() {
	system("CLS");
	string ID;
	bool flag = false;
	cout << "��������Ҫ�һ������QQ��:" << endl;
	cin >> ID;
	judge_flush(stdin);
	int sub = 0;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == ID)
		{
			flag = true;
			sub = i;
			break;
		}
	}
	if (flag != true)
	{
		cout << "û�и�QQ�ţ����������Ƿ���ȷ�������������" << endl;
		if (getchar() != EOF)
			Menu();
		return;
	}
	cout<<"�����û�����Ϊ��" << QQ[sub]->Return_PassWord() << endl;
	cout << "�������������£�";
	cout << "�������QQ������" << endl;
	string PassWord;
	cin >> PassWord;
	judge_flush(stdin);
	while (PassWord != QQ[sub]->Return_PassWord())
	{
		cout << "�����������,��������������(�򰴡�#��������һ���˵�)" << endl;
		cin >> PassWord;
		if (PassWord == "#") { Menu(); return; }
		judge_flush(stdin);
	}
	cout << "�������µ�����" << endl;
	string NewPassWord;
	cin >> NewPassWord;
	judge_flush(stdin);
	while (NewPassWord == "")
	{
		cout << "���벻��Ϊ��,��������������(�򰴡�#��������һ���˵�)" << endl;
		cin >> NewPassWord;
		if (NewPassWord == "#") { Menu(); return; }
		judge_flush(stdin);
	}
	QQ[sub]->Change_PassWord(NewPassWord);
	SaveQQ();
	cout << "�����޸ĳɹ��������������" << endl;
	if (getchar() != EOF)
		Menu();
	return;
}


//QQ���ܲ˵�
void QQChatBase_Qfh::QQMenu()
{
	system("CLS");
	int select;
	string temp;
	const int menuWidth = 130;

	// ��ʾ���˵�
	displayMainMenu(menuWidth);

	// ��ȡ�û�ѡ��
	cin >> temp;
	judge_flush(stdin);
	select = judge_count_menu(temp, 5);

	// �����û�ѡ��
	handleMainMenuSelection(select, menuWidth);
}

//QQ�����˵�
void QQChatBase_Qfh::displayMainMenu(int menuWidth)
{
	cout << "         �û�: " << qqnumber << endl;
	printCentered("|*---------QQ���ܲ˵�--------------*|", menuWidth);
	
	printCentered("|*        1.���ѹ���               *|", menuWidth);
	printCentered("|*        2.Ⱥ����                 *|", menuWidth);
	printCentered("|*        3.������Ϣ               *|", menuWidth);
	printCentered("|*        4.��ͨ����               *|", menuWidth);
	printCentered("|*        5.�鿴��ʷ��¼           *|", menuWidth);
	printCentered("|*        0.������һ��             *|", menuWidth);
	printCentered("|*---------------------------------*|", menuWidth);
	printCentered("ѡ����Ҫִ�еĲ���", menuWidth);
}

void QQChatBase_Qfh::handleMainMenuSelection(int select, int menuWidth)
{
	switch (select)
	{
	case 1:
		handleFriendMenu(menuWidth);
		break;
	case 2:
		handleGroupMenu(menuWidth);
		break;
	case 3:
		handlePersonalInfoMenu(menuWidth);
		break;
	case 4:
		handleServiceMenu(menuWidth);
		break;
	case 5:
		ShowUserLog(qqnumber);
		break;
	case 0:
		Menu();
		return;
	default:
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::handleFriendMenu(int menuWidth)
{
	system("cls");
	ShowFriends();
	displayFriendMenu(menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 6);

	switch (select)
	{
	case 1:
		AddFriend();
		break;
	case 2:
		DeleteFriend();
		break;
	case 3:
		ChangeFriendRemarks();
		break;
	case 4:
		ShowFriendInformation();
		break;
	case 5:
		 AgreeFriend();
		break;
	case 6:
		AddWeiChatCommonFriend();
		break;
	case 0:
		QQMenu();
		return;
	default:
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::displayFriendMenu(int menuWidth)
{
	cout << "         �û�: " << qqnumber << endl;
	printCentered("|*--------------���ѹ���----------------*|", menuWidth);
	printCentered("|*          1.��Ӻ���                  *|", menuWidth);
	printCentered("|*          2.ɾ����                    *|", menuWidth);
	printCentered("|*          3.�޸ĺ��ѱ�ע              *|", menuWidth);
	printCentered("|*          4.�鿴���Ѿ�����Ϣ          *|", menuWidth);
	printCentered("|*          5.�鿴��������              *|", menuWidth);
	printCentered("|*          6.΢�����Ӻ��ѣ����ӹ��ܣ�  *|", menuWidth);
	printCentered("|*          0.������һ��                *|", menuWidth);
	printCentered("|*--------------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handleGroupMenu(int menuWidth)
{
	system("cls");
	displayGroupMenu(menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int Grouptype = judge_count_menu(temp, 1);

	switch (Grouptype)
	{
	case 0:
		handleQQGroupMenu(menuWidth);
		break;
	case 1:
		handleWeChatGroupMenu(menuWidth);
		break;
	default:
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::displayGroupMenu(int menuWidth)
{
	cout << "         �û�: " << qqnumber << endl;
	printCentered("|*----------------Ⱥ������-------------*|", menuWidth);
	printCentered("|*              0.QQ����Ⱥ               *|", menuWidth);
	printCentered("|*              1.΢������Ⱥ             *|", menuWidth);
	printCentered("|*       random_input������һ��      *|", menuWidth);
	printCentered("|*---------------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handleQQGroupMenu(int menuWidth)
{
	system("cls");
	ShowQQGroup();
	displayQQGroupMenu(menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 10);

	switch (select)
	{
	case 1:
		AddInGroupMember();
		break;
	case 2:
		QuitGroup();
		break;
	case 3:
		CreatQQgroup();
		break;
	case 4:
		InviteGroupMember();
		break;
	case 5:
		AddGroupAdmin();
		break;
	case 6:
		AgreeMember();
		break;
	case 7:
		DeleteGroupMember();
		break;
	case 8:
		CreatTemporaryGroup();
		break;
	case 9:

		JoinTemporaryGroup();
		break;
	case 10:	
		ShowGroupInformation();

		break;
	case 0:
		QQMenu();
		return;
	default:
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::displayQQGroupMenu(int menuWidth)
{
	cout << "         �û�: " << qqnumber << endl;
	printCentered("|*----------��ѡ��ʹ�õ�Ⱥ����----------*|", menuWidth);
	printCentered("|* status:(1)Ⱥ��Ա                     *|", menuWidth);
	printCentered("|*            1.����Ⱥ��                *|", menuWidth);
	printCentered("|*            2.�˳�Ⱥ��                *|", menuWidth);
	printCentered("|* status:(2)Ⱥ��                       *|", menuWidth);
	printCentered("|*            3.����Ⱥ                  *|", menuWidth);
	printCentered("|* status:(3)Ⱥ����Ա                   *|", menuWidth);
	printCentered("|*            4.�����Ⱥ                *|", menuWidth);
	printCentered("|*            5.���Ⱥ����Ա            *|", menuWidth);
	printCentered("|*            6.�鿴��Ⱥ����            *|", menuWidth);
	printCentered("|*            7.ɾ��Ⱥ��Ա              *|", menuWidth);
	printCentered("|* ---------- ��link)���⹦�� ------------ *|", menuWidth);
	printCentered("|*            8.������ʱ������          *|", menuWidth);
	printCentered("|*            9.������ʱ������         *|", menuWidth);
	printCentered("|*            10.����Ⱥ��Ա             *|", menuWidth);
	printCentered("|*            0.������һ��          *|", menuWidth);
	printCentered("|*--------------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handleWeChatGroupMenu(int menuWidth)
{
	system("cls");
	ShowQQGroup();
	displayWeChatGroupMenu(menuWidth);
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	int select = judge_count_menu(tempstr, 5);

	switch (select)
	{
	case 1:
		 QuitGroup();
		break;
	case 2:
		CreatQQgroup();
		break;
	case 3:
		InviteGroupMember();
		break;
	case 4:
		DeleteGroupMember();
		break;
	case 5:
		ShowGroupInformation();
		break;
	default:
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::displayWeChatGroupMenu(int menuWidth)
{
	cout << "         �û�: " << qqnumber << endl;
	printCentered("|*--------��ѡ��ʹ�õ�Ⱥ����--------*|", menuWidth);
	printCentered("|*          1.��Ⱥ                 *|", menuWidth);
	printCentered("|* status:Ⱥ��                     *|", menuWidth);
	printCentered("|*          2.����Ⱥ                 *|", menuWidth);
	printCentered("|*          3.�����Ⱥ              *|", menuWidth);
	printCentered("|*          4.�߳�Ⱥ��Ա            *|", menuWidth);
	printCentered("|*          5.�鿴Ⱥ��Ա��Ϣ        *|", menuWidth);
	printCentered("|*          0.������һ��           *|", menuWidth);
	printCentered("|*----------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handlePersonalInfoMenu(int menuWidth)
{
	
	displayViewPersonalInfoMenu(menuWidth);
}

void QQChatBase_Qfh::displayViewPersonalInfoMenu(int menuWidth)
{
	cout << "         �û�: " << qqnumber << endl;
	ShowMyInformation();
	printCentered("|*--------������Ϣ-------*|", menuWidth);
	printCentered("|* 1.�޸ĸ�����Ϣ        *|", menuWidth);
	printCentered("|* 0.������һ��          *|", menuWidth);
	printCentered("|*-----------------------*|", menuWidth);
	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 1);
	switch (select)
	{
	case 1:
		handleModifyPersonalInfoMenu(menuWidth);
		break;
	default:
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::handleModifyPersonalInfoMenu(int menuWidth)
{
	
	displayModifyPersonalInfoMenu(menuWidth);
}

void QQChatBase_Qfh::displayModifyPersonalInfoMenu(int menuWidth)
{
	cout << "         �û�: " << qqnumber << endl;
	printCentered("|*------------�޸ĸ�����Ϣ--------------*|", menuWidth);
	printCentered("|*           1.�޸�����                 *|", menuWidth);
	printCentered("|*           2.�޸�����                 *|", menuWidth);
	printCentered("|*           3.�޸�ǩ��                 *|", menuWidth);
	printCentered("|*           4.�޸�IP��ַ               *|", menuWidth);
	printCentered("|*           0.������һ��               *|", menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 4);

	switch (select)
	{
	case 1:
		Change_PassWord();
		break;
	case 2:
		Change_Name();
		break;
	case 3:
		Change_AutoGraph();
		break;
	case 4:
		Change_Area();
		break;
	default:
		QQMenu();
		return;
	}
}


void QQChatBase_Qfh::handleServiceMenu(int menuWidth)
{
	system("cls");
	displayServiceMenu(menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 4);

	switch (select)
	{
	case 1:
		CreateWeChat();
		break;
	case 2:
		LinkWeiChat(); // ��΢�ŵ���link
		break;
	case 3:
		UnlinkWeiChat();
		break;
	case 4:
		CreateWeiBo();
		return;
	case 0:
		QQMenu();
		return;
	default:
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::displayServiceMenu(int menuWidth)
{
	cout << "         �û�: " << qqnumber << endl;
	printCentered("|*------------��link�ã�������----------*|", menuWidth);
	printCentered("|*             1.QQ����΢��               *|", menuWidth);
	printCentered("|*             2.QQ����΢��               *|", menuWidth);
	printCentered("|*             3.QQ���΢��               *|", menuWidth);
	printCentered("|*             4.QQ����΢��               *|", menuWidth);
	printCentered("|*             5.QQ����΢��               *|", menuWidth);
	printCentered("|*             6.QQ���΢��               *|", menuWidth);
	printCentered("|*             0.������һ��               *|", menuWidth);
	printCentered("|*----------------------------------------*|", menuWidth);
}

/*���ѹ���*/

void QQChatBase_Qfh::AddFriend()
{
	system("CLS");
	int sub = 0;
	int subfriend;
	string id;
	string name, subname;
	bool flag = false;
	cout << "��������Ӻ��ѵ�QQ��" << endl;
	cin >> id;
	judge_flush(stdin);

	// ����Ƿ�����Լ�Ϊ����
	if (id == qqnumber)
	{
		cout << "����������Լ�Ϊ����" << endl;
		cout << "�������������һҳ" << endl;
		if (getchar() != EOF)
			handleFriendMenu(130);
		return;
	}

	// ���ҵ�ǰ�û�
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			subname = QQ[i]->Return_Name();
			break;
		}
	}

	// �������б����Ƿ��Ѵ��ڸú���
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if (id == QQ[sub]->Return_Friend_List()[i]->Return_ID())
		{
			cout << "������Ӵ˺���,�밴�����������һҳ" << endl;
			if (getchar() != EOF)
				handleFriendMenu(130);
			return;
		}
	}

	// ����Ҫ��ӵ�QQ��
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == id)
		{
			flag = true;
			subfriend = i;
			name = QQ[i]->Return_Name();
			// ����Ƿ��Ѿ�������������
			bool requestExists = false;
			for (int j = 0; j < QQ[sub]->Return_Friend_List().size(); j++)
			{
				if (QQ[sub]->Return_Friend_List()[j]->Return_ID() == "&" + id)
				{
					requestExists = true;
					break;
				}
			}
			if (requestExists)
			{
				cout << "���Ѿ����QQ���͹��������룬��ȴ��Է�ȷ�ϡ�" << endl;
				cout << "�������������һҳ" << endl;
				if (getchar() != EOF)
					handleFriendMenu(130);
				return;
			}
			cout << "���ͺ�������ɹ�����ȴ��Է�ȷ��" << endl;
		}
	}

	// ���QQ��δע��
	if (!flag)
	{
		cout << "��QQ��û��ע�ᣬ���������������QQ��" << endl;
		cout << "1.��������QQ����Ӻ���" << endl;
		cout << "0.������һҳ" << endl;
		int select;
		string temp;
		cin >> temp;
		judge_flush(stdin);
		select = judge_count_menu(temp, 1);
		switch (select)
		{
		case 1:
			AddFriend();
			return;
		case 0:
			handleFriendMenu(130);
			return;
		default:
			handleFriendMenu(130);
			return;
		}
	}

	// ��¼��������
	string mark = "&";
	string ID = mark + id;
	fstream file;
	string friendfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string remarks = "δ��ע";
	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	file.open(friendfilename, ios::app);
	file << ID << endl;
	file << name << endl;
	file << remarks << endl;
	file << " " << endl; // �����жϼ�������
	file.close();

	// �����QQ�ļ�����ӱ�QQ
	friendfilename = "QQ\\" + id + "\\" + id + "Friendlist.txt";
	subname = "$" + subname;
	QQ[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subname, qqnumber));
	file.open(friendfilename, ios::app);
	file << "$" << QQ[sub]->Return_ID() << endl;
	file << QQ[sub]->Return_Name() << endl;
	file << remarks << endl;
	file << " " << endl; // �����жϼ�������
	file.close();
	LogOperation("������������Է�QQ��Ϊ��" + QQ[sub]->Return_ID(), qqnumber);

	cout << "�������������һҳ" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;
}


void QQChatBase_Qfh::DeleteFriend()
{
	system("CLS");
	//��ʾ���к���
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}//�ҵ���ǰ��QQ����
	cout << "�����б����£�" << endl;
	for (int i = 0; i < QQ[sub]->Return_Friend_Number(); i++)
	{
		if (QQ[sub]->Return_Friend_List()[i]->ReturnFriendName()[0] == '$' || QQ[sub]->Return_Friend_List()[i]->ReturnFriendName()[i] == '&')
			continue;
		cout << "QQ:" << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "����:" << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		
		cout << "��ע��" << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		cout << endl;
	}

	//ɾ����QQ�еĺ���
	string delq;
	cout << "��������ɾ�����ѵ�QQ�ţ�������#������һҳ" << endl;
	cin >> delq;
	judge_flush(stdin);
	if (delq == "#")
	{
		handleFriendMenu(130);
		return;
	}
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}
	bool flag = false;
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if (QQ[sub]->Return_Friend_List()[i]->Return_ID() == delq)
		{
			flag = true;
			break;
		}
	}
	if (flag == false)
	{
		cout << "��û�д˺���" << endl;
		cout << "1.��������QQ��" << endl;
		cout << "0.������һҳ" << endl;
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
			handleFriendMenu(130);
			return;
		}

	}
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}
	int num = QQ[sub]->Return_Friend_List().size();
	for (int i = 0; i < num; i++)
	{
		if (QQ[sub]->Return_Friend_List()[i]->Return_ID() == delq)
		{
			QQ[sub]->Return_Friend_List().erase(QQ[sub]->Return_Friend_List().begin() + i);
			QQ[sub]->Change_Friends_Number(num - 1);
			break;
		}
	}
	int friendqq;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == delq)
		{
			friendqq = i;
			break;
		}
	}
	num = QQ[friendqq]->Return_Friend_List().size();
	for (int i = 0; i < num; i++)
	{
		if (QQ[friendqq]->Return_Friend_List()[i]->Return_ID() == qqnumber)
		{
			QQ[friendqq]->Return_Friend_List().erase(QQ[friendqq]->Return_Friend_List().begin() + i);
			QQ[friendqq]->Change_Friends_Number(num - 1);
			break;
		}
	}
	//ɾ����QQ�еĺ���QQ,���ļ�
	ofstream subfile, outfile;
	string temp1;
	string content1;
	string subfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string friendqqfilename = "QQ\\" + delq + "\\" + delq + "Friendlist.txt";
	subfile.open(subfilename, ios::ate);
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if (i > 0)
			subfile << endl;
		subfile << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		subfile << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		subfile << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		subfile << " ";
	}
	subfile.close();
	outfile.open(friendqqfilename, ios::ate);
	for (int i = 0; i < QQ[friendqq]->Return_Friend_List().size(); i++)
	{
		if (i > 0)
			subfile << endl;
		subfile << QQ[friendqq]->Return_Friend_List()[i]->Return_ID() << endl;
		subfile << QQ[friendqq]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		subfile << QQ[friendqq]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		subfile << " ";
	}
	outfile.close();
	cout << "ɾ�����ѳɹ�" << endl;
	LogOperation("ɾ�����ѣ�����QQ��Ϊ��"+delq, qqnumber);
	cout << "�������������һҳ" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;
}
//ɾ������(Bug:ɾ�����Ѻ�����б�����)
void QQChatBase_Qfh::SortFriendList() {
	int sub = FindQQIndex(qqnumber);
	if (sub == -1) {
		cout << "�޷��ҵ���ǰ�û��ĺ����б�" << endl;
		return;
	}

	auto& friendList = QQ[sub]->Return_Friend_List();
	sort(friendList.begin(), friendList.end(), CompareFriends);
}
void QQChatBase_Qfh::ShowFriends(){
	SortFriendList();
	// ��ʾ������Ϣ
	int sub = FindQQIndex(qqnumber);
	if (sub == -1) {
		cout << "δ�ҵ���ǰ�û��ĺ����б�" << endl;
		return;
	}

	auto& friendList = QQ[sub]->Return_Friend_List();

	// ��ʾ������Ϣ
	for (const auto& friendObj : friendList) {
		if (friendObj->Return_ID()[0] == '&'|| friendObj->Return_ID()[0] == '$') continue; // ��������ǵĺ���
		cout << "��������: " << friendObj->ReturnFriendName() << endl;
		cout << "QQ��: " << friendObj->Return_ID() << endl;
		cout << "��ע: " << friendObj->ReturnRemarks() << endl;
		cout << endl;
	}
}

void QQChatBase_Qfh::AgreeFriend()
{
	system("CLS");
	fstream subfile;
	string subfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string friendqqfilename;
	subfile.open(subfilename);
	int sub, friendqq;
	string qq;
	vector<string> temp;
	string tempf;
	string fdqq;

	string name, id;

	char c;
	int line = 0;
	bool flag = false;
	while (subfile.get(c))//��ȡ������QQ
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
		cout << "�������������һҳ" << endl;
		if (getchar() != EOF)
			handleFriendMenu(130);
		return;
	}
	subfile.close();
	for (int i = 0; i < temp.size(); i++) {
		fdqq = temp[i];
		friendqqfilename = "QQ\\" + fdqq + "\\" + fdqq + "Friendlist.txt";
		cout << "���Ƿ�ͬ��" << temp[i] << "�ĺ�������?" << endl;
		LogOperation("�鿴��������,����QQ��Ϊ" + fdqq, qqnumber);
		cout << "1.ͬ��" << endl;
		cout << "0.�ܾ�" << endl;
		string FriendApplyQQ = temp[i];
		int select;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 1);
		string content;
		string msg;
		fstream friendqqfile;
		int n = 0;
		int linefriend = 0;
		string contentfriend;
		string msgfriend;
		string Aceptemp;
		vector<string> Aception;
		string friendacepttemp;
		vector<string> friendaceptcontent;
		switch (select)
		{
		case 1:
			subfile.open(subfilename);
			while (!subfile.eof())
			{

				getline(subfile, Aceptemp);
				Aception.push_back(Aceptemp);
			}
			Aception.pop_back();//��һ������
			for (int i = 0; i < Aception.size(); i++)
			{
				if (Aception[i] == ("$" + FriendApplyQQ))
				{
					Aception[i] = FriendApplyQQ;//�����к��ѱ�ǵı��ȥ��
				}
			}
			subfile.close();
			subfile.open(subfilename, ios::out | ios::trunc); //���ԭ���ļ�����
			for (int i = 0; i < Aception.size(); i++)//����д��
			{
				subfile << Aception[i] << endl;
			}
			subfile.close();
			friendqqfile.open(friendqqfilename);
			while (!friendqqfile.eof())//��ȡ�����ļ�����
			{
				getline(friendqqfile, friendacepttemp);
				friendaceptcontent.push_back(friendacepttemp);
			}
			friendaceptcontent.pop_back();
			for (int i = 0; i < friendaceptcontent.size(); i++)
			{
				if (friendaceptcontent[i] == ("&" + qqnumber))
				{
					friendaceptcontent[i] = qqnumber;
				}
			}
			friendqqfile.close();

			friendqqfile.open(friendqqfilename, ios::out | ios::trunc);//��պ����ļ�����
			for (int i = 0; i < friendaceptcontent.size(); i++)
			{
				friendqqfile << friendaceptcontent[i] << endl;
			}
			friendqqfile.close();

			for (int i = 0; i < QQ.size(); i++)
			{
				if (QQ[i]->Return_ID() == qqnumber)
				{
					sub = i;
				}
			}
			for (int i = 0; i < QQ.size(); i++)
			{
				if (QQ[i]->Return_ID() == fdqq)
				{
					friendqq = i;
				}
			}
			name = QQ[friendqq]->Return_Name();
			id = QQ[friendqq]->Return_ID();
			QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, id));
			QQ[sub]->Change_Friends_Number(QQ[sub]->Return_Friend_Number() + 1);
			QQ[friendqq]->Return_Friend_List().push_back(new QQFriends_Qfh(QQ[sub]->Return_Name(), qqnumber));
			QQ[friendqq]->Change_Friends_Number(QQ[friendqq]->Return_Friend_Number() + 1);
			friendqqfile.close();
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
				if (subfilecontent[i] == ("$" + FriendApplyQQ))
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

			for (int i = 0; i < size(subfilecontent); i++)
			{
				subfile << subfilecontent[i] << endl;
			}
			subfile.close();

			//ɾ�������ļ��е�QQ
			friendqqfile.open(friendqqfilename);
			string friendfiletemp;
			vector<string> friendfilecontent;
			while (!friendqqfile.eof())
			{
				getline(friendqqfile, friendfiletemp);
				friendfilecontent.push_back(friendfiletemp);
			}
			friendfilecontent.pop_back();
			friendqqfile.close();
			for (int i = 0; i < friendfilecontent.size(); i++)
			{
				if (friendfilecontent[i] == ("&" + qqnumber))
				{
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);//ͬ��
				}
			}
			friendfilecontent.shrink_to_fit();//��������������������sizeƥ��

			friendqqfile.open(friendqqfilename, ios::out, ios::trunc);//���ԭ������

			for (int i = 0; i < friendfilecontent.size(); i++)
			{
				friendqqfile << friendfilecontent[i] << endl;
			}
			friendqqfile.close();
			if (getchar() != EOF)
				break;
		}
		default:
			handleFriendMenu(130);
			return;
		}
	}
	cout << "���е����봦����ϣ������������QQ���˵�" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;
}


// ����ͬ�����������߼�
void QQChatBase_Qfh::ProcessAgreeFriend(const string& fdqq, const string& friendqqfilename) {
	// ���ȣ��ҵ���ǰ�û��ĺ����б��±�
	int sub = FindQQIndex(qqnumber);
	int subfriend=FindQQIndex(fdqq);
	if (sub == -1 || subfriend == -1) {
		cout << "δ�ҵ���ǰ�û���Ŀ���û����޷������������" << endl;
		return;
	}

	// ���µ�ǰ�û��ĺ����б�
	string mark = "&";
	string ID = mark + fdqq; // ���ڱ�ʶ�ú��ѵ�ID
	string name; // Ŀ���û�������

	// �Ӻ����б����ҳ�Ŀ����ѵ���Ϣ
	for (const auto& friendObj : QQ[sub]->Return_Friend_List()) {
		if (friendObj->Return_ID() == ID) {
			name = friendObj->ReturnFriendName();
			break;
		}
	}
	string subfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	// ���ȣ���ȡ��ǰ�û��ĺ��������ļ�����ɾ����ͬ�������
	fstream subfile;
	subfile.open(friendqqfilename, ios::in);
	vector<string> lines;
	string line;

	// ��ȡ������������
	while (getline(subfile, line)) {
		if (line.find("$" + fdqq) == string::npos) { // �������Ҫͬ������룬����
			lines.push_back(line);
		}
	}
	subfile.close();

	// ����д���ļ����ų���ͬ�������
	subfile.open(friendqqfilename, ios::out | ios::trunc);
	for (const auto& l : lines) {
		subfile << l << endl;
	}
	subfile.close();

	// Ȼ���º�����ӵ������б�
	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, fdqq));
	// ���¶Է��ĺ����ļ�
	fstream file;
	string remarks = "δ��ע";
    file.open(friendqqfilename, ios::app);
	string friendfilename = "QQ\\" + fdqq + "\\" + fdqq + "Friendlist.txt";
	QQ[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(QQ[subfriend]->Return_Name(), qqnumber));

	// ��󣬸��µ�ǰ�û��ĺ��������ļ���ɾ����ͬ�������
	lines.clear();
	while (getline(subfile, line)) {
		if (line.find("$" + fdqq) == string::npos) { // �������Ҫͬ������룬����
			lines.push_back(line);
		}
	}
	subfile.close();

	// ����д���ļ����ų���ͬ�������
	subfile.open(subfilename, ios::out | ios::trunc);
	for (const auto& l : lines) {
		subfile << l << endl;
	}
	subfile.close();
	file.close();

	cout << "�ѳɹ����" << fdqq << "Ϊ���ѡ�" << endl;
}

// ����ܾ�����������߼�
void QQChatBase_Qfh::ProcessRejectFriend(const string& fdqq, const string& subfilename, const string& friendqqfilename) {
	// ���û��ĺ��������ļ���ɾ����ص�������Ϣ
	fstream subfile;
	subfile.open(subfilename, ios::in);
	vector<string> lines;
	string line;

	// ��ȡ������������
	while (getline(subfile, line)) {
		if (line.find("$" + fdqq) == string::npos) { // �������Ҫ�ܾ������룬����
			lines.push_back(line);
		}
	}
	subfile.close();

	// ����д���ļ����ų��Ѿܾ�������
	subfile.open(subfilename, ios::out | ios::trunc);
	for (const auto& l : lines) {
		subfile << l << endl;
	}
	subfile.close();

	cout << "�Ѿܾ�" << fdqq << "�ĺ������롣" << endl;
}


void QQChatBase_Qfh::Get_Friends()
{
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}
	QQ[sub]->Get_Friends();
	return;
}
// ���º��������ļ�
// ɾ����������
void QQChatBase_Qfh::RemoveFriendApplication(const string& filename, const string& applicantID) {
	ifstream file(filename);
	vector<string> lines;
	string line;

	while (getline(file, line)) {
		if (line != ('&'+ applicantID)) {
			lines.push_back(line);
		}
	}
	file.close();

	ofstream outFile(filename);
	for (const auto& l : lines) {
		outFile << l << endl;
	}
	outFile.close();
}



//������
void QQChatBase_Qfh::ShowFriendNoReturn()
{
	int friendsnum;
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	friendsnum = QQ[sub]->Return_Friend_List().size();
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&'|| (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//�ж���Ӻ��ѱ��
		{
			friendsnum--;
		}
	}

	cout << "����" << friendsnum << "������" << endl;
	int friends = 0;
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&'|| (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
		{
			continue;
		}
		cout << "��" << friends + 1 << "λ����" << endl;
		cout << "�ǳ�:" << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "QQ:" << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "��ע:" << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		cout << endl;
		friends++;
	}
}
//չʾ���Ѿ�����Ϣ
void QQChatBase_Qfh::ShowFriendInformation()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "�����������ѯ�ĺ���QQ�ţ�������#������һ��" << endl;
	string FriendQQ;
	cin >> FriendQQ;
	judge_flush(stdin);
	int sub;
	if (FriendQQ == "#")
	{
		handleFriendMenu(130);
		return;
	}

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}

	bool FriendCheckFlag = false;
	while (1)
	{
		for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
		{
			if (QQ[sub]->Return_Friend_List()[i]->Return_ID() == FriendQQ)
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
			cout << "��û������ѣ����������������#������һ��" << endl;
			cin >> FriendQQ;
			judge_flush(stdin);
			if (FriendQQ == "#")
			{
				handleFriendMenu(130);
				return;
			}
			else
			{
				continue;
			}
		}
	}
	int friendsub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == FriendQQ)
		{
			friendsub = i;
		}
	}

	int friendremarks;
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if (QQ[sub]->Return_Friend_List()[i]->Return_ID() == FriendQQ)
		{
			friendremarks = i;
		}
	}

	cout << "����Ϊ��Ϊ������Ϣ" << endl;
	cout << "�ʺ�:" << QQ[friendsub]->Return_ID() << endl;
	cout << "����:" << QQ[friendsub]->Return_Name() << endl;
	cout << "��ע:" << QQ[sub]->Return_Friend_List()[friendremarks]->ReturnRemarks() << endl;//��ע������ӡ����ֱ��ͨ��QQ������ȡ
	cout << "�Ա�" << QQ[sub]->Return_Sex() << endl;
	cout << "����ǩ��:" << QQ[friendsub]->Return_Autograph() << endl;
	cout << "���ڵ���:" << QQ[friendsub]->Return_Area() << endl;
	cout << "�û�������:" << QQ[friendsub]->Return_bir() << endl;
	cout << "ע��ʱ��:" << QQ[friendsub]->Return_ApplyDate() << endl;
	calculateAge(QQ[friendsub]->Return_ApplyDate());
	cout << endl;
	LogOperation("�鿴���Ѿ�����Ϣ,����QQ��Ϊ"+FriendQQ, qqnumber);
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;

}
//�ı���ѱ�ע
void QQChatBase_Qfh::ChangeFriendRemarks()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "�����������޸ĵĺ���QQ�ţ�������#������һ��" << endl;
	string FriendQQ;
	cin >> FriendQQ;
	judge_flush(stdin);
	int sub;
	if (FriendQQ == "#")
	{
		handleFriendMenu(130);
		return;
	}

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	bool FriendCheckFlag = false;
	while (1)
	{
		for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
		{
			if (QQ[sub]->Return_Friend_List()[i]->Return_ID() == FriendQQ)
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
			cout << "��û����Ϊ���ѣ����������������#������һ��" << endl;
			cin >> FriendQQ;
			judge_flush(stdin);
			if (FriendQQ == "#")
			{
				handleFriendMenu(130);
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
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if (QQ[sub]->Return_Friend_List()[i]->Return_ID() == FriendQQ)
		{
			friendid = i;
			break;
		}
	}

	QQ[sub]->Return_Friend_List()[friendid]->ChangeRemarks(NewRemarks);
	SaveChange();
	cout << "�޸ı�ע�ɹ�" << endl;
	LogOperation("�޸ĺ��ѱ�ע�����ѱ�עΪ��" + NewRemarks, qqnumber);
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;

}


/*                      
* ���ܣ�QQȺ
	*/

//����QQȺ
void QQChatBase_Qfh::CreatQQgroup()
{
	system("CLS");
	int sub = -1;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;

		}
	}
	time_t ti;
	srand((unsigned)time(&ti));//��ǰʱ��Ϊ����
	int temp = QQ[sub]->Return_Group_Number()+1;//���Ⱥ��
	stringstream ss;
	ss << temp;
	string ID;
	ss >> ID;

	cout << "������Ⱥ����: " << endl;
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "����Ⱥ��Ϊ:" << ID << endl;
	QQgroup = ID;
	//�ҵ����ѭ��
	QQ[sub]->Return_group_List().push_back(new QQgroups_Qfh(ID, name, qqnumber));
	QQ[sub]->Change_group_num(QQ[sub]->Return_Group_Number() + 1);
	SaveQQGroup();
	//дȺ�ŵ�Ⱥ�ļ�
	string qq = qqnumber;
	string txt1 = "Groupslist.txt";
	string groupListPath = "QQ\\" + qqnumber + "\\" + qqnumber + "Groupslist.txt";
	ofstream FILE(groupListPath, ios::app);
	FILE << ID << endl;
	//�����б�д��
	fstream GroupListFile;
	string GroupListFileName = "Groupslist.txt";
	GroupListFile.open(GroupListFileName, ios::app);
	GroupListFile << ID << endl;

	GroupListFile.close();
	cout << "�����ɹ�" << endl;
	LogOperation("����QQȺ��Ⱥ��Ϊ��" + ID, qqnumber);
    cout << "�������������һҳ" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
}
//��Ⱥ
void QQChatBase_Qfh::QuitGroup()
{
	bool flag = false;
	string groupid;
	cout << "�����������˳���QQȺ" << endl;
	cin >> groupid;
	judge_flush(stdin);
	int sub = -1;
	//����������ΪȺ
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}
	if (sub == -1)return;
	//����û��Ƿ��ڸ�Ⱥ
	for (const auto& group : QQ[sub]->Return_group_List())
	{
		if (group->Return_Group_ID() == groupid)
		{
			flag = true;
			break;
		}
	}

	if (flag == false)
	{
		cout << "��û�м�����ΪȺ" << endl;
		cout << "��ѡ����������򷵻ز˵�" << endl;
		cout << "1.��������QQȺ" << endl;
		cout << "0.���ز˵�" << endl;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		int select = judge_count_menu(tempstr, 1);
		switch (select)
		{
		case 1:
			QuitGroup();
			break;
		case 0:
			handleQQGroupMenu(130);
			return;
		default:
			handleQQGroupMenu(130);
			return;
		}
	}
	LogOperation("�˳�QQȺ��Ⱥ��Ϊ��" + groupid, qqnumber);
	// ɾ��Ⱥ�б��еĸ�Ⱥ
	string subgrouplistfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Groupslist.txt";
	removeGroupFromFile(subgrouplistfilename, groupid);

	// ��Ⱥ��Ա�ļ���ɾ����ǰ�û�
	string groupfilename = "QQ\\Groups\\" + groupid + "\\" + groupid + ".txt";
	removeUserFromGroupFile(groupfilename, qqnumber);

	// �ӹ���Ա�ļ���ɾ����ǰ�û�
	string groupadminfilename = "QQ\\Groups\\" + groupid + "\\" + groupid + "admin.txt";
	removeUserFromAdminFile(groupadminfilename, qqnumber, groupid);
	return;
}
//���Ⱥ����Ա
void QQChatBase_Qfh::AddGroupAdmin()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "������Ҫ�����Ⱥ��" << endl;

	string id;
	getline(cin, id);

	string filename = "QQ\\Groups\\" + id + "\\" + id + ".txt";
	ifstream infile(filename, ios::in);

	if (!infile) {
		ShowMenu("û����ΪȺ,����������򷵻���ҳ", { "1.��������", "0.������ҳ" });
		string tempstr;
		getline(cin, tempstr);
		int select = judge_count_menu(tempstr, 1);
		HandleMenuSelection(select);
		return;
	}
	infile.close();

	fstream outfile(filename);
	string temp;
	int line = 0;
	char c;
	while (outfile.get(c)) {
		if (c == '\n') {
			line++;
			continue;
		}
		if (line == 2) { // ��ȡȺ��QQ��
			temp.push_back(c);
		}
	}
	outfile.close();

	if (temp != qqnumber) { // ����Ⱥ���޷���������Ա
		cout << "�����Ǹ�Ⱥ��Ⱥ��,�޷�ʹ�ô˹���" << endl;
		cout << "�������������һ��" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);;
		return;
	}

	// ��ȡȺ��Ա
	vector<string> GroupMember;
	outfile.open(filename);
	line = 0;
	temp.clear();
	while (getline(outfile, temp)) {
		if (temp == "*") {
			line++;
			continue;
		}
		if (line == 1) {
			GroupMember.push_back(temp);
		}
	}
	outfile.close();

	if (GroupMember.empty()) {
		cout << "��Ⱥû�г�Ա���������������һ��" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);;
		return;
	}

	string adminfilename = "QQ\\Groups\\" + id + "\\" + id + "admin.txt";
	fstream adminfile(adminfilename, ios::app);
	Show_Group_InformationNo_Return(id);
	cout << "������������ӵĹ���ԱQQ" << endl;
	string adminid;
	getline(cin, adminid);
	judge_flush(stdin);

	bool flag = false;
	for (const auto& member : GroupMember) {
		if (member == adminid) {
			flag = true;
			break;
		}
	}

	if (!flag) {
		cout << "��Ⱥû����Ϊ��Ա����������" << endl;
		AddGroupAdmin();
		return;
	}

	int sub = 0;
	for (int i = 0; i < QQ.size(); i++) {
		if (QQ[i]->Return_ID() == qqnumber) {
			sub = i;
		}
	}

	int Thisgroup = 0;
	for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++) {
		if (QQ[sub]->Return_group_List()[i]->Return_Group_Name() == id) {
			Thisgroup = i;
			break;
		}
	}

	for (int i = 0; i < QQ[sub]->Return_group_List()[Thisgroup]->Return_Admins_ID().size(); i++) {
		if (QQ[sub]->Return_group_List()[Thisgroup]->Return_Admins_ID()[i] == adminid) {
			ShowMenu("�ó�Ա�Ѿ��ǹ���Ա���Ƿ����ɾ��", { "1.ɾ��", "0.�������˵�" });
			string tempstr;
			getline(cin, tempstr);
			judge_flush(stdin);
			int select = judge_count_menu(tempstr, 1);
			if (select == 0) {
				if (getchar() != EOF)
					handleQQGroupMenu(130);;
				return;
			}
			if (select == 1) {
				QQ[sub]->Return_group_List()[Thisgroup]->Return_Admins_ID().erase(QQ[sub]->Return_group_List()[Thisgroup]->Return_Admins_ID().begin() + i);
				adminfile.open(adminfilename, ios::trunc | ios::out);
				for (const auto& admin : QQ[sub]->Return_group_List()[Thisgroup]->Return_Admins_ID()) {
					adminfile << admin << endl;
				}
				cout << "ɾ������Ա�ɹ�,�����������" << endl;
				if (getchar() != EOF)
					handleQQGroupMenu(130);;
				return;
			}
		}
	}

	adminfile << adminid << endl;
	adminfile.close();
	LogOperation("���Ⱥ����Ա��Ⱥ��Ϊ��" + id + "������ԱQQ��Ϊ��" + adminid, qqnumber);
	cout << "��ӳɹ����������������һҳ" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
}
//����Ⱥ��Ա
void QQChatBase_Qfh::SaveQQGroup() //ÿ����һ��Ⱥ�㽫��Ⱥ�����һ��.txt�ļ�
{
	system("CLS");
	int i = 0, sub, n;
	string ID;
	ID = QQgroup;
	string txt = ".txt";
	string DirectoryName = "QQ\\Groups\\" + ID;
	CreateDirectory(DirectoryName.c_str(), NULL);
	string GroupID = "QQ\\Groups\\" + ID + "\\" + ID + ".txt";
	fstream file;
	file.open(GroupID, ios::app);
	for (i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	//ȺID
	//Ⱥ����
	//Ⱥ��ID
	// *
	//Ⱥ��Ա
	n = QQ[sub]->Return_group_List().size();
	file << QQ[sub]->Return_group_List()[n - 1]->Return_Group_ID() << endl;
	file << QQ[sub]->Return_group_List()[n - 1]->Return_Group_Name() << endl;
	file << QQ[sub]->Return_group_List()[n - 1]->ReturnCreatUserID() << endl;
	file << "*" << endl;
	file.close();
}
//������Ⱥ
void QQChatBase_Qfh::InviteGroupMember()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "��������Ҫ������ѽ���Ⱥ��" << endl;
	string invitegroup;
	cin >> invitegroup;
	judge_flush(stdin);

	int sub = -1;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	if (sub == -1)
	{
		cout << "δ�ҵ������˺���Ϣ�������µ�¼��" << endl;
		handleQQGroupMenu(130);
		return;
	}

	int ThisGroup = -1;
	while (ThisGroup == -1)
	{
		ThisGroup = FindGroup(invitegroup, sub);
		if (ThisGroup == -1)
		{
			cout << "��û�м�����ΪȺ�����������������#����" << endl;
			cin >> invitegroup;
			judge_flush(stdin);
			if (invitegroup == "#")
			{
				handleQQGroupMenu(130);
				return;
			}
		}
	}

	ShowFriendNoReturn();
	cout << "��������Ҫ����ĺ���QQ��" << endl;
	string invitefriend;
	cin >> invitefriend;
	judge_flush(stdin);

	while (!IsFriend(invitefriend, sub))
	{
		cout << "��û����Ϊ���ѣ�����������(������#����)" << endl;
		cin >> invitefriend;
		judge_flush(stdin);
		if (invitefriend == "#")
		{
			handleQQGroupMenu(130);
			return;
		}
	}

	while (IsMemberInGroup(invitefriend, ThisGroup, sub))
	{
		cout << "�ú������ڸ�Ⱥ��,�������������QQ�Ż�����#����" << endl;
		cin >> invitefriend;
		judge_flush(stdin);
		if (invitefriend == "#")
		{
			handleQQGroupMenu(130);
			return;
		}
	}

	AddMemberToGroup(invitegroup, invitefriend);
	cout << "������ѽ�Ⱥ�ɹ�" << endl;
	LogOperation("������ѽ�Ⱥ��Ⱥ��Ϊ��" + invitegroup + "������QQ��Ϊ��" + invitefriend, qqnumber);
	cout << "�����������������ѽ�Ⱥ��������#������һ�㣩" << endl;
	getchar() == '#' ? handleQQGroupMenu(130):InviteGroupMember();
	return;
}
//��Ⱥ
int QQChatBase_Qfh::FindGroup(const string& groupID, int sub)
{
	for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
	{
		if (QQ[sub]->Return_group_List()[i]->Return_Group_ID() == groupID)
		{
			return i;
		}
	}
	return -1;
}
//�Ƿ��Ǻ���
bool QQChatBase_Qfh::IsFriend(const string& friendID, int sub)
{
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if (QQ[sub]->Return_Friend_List()[i]->Return_ID() == friendID)
		{
			return true;
		}
	}
	return false;
}
//�Ƿ���Ⱥ��Ա
bool QQChatBase_Qfh::IsMemberInGroup(const string& memberID, int groupIndex, int sub)
{
	for (int i = 0; i < QQ[sub]->Return_group_List()[groupIndex]->ReturnGroupMembers().size(); i++)
	{
		if (QQ[sub]->Return_group_List()[groupIndex]->ReturnGroupMembers()[i] == memberID)
		{
			return true;
		}
	}
	return false;
}
//���Ⱥ��Ա
void QQChatBase_Qfh::AddMemberToGroup(const string& groupID, const string& memberID)
{
	fstream InviteGroupFile;
	string InviteGroupFileName = "QQ\\Groups\\" + groupID + "\\" + groupID + ".txt";
	InviteGroupFile.open(InviteGroupFileName, ios::app);
	InviteGroupFile << memberID << endl;
	InviteGroupFile.close();

	fstream InviteFriendFile;
	string InviteFriendFileName = "QQ\\" + memberID + "\\" + memberID + "Groupslist.txt";
	InviteFriendFile.open(InviteFriendFileName, ios::app);
	InviteFriendFile << groupID << endl;
	InviteFriendFile.close();
}
//��ȡQQȺ�����ļ���ȡ��ѹ����
void QQChatBase_Qfh::GetQQGroup() 
{
	for (int i = 0; i < QQ.size(); i++)
	{
		for (int j = 0; j < QQ[i]->Return_group_List().size(); j++)
		{
			QQ[i]->Return_group_List()[j]->ReturnGroupMembers().clear();
		}
		QQ[i]->Return_group_List().clear();
	}
	int sub, line = 0;
	char c;
	string txt1 = "Groupslist.txt";
	string txt = ".txt";
	ifstream listfile;
	ifstream groupfile;
	string qq = qqnumber;
	vector<string>group;
	string temp;
	string filename = "QQ\\" + qq + "\\" + qq + "Groupslist.txt";
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
			temp.pop_back();//�ѻس�����ȥ
			group.push_back(temp);
			temp.clear();
		}
	}
	listfile.close();
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	QQ[sub]->Change_group_num(line);
	//��ȡȺ��Ա
	for (int i = 0; i < group.size(); i++)
	{
		temp = group[i];
		groupfilename = "QQ\\Groups\\" + temp + "\\" + temp + ".txt";
		groupfile.open(groupfilename);
		string id;
		string name;
		string userid;
		groupfile >> id;
		groupfile >> name;
		groupfile >> userid;
		groupfile.close();
		QQ[sub]->Return_group_List().push_back(new QQgroups_Qfh(id, name, userid));
	}

	fstream QQGroupMemberFile;
	string QQGroupMemberFileName;
	string QQGroupMemberFileTemp;
	string OwnerQQ;
	vector<string>QQGroupMemberFileContent;

	int ThisGroupID;
	string QQGroupID;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	//��ȡȺ����ԱQQ
	for (int i = 0; i < group.size(); i++)
	{
		QQGroupMemberFileName = "QQ\\Groups\\" + group[i] + "\\" + group[i] + ".txt";
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
		QQGroupMemberFileContent.erase(QQGroupMemberFileContent.begin());//Ⱥ���Ѿ���ȡ��������
		if (QQGroupMemberFileContent.size() != 0)
		{
			QQGroupMemberFileContent.pop_back();
		}

		for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
		{
			if (QQ[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
			{
				ThisGroupID = i;
				break;
			}
		}

		QQ[sub]->Return_group_List()[ThisGroupID]->ReturnGroupMembers().push_back(OwnerQQ);
		for (int i = 0; i < QQGroupMemberFileContent.size(); i++)
		{
			QQ[sub]->Return_group_List()[ThisGroupID]->ReturnGroupMembers().push_back(QQGroupMemberFileContent[i]);
		}
		QQGroupMemberFileContent.clear();
		QQGroupMemberFile.close();
	}
	
	fstream adminfile;
	string adminfilename;
	string admintemp;
	string ThidGroupID;

	for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
	{
		ThidGroupID = QQ[sub]->Return_group_List()[i]->Return_Group_ID();
		fstream CheckGroupAdminFile;
		string GetLinkFileName = "QQ\\Groups\\" + ThidGroupID + "\\" + ThidGroupID + "admin.txt";
		CheckGroupAdminFile.open(GetLinkFileName, ios::in);
		if (!CheckGroupAdminFile)
		{
			CheckGroupAdminFile.close();
			CheckGroupAdminFile.open(GetLinkFileName, ios::out);
		}
		CheckGroupAdminFile.close();
		adminfilename = "QQ\\Groups\\" + ThidGroupID + "\\" + ThidGroupID + "admin.txt";
		adminfile.open(adminfilename);

		while (!adminfile.eof())
		{
			getline(adminfile, admintemp);
			QQ[sub]->Return_group_List()[i]->Return_Admins_ID().push_back(admintemp);
		}
		if (QQ[sub]->Return_group_List()[i]->Return_Admins_ID().size() != 0)
		{
			QQ[sub]->Return_group_List()[i]->Return_Admins_ID().pop_back();//������0�Ż���һ����Ϊ����
		}
		adminfile.close();
	}
}
//��ʾȺ��Ա
void QQChatBase_Qfh::ShowQQGroup()
{
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	cout << "������" << QQ[sub]->Return_group_List().size() << "��Ⱥ" << endl;
	for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
	{
		if (QQ[sub]->Return_group_List()[i]->Return_Group_ID()[0] == '$' || QQ[sub]->Return_group_List()[i]->Return_Group_ID()[0] == '&')
			cout << "��" << i + 1 << "��Ⱥ" << endl;
		cout << "Ⱥ��:" << QQ[sub]->Return_group_List()[i]->Return_Group_ID() << endl;
		cout << "Ⱥ����:" << QQ[sub]->Return_group_List()[i]->Return_Group_Name() << endl;
		cout << "Ⱥ��:" << QQ[sub]->Return_group_List()[i]->ReturnCreatUserID() << endl;
		cout << endl;
	}
}
//��Ⱥ
void QQChatBase_Qfh::AddInGroupMember()
{
	system("CLS");
	cout << "��������������Ⱥ��������#������һ�㣩" << endl;
	string groupid;
	cin >> groupid;
	judge_flush(stdin);
	if (groupid == "#")
	{
		handleQQGroupMenu(130);
		return;
	}
	GroupMember = groupid;
	string id;
	int sub;
	id = GroupMember;
	string txt = ".txt";

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
	{
		if (QQ[sub]->Return_group_List()[i]->Return_Group_ID() == groupid)
		{
			cout << "���������ΪȺ" << endl;
			cout << "�������������һ��" << endl;
			if (getchar() != EOF)
				handleQQGroupMenu(130);
			return;
		}
	}

	fstream CheckGroupListFile;
	string GetLinkFileName = "Groupslist.txt";
	CheckGroupListFile.open(GetLinkFileName, ios::in);
	if (!CheckGroupListFile)
	{
		CheckGroupListFile.close();
		CheckGroupListFile.open(GetLinkFileName, ios::out);//���û�оʹ���
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
	for (int i = 0; i < AllGroupIDList.size(); i++)
	{
		if (AllGroupIDList[i] == groupid)
		{
			IsGroupFlag = true;
			break;
		}
	}
	if (IsGroupFlag == false)
	{
		cout << "û�и�Ⱥ���������������һ��" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);
		return;
	}
	string filename = "QQ\\Groups\\" + groupid + "\\" + groupid + ".txt";
	ofstream ofile;
	ofile.open(filename, ios::app);
	ofile << "$" << qqnumber << endl;
	ofile.close();
	LogOperation( "�����Ⱥ��Ⱥ�ţ�"+groupid, qqnumber);
	cout << "�����Ⱥ�ɹ�,��ȴ�Ⱥ�������Աͬ��" << endl;
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
	return;
}
//�鿴����ͬ����Ⱥ
void QQChatBase_Qfh::AgreeMember()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "������Ҫ�����Ⱥ��" << endl;
	char c;
	int line = 0;
	bool flag = false;
	string id;
	string txt = ".txt";
	cin >> id;
	judge_flush(stdin);
	string filename = "QQ\\Groups\\" + id + "\\" + id + ".txt";
	ifstream infile;
	infile.open(filename, ios::in);
	if (!infile)
	{
		cout << "û����ΪȺ,����������򷵻���һ��" << endl;
		cout << "1.��������" << endl;
		cout << "0.������һ��" << endl;
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
		default:
			handleQQGroupMenu(130);
			return;
		}
	}
	infile.close();
	fstream outfile;
	outfile.open(filename);

	string temp;
	vector<string>tempstr;
	while (outfile.get(c))
	{
		if (c == '\n')
		{
			line++;
			continue;
		}
		if (line == 2) //��ȡȺ��QQ��
		{
			temp.push_back(c);
		}

	}
	string OwnerQQ = temp;
	//��ȡȺ����ԱQQ
	fstream adminfile;
	string adminfilename;
	string admintemp;
	vector<string> AdminQQ;
	adminfilename = "QQ\\Groups\\" + id + "\\" + id + "admin.txt";
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
		if (AdminQQ[i] == qqnumber)
		{
			Adminflag = true;
			break;
		}
	}
	if (OwnerQQ == qqnumber)
	{
		cout << "�鿴��Ⱥ������ݣ�Ⱥ��" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "�鿴��Ⱥ������ݣ�����Ա" << endl;
	}
	else
	{
		cout << "�����Ǹ�Ⱥ��Ⱥ�������Ա,�޷������Ⱥ" << endl;
		cout << "�������������һ��" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);
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
			while (1) {
				outfile.get(c);
				temp.push_back(c);
				if (c == '\n')
				{
					temp.pop_back();
					tempstr.push_back(temp);
					temp.clear();
					break;
				}
			}
		}
	}

	if (flag == false)
	{
		cout << "û�м�Ⱥ����" << endl;
		cout << "�������������һ��" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);
		return;
	}
	outfile.close();
	for (int i = 0; i < tempstr.size(); i++)
	{
		cout << "���Ƿ�ͬ��" << tempstr[i] << "��Ⱥ?" << endl;
		cout << "1.ͬ��" << endl;
		cout << "0.�ܾ�" << endl;
		int select;
		string choice;
		cin >> choice;
		judge_flush(stdin);
		select = judge_count_menu(choice, 1);
		string member = tempstr[i];
		string GroupList = "Groupslist.txt";
		string filename1 = "QQ\\" + member + "\\" + member + "Groupslist.txt";
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
			LogOperation( "ͬ����Ⱥ��Ⱥ�ţ�"+id+"�����ˣ�"+tempstr[i], qqnumber);
			outfile.close();
			outfile.open(filename1, ios::app);
			outfile << id << endl;
			outfile.close();
			break;
		default:
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
						msg.erase(msg.begin() + n); //ɾ��������QQ
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
		}
	}
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
	return;
}
//ɾ��Ⱥ��Ա
void QQChatBase_Qfh::DeleteGroupMember()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "������Ҫ�����Ⱥ��" << endl;
	char c;
	int line = 0;
	bool flag = false;
	string id;
	string txt = ".txt";
	string GroupOwner;
	cin >> id;
	judge_flush(stdin);
	string filename = "QQ\\Groups\\" + id + "\\" + id + ".txt";
	ifstream infile;
	infile.open(filename, ios::in);
	if (!infile)
	{
		cout << "û����ΪȺ,����������򷵻���һ��" << endl;
		cout << "1.��������" << endl;
		cout << "0.������һ��" << endl;
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
		default:
			handleQQGroupMenu(130);
			return;
		}
	}
	infile.close();
	//��ȡȺ��QQ
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
		if (line == 2) //��ȡȺ��QQ��
		{
			temp.push_back(c);
		}
	}
	GroupOwner = temp;//Ⱥ��QQ
	//��ȡȺ����ԱQQ
	fstream adminfile;
	string adminfilename;
	string admintemp;
	vector<string> AdminQQ;
	adminfilename = "QQ\\Groups\\" + id + "\\" + id + "admin.txt";
	adminfile.open(adminfilename);
	while (!adminfile.eof())
	{
		getline(adminfile, temp);
		AdminQQ.push_back(temp);

	}
	AdminQQ.pop_back();//Ϊ��������з���

	//�ж��Ƿ��ǹ���Ա��Ⱥ��
	bool Adminflag = false;
	for (int i = 0; i < AdminQQ.size(); i++)
	{
		if (AdminQQ[i] == qqnumber)
		{
			Adminflag = true;
			break;
		}
	}

	if (GroupOwner == qqnumber)
	{
		cout << "Ⱥ��Ա������ݣ�Ⱥ��" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "Ⱥ��Ա������ݣ�����Ա" << endl;
	}
	else
	{
		cout << "�����Ǹ�Ⱥ��Ⱥ�������Ա,�޷������Ⱥ" << endl;
		cout << "�������������һ��" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);
		return;
	}
	outfile.close();
	temp.clear();
	//��ȡȺ��Ա
	fstream Groupfile;
	string Groupfilename = "QQ\\Groups\\" + id + "\\" + id + ".txt";
	string GroupMembertemp;
	vector<string> GroupMember;
	Groupfile.open(Groupfilename);
	while (!Groupfile.eof())
	{
		getline(Groupfile, GroupMembertemp);

		GroupMember.push_back(GroupMembertemp);
	}
	GroupMember.pop_back();//������з���
	bool Ownerflag = false;
	Adminflag = false;
	if (qqnumber == GroupOwner)
	{
		cout << "��Ϊ��ΪȺȺ�������߳���������κ���" << endl;
		Ownerflag = true;
	}
	else
	{
		cout << "��Ϊ��ΪȺ����Ա�������߳���Ⱥ���͹���Ա�������" << endl;
		Adminflag = true;
	}
	Show_Group_InformationNo_Return(id);
	cout << "������Ҫ�߳��ĳ�ԱQQ��,������#������һ��" << endl;
	string DeleteMemberQQ;
	cin >> DeleteMemberQQ;
	judge_flush(stdin);
	if (DeleteMemberQQ == "#")
	{
		handleQQGroupMenu(130);
		return;
	}
	//�������QQ�Ƿ���Ⱥ�������Լ�
	bool checkflag = false;//����Ƿ�����Ϊ��Ա
	while (1)
	{
		if (DeleteMemberQQ == GroupOwner || DeleteMemberQQ == qqnumber)
		{
			cout << "�޷��߳�Ⱥ�����Լ������������������#������һ��" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				handleQQGroupMenu(130);
				return;
			}
			continue;
		}

		for (int i = 0; i < size(GroupMember); i++)//����Ƿ�����Ϊ��Ա
		{
			if (DeleteMemberQQ == GroupMember[i])
			{
				checkflag = true;
				break;
			}
		}

		if (checkflag == false)
		{
			cout << "û����Ϊ��Ա����������,������#������һ��" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				handleQQGroupMenu(130);
				return;
			}
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
		if (DeleteMemberQQ != GroupOwner && DeleteMemberQQ != qqnumber)
		{
			break;
		}
		else
		{
			cout << "�޷��߳�Ⱥ�����Լ������������������#������һ��" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				handleQQGroupMenu(130);
				return;
			}
			continue;
		}

	}

	//�Ӹó�ԱȺ�б���ɾ����ΪȺ
	fstream membergrouplistfile;
	string membergrouplistfilename = "QQ\\" + DeleteMemberQQ + "\\" + DeleteMemberQQ + "Groupslist.txt";
	string membergrouplisttemp;
	vector<string> memebergrouplistcontent;
	membergrouplistfile.open(membergrouplistfilename);//�򿪱�ɾ����Ա��Ⱥ�б�
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
			memebergrouplistcontent.erase(memebergrouplistcontent.begin() + i);//ɾ���ó�Ա�е�Ⱥ
			break;
		}
	}
	memebergrouplistcontent.shrink_to_fit();
	membergrouplistfile.open(membergrouplistfilename, ios::trunc | ios::out);//���ԭ�����ļ�
	for (int i = 0; i < size(memebergrouplistcontent); i++)
	{
		membergrouplistfile << memebergrouplistcontent[i] << endl;//����д��
	}
	membergrouplistfile.close();

	//�ӱ�Ⱥ��Ա�б���ɾ����Ϊ��Ա��ԭ����������
	fstream GroupMemberListFile;
	string GroupMEmberListFileName = "QQ\\Groups\\" + id + "\\" + id + ".txt";
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
	GroupMemberListContent.shrink_to_fit();
	GroupMemberListFile.close();
	GroupMemberListFile.open(GroupMEmberListFileName, ios::trunc | ios::out);
	for (int i = 0; i < GroupMemberListContent.size(); i++)
	{

		GroupMemberListFile << GroupMemberListContent[i] << endl;

	}
	GroupMemberListFile.close();
	int ThisGroup;
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}
	for (int i = 0; i < size(QQ[sub]->Return_group_List()); i++)
	{
		if (QQ[sub]->Return_group_List()[i]->Return_Group_ID() == id)
		{
			ThisGroup = i;
			break;
		}
	}
	for (int i = 0; i < size(QQ[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers()); i++)
	{
		if (QQ[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers()[i] == DeleteMemberQQ)
		{
			QQ[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers().erase(QQ[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers().begin() + i);
			break;
		}
	}
	QQ[sub]->Return_group_List()[ThisGroup]->ReturnGroupMembers().shrink_to_fit();
	//����ó�Ա�ǹ���Ա��ӹ���Ա�б���ɾ����QQ
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
			cout << "�������������һ��" << endl;
			if (getchar() != EOF)
				handleQQGroupMenu(130);
			return;
		}
		else
		{
			cout << "�߳�" << DeleteMemberQQ << "�ɹ�" << endl;
			LogOperation( "�߳�Ⱥ��Ա��Ⱥ�ţ�"+id+"���߳��ˣ�"+DeleteMemberQQ, qqnumber);
			cout << "�������������һ��" << endl;
			if (getchar() != EOF)
				handleQQGroupMenu(130);
			return;
		}
	}

}
/// <summary>
/// ������
/// </summary>
void QQChatBase_Qfh::ShowQQGroupNoReturn()
{
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	cout << "������" << QQ[sub]->Return_Group_Number() << "��Ⱥ" << endl;
	for (int i = 0; i < QQ[sub]->Return_Group_Number(); i++)
	{
		cout << "��" << i + 1 << "��Ⱥ" << endl;
		cout << "Ⱥ��:" << QQ[sub]->Return_group_List()[i]->Return_Group_ID() << endl;
		cout << "Ⱥ����:" << QQ[sub]->Return_group_List()[i]->Return_Group_Name() << endl;
		cout << "Ⱥ��:" << QQ[sub]->Return_group_List()[i]->ReturnCreatUserID() << endl;
		cout << endl;
	}

}

void QQChatBase_Qfh::Show_Group_InformationNo_Return(string groupId)
{
	string  QQGroupID;
	QQGroupID = groupId;
	if (QQGroupID == "#")
	{
		handleQQGroupMenu(130);
		return;
	}
	int sub;
	int ThisQQGroupID;
	int ThisQQ;
	string Thisqqnumber;

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	bool CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
		{
			if (QQ[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
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
			cout << "��û�м�����ΪȺ�����������������#������һ��" << endl;
			cin >> QQGroupID;
			judge_flush(stdin);
			continue;
		}
	}

	system("CLS");
	bool AdminFlag = false;//��ʾ�ó�Ա�Ƿ��ǹ���Ա
	for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
	{
		if (QQ[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
		{
			ThisQQGroupID = i;
			break;
		}
	}

	for (int i = 0; i < size(QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers()); i++)
	{
		int m = size(QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers());

		Thisqqnumber = QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers()[i];//��Ⱥ�б��ȡȺ��ԱQQ
		for (int i = 0; i < QQ.size(); i++)
		{
			if (QQ[i]->Return_ID() == Thisqqnumber)
			{
				ThisQQ = i;
				break;
			}
		}
		for (int i = 0; i < QQ[sub]->Return_group_List()[ThisQQGroupID]->Return_Admins_ID().size(); i++)
		{
			if (QQ[sub]->Return_group_List()[ThisQQGroupID]->Return_Admins_ID()[i] == Thisqqnumber)
			{
				AdminFlag = true;
				break;
			}
		}
		if (Thisqqnumber == QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnCreatUserID())
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "����:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:Ⱥ��" << endl;
			cout << "���ڵ���:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
		else if (AdminFlag == true)
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "����:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:����Ա" << endl;
			cout << "���ڵ���:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
			AdminFlag = false;
		}

		else
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "�ʺ�:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "����:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "Ⱥ��Ա����:��ͨ��Ա" << endl;
			cout << "���ڵ���:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
	}

	cout << endl;
}
//����Ⱥ��Ա
void QQChatBase_Qfh::ShowGroupInformation()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "������QQȺ���Բ�ѯ��Ա��Ϣ,������#������һ��" << endl;
	string  QQGroupID;
	cin >> QQGroupID;
	judge_flush(stdin);
	if (QQGroupID == "#")
	{
		handleQQGroupMenu(130);
		return;
	}
	int sub;
	int ThisQQGroupID;
	int ThisQQ;
	string Thisqqnumber;
	string fathername;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	bool CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
		{
			if (QQ[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
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
			cout << "��û�м����Ⱥ�����������������#������һ��" << endl;
			cin >> QQGroupID;
			judge_flush(stdin);
			continue;
		}
	}
	system("CLS");
	bool AdminFlag = false;
	for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
	{
		if (QQ[sub]->Return_group_List()[i]->Return_Group_ID() == QQGroupID)
		{
			ThisQQGroupID = i;
			break;
		}
	}

	for (int i = 0; i < QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers().size(); i++)
	{
		int m = QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers().size();

		Thisqqnumber = QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers()[i];//��Ⱥ�б��ȡȺ��ԱQQ
		if(Thisqqnumber[0]=='$'){continue;}
		for (int i = 0; i < QQ.size(); i++)
		{
			if (QQ[i]->Return_ID() == Thisqqnumber)
			{
				ThisQQ = i;
				break;
			}
		}
		for (int i = 0; i < QQ[sub]->Return_group_List()[ThisQQGroupID]->Return_Admins_ID().size(); i++)
		{
			if (QQ[sub]->Return_group_List()[ThisQQGroupID]->Return_Admins_ID()[i] == Thisqqnumber)
			{
				AdminFlag = true;
				break;
			}
		}
		if (Thisqqnumber == QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnCreatUserID())
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "Ⱥ��Ա����:Ⱥ��" << endl;
			cout << "�ʺ�:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "����:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "���ڵ���:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
		else if (AdminFlag == true&&(Thisqqnumber != QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnCreatUserID()))
		{
			
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "Ⱥ��Ա����:����Ա" << endl;
			cout << "�ʺ�:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "����:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "���ڵ���:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
			AdminFlag = false;
		}
		else if(AdminFlag == false&&(Thisqqnumber != QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnCreatUserID()))
		{
			cout << "��" << i + 1 << "����Ա��Ϣ:" << endl;
			cout << "Ⱥ��Ա����:��ͨ��Ա" << endl;
			cout << "�ʺ�:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "����:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "���ڵ���:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "����ǩ��:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
	}

	cout << endl;
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
	return;
}

/*������Ϣģ��*/

//չʾ������Ϣ
void QQChatBase_Qfh::ShowMyInformation()
{
	system("CLS");
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	
	cout << "         ������Ϣ���£�             \n";
	cout << "\t�ǳ�: " << QQ[sub]->Return_Name() << "\t�Ա�: " << QQ[sub]->Return_Sex() << endl;
	cout << "\t�ʺ�: " << QQ[sub]->Return_ID() << endl;
	cout << "\t����: " << QQ[sub]->Return_PassWord() << endl;
	cout << "\tע������: " << QQ[sub]->Return_ApplyDate() << endl;

	cout << "\t "; calculateAge(QQ[sub]->Return_ApplyDate());

	cout << "\t����: " << QQ[sub]->Return_bir() << endl;
	cout << "\t����: " << QQ[sub]->Return_Area() << endl;
	cout << "\t����ǩ��: " << QQ[sub]->Return_Autograph() << endl;

}
//�ı������Ϣ
void QQChatBase_Qfh::Change_PassWord()
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
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}

	QQ[sub]->Change_PassWord(pw);
	SaveChange();
	cout << "�޸�����ɹ�" << endl;
	LogOperation( "�޸����룬�����룺"+pw, qqnumber);
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handlePersonalInfoMenu(130);
	return;
}
void QQChatBase_Qfh::Change_Name()
{
	system("CLS");
	string newname;
	cout << "��������������" << endl;
	cin >> newname;
	judge_flush(stdin);
	int sub;

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}

	QQ[sub]->Change_Name(newname);
	SaveChange();

	cout << "�޸����Ƴɹ�" << endl;
	LogOperation( "�޸��ǳƣ����ǳƣ�"+newname, qqnumber);
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handlePersonalInfoMenu(130);
	return;
}
void QQChatBase_Qfh::Change_AutoGraph()
{
	system("CLS");
	string autograph;
	cout << "����������ǩ��" << endl;
	cin >> autograph;
	judge_flush(stdin);
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}

	QQ[sub]->Change_AutoGraph(autograph);
	cout << "�޸ĸ���ǩ���ɹ�" << endl;
	LogOperation( "�޸ĸ���ǩ������ǩ����"+autograph, qqnumber);
	SaveChange();
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handlePersonalInfoMenu(130);
	return;
}
void QQChatBase_Qfh::Change_Area()
{
	system("CLS");
	string Area;
	cout << "�������ĵ���" << endl;
	cin >> Area;
	judge_flush(stdin);
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	QQ[sub]->Change_Area(Area);
	LogOperation( "�޸�IP��ַ����IP��"+Area, qqnumber);
	SaveChange();
	cout << "�������������һ��" << endl;
	if (getchar() != EOF)
		handlePersonalInfoMenu(130);
	return;
}
//�����޸�
void QQChatBase_Qfh::SaveChange()
{
	fstream qqfile;
	string qqfilename = "QQ.txt";
	qqfile.open(qqfilename, ios::trunc | ios::out);
	for (int i = 0; i < QQ.size(); i++)
	{
		qqfile << QQ[i]->Return_ID() << endl;
		qqfile << QQ[i]->Return_ApplyDate() << endl;
		qqfile << QQ[i]->Return_PassWord() << endl;
		qqfile << QQ[i]->Return_Name() << endl;
		qqfile << QQ[i]->Return_Sex() << endl;
		qqfile << QQ[i]->Return_Area() << endl;
		qqfile << QQ[i]->Return_Autograph() << endl;
		qqfile << QQ[i]->Return_bir() << endl;
		qqfile << " " << endl;
	}
	qqfile.close();
	fstream qqfriendlistfile;
	string qqfriendlistfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	qqfriendlistfile.open(qqfriendlistfilename, ios::out | ios::trunc);
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}

	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		qqfriendlistfile << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		qqfriendlistfile << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		qqfriendlistfile << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		qqfriendlistfile << " " << endl;
	}
	qqfriendlistfile.close();
}



/*���ӽ�ģ��*/
void QQChatBase_Qfh::CreateWeiBo()
{
	system("CLS");
	int sub;
	string WeiBoDirectory = "WeiBo\\" + qqnumber;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}

	//�ж��Ƿ��Ѿ���ͨ΢��
	for (int i = 0; i < WeiBoFun.ReturnWeiBolist().size(); i++)
	{
		if (WeiBoFun.ReturnWeiBolist()[i]->Return_ID() == qqnumber)
		{
			cout << "���ѿ�ͨ΢��" ;
			cout << "     �������������һ��" << endl;
			if (getchar() != EOF)
				handleServiceMenu(130);
			return;
		}
	}

	cout << "����΢����:" << qqnumber << endl;
	cout << "����:" << QQ[sub]->Return_Name() << endl;
	cout << "�Ƿ�Ҫ��ͨ΢����" << endl;
	cout << "1.ȷ��" << endl;
	cout << "0.ȡ��" << endl;
	int select;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 1);
	switch (select)
	{
	case 1:
		WeiBoFun.ReturnWeiBolist().push_back(new WeiBo_Qfh(qqnumber));
		CreateDirectory(WeiBoDirectory.c_str(), NULL);//�����ļ���
		WeiBoFun.SaveWeiBo();
		cout << "��ͨ΢���ɹ�" << endl;
		LogOperation( "��ͨ΢��", qqnumber);
		cout << "�������������һ��" << endl;
		if (getchar() != EOF)
			handleServiceMenu(130);
		return;

	default:
		cout << "��ȡ���˿�ͨ����" << endl;
		cout << "�������������һ��" << endl;
		if (getchar() != EOF)
			handleServiceMenu(130);
		return;
	}
}

void QQChatBase_Qfh::CreateWeChat()
{
	system("CLS");
	int sub;
	string WeChatDirectory = "WeChat\\" + qqnumber;

	// ���ҵ�ǰQQ�ŵ�����
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	// �жϵ�ǰ�Ƿ��Ѿ���ͨ΢��
	for (int i = 0; i < WeChatFun.ReturnWeiChatList().size(); i++)
	{
		if (WeChatFun.ReturnWeiChatList()[i]->Return_ID() == qqnumber)
		{
			cout << "���ѿ�ͨ΢��" << endl;
			cout << "     �������������һ��" << endl;
			if (getchar() != EOF)
				handleServiceMenu(130);
			return;
		}
	}

	cout << "����΢�ź�: " << qqnumber << endl;
	cout << "����: " << QQ[sub]->Return_Name() << endl;
	cout << "�Ƿ�Ҫ��ͨ΢�ţ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "0.ȡ��" << endl;

	int select;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 1);

	switch (select)
	{
	case 1:
		// ����΢���ʻ�
		WeChatFun.ReturnWeiChatList().push_back(new Weixin_Qfh(qqnumber));
		CreateDirectory(WeChatDirectory.c_str(), NULL); // �����ļ���
		WeChatFun.SaveWeChat(); // ����΢����Ϣ
		cout << "��ͨ΢�ųɹ�" << endl;
		LogOperation( "��ͨ΢��", qqnumber);
		cout << "�������������һ��(��#����΢��ҳ��)" << endl;
		if (getchar() == '#') { SwitchToWeChat(qqnumber); }
			else handleServiceMenu(130);
		return;

	default:
		cout << "��ȡ���˴���" << endl;
		cout << "�������������һ��" << endl;
		if (getchar() != EOF)
			handleServiceMenu(130);
		return;
	}
}

void QQChatBase_Qfh::LinkWeiChat()
{
	string linkweichat;
	string linkpw;
	int ThisQQ;
	int ThisWeiChat;
	system("CLS");

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			ThisQQ = i;
			break;
		}

	}

	if (QQ[ThisQQ]->Return_Linked_WeiChat() != "")
	{
		cout << "���Ѿ���΢��" << QQ[ThisQQ]->Return_Linked_WeiChat() << endl;
		string temp = QQ[ThisQQ]->Return_Linked_WeiChat();
		for (int i = 0; i < WeChatFun.ReturnWeiChatList().size(); i++)
		{
			if (WeChatFun.ReturnWeiChatList()[i]->Return_ID() == temp)
			{
				WeChatFun.ReturnWeiChatList()[i]->flag = 1;
				cout << "��΢���Ѿ��Զ���¼" << endl;
				break;
			}
		}
		cout << "����������ط�����һ��(��#����΢��ҳ��)" << endl;
		if (getchar() == '#'){ SwitchToWeChat(QQ[ThisQQ]->Return_Linked_WeiChat()); }
		else { handleServiceMenu(130); }
		return;
	}
	cout << "��������Ҫ�󶨵�΢�ź�" << endl;
	cin >> linkweichat;
	judge_flush(stdin);
	bool CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < WeChatFun.ReturnWeiChatList().size(); i++)
		{
			if (WeChatFun.ReturnWeiChatList()[i]->Return_ID() == linkweichat)
			{
				CheckFlag = true;
				ThisWeiChat = i;
				break;

			}
		}
		if (CheckFlag == false)
		{
			cout << "û����Ϊ΢�ţ����������������#���ط�����һ��" << endl;
			cin >> linkweichat;
			judge_flush(stdin);
			if (linkweichat == "#")
			{
				handleServiceMenu(130);
				return;
			}
			continue;
		}
		else
		{
			break;
		}
	}

	cout << "��������Ϊ΢�źŵ�����" << endl;
	cin >> linkpw;
	judge_flush(stdin);
	bool PWCheckFlag = false;
	while (1)
	{
		if (WeChatFun.ReturnWeiChatList()[ThisWeiChat]->Return_PassWord() == linkpw)
		{
			PWCheckFlag = true;
			WeChatFun.ReturnWeiChatList()[ThisWeiChat]->flag = 1;
			break;
		}

		if (PWCheckFlag == false)
		{
			cout << "��������������������������#���ط�����һ��" << endl;
			cin >> linkpw;
			judge_flush(stdin);
			if (linkpw == "#")
			{
				handleServiceMenu(130);
				return;
			}
			continue;
		}
	}

	//��΢�����QQ
	fstream LinkFile;
	string LinkFileName = "WeChat\\" + linkweichat + "\\Links.txt";
	LinkFile.open(LinkFileName, ios::app);

	LinkFile << "QQ:" + qqnumber;
	LinkFile.close();
	WeChatFun.ReturnWeiChatList()[ThisWeiChat]->Change_LinkedQQ(qqnumber);

	//��QQ���΢��
	fstream QQLinkFile;
	string QQLinkFileName = "QQ\\" + qqnumber + "\\Links.txt";
	QQLinkFile.open(QQLinkFileName, ios::app);

	QQLinkFile << "΢��:" + linkweichat;
	QQLinkFile.close();
	QQFun.ReturnQQ()[ThisQQ]->Change_Linked_WeiChat(linkweichat);

	cout << "��΢�ųɹ�" << endl;
	LogOperation( "��΢�ţ�΢�źţ�"+linkweichat, qqnumber);
	cout << "�������������һ��(��#����΢��ҳ��)" << endl;
	
	if (getchar() == '#') {
		LogOperation( "����΢��ҳ��,�û���"+linkweichat, qqnumber);
		SwitchToWeChat(linkweichat);
	}
		handleServiceMenu(130);
	return;
}

void QQChatBase_Qfh::UnlinkWeiChat()
{
	system("CLS");
	int ThisQQ;
	string linkedWeChat;

	// ���ҵ�ǰQQ�ŵ�����
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			ThisQQ = i;
			break;
		}
	}

	// ��ȡ��ǰ�󶨵�΢�ź�
	linkedWeChat = QQ[ThisQQ]->Return_Linked_WeiChat();
	if (linkedWeChat.empty())
	{
		cout << "��û�а��κ�΢��" << endl;
		cout << "�������������һ��" << endl;
		getchar();
		handleServiceMenu(130);
		return;
	}

	cout << "����ǰ�󶨵�΢�ź�: " << linkedWeChat << endl;
	cout << "ȷ�Ͻ���󶨴�΢�ź���" << endl;
	cout << "1. ȷ��" << endl;
	cout << "0. ȡ��" << endl;

	int select;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 1);

	if (select == 1)
	{
		// ����󶨲���
		UnlinkQQFromWeChat(ThisQQ, linkedWeChat);
		UnlinkWeChatFromQQ(ThisQQ, linkedWeChat);

		cout << "���΢�ųɹ�" << endl;
		LogOperation("���΢�ţ�΢�źţ�" + linkedWeChat, qqnumber);
	}
	else
	{
		cout << "��ȡ���˲���" << endl;
	}

	cout << "�������������һ��" << endl;
	getchar();
	handleServiceMenu(130);
}

void QQChatBase_Qfh::UnlinkQQFromWeChat(int thisQQ, const string& linkedWeChat)
{
	QQFun.ReturnQQ()[thisQQ]->Change_Linked_WeiChat(""); // ���QQ�ŵİ�

	// �ҵ���Ӧ��΢�Ų������
	for (auto& weChat : WeChatFun.ReturnWeiChatList())
	{
		if (weChat->Return_ID() == linkedWeChat)
		{
			weChat->Change_LinkedQQ(""); // ���΢�źŵİ�
			break;
		}
	}
}

void QQChatBase_Qfh::UnlinkWeChatFromQQ(int thisQQ, const string& linkedWeChat)
{
	// �Ƴ�QQ�����Ӽ�¼
	RemoveLinkRecord("QQ", qqnumber, "΢��:" + linkedWeChat);

	// �Ƴ�΢�ŵ����Ӽ�¼
	RemoveLinkRecord("WeChat", linkedWeChat, "QQ:" + qqnumber);
}

void QQChatBase_Qfh::RemoveLinkRecord(const string& service, const string& serviceID, const string& linkLine)
{
	string linkFileName = service + "\\" + serviceID + "\\Links.txt";

	// ��ȡ�����е� vector
	vector<string> lines;
	fstream linkFile(linkFileName);
	string line;
	while (getline(linkFile, line))
	{
		lines.push_back(line);
	}
	linkFile.close();

	// ��������Ҫɾ�����е�����д���ļ�
	ofstream out(linkFileName);
	for (const auto& l : lines)
	{
		if (l != linkLine)
		{
			out << l << endl;
		}
	}
}



//Bug�����Ӳ���
void QQChatBase_Qfh::SwitchToWeChat(const string& linkweichat) {
	system("CLS"); // ����
	cout << "�����л���΢�Ž���..." << endl;
	WeiChat_Qfh weichat;
	// ȷ��linkweichat��Ч
	string linkId = linkweichat;
	trim(linkId); // ȥ��ǰ��ո�
	if (linkId.empty()) {
		cout << "����΢�źŲ���Ϊ�ա�" << endl;
		return;
	}
	vector<Weixin_Qfh*> WeiChatList=weichat.GetWeChat(linkId); // ��ȡ΢���ʻ�
	
	// ����ָ����΢�Ŷ��󲢵�¼
	for (auto& weixinObj : WeiChatList) {
		if (toLower(weixinObj->Return_ID()) == toLower(linkId)) {
			
			weichat.splogin(weixinObj->Return_ID()); // ���õ�¼
			return; // �ɹ���¼���˳�
		}
	}

	cout << "����δ�ҵ���Ӧ��΢�źš�" << endl; // ���δ�ҵ�΢�ź�

	// �ͷ��ڴ�
	for (auto& weixin : WeiChatList) {
		delete weixin;
	}
}


/*
΢�����Ӻ���
*/
//��ѯ�����QQ��ͬ����
void QQChatBase_Qfh::Get_Links()
{
	system("CLS");
	fstream CheckFile;
	fstream GetLinksFile;
	string GetLinkFileName = "QQ\\" + qqnumber + "\\Links.txt";

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
	int sub;

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}

	while (!GetLinksFile.eof())
	{
		getline(GetLinksFile, GetLinksFileTemp);

		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		GetLinksFileTemp.erase(GetLinksFileTemp.begin() + 0);
		
		Links.push_back(GetLinksFileTemp);
	}

	if (Links.size() != 0)
	{
		QQ[sub]->Change_Linked_WeiChat(Links[0]);
	}
}

void QQChatBase_Qfh::DisplayCommonFriends(bool shouldReturn) {
	system("CLS");
	int sub = -1;

	// ���ҵ�ǰQQ������
	for (size_t i = 0; i < QQ.size(); ++i) {
		if (QQ[i]->Return_ID() == qqnumber) {
			sub = i;
			break;
		}
	}

	// ����Ƿ��ҵ�����Ч��sub����
	if (sub == -1) {
		cout << "δ�ҵ���ǰQQ�ţ�" << endl;
		return;
	}

	const auto& linkedWeiChatID = QQ[sub]->Return_Linked_WeiChat();
	int LinkedWeiChat = -1;

	if (linkedWeiChatID.empty()) {
		cout << "��û�а�΢�ţ����Ȱ�΢��" << endl;
		if (shouldReturn) {
			cout << "�������������һ��" << endl;
			getchar();
			handleFriendMenu(130);
		}
		return;
	}

	for (size_t i = 0; i < WeChatFun.ReturnWeiChatList().size(); ++i) {
		if (WeChatFun.ReturnWeiChatList()[i]->Return_ID() == linkedWeiChatID) {
			LinkedWeiChat = i;
			break;
		}
	}

	if (LinkedWeiChat == -1) {
		cout << "δ�ҵ��󶨵�΢�źţ�" << endl;
		return;
	}

	cout << "�����ӵ�΢�ź�Ϊ" << linkedWeiChatID << endl;
	cout << "���͸�΢�ŵĹ�ͬ��������" << endl;

	WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Get_Friends();
	auto& friendList = WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List();
	cout << "΢�ź����б��С: " << friendList.size() << endl;

	unordered_set<string> QQLinkedIDs;
	for (const auto& qq : QQ) {
		QQLinkedIDs.insert(qq->Return_Linked_WeiChat());
	}

	int CommonFriendNumber = 0;

	for (const auto& wechatFriend : friendList) {
		string wechatID = wechatFriend->Return_ID(); // ΢�ź��� ID
	//	cout << "���΢�ź��� ID: " << wechatID << " (΢�ź���)" << endl;

		for (const auto& qqFriend : QQ[sub]->Return_Friend_List()) {
			string qqID = qqFriend->Return_ID(); // QQ ���� ID
		//	cout << "��� QQ ���� ID: " << qqID << " (QQ����)" << endl;

			// ��¼�����Ƚϵ� ID
		//	cout << "�����Ƚϵ�΢�� ID: " << wechatID << " �� QQ ID: " << qqID << endl;

			if (qqID == wechatID) {
				cout << "�ҵ���ͬ����: " << wechatID << endl;
				// �����ͨ������Ϣ
				cout << "��" << ++CommonFriendNumber << "����ͬ����: " << endl;
				cout << "�ʺ�: " << qqID << endl; // ����Ϊ��Ӧ�� qqID
				cout << "����: " << qqFriend->ReturnFriendName() << endl;
				cout << "��ע: " << qqFriend->ReturnRemarks() << endl;
				cout << endl;
				break; // �ҵ�����˳�
			}
		}
	}

	if (CommonFriendNumber == 0) {
		cout << "û���ҵ���ͬ���ѣ�" << endl;
	}
	
	// ����΢�ź����б���ѡ��
	friendList.clear();
}






void QQChatBase_Qfh::ShowWeiChatCommonFriends() {
	LogOperation("�鿴΢�Ź�ͬ����", qqnumber);
	DisplayCommonFriends(true);
}

void QQChatBase_Qfh::Show_WeiChat_Common_FriendsNo_Return() {
	DisplayCommonFriends(false);
}

void QQChatBase_Qfh::AddWeiChatCommonFriend() {
	ShowWeiChatCommonFriends();
	string id;
	cout << "������Ҫ��ӵ�΢�ź��ѵ�QQID" << endl;
	cin >> id;
	judge_flush(stdin);

	if (id == qqnumber) {
		cout << "����������Լ�Ϊ����" << endl;
		cout << "�������������һ��" << endl;
		getchar();
		handleFriendMenu(130);
		return;
	}

	// ���ҵ�ǰ�û�������
	int sub = -1;
	for (size_t i = 0; i < QQ.size(); ++i) {
		if (QQ[i]->Return_ID() == qqnumber) {
			sub = i;
			break;
		}
	}

	if (sub == -1) {
		cout << "δ�ҵ���ǰQQ�ţ�" << endl;
		return;
	}

	// ����Ƿ��Ѿ��Ǻ���
	for (const auto& friendItem : QQ[sub]->Return_Friend_List()) {
		if (id == friendItem->Return_ID()) {
			cout << "���������Ϊ����,�밴�����������һ��" << endl;
			getchar();
			handleFriendMenu(130);
			return;
		}
	}

	// ����Ŀ���û�
	int subFriend = -1;
	bool foundFriend = false;
	string name;

	for (size_t i = 0; i < QQ.size(); ++i) {
		if (QQ[i]->Return_ID() == id) {
			foundFriend = true;
			name = QQ[i]->Return_Name();
			subFriend = i;
			LogOperation("��ѯ�����QQ��ͬ���� Ŀ��QQ�ţ�" + id ,qqnumber);
			cout << "��������ɹ�����ȴ��Է�ȷ��" << endl;
			break;
		}
	}

	if (!foundFriend) {
		cout << "��QQ��û��ע�᣺" << endl;
		cout << "1.��������QQ����Ӻ���" << endl;
		cout << "0.������һ��" << endl;

		int select;
		string tempstr;

		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 1);

		if (select == 1) {
			AddFriend();
		}
		else {
			handleFriendMenu(130);
		}
		return;
	}

	// ��Ӻ�������
	string mark = "&";
	string ID = mark + id;
	string friendFileName = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string remarks = "δ��ע";

	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	ofstream file(friendFileName, ios::app);

	if (file.is_open()) {
		file << ID << endl;
		file << name << endl;
		file << remarks << endl;
		file << " " << endl; // �����жϼ�������
		file.close();
	}

	// �����QQ�ļ�����ӱ�QQ
	friendFileName = "QQ\\" + id + "\\" + id + "Friendlist.txt";
	string subName = "$" + QQ[sub]->Return_Name();
	QQ[subFriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subName, qqnumber));

	ofstream friendFile(friendFileName, ios::app);
	if (friendFile.is_open()) {
		friendFile << "$" << QQ[sub]->Return_ID() << endl;
		friendFile << QQ[sub]->Return_Name() << endl;
		friendFile << remarks << endl;
		friendFile << " " << endl; // �жϼ�������
		friendFile.close();
	}
	LogOperation("���΢�Ź�ͬ����,����ID��"+id, qqnumber);
	cout << "�������������һ��" << endl;
	getchar();
	handleFriendMenu(130);
}




//QQȺ����(��ʱȺ)��������������TCP�汾���ݴ�΢������
void QQChatBase_Qfh::CreatTemporaryGroup() {
	system("CLS");

	// ������ʱ��������
	int temp = AllQQTemporaryGroup.size() + 1;
	string ID = to_string(temp); // to_string��ת��

	cout << "����������������: ";
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "������ʱ�������Ϊ: " << ID << endl;

	// �ҵ���ǰ�û�����
	int sub = findUserIndex(qqnumber);
	// ������ʱ�����鲢��ӵ��б�
	QQ[sub]->Return_Temporary_GroupList().emplace_back(new QQgroups_Qfh(ID, name, qqnumber));
	AllQQTemporaryGroup.emplace_back(new QQgroups_Qfh(ID, name, qqnumber));
	LogOperation("������ʱ������", qqnumber); // ��¼����������Ĳ���
	cout << "�������������һ��" << endl;
	if (getchar() != EOF) {
		handleQQGroupMenu(130);
	}
}

void QQChatBase_Qfh::JoinTemporaryGroup() {
	system("CLS");

	displayTemporaryGroups(AllQQTemporaryGroup); // ��ʾ�������б�

	cout << "��������������Ⱥ�ţ�������#������һ��: ";
	string TemporaryGroup;
	cin >> TemporaryGroup;
	judge_flush(stdin);

	if (TemporaryGroup == "#") {
		handleQQGroupMenu(130);
		return;
	}

	// ��֤Ⱥ���Ƿ���Ч
	while (!isTemporaryGroupValid(TemporaryGroup)) {
		cout << "û����Ϊ�����飬����������Ⱥ�Ż�����#������һ��: ";
		cin >> TemporaryGroup;
		judge_flush(stdin);
		if (TemporaryGroup == "#") {
			handleQQGroupMenu(130);
			return;
		}
	}

	// �ҵ���ǰ�û�����
	int sub = findUserIndex(qqnumber);

	// �ҵ�Ŀ����������Ϣ
	auto groupIndex = findTemporaryGroupIndex(TemporaryGroup);
	if (groupIndex == -1) return; // ���û���ҵ���ֱ�ӷ���

	string TemporaryName = ReturnAllQQTemporaryGroup()[groupIndex]->Return_Group_Name();
	string TemporaryOwner = ReturnAllQQTemporaryGroup()[groupIndex]->ReturnCreatUserID();

	// ���û���ӵ�������
	QQ[sub]->Return_Temporary_GroupList().emplace_back(new QQgroups_Qfh(TemporaryGroup, TemporaryName, TemporaryOwner));
	LogOperation("������ʱ������", qqnumber); // ��¼����������Ĳ���
	cout << "������ʱ������ɹ�" << endl;
	cout << "�������������һ��" << endl;
	if (getchar() != EOF) {
		handleQQGroupMenu(130);
	}
}

// ���������������û�����
int QQChatBase_Qfh::findUserIndex(const string& userId) {
	for (int i = 0; i < QQ.size(); i++) {
		if (QQ[i]->Return_ID() == userId) {
			return i;
		}
	}
	return -1; // �û�δ�ҵ�
}

// ������������ʾ������
void QQChatBase_Qfh::displayTemporaryGroups(const vector<QQgroups_Qfh*>& groups) {
	for (size_t i = 0; i < groups.size(); i++) {
		cout << "��" << i + 1 << "����ʱ������" << endl;
		cout << "Ⱥ��: " << groups[i]->Return_Group_ID() << endl;
		cout << "Ⱥ����: " << groups[i]->Return_Group_Name() << endl;
	}
}

// ������������֤�������Ƿ���Ч
bool QQChatBase_Qfh::isTemporaryGroupValid(const string& groupId) {
	for (const auto& group : AllQQTemporaryGroup) {
		if (group->Return_Group_ID() == groupId) {
			return true;
		}
	}
	return false;
}

// ����������������ʱ����������
int QQChatBase_Qfh::findTemporaryGroupIndex(const string& groupId) {
	for (size_t i = 0; i < AllQQTemporaryGroup.size(); i++) {
		if (AllQQTemporaryGroup[i]->Return_Group_ID() == groupId) {
			return i;
		}
	}
	return -1; // δ�ҵ�
}

template <typename T>
void QQChatBase_Qfh::LogOperation(const T& operation, const string& userId) {
	// Ϊÿ���û�����һ����־�ļ�
	string direcctoryPath = "QQ\\" + userId;
	string logFileName = direcctoryPath + "\\" + userId + "_log.txt"; // ʹ���û�ID��Ϊ�ļ���
	ofstream logFile(logFileName, ios::app);
	if (logFile.is_open()) {
		time_t now = time(0);
		char* dt = ctime(&now);

		// �Ƴ����з�
		dt[strlen(dt) - 1] = '\0';

		ostringstream oss;
		oss << operation;

		// ���ո�ʽд����־
		logFile << dt << ": " << userId << ": " << oss.str() << endl;
		logFile.close();
	}
	else {
		cerr << "�޷�����־�ļ�: " << logFileName << "!" << endl;
	}
}

void QQChatBase_Qfh::DisplayLog(const string& userId) {
	string logFileName = "QQ\\" + userId + "\\" + userId + "_log.txt";

	ifstream logFile(logFileName);
	if (logFile.is_open()) {
		string line;
		cout << "��־�ļ��������£�" << endl;
		while (getline(logFile, line)) {
			cout << line << endl; // ���ÿһ��
		}
		logFile.close();
	}
	else {
		cerr << "�޷�����־�ļ�: " << logFileName << "!" << endl;
	}
}

void QQChatBase_Qfh::ShowUserLog(const string& userId) {
	system("CLS");
	LogOperation("�鿴�û���־", userId); // ��¼�鿴��־�Ĳ���
	DisplayLog(userId); // չʾ�û���־
	cout << "�������������һ��" << endl;
	if (getchar() != EOF) {
		QQMenu();
	}
}