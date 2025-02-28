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
#include <string>
#include<stdlib.h>
#include<time.h>
#include<chrono>
#include<iomanip>
using namespace std;
int Grouptype;
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
		cout << "�����������QQ���˵�" << endl;
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
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
}
// agree�����ã���ȡ�ļ����ݵ�������
void ReadFileToVector(const string& filename, vector<string>& content) {
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		content.push_back(line);
	}
	if (!content.empty()) {
		content.pop_back(); // ɾ�����һ������
	}
}

// agree�����ã�д�������ݵ��ļ�
void WriteVectorToFile(const string& filename, const vector<string>& content) {
	ofstream file(filename, ios::trunc); // ����ļ�����
	for (const auto& line : content) {
		file << line << endl;
	}
}

// agree�����ã����º����б�������ǵ�IDȥ��
void UpdateFriendApplication(vector<string>& content, const string& prefix, const string& id) {
	for (auto& entry : content) {
		if (entry == (prefix + id)) {
			entry = id; // ȥ�����
		}
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
//ͨ�ã��Һ��ѵݹ����QQ�Ŷ�Ӧ������
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
//ͨ�ã����ؽ���
void QQChatBase_Qfh::WaitForUserInput() {
	cout << "�����������QQ��ҳ" << endl;
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
		QQMenu();
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
		file << QQ[i - 1]->Return_ID() << endl;
		file << QQ[i - 1]->Return_ApplyDate();
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
	string qq = qqnumber;
	string txt = ".txt";
	string filename = "QQ\\" + qq + "\\" + qq + "Friendlist.txt";
	file.open(filename, ios::app);
	for (i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	n = QQ[sub]->Return_Friend_List().size();
	if (n > 0)
	{
		file << QQ[sub]->Return_Friend_List()[n - 1]->Return_ID() << endl;
		file << QQ[sub]->Return_Friend_List()[n - 1]->ReturnFriendName() << endl;
		file << QQ[sub]->Return_Friend_List()[n - 1]->ReturnRemarks() << endl;
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
	cout << "����������ѡ��:" << endl;
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
	select = judge_count_menu(temp, 4);

	// �����û�ѡ��
	handleMainMenuSelection(select, menuWidth);
}

void QQChatBase_Qfh::displayMainMenu(int menuWidth)
{
	printCentered("|*---------QQ���ܲ˵�--------------*|", menuWidth);
	cout << "         �û�: " << qqnumber << endl;
	printCentered("|*        ��ѡ��ʹ�õĹ���         *|", menuWidth);
	printCentered("|*        1.���ѹ���               *|", menuWidth);
	printCentered("|*        2.Ⱥ����                 *|", menuWidth);
	printCentered("|*        3.������Ϣ               *|", menuWidth);
	printCentered("|*        4.��ͨ����               *|", menuWidth);
	printCentered("|*        0.�������˵�             *|", menuWidth);
	printCentered("|*---------------------------------*|", menuWidth);
	printCentered("����������ѡ��", menuWidth);
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
	displayFriendMenu(menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 8);

	switch (select)
	{
	case 1:
		AddFriend();
		break;
	case 2:
		ShowFriends();
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
		ShowWeiChatCommonFriends();
		break;
	case 8:
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
	printCentered("|*--------------���ѹ���--------------*|", menuWidth);
	printCentered("|*          1.��Ӻ���                *|", menuWidth);
	printCentered("|*          2.��ʾ����                *|", menuWidth);
	printCentered("|*          3.ɾ������                *|", menuWidth);
	printCentered("|*          4.�鿴��������            *|", menuWidth);
	printCentered("|*          5.�鿴������Ϣ            *|", menuWidth);
	printCentered("|*          6.�޸ĺ��ѱ�ע            *|", menuWidth);
	printCentered("|*          7.�鿴΢�Ź�ͬ����        *|", menuWidth);
	printCentered("|*          8.���΢�Ź�ͬ����        *|", menuWidth);
	printCentered("|*          0.����QQ���˵�            *|", menuWidth);
	printCentered("|*------------------------------------*|", menuWidth);
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
	printCentered("|*----------------Ⱥ������-------------*|", menuWidth);
	printCentered("|*              0.QQ����Ⱥ               *|", menuWidth);
	printCentered("|*              1.΢������Ⱥ             *|", menuWidth);
	printCentered("|*       random_input������һ���˵�      *|", menuWidth);
	printCentered("|*---------------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handleQQGroupMenu(int menuWidth)
{
	system("cls");
	displayQQGroupMenu(menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 11);

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
		ShowQQGroup();
		break;
	case 5:
		AgreeMember();
		break;
	case 6:
		AddGroupAdmin();
		break;
	case 7:
		DeleteGroupMember();
		break;
	case 8:
		ShowGroupInformation();
		break;
	case 9:
		CreatTemporaryGroup();
		break;
	case 10:
		JoinTemporaryGroup();
		break;
	case 11:
		InviteGroupMember();
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
	printCentered("|*----------��ѡ��ʹ�õ�Ⱥ����----------*|", menuWidth);
	printCentered("|*            1.��Ⱥ                *|", menuWidth);
	printCentered("|*            2.��Ⱥ                *|", menuWidth);
	printCentered("|*            3.����Ⱥ                *|", menuWidth);
	printCentered("|*            4.�鿴�Ѽ����Ⱥ        *|", menuWidth);
	printCentered("|*            5.�鿴��Ⱥ����            *|", menuWidth);
	printCentered("|*            6.���QQȺ����Ա          *|", menuWidth);
	printCentered("|*            7.�߳�Ⱥ��Ա              *|", menuWidth);
	printCentered("|*            8.�鿴Ⱥ��Ա��Ϣ          *|", menuWidth);
	printCentered("|*            9.������ʱ������          *|", menuWidth);
	printCentered("|*            10.������ʱ������         *|", menuWidth);
	printCentered("|*            11.������ѽ�Ⱥ           *|", menuWidth);
	printCentered("|*            0.������һ���˵�              *|", menuWidth);
	printCentered("|*--------------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handleWeChatGroupMenu(int menuWidth)
{
	system("cls");
	displayWeChatGroupMenu(menuWidth);

	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	int select = judge_count_menu(tempstr, 6);

	switch (select)
	{
	case 1:
		QuitGroup();
		break;
	case 2:
		CreatQQgroup();
		break;
	case 3:
		ShowQQGroup();
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
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::displayWeChatGroupMenu(int menuWidth)
{
	printCentered("|*--------��ѡ��ʹ�õ�Ⱥ����--------*|", menuWidth);
	printCentered("|*          1.��Ⱥ                  *|", menuWidth);
	printCentered("|*          2.����Ⱥ                *|", menuWidth);
	printCentered("|*          3.�鿴�Ѽ����Ⱥ        *|", menuWidth);
	printCentered("|*          4.�߳�Ⱥ��Ա            *|", menuWidth);
	printCentered("|*          5.�鿴Ⱥ��Ա��Ϣ        *|", menuWidth);
	printCentered("|*          6.������ѽ�Ⱥ          *|", menuWidth);
	printCentered("|*          0.�����ϼ��˵�           *|", menuWidth);
	printCentered("|*----------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handlePersonalInfoMenu(int menuWidth)
{
	system("cls");
	displayPersonalInfoMenu(menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 5);

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
		QQMenu();
		return;
	}
}

void QQChatBase_Qfh::displayPersonalInfoMenu(int menuWidth)
{
	printCentered("|*------------������Ϣ����--------------*|", menuWidth);
	printCentered("|*           1.�鿴������Ϣ             *|", menuWidth);
	printCentered("|*           2.�޸�����                 *|", menuWidth);
	printCentered("|*           3.�޸�����                 *|", menuWidth);
	printCentered("|*           4.�޸�ǩ��                 *|", menuWidth);
	printCentered("|*           5.�޸ĵ�ַ                 *|", menuWidth);
	printCentered("|*           0.������һ���˵�           *|", menuWidth);
	printCentered("|*--------------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handleServiceMenu(int menuWidth)
{
	system("cls");
	displayServiceMenu(menuWidth);

	string temp;
	cin >> temp;
	judge_flush(stdin);
	int select = judge_count_menu(temp, 2);

	switch (select)
	{
	case 1:
		CreateWeiBo();
		break;
	case 2:
		LinkWeiChat(); // ��΢�ŵ���link
		break;
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
	printCentered("|*------------��¼������--------------*|", menuWidth);
	printCentered("|*             1.QQ��¼΢��               *|", menuWidth);
	printCentered("|*             2.QQ��¼΢��               *|", menuWidth);
	printCentered("|*             0.������һ���˵�           *|", menuWidth);
	printCentered("|*--------------------------------------*|", menuWidth);
}


//�Ӻ���
void QQChatBase_Qfh::AddFriend()
{
	system("CLS");
	string id;
	bool flag = false;//��־��û�ҵ�Ҫ��ӵ�QQ
	cout << "������Ҫ��Ӻ��ѵ�QQ��" << endl;
	cin >> id;
	judge_flush(stdin);
	if (id == qqnumber)
	{
		cout << "��������Լ�Ϊ���ѣ�" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	// ���ҵ�ǰQQ����Ϣ

	int sub = -1;
	string subname;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			subname = QQ[i]->Return_Name();
			break;
		}
	}
	//ʧ�ܴ���
	if (sub == -1) {
		cout << "û���ҵ���ǰQQ��Ϣ�������������" << endl;
		if (getchar() != EOF)QQMenu();
		return;
	}


	for (const auto& friendObj : QQ[sub]->Return_Friend_List())
	{
		if (id == friendObj->Return_ID())
		{
			cout << "������Ӵ˺���,�����������" << endl;
			if (getchar() != EOF)
				QQMenu();
			return;
		}
	}
	//����Ҫ��ӵ�QQ����Ϣ�Ƿ����
	int subfriend = -1;
	string name;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == id)
		{
			flag = true;
			subfriend = i;
			name = QQ[i]->Return_Name();
			cout << "���ͺ�������ɹ�����ȴ��Է�ȷ��" << endl;
			break;
		}
	}

	if (subfriend == -1)
	{
		cout << "��QQ��û��ע�ᣬ���������������QQ��" << endl;
		cout << "1.��������QQ����Ӻ���" << endl;
		cout << "0.����QQ��ҳ" << endl;
		cout << "����������ѡ��" << endl;
		string temp;
		cin >> temp;
		judge_flush(stdin);
		int select = judge_count_menu(temp, 1);
		switch (select)
		{
		case 1:
			AddFriend();
			return;
		case 0:
			QQMenu();
			return;
		default:
			QQMenu();
			return;
		}
	}
	//���ͺ�������
	string mark = "&";
	string ID = mark + id;//&��ʾ����������ĺ��ѵ���Ϣ�б�
	string friendfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string remarks = "δ��ע";

	//���µ�ǰ�û������б�
	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	ofstream file(friendfilename, ios::app);//׷�Ӻ���
	file << ID << endl;
	file << name << endl;
	file << remarks << endl;
	file << " " << endl;//�����жϼ�������
	file.close();

	//�����QQ�ļ�����ӱ�QQ
	friendfilename = "QQ\\" + id + "\\" + id + "Friendlist.txt";
	subname = "$" + subname;
	QQ[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subname, qqnumber));

	ofstream friendfile(friendfilename, ios::app);
	friendfile << "$" << QQ[sub]->Return_ID() << endl;
	friendfile << QQ[sub]->Return_Name() << endl;
	friendfile << remarks << endl;
	friendfile << " " << endl;//�����жϼ�������
	friendfile.close();
	cout << "�����������" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

//ɾ���ѣ�BUG��Xstring���⣺��ʱ���޸���
void QQChatBase_Qfh::DeleteFriend()
{
	system("CLS");

	int sub = -1;
	// һ���Բ��Ҳ�������
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	// ��ʾ�����б�
	cout << "�����б����£�" << endl;
	for (int i = 0; i < QQ[sub]->Return_Friend_Number(); i++)
	{
		// �����������Ƽ���߼�
		if (QQ[sub]->Return_Friend_List()[i]->ReturnFriendName()[0] == '$' ||
			QQ[sub]->Return_Friend_List()[i]->ReturnFriendName()[0] == '&')
			continue;
		cout << "����:" << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "QQ:" << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "��ע��" << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl << endl;
	}

	// ɾ����QQ�еĺ���
	string delq;
	cout << "������Ҫɾ�����ѵ�QQ��(��#������ҳ)" << endl;
	cin >> delq;
	judge_flush(stdin);
	if (delq == "#")
	{
		QQMenu();
		return;
	}

	// ����Ƿ��д˺���
	bool found = false;
	for (const auto& friendObj : QQ[sub]->Return_Friend_List())
	{
		if (friendObj->Return_ID() == delq)
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << "��û�д˺���" << endl;
		cout << "1.��������QQ��" << endl;
		cout << "0.������ҳ" << endl;
		cout << "����������ѡ��" << endl;
		string temp;
		cin >> temp;
		judge_flush(stdin);
		int select = judge_count_menu(temp, 1);
		switch (select)
		{
		case 1:
			DeleteFriend();
			return;
		default:
			QQMenu();
			return;
		}
	}

	// �Ӻ����б���ɾ������
	auto& friendList = QQ[sub]->Return_Friend_List();
	friendList.erase(remove_if(friendList.begin(), friendList.end(),
		[&delq](const auto& friendObj) {
			return friendObj->Return_ID() == delq;
		}),
		friendList.end());

	// �޸ĺ�������
	QQ[sub]->Change_Friends_Number(friendList.size()); // ֱ��ʹ�õ�ǰ�Ѹ��µĺ����б��С

	// ɾ���Է��ĺ���
	string currentQQ = QQ[sub]->Return_ID();
	int friendIndex = FindQQIndex(delq); // �Ȳ��Һ�������

	if (friendIndex != -1) {
		auto& friendOfFriendList = QQ[friendIndex]->Return_Friend_List();
		friendOfFriendList.erase(remove_if(friendOfFriendList.begin(), friendOfFriendList.end(),
			[currentQQ](const auto& friendObj) {
				return friendObj->Return_ID() == currentQQ;
			}),
			friendOfFriendList.end());

		// ���º�������
		QQ[friendIndex]->Change_Friends_Number(friendOfFriendList.size());
	}

	// ���º����ļ�
	UpdateFriendFile(sub);
	if (friendIndex != -1) {
		UpdateFriendFile(friendIndex);
	}

	cout << "ɾ�����ѳɹ�" << endl;
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;

}
//չʾ������Ϣ
void QQChatBase_Qfh::ShowFriends()
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
	if (sub == -1)return;//ʧ�ܴ���

	int friendsnum = QQ[sub]->Return_Friend_List().size();
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{    //&���������б�,$��������Լ�Ϊ�����б�
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//�ж���Ӻ��ѱ��
		{
			friendsnum--;//ȥ����ӵ�$��&��ǵĺ���

		}
	}
	cout << "���ĺ��Ѹ���Ϊ��" << friendsnum << endl;
	int count = 0;
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
		{
			continue;//��������ӡ
		}
		cout << "��" << count + 1 << "λ����" << endl;
		cout << "����:" << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "QQID:" << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "��ע:" << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		cout << endl;
		count++;
	}

	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

//ͬ���������
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
	//��ȡ������QQ
	while (subfile.get(c))
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
	subfile.close();
	if (flag == false)
	{
		cout << "û�к�������" << endl;
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	for (int i = 0; i < temp.size(); i++) {
		fdqq = temp[i];
		friendqqfilename = "QQ\\" + fdqq + "\\" + fdqq + "Friendlist.txt";
		cout << "���Ƿ�ͬ��" << temp[i] << "�ĺ�������?" << endl;
		cout << "1.ͬ��" << endl;
		cout << "0.�ܾ�" << endl;
		string FriendApplyQQ = temp[i];
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		int select = judge_count_menu(tempstr, 1);


		string content;
		string msg;
		fstream friendqqfile;
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
		case 1: {
			//������������Ϣ
			vector<string> myaceptcontent;
			ReadFileToVector(subfilename, myaceptcontent);
			UpdateFriendApplication(myaceptcontent, "$", FriendApplyQQ);
			WriteVectorToFile(subfilename, myaceptcontent);

			// ���������Ϣ
			vector<string> friendaceptcontent;
			ReadFileToVector(friendqqfilename, friendaceptcontent);
			UpdateFriendApplication(friendaceptcontent, "&", qqnumber);
			WriteVectorToFile(friendqqfilename, friendaceptcontent);

			// ���ҵ�ǰ�û��������˵�����
			int sub = FindQQIndex(qqnumber);
			int friendqq = FindQQIndex(fdqq);

			if (sub != -1 && friendqq != -1) {
				string name = QQ[friendqq]->Return_Name();
				string id = QQ[friendqq]->Return_ID();

				// ����˫���ĺ����б�
				QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, id));
				QQ[sub]->Change_Friends_Number(QQ[sub]->Return_Friend_Number() + 1);

				QQ[friendqq]->Return_Friend_List().push_back(new QQFriends_Qfh(QQ[sub]->Return_Name(), qqnumber));
				QQ[friendqq]->Change_Friends_Number(QQ[friendqq]->Return_Friend_Number() + 1);
			}

			cout << "ȷ������ɹ����������������һ��" << endl;
			if (getchar() != EOF)
				break;
		}
		case 0:
		{
			cout << "���Ѿܾ������󣬰������������һ��" << endl;
			//ɾ���������ļ��е�QQ
			subfile.open(subfilename);
			string subfiletemp;
			vector<string> subfilecontent;
			while (!subfile.eof())
			{
				getline(subfile, subfiletemp);
				subfilecontent.push_back(subfiletemp);
			}
			subfilecontent.pop_back();
			//���ԭ���ļ����ݺ͡�$�����
			for (int i = 0; i < size(subfilecontent); i++)
			{
				if (subfilecontent[i] == ("$" + FriendApplyQQ))
				{
					subfilecontent.erase(subfilecontent.begin() + i);//ID
					subfilecontent.erase(subfilecontent.begin() + i);//�ǳ�
					subfilecontent.erase(subfilecontent.begin() + i);//��ע
					subfilecontent.erase(subfilecontent.begin() + i);//����
					break;
				}
			}
			subfile.close();
			subfilecontent.shrink_to_fit();//������С���٣�������������sizeƥ��
			subfile.open(subfilename, ios::out | ios::trunc); //���ԭ������

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

			//��պ��������б�i��&�����
			for (int i = 0; i < friendfilecontent.size(); i++)
			{
				if (friendfilecontent[i] == ("&" + qqnumber))
				{
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);
					friendfilecontent.erase(friendfilecontent.begin() + i);
				}
			}
			friendfilecontent.shrink_to_fit();//������С���٣�������������sizeƥ��
			friendqqfile.open(friendqqfilename, ios::out, ios::trunc);//���ԭ������
			//����д���µ������б�����ļ�
			for (int i = 0; i < friendfilecontent.size(); i++)
			{
				friendqqfile << friendfilecontent[i] << endl;
			}
			friendqqfile.close();
			if (getchar() != EOF)
				break;
		}
		default:
			QQMenu();
			return;
		}
	}
	cout << "���е����봦����ϣ������������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
//����QQȺ
void QQChatBase_Qfh::CreatQQgroup()
{
	system("CLS");

	time_t ti;
	srand((unsigned)time(&ti));//��ǰʱ��Ϊ����
	int temp = rand() % 99999;//���Ⱥ��
	stringstream ss;
	ss << temp;
	string ID;
	ss >> ID;

	cout << "������Ⱥ����: " << endl;
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "����Ⱥ��Ϊ:" << ID << endl;

	int sub = -1;
	QQgroup = ID;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}
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
	//�������޴�Ⱥ
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
		cout << "��û�м����Ⱥ" << endl;
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
	judge_flush(stdin);

	string filename = "QQ\\Groups\\" + id + "\\" + id + ".txt";
	ifstream infile(filename, ios::in);

	if (!infile) {
		ShowMenu("û�д�Ⱥ,����������򷵻���ҳ", { "1.��������", "0.������ҳ" });
		string tempstr;
		getline(cin, tempstr);
		judge_flush(stdin);
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
		cout << "�����Ǹ�Ⱥ��Ⱥ��,�޷������Ⱥ" << endl;
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
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
		cout << "��Ⱥû�г�Ա�������������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
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
		cout << "��Ⱥû�д˳�Ա����������" << endl;
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
					QQMenu();
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
					QQMenu();
				return;
			}
		}
	}

	adminfile << adminid << endl;
	adminfile.close();
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
			cout << "��û�м����Ⱥ�����������������#����" << endl;
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
		cout << "��û�д˺��ѣ�����������(������#����)" << endl;
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
	cout << "�����������������ѽ�Ⱥ��������#����QQ��ҳ��" << endl;
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
//��ȡ
void QQChatBase_Qfh::GetQQGroup() //���ļ���ȡ��QQ��Ⱥ�������浽������
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
	system("CLS");
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
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
//������Ⱥ
void QQChatBase_Qfh::AddInGroupMember()
{
	system("CLS");
	cout << "��������������Ⱥ,������#����QQ��ҳ" << endl;
	string groupid;
	cin >> groupid;
	judge_flush(stdin);
	if (groupid == "#")
	{
		QQMenu();
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
			cout << "������Ӵ�Ⱥ" << endl;
			cout << "�����������QQ��ҳ" << endl;
			if (getchar() != EOF)
				QQMenu();
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
		cout << "û�д�Ⱥ�������������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}
	string filename = "QQ\\Groups\\" + groupid + "\\" + groupid + ".txt";
	ofstream ofile;
	ofile.open(filename, ios::app);
	ofile << "$" << qqnumber << endl;
	ofile.close();
	cout << "������Ⱥ�ɹ�,��ȴ�Ⱥ��ͬ��" << endl;
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
//ͬ����Ⱥ
void QQChatBase_Qfh::AgreeMember()//Ⱥ���鿴����
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
		cout << "û�д�Ⱥ,����������򷵻�QQ��ҳ" << endl;
		cout << "1.��������" << endl;
		cout << "0.����QQ��ҳ" << endl;
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
			QQMenu();
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
		cout << "Ⱥ�����ã���ӭ�鿴��Ⱥ����" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "����Ա���ã���ӭ�鿴��Ⱥ����" << endl;
	}
	else
	{
		cout << "�����Ǹ�Ⱥ��Ⱥ�������Ա,�޷������Ⱥ" << endl;
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
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
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
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
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

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
		cout << "û�д�Ⱥ,����������򷵻�QQ��ҳ" << endl;
		cout << "1.��������" << endl;
		cout << "0.����QQ��ҳ" << endl;
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
			QQMenu();
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
		cout << "Ⱥ�����ã���ӭ����Ⱥ��Ա����" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "����Ա���ã���ӭ����Ⱥ��Ա����" << endl;
	}
	else
	{
		cout << "�����Ǹ�Ⱥ��Ⱥ�������Ա,�޷������Ⱥ" << endl;
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
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
		cout << "��Ϊ��ȺȺ�������߳���������κ���" << endl;
		Ownerflag = true;
	}
	else
	{
		cout << "��Ϊ��Ⱥ����Ա�������߳���Ⱥ���͹���Ա�������" << endl;
		Adminflag = true;
	}
	Show_Group_InformationNo_Return(id);
	cout << "������Ҫ�߳��ĳ�ԱQQ��,������#����QQ��ҳ" << endl;
	string DeleteMemberQQ;
	cin >> DeleteMemberQQ;
	judge_flush(stdin);
	if (DeleteMemberQQ == "#")
	{
		QQMenu();
		return;
	}
	//�������QQ�Ƿ���Ⱥ�������Լ�
	bool checkflag = false;//����Ƿ��д˳�Ա
	while (1)
	{
		if (DeleteMemberQQ == GroupOwner || DeleteMemberQQ == qqnumber)
		{
			cout << "�޷��߳�Ⱥ�����Լ������������������#����QQ��ҳ" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				QQMenu();
				return;
			}
			continue;
		}

		for (int i = 0; i < size(GroupMember); i++)//����Ƿ��д˳�Ա
		{
			if (DeleteMemberQQ == GroupMember[i])
			{
				checkflag = true;
				break;
			}
		}

		if (checkflag == false)
		{
			cout << "û�д˳�Ա����������,������#����QQ��ҳ" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				QQMenu();
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
			cout << "�޷��߳�Ⱥ�����Լ������������������#����QQ��ҳ" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				QQMenu();
				return;
			}
			continue;
		}

	}

	//�Ӹó�ԱȺ�б���ɾ����Ⱥ
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

	//�ӱ�Ⱥ��Ա�б���ɾ���˳�Ա��ԭ����������
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
			cout << "�����������QQ���˵�" << endl;
			if (getchar() != EOF)
				QQMenu();
			return;
		}
		else
		{
			cout << "�߳�" << DeleteMemberQQ << "�ɹ�" << endl;
			cout << "�����������QQ���˵�" << endl;
			if (getchar() != EOF)
				QQMenu();
			return;
		}
	}

}
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
	cout << "����Ϊ���ĸ�����Ϣ:" << endl;
	cout << "�ʺ�:" << QQ[sub]->Return_ID() << endl;
	cout << "����:" << QQ[sub]->Return_PassWord() << endl;
	cout << "����:" << QQ[sub]->Return_Name() << endl;
	cout << "����:" << QQ[sub]->Return_Area() << endl;
	cout << "�Ա�" << QQ[sub]->Return_Sex() << endl;
	cout << "ע������:" << QQ[sub]->Return_ApplyDate();
	cout << "����ǩ��:" << QQ[sub]->Return_Autograph() << endl;
	cout << "��������:" << QQ[sub]->Return_bir() << endl;
	cout << endl;
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

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
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
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
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
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
	SaveChange();
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
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
	SaveChange();
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

void QQChatBase_Qfh::SaveChange()
{
	fstream qqfile;
	string qqfilename = "QQ.txt";
	qqfile.open(qqfilename, ios::trunc | ios::out);
	for (int i = 0; i < QQ.size(); i++)
	{
		qqfile << QQ[i]->Return_ID() << endl;
		qqfile << QQ[i]->Return_ApplyDate();
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
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//�ж���Ӻ��ѱ��
		{
			friendsnum--;
		}
	}

	cout << "����" << friendsnum << "������" << endl;
	int friends = 0;
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
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

void QQChatBase_Qfh::ShowFriendInformation()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "�����������ѯ�ĺ���QQ�ţ�������#����QQ���˵�" << endl;
	string FriendQQ;
	cin >> FriendQQ;
	judge_flush(stdin);
	int sub;
	if (FriendQQ == "#")
	{
		QQMenu();
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
			cout << "��û�д˺��ѣ����������������#����QQ���˵�" << endl;
			cin >> FriendQQ;
			judge_flush(stdin);
			if (FriendQQ == "#")
			{
				QQMenu();
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

	cout << "����Ϊ�˺�����Ϣ" << endl;
	cout << "�ʺ�:" << QQ[friendsub]->Return_ID() << endl;
	cout << "����:" << QQ[friendsub]->Return_Name() << endl;
	cout << "��ע:" << QQ[sub]->Return_Friend_List()[friendremarks]->ReturnRemarks() << endl;//��ע������ӡ����ֱ��ͨ��QQ������ȡ
	cout << "�Ա�" << QQ[sub]->Return_Sex() << endl;
	cout << "����ǩ��:" << QQ[friendsub]->Return_Autograph() << endl;
	cout << "���ڵ���:" << QQ[friendsub]->Return_Area() << endl;
	cout << "�û�������:" << QQ[friendsub]->Return_bir() << endl;
	cout << "ע��ʱ��:" << QQ[friendsub]->Return_ApplyDate() << endl;

	cout << endl;
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;

}

void QQChatBase_Qfh::ChangeFriendRemarks()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "�����������޸ĵĺ���QQ�ţ�������#����QQ���˵�" << endl;
	string FriendQQ;
	cin >> FriendQQ;
	judge_flush(stdin);
	int sub;
	if (FriendQQ == "#")
	{
		QQMenu();
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
			cout << "��û�д˺��ѣ����������������#����QQ���˵�" << endl;
			cin >> FriendQQ;
			judge_flush(stdin);
			if (FriendQQ == "#")
			{
				QQMenu();
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
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;

}
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
		QQMenu();
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
			cout << "��û�м����Ⱥ�����������������#����QQ���˵�" << endl;
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

void QQChatBase_Qfh::ShowGroupInformation()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "��������Ҫ��ѯ��Ա��Ϣ��QQȺ,������#����QQ���˵�" << endl;
	string  QQGroupID;
	cin >> QQGroupID;
	judge_flush(stdin);
	if (QQGroupID == "#")
	{
		QQMenu();
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
			cout << "��û�м����Ⱥ�����������������#����QQ���˵�" << endl;
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
	cout << "�����������QQ���˵�" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
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
			cout << "���ѿ�ͨ΢���������ظ���ͨ" << endl;
			cout << "�����������QQ���˵�" << endl;
			if (getchar() != EOF)
				QQMenu();
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
		cout << "�����������QQ���˵�" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;

	default:
		cout << "��ȡ���˿�ͨ����" << endl;
		cout << "�����������QQ���˵�" << endl;
		if (getchar() != EOF)
			QQMenu();
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
		cout << "�����������΢����ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
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
			cout << "û�д�΢�ţ����������������#����΢����ҳ" << endl;
			cin >> linkweichat;
			judge_flush(stdin);
			if (linkweichat == "#")
			{
				QQMenu();
				return;
			}
			continue;
		}
		else
		{
			break;
		}
	}

	cout << "�������΢�źŵ�����" << endl;
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
			cout << "��������������������������#����΢����ҳ" << endl;
			cin >> linkpw;
			judge_flush(stdin);
			if (linkpw == "#")
			{
				QQMenu();
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

	cout << "��΢�ųɹ�,��΢���Ѿ��Զ���¼" << endl;
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

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
		//�����ַ���Ҫerase����
		Links.push_back(GetLinksFileTemp);
	}

	if (Links.size() != 0)
	{
		QQ[sub]->Change_Linked_WeiChat(Links[0]);
	}
}


void QQChatBase_Qfh::ShowWeiChatCommonFriends()
{
	system("CLS");
	int sub;
	int LinkedWeiChat;
	int ThisQQ;

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	for (int i = 0; i < size(WeChatFun.ReturnWeiChatList()); i++)
	{
		string m = QQ[sub]->Return_Linked_WeiChat();
		if (WeChatFun.ReturnWeiChatList()[i]->Return_ID() == QQ[sub]->Return_Linked_WeiChat())
		{
			LinkedWeiChat = i;
			break;
		}
	}

	if (QQ[sub]->Return_Linked_WeiChat() == "")
	{
		cout << "��û�а�΢�ţ����Ȱ�΢��" << endl;
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	cout << "���󶨵�΢�ź�Ϊ" << QQ[sub]->Return_Linked_WeiChat() << endl;
	cout << "���ʹ�΢�ŵĹ�ͬ����������" << endl;

	int FriendFlag = false;
	int CommonFriendNumber = 1;

	WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Get_Friends();
	for (int j = 0; j < size(WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List()); j++)//΢�ź����б�
	{

		FriendFlag = false;

		for (int k = 0; k < QQ.size(); k++)
		{
			QQ[k]->Get_Links();
			//QQ�б����ҵ��˺���
			if (QQ[k]->Return_Linked_WeiChat() == WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List()[j]->Return_ID())
			{
				ThisQQ = k;
				FriendFlag = true;
				break;
			}
		}

		if (FriendFlag == false)
		{
			continue;
		}

		for (int p = 0; p < QQ[sub]->Return_Friend_List().size(); p++)
		{
			if (QQ[sub]->Return_Friend_List()[p]->Return_ID() == QQ[ThisQQ]->Return_ID())
			{
				cout << "��" << CommonFriendNumber << "����ͬ����" << endl;
				cout << "�ʺ�:" << QQ[sub]->Return_Friend_List()[j]->Return_ID();
				cout << "����:" << QQ[sub]->Return_Friend_List()[j]->ReturnFriendName();
				cout << "��ע:" << QQ[sub]->Return_Friend_List()[j]->ReturnRemarks();
				cout << endl;
				CommonFriendNumber++;
				break;
			}
		}
	}
	WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List().clear();
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

void QQChatBase_Qfh::Show_WeiChat_Common_FriendsNo_Return()
{
	system("CLS");
	int sub;
	int LinkedWeiChat;
	int ThisQQ;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	for (int i = 0; i < size(WeChatFun.ReturnWeiChatList()); i++)
	{
		string m = QQ[sub]->Return_Linked_WeiChat();
		if (WeChatFun.ReturnWeiChatList()[i]->Return_ID() == QQ[sub]->Return_Linked_WeiChat())
		{
			LinkedWeiChat = i;
			break;
		}
	}
	if (QQ[sub]->Return_Linked_WeiChat() == "")
	{
		cout << "��û�а�΢�ţ����Ȱ�΢��" << endl;
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	cout << "���󶨵�΢�ź�Ϊ" << QQ[sub]->Return_Linked_WeiChat() << endl;
	cout << "���ʹ�΢�ŵĹ�ͬ����������" << endl;

	int FriendFlag = false;
	int CommonFriendNumber = 1;

	WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Get_Friends();
	for (int j = 0; j < size(WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List()); j++)//΢�ź����б�
	{

		FriendFlag = false;
		for (int k = 0; k < QQ.size(); k++)
		{
			QQ[k]->Get_Links();
			//QQ�б����ҵ��˺���
			if (QQ[k]->Return_Linked_WeiChat() == WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List()[j]->Return_ID())
			{
				ThisQQ = k;
				FriendFlag = true;
				break;
			}
		}

		if (FriendFlag == false)
		{
			continue;
		}

		for (int p = 0; p < QQ[sub]->Return_Friend_List().size(); p++)
		{
			if (QQ[sub]->Return_Friend_List()[p]->Return_ID() == QQ[ThisQQ]->Return_ID())
			{
				cout << "��" << CommonFriendNumber << "����ͬ����" << endl;
				cout << "QQ:" << QQ[sub]->Return_Friend_List()[j]->Return_ID();
				cout << "����:" << QQ[sub]->Return_Friend_List()[j]->ReturnFriendName();
				cout << "��ע:" << QQ[sub]->Return_Friend_List()[j]->ReturnRemarks();
				cout << endl;
				CommonFriendNumber++;
				break;
			}
		}
	}
}

void QQChatBase_Qfh::AddWeiChatCommonFriend()
{
	Show_WeiChat_Common_FriendsNo_Return();

	int sub, subfriend;
	string id;
	string name, subname;
	bool flag = false;
	cout << "������Ҫ��ӵ�΢�Ź�ͬ���ѵ�QQ��" << endl;
	cin >> id;
	judge_flush(stdin);
	if (id == qqnumber)
	{
		cout << "����������Լ�Ϊ����" << endl;
		cout << "�����������QQ��ҳ" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			subname = QQ[i]->Return_Name();
			break;
		}
	}

	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if (id == QQ[sub]->Return_Friend_List()[i]->Return_ID())
		{
			cout << "������Ӵ˺���,�밴���������QQ��ҳ" << endl;
			if (getchar() != EOF)
				QQMenu();
			return;
		}
	}

	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == id)
		{
			flag = true;
			name = QQ[i]->Return_Name();
			subfriend = i;
			cout << "��������ɹ�����ȴ��Է�ȷ��" << endl;
		}
	}
	if (flag == false)
	{
		cout << "��QQ��û��ע�ᣬ���������������QQ��" << endl;
		cout << "1.��������QQ����Ӻ���" << endl;
		cout << "0.����QQ��ҳ" << endl;
		int select;
		string tempstr;
		cin >> tempstr;
		judge_flush(stdin);
		select = judge_count_menu(tempstr, 1);
		switch (select)
		{
		case 1:
			AddFriend();
			return;
		case 0:
			QQMenu();
			return;

		default:
			QQMenu();
			return;
		}

	}
	string mark = "&";
	string ID = mark + id;//&��ʾ����������ĺ��ѵ���Ϣ�б�
	fstream file;
	string friendfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string remarks = "δ��ע";
	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	file.open(friendfilename, ios::app);
	file << ID << endl;
	file << name << endl;
	file << remarks << endl;
	file << " " << endl;//�����жϼ�������
	file.close();
	//�����QQ�ļ�����ӱ�QQ
	friendfilename = "QQ\\" + id + "\\" + id + "Friendlist.txt";
	subname = "$" + subname;
	QQ[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subname, qqnumber));
	file.open(friendfilename, ios::app);
	file << "$" << QQ[sub]->Return_ID() << endl;
	file << QQ[sub]->Return_Name() << endl;
	file << remarks << endl;
	file << " " << endl;//�����жϼ�������
	file.close();
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

void QQChatBase_Qfh::CreatTemporaryGroup()
{
	system("CLS");
	int sub;
	int temp;
	time_t  t;
	srand((unsigned)time(&t));
	temp = rand() % 99999999;
	stringstream ss;
	ss << temp;
	string ID;
	ss >> ID;

	cout << "����������������" << endl;
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "������ʱ�������Ϊ:" << ID << endl;
	QQgroup = ID;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}
	QQ[sub]->Return_Temporary_GroupList().push_back(new QQgroups_Qfh(ID, name, qqnumber));
	AllQQTemporaryGroup.push_back(new QQgroups_Qfh(ID, name, qqnumber));
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

void QQChatBase_Qfh::JoinTemporaryGroup()
{
	system("CLS");
	int sub;
	int ThisTemporaryGroup;
	string TemporaryName;
	string TemporaryOwner;
	for (int i = 0; i < AllQQTemporaryGroup.size(); i++)
	{
		cout << "��" << i + 1 << "����ʱ������" << endl;
		cout << "Ⱥ��:" << ReturnAllQQTemporaryGroup()[i]->Return_Group_ID();
		cout << "Ⱥ����" << ReturnAllQQTemporaryGroup()[i]->Return_Group_Name();
	}
	cout << "��������������Ⱥ�ţ�������#����QQ��ҳ" << endl;
	string TemporaryGroup;
	cin >> TemporaryGroup;
	judge_flush(stdin);
	if (TemporaryGroup == "#")
	{
		QQMenu();
		return;
	}

	bool CheckFlag = false;
	while (1)
	{
		for (int i = 0; i < AllQQTemporaryGroup.size(); i++)
		{
			if (ReturnAllQQTemporaryGroup()[i]->Return_Group_ID() == TemporaryGroup)
			{
				CheckFlag = true;
				break;
			}
			else
			{
				cout << "û�д�������" << endl;
				cout << "����������Ⱥ�Ż�����#����QQ��ҳ" << endl;
				string TemporaryGroup;
				cin >> TemporaryGroup;
				judge_flush(stdin);
				if (TemporaryGroup == "#")
				{
					QQMenu();
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
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}
	for (int i = 0; i < AllQQTemporaryGroup.size(); i++)
	{
		if (ReturnAllQQTemporaryGroup()[i]->Return_Group_ID() == TemporaryGroup)
		{
			ThisTemporaryGroup = i;
			break;
		}
	}
	TemporaryName = ReturnAllQQTemporaryGroup()[ThisTemporaryGroup]->Return_Group_Name();
	TemporaryOwner = ReturnAllQQTemporaryGroup()[ThisTemporaryGroup]->ReturnCreatUserID();

	QQ[sub]->Return_Temporary_GroupList().push_back(new QQgroups_Qfh(TemporaryGroup, TemporaryName, TemporaryOwner));

	cout << "������ʱ������ɹ�" << endl;
	cout << "�����������QQ��ҳ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}