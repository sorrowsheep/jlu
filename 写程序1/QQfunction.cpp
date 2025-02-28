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
#include <algorithm> // 用于 std::sort
#include <locale>   // 用于 std::tolower
#include <unordered_set>
using namespace std;
int Grouptype;
//仿函数与hashcode的结合（通讯录）
bool CompareFriends(QQFriends_Qfh* a,  QQFriends_Qfh* b) {
	// 转化为小写以确保比较不受大小写影响
	return std::tolower(a->ReturnFriendName()[0]) < std::tolower(b->ReturnFriendName()[0]);
}
// quitgroup函数用：删除群列表中的该群
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
// quitgroup函数用：从群成员文件中删除当前用户
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
// quitgroup函数用：从管理员文件中删除当前用户
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

	// 如果用户不是管理员
	if (AdminQQ.size() == 0 || it == AdminQQ.end()) {
		cout << "退出群" << groupid << "成功" << endl;
		cout << "按任意键返回上一层" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	file.open(filename, ios::out | ios::trunc);
	for (const auto& admin : AdminQQ) {
		file << admin << endl;
	}
	file.close();

	cout << "退出群" << groupid << "成功" << endl;
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		QQMenu();
}
// agree函数用：读取文件内容到向量中


	// 读取文件到向量
	static void ReadFileToVector(const string& filename, vector<string>& content) {
		ifstream file(filename);
		string line;
		while (getline(file, line)) {
			content.push_back(line);
		}
		if (!content.empty()) {
			content.pop_back(); // 删除最后一个空行
		}
	}

	// 写向量内容到文件
	static void WriteVectorToFile(const string& filename, const vector<string>& content) {
		ofstream file(filename, ios::trunc); // 清空文件内容
		for (const auto& line : content) {
			file << line << endl;
		}
	}

//delete函数用：更新好友文件列表
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

// delete函数用：查找QQ好友的索引
int QQChatBase_Qfh::FindQQIndex(const string& qqid) {
	for (int i = 0; i < QQ.size(); i++) {
		if (QQ[i]->Return_ID() == qqid) {
			return i;
		}
	}
	return -1; // 未找到
}


//通用：返回界面
void QQChatBase_Qfh::WaitForUserInput() {
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF) {
		QQMenu();
	}
}
//管理员：小菜单
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
//管理员：添加群管理员
void ShowMenu(const string& message, const vector<string>& options) {
	cout << message << endl;
	for (const auto& option : options) {
		cout << option << endl;
	}
}
//待定
vector<WeiBo_Qfh*>& WeiBoChatBase_Qfh::ReturnWeiBolist() {
	return WeiBoList;
}
void WeiBoChatBase_Qfh：：Apply() {
	std::cout << "请登录QQ开通微博" << endl;
}
//保存QQ信息
void QQChatBase_Qfh::SaveQQ()
{
	ofstream file;
	string filename = "QQ.txt";
	file.open("QQ.txt", ios::app);
	int i = 0;
	i = QQ.size();
	if (i > 0)
	{
	  //QQ号:2
		//注册日期 : Mon Dec 16 13 : 00 : 05 2024
		//QQ密码 : 1
		//QQ名称 : 1
		// QQ性别 : 1
		//所在地区 : 1
		//用户生日 : 20000505
		//个性签名 : 1
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
		file.open(filename, ios::trunc | ios::out);//清空文件内容
		file.close();
	}

	file.close();
}
//保存QQ好友信息
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
			file << " "; // 添加一个空行作为分隔符
		}
		file.close();
	}

//将QQ信息从文件中读取
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
		//读取注册日期信息
		for (int i = 0; i < 4; i++)
		{
			file >> temp;
			qage += temp + " ";

		}
		//读取其他信息
		file >> temp;
		qage += temp;
		file >> qqpw >> qqname >> qqsex >> qqpv >> qqag >> qqbir;
		QQ.push_back(new QQ_Qfh(qqnumber, qage, qqpw, qqname, qqsex, qqpv, qqag, qqbir));
		qage.clear();
	}
	file.close();
}
//展示以注册qq
void QQChatBase_Qfh::ShowQQ()
{
	system("CLS");
	GetQQ();
	
	for (int i = 0; i < QQ.size(); i++)
	{
		string applydate = QQ[i]->Return_ApplyDate();
		cout << "QQ号:" << QQ[i]->Return_ID() << endl;
		cout << "QQ密码:" << QQ[i]->Return_PassWord() << endl;
		cout << "QQ名称:" << QQ[i]->Return_Name() << endl;
		cout << "IP地址:" << QQ[i]->Return_Area() << endl;
		cout << "用户生日:" << QQ[i]->Return_bir() << endl;
		calculateAge(applydate);
		cout << "个性签名:" << QQ[i]->Return_Autograph() << endl;
		cout << endl;
	}
	cout << "按任意键返回" << endl;
	if (getchar() != EOF)
		Menu();
}
//QQ页面菜单
void QQChatBase_Qfh::Menu()
{
	const int menuWidth = 130;
	system("CLS");
	int  key = 1;
	bool flag = false;
	printCentered("|*---------QQ页面菜单--------------*|", menuWidth);
	printCentered("|*          1.登陆QQ               *|", menuWidth);
	printCentered("|*          2.注册QQ               *|", menuWidth);
	printCentered("|*          3.找回密码             *|", menuWidth);
	printCentered("|*          4.查看已申请QQ号       *|", menuWidth);
	printCentered("|*          0.返回主菜单           *|", menuWidth);
	printCentered("|*---------------------------------*|", menuWidth);
	cout << "选择您要执行的操作:" << endl;
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

//注册QQ
void QQChatBase_Qfh::Apply()
{
	system("CLS");
	QQ.push_back(new QQ_Qfh(QQ.size() + 1));//通过构造函数创建
	SaveQQ();				   //保存QQ信息
	cout << "按任意键返回" << endl;
	if (getchar() != EOF)
		Menu();
	return;
}
//登录QQ
void QQChatBase_Qfh::Login()
{
	system("CLS");
	string ID;
	bool flag = false;//标记有没有这个要登陆的QQ号
	string PassWord;
	int sub = 0;//记录下标
	cout << "输入您要登陆的QQ:" << endl;
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

		cout << "没有该QQ号，请先申请，按任意键返回" << endl;
		if (getchar() != EOF)
			Menu();
		return;
	}
	if (QQ[sub]->flag != 1)
	{
		cout << "请输入该QQ的密码" << endl;
		cin >> PassWord;
		judge_flush(stdin);
		while (PassWord != QQ[sub]->Return_PassWord())
		{
			cout << "密码输入错误,请重新输入密码(或按“#”返回上一级菜单)" << endl;
			cin >> PassWord;
			if (PassWord == "#") { Menu(); return; }
			judge_flush(stdin);
		}
	}
	qqnumber = ID;
	Get_Friends();//获取好友
	GetQQGroup();//获取群
	Get_Links();//获取绑定的微信
	LogOperation("用户登录", ID);
	cout << "登陆成功" << endl;
	cout << "按任意键开始使用QQ" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
//忘记密码
void QQChatBase_Qfh::Find_PassWord() {
	system("CLS");
	string ID;
	bool flag = false;
	cout << "请输入您要找回密码的QQ号:" << endl;
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
		cout << "没有该QQ号，请检查输入是否正确，按任意键返回" << endl;
		if (getchar() != EOF)
			Menu();
		return;
	}
	cout<<"您的用户密码为：" << QQ[sub]->Return_PassWord() << endl;
	cout << "下面进行密码更新：";
	cout << "请输入该QQ的密码" << endl;
	string PassWord;
	cin >> PassWord;
	judge_flush(stdin);
	while (PassWord != QQ[sub]->Return_PassWord())
	{
		cout << "密码输入错误,请重新输入密码(或按“#”返回上一级菜单)" << endl;
		cin >> PassWord;
		if (PassWord == "#") { Menu(); return; }
		judge_flush(stdin);
	}
	cout << "请输入新的密码" << endl;
	string NewPassWord;
	cin >> NewPassWord;
	judge_flush(stdin);
	while (NewPassWord == "")
	{
		cout << "密码不能为空,请重新输入密码(或按“#”返回上一级菜单)" << endl;
		cin >> NewPassWord;
		if (NewPassWord == "#") { Menu(); return; }
		judge_flush(stdin);
	}
	QQ[sub]->Change_PassWord(NewPassWord);
	SaveQQ();
	cout << "密码修改成功，按任意键返回" << endl;
	if (getchar() != EOF)
		Menu();
	return;
}


//QQ功能菜单
void QQChatBase_Qfh::QQMenu()
{
	system("CLS");
	int select;
	string temp;
	const int menuWidth = 130;

	// 显示主菜单
	displayMainMenu(menuWidth);

	// 获取用户选择
	cin >> temp;
	judge_flush(stdin);
	select = judge_count_menu(temp, 5);

	// 处理用户选择
	handleMainMenuSelection(select, menuWidth);
}

//QQ附属菜单
void QQChatBase_Qfh::displayMainMenu(int menuWidth)
{
	cout << "         用户: " << qqnumber << endl;
	printCentered("|*---------QQ功能菜单--------------*|", menuWidth);
	
	printCentered("|*        1.好友功能               *|", menuWidth);
	printCentered("|*        2.群功能                 *|", menuWidth);
	printCentered("|*        3.个人信息               *|", menuWidth);
	printCentered("|*        4.开通服务               *|", menuWidth);
	printCentered("|*        5.查看历史记录           *|", menuWidth);
	printCentered("|*        0.返回上一层             *|", menuWidth);
	printCentered("|*---------------------------------*|", menuWidth);
	printCentered("选择您要执行的操作", menuWidth);
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
	cout << "         用户: " << qqnumber << endl;
	printCentered("|*--------------好友功能----------------*|", menuWidth);
	printCentered("|*          1.添加好友                  *|", menuWidth);
	printCentered("|*          2.删好友                    *|", menuWidth);
	printCentered("|*          3.修改好友备注              *|", menuWidth);
	printCentered("|*          4.查看好友具体信息          *|", menuWidth);
	printCentered("|*          5.查看好友申请              *|", menuWidth);
	printCentered("|*          6.微信链接好友（链接功能）  *|", menuWidth);
	printCentered("|*          0.返回上一层                *|", menuWidth);
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
	cout << "         用户: " << qqnumber << endl;
	printCentered("|*----------------群管理功能-------------*|", menuWidth);
	printCentered("|*              0.QQ类型群               *|", menuWidth);
	printCentered("|*              1.微信类型群             *|", menuWidth);
	printCentered("|*       random_input返回上一层      *|", menuWidth);
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
	cout << "         用户: " << qqnumber << endl;
	printCentered("|*----------请选择使用的群功能----------*|", menuWidth);
	printCentered("|* status:(1)群成员                     *|", menuWidth);
	printCentered("|*            1.加入群聊                *|", menuWidth);
	printCentered("|*            2.退出群聊                *|", menuWidth);
	printCentered("|* status:(2)群主                       *|", menuWidth);
	printCentered("|*            3.创建群                  *|", menuWidth);
	printCentered("|* status:(3)群管理员                   *|", menuWidth);
	printCentered("|*            4.邀请进群                *|", menuWidth);
	printCentered("|*            5.添加群管理员            *|", menuWidth);
	printCentered("|*            6.查看入群申请            *|", menuWidth);
	printCentered("|*            7.删除群成员              *|", menuWidth);
	printCentered("|* ---------- （link)特殊功能 ------------ *|", menuWidth);
	printCentered("|*            8.创建临时讨论组          *|", menuWidth);
	printCentered("|*            9.加入临时讨论组         *|", menuWidth);
	printCentered("|*            10.查找群成员             *|", menuWidth);
	printCentered("|*            0.返回上一层          *|", menuWidth);
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
	cout << "         用户: " << qqnumber << endl;
	printCentered("|*--------请选择使用的群功能--------*|", menuWidth);
	printCentered("|*          1.退群                 *|", menuWidth);
	printCentered("|* status:群主                     *|", menuWidth);
	printCentered("|*          2.创建群                 *|", menuWidth);
	printCentered("|*          3.邀请进群              *|", menuWidth);
	printCentered("|*          4.踢出群成员            *|", menuWidth);
	printCentered("|*          5.查看群成员信息        *|", menuWidth);
	printCentered("|*          0.返回上一层           *|", menuWidth);
	printCentered("|*----------------------------------*|", menuWidth);
}

void QQChatBase_Qfh::handlePersonalInfoMenu(int menuWidth)
{
	
	displayViewPersonalInfoMenu(menuWidth);
}

void QQChatBase_Qfh::displayViewPersonalInfoMenu(int menuWidth)
{
	cout << "         用户: " << qqnumber << endl;
	ShowMyInformation();
	printCentered("|*--------个人信息-------*|", menuWidth);
	printCentered("|* 1.修改个人信息        *|", menuWidth);
	printCentered("|* 0.返回上一层          *|", menuWidth);
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
	cout << "         用户: " << qqnumber << endl;
	printCentered("|*------------修改个人信息--------------*|", menuWidth);
	printCentered("|*           1.修改密码                 *|", menuWidth);
	printCentered("|*           2.修改名称                 *|", menuWidth);
	printCentered("|*           3.修改签名                 *|", menuWidth);
	printCentered("|*           4.修改IP地址               *|", menuWidth);
	printCentered("|*           0.返回上一层               *|", menuWidth);

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
		LinkWeiChat(); // 绑定微信调用link
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
	cout << "         用户: " << qqnumber << endl;
	printCentered("|*------------（link用）服务功能----------*|", menuWidth);
	printCentered("|*             1.QQ创建微信               *|", menuWidth);
	printCentered("|*             2.QQ链接微信               *|", menuWidth);
	printCentered("|*             3.QQ解绑微信               *|", menuWidth);
	printCentered("|*             4.QQ创建微博               *|", menuWidth);
	printCentered("|*             5.QQ链接微博               *|", menuWidth);
	printCentered("|*             6.QQ解绑微博               *|", menuWidth);
	printCentered("|*             0.返回上一层               *|", menuWidth);
	printCentered("|*----------------------------------------*|", menuWidth);
}

/*好友功能*/

void QQChatBase_Qfh::AddFriend()
{
	system("CLS");
	int sub = 0;
	int subfriend;
	string id;
	string name, subname;
	bool flag = false;
	cout << "请输入添加好友的QQ号" << endl;
	cin >> id;
	judge_flush(stdin);

	// 检查是否添加自己为好友
	if (id == qqnumber)
	{
		cout << "您不能添加自己为好友" << endl;
		cout << "按任意键返回上一页" << endl;
		if (getchar() != EOF)
			handleFriendMenu(130);
		return;
	}

	// 查找当前用户
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			subname = QQ[i]->Return_Name();
			break;
		}
	}

	// 检查好友列表中是否已存在该好友
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if (id == QQ[sub]->Return_Friend_List()[i]->Return_ID())
		{
			cout << "您已添加此好友,请按任意键返回上一页" << endl;
			if (getchar() != EOF)
				handleFriendMenu(130);
			return;
		}
	}

	// 查找要添加的QQ号
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == id)
		{
			flag = true;
			subfriend = i;
			name = QQ[i]->Return_Name();
			// 检查是否已经发过好友申请
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
				cout << "您已经向此QQ发送过好友申请，请等待对方确认。" << endl;
				cout << "按任意键返回上一页" << endl;
				if (getchar() != EOF)
					handleFriendMenu(130);
				return;
			}
			cout << "发送好友申请成功，请等待对方确认" << endl;
		}
	}

	// 如果QQ号未注册
	if (!flag)
	{
		cout << "该QQ还没有注册，按任意键重新输入QQ号" << endl;
		cout << "1.重新输入QQ号添加好友" << endl;
		cout << "0.返回上一页" << endl;
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

	// 记录好友申请
	string mark = "&";
	string ID = mark + id;
	fstream file;
	string friendfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string remarks = "未备注";
	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	file.open(friendfilename, ios::app);
	file << ID << endl;
	file << name << endl;
	file << remarks << endl;
	file << " " << endl; // 用作判断几个好友
	file.close();

	// 向好友QQ文件中添加本QQ
	friendfilename = "QQ\\" + id + "\\" + id + "Friendlist.txt";
	subname = "$" + subname;
	QQ[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subname, qqnumber));
	file.open(friendfilename, ios::app);
	file << "$" << QQ[sub]->Return_ID() << endl;
	file << QQ[sub]->Return_Name() << endl;
	file << remarks << endl;
	file << " " << endl; // 用作判断几个好友
	file.close();
	LogOperation("发出好友申请对方QQ号为：" + QQ[sub]->Return_ID(), qqnumber);

	cout << "按任意键返回上一页" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;
}


void QQChatBase_Qfh::DeleteFriend()
{
	system("CLS");
	//显示所有好友
	int sub;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
		}
	}//找到当前的QQ对象
	cout << "好友列表如下：" << endl;
	for (int i = 0; i < QQ[sub]->Return_Friend_Number(); i++)
	{
		if (QQ[sub]->Return_Friend_List()[i]->ReturnFriendName()[0] == '$' || QQ[sub]->Return_Friend_List()[i]->ReturnFriendName()[i] == '&')
			continue;
		cout << "QQ:" << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "姓名:" << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		
		cout << "备注：" << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		cout << endl;
	}

	//删除本QQ中的好友
	string delq;
	cout << "请输入想删除好友的QQ号，或输入#返回上一页" << endl;
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
		cout << "您没有此好友" << endl;
		cout << "1.重新输入QQ号" << endl;
		cout << "0.返回上一页" << endl;
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
	//删除本QQ中的好友QQ,两文件
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
	cout << "删除好友成功" << endl;
	LogOperation("删除好友，好友QQ号为："+delq, qqnumber);
	cout << "按任意键返回上一页" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;
}
//删除好友(Bug:删除好友后好友列表不更新)
void QQChatBase_Qfh::SortFriendList() {
	int sub = FindQQIndex(qqnumber);
	if (sub == -1) {
		cout << "无法找到当前用户的好友列表。" << endl;
		return;
	}

	auto& friendList = QQ[sub]->Return_Friend_List();
	sort(friendList.begin(), friendList.end(), CompareFriends);
}
void QQChatBase_Qfh::ShowFriends(){
	SortFriendList();
	// 显示好友信息
	int sub = FindQQIndex(qqnumber);
	if (sub == -1) {
		cout << "未找到当前用户的好友列表。" << endl;
		return;
	}

	auto& friendList = QQ[sub]->Return_Friend_List();

	// 显示好友信息
	for (const auto& friendObj : friendList) {
		if (friendObj->Return_ID()[0] == '&'|| friendObj->Return_ID()[0] == '$') continue; // 跳过被标记的好友
		cout << "好友名字: " << friendObj->ReturnFriendName() << endl;
		cout << "QQ号: " << friendObj->Return_ID() << endl;
		cout << "备注: " << friendObj->ReturnRemarks() << endl;
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
	while (subfile.get(c))//获取申请人QQ
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
		cout << "没有好友申请" << endl;
		cout << "按任意键返回上一页" << endl;
		if (getchar() != EOF)
			handleFriendMenu(130);
		return;
	}
	subfile.close();
	for (int i = 0; i < temp.size(); i++) {
		fdqq = temp[i];
		friendqqfilename = "QQ\\" + fdqq + "\\" + fdqq + "Friendlist.txt";
		cout << "您是否同意" << temp[i] << "的好友申请?" << endl;
		LogOperation("查看好友申请,好友QQ号为" + fdqq, qqnumber);
		cout << "1.同意" << endl;
		cout << "0.拒绝" << endl;
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
			Aception.pop_back();//多一个弹出
			for (int i = 0; i < Aception.size(); i++)
			{
				if (Aception[i] == ("$" + FriendApplyQQ))
				{
					Aception[i] = FriendApplyQQ;//将带有好友标记的标记去掉
				}
			}
			subfile.close();
			subfile.open(subfilename, ios::out | ios::trunc); //清空原有文件内容
			for (int i = 0; i < Aception.size(); i++)//重新写入
			{
				subfile << Aception[i] << endl;
			}
			subfile.close();
			friendqqfile.open(friendqqfilename);
			while (!friendqqfile.eof())//获取好友文件内容
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

			friendqqfile.open(friendqqfilename, ios::out | ios::trunc);//清空好友文件内容
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
			cout << "确认申请成功，按任意键处理下一个" << endl;
			if (getchar() != EOF)
				break;
		case 0:
		{
			cout << "您已拒绝该请求，按任意键处理下一个" << endl;
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
					subfilecontent.erase(subfilecontent.begin() + i);//号码
					subfilecontent.erase(subfilecontent.begin() + i);//昵称
					subfilecontent.erase(subfilecontent.begin() + i);//备注
					subfilecontent.erase(subfilecontent.begin() + i);//在文件中存储是四行
					break;
				}
			}
			subfile.close();
			subfilecontent.shrink_to_fit();
			subfile.open(subfilename, ios::out | ios::trunc); //清空原有文件内容

			for (int i = 0; i < size(subfilecontent); i++)
			{
				subfile << subfilecontent[i] << endl;
			}
			subfile.close();

			//删除好友文件中的QQ
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
					friendfilecontent.erase(friendfilecontent.begin() + i);//同理
				}
			}
			friendfilecontent.shrink_to_fit();//请求容器降低其容量和size匹配

			friendqqfile.open(friendqqfilename, ios::out, ios::trunc);//清空原有内容

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
	cout << "所有的申请处理完毕，按任意键返回QQ主菜单" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;
}


// 处理同意好友申请的逻辑
void QQChatBase_Qfh::ProcessAgreeFriend(const string& fdqq, const string& friendqqfilename) {
	// 首先，找到当前用户的好友列表下标
	int sub = FindQQIndex(qqnumber);
	int subfriend=FindQQIndex(fdqq);
	if (sub == -1 || subfriend == -1) {
		cout << "未找到当前用户或目标用户，无法处理好友申请" << endl;
		return;
	}

	// 更新当前用户的好友列表
	string mark = "&";
	string ID = mark + fdqq; // 用于标识该好友的ID
	string name; // 目标用户的名称

	// 从好友列表中找出目标好友的信息
	for (const auto& friendObj : QQ[sub]->Return_Friend_List()) {
		if (friendObj->Return_ID() == ID) {
			name = friendObj->ReturnFriendName();
			break;
		}
	}
	string subfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	// 首先，读取当前用户的好友申请文件，并删除已同意的申请
	fstream subfile;
	subfile.open(friendqqfilename, ios::in);
	vector<string> lines;
	string line;

	// 读取现有申请内容
	while (getline(subfile, line)) {
		if (line.find("$" + fdqq) == string::npos) { // 如果不是要同意的申请，保留
			lines.push_back(line);
		}
	}
	subfile.close();

	// 重新写入文件，排除已同意的申请
	subfile.open(friendqqfilename, ios::out | ios::trunc);
	for (const auto& l : lines) {
		subfile << l << endl;
	}
	subfile.close();

	// 然后将新好友添加到好友列表
	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, fdqq));
	// 更新对方的好友文件
	fstream file;
	string remarks = "未备注";
    file.open(friendqqfilename, ios::app);
	string friendfilename = "QQ\\" + fdqq + "\\" + fdqq + "Friendlist.txt";
	QQ[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(QQ[subfriend]->Return_Name(), qqnumber));

	// 最后，更新当前用户的好友申请文件，删除已同意的申请
	lines.clear();
	while (getline(subfile, line)) {
		if (line.find("$" + fdqq) == string::npos) { // 如果不是要同意的申请，保留
			lines.push_back(line);
		}
	}
	subfile.close();

	// 重新写入文件，排除已同意的申请
	subfile.open(subfilename, ios::out | ios::trunc);
	for (const auto& l : lines) {
		subfile << l << endl;
	}
	subfile.close();
	file.close();

	cout << "已成功添加" << fdqq << "为好友。" << endl;
}

// 处理拒绝好友申请的逻辑
void QQChatBase_Qfh::ProcessRejectFriend(const string& fdqq, const string& subfilename, const string& friendqqfilename) {
	// 在用户的好友申请文件中删除相关的申请信息
	fstream subfile;
	subfile.open(subfilename, ios::in);
	vector<string> lines;
	string line;

	// 读取现有申请内容
	while (getline(subfile, line)) {
		if (line.find("$" + fdqq) == string::npos) { // 如果不是要拒绝的申请，保留
			lines.push_back(line);
		}
	}
	subfile.close();

	// 重新写入文件，排除已拒绝的申请
	subfile.open(subfilename, ios::out | ios::trunc);
	for (const auto& l : lines) {
		subfile << l << endl;
	}
	subfile.close();

	cout << "已拒绝" << fdqq << "的好友申请。" << endl;
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
// 更新好友申请文件
// 删除好友申请
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



//附属项
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
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&'|| (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//判断添加好友标记
		{
			friendsnum--;
		}
	}

	cout << "您有" << friendsnum << "个好友" << endl;
	int friends = 0;
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&'|| (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
		{
			continue;
		}
		cout << "第" << friends + 1 << "位好友" << endl;
		cout << "昵称:" << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "QQ:" << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "备注:" << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		cout << endl;
		friends++;
	}
}
//展示好友具体信息
void QQChatBase_Qfh::ShowFriendInformation()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "请输入您想查询的好友QQ号，或输入#返回上一层" << endl;
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
			cout << "您没有其好友，请重新输入或输入#返回上一层" << endl;
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

	cout << "以下为其为好友信息" << endl;
	cout << "帐号:" << QQ[friendsub]->Return_ID() << endl;
	cout << "姓名:" << QQ[friendsub]->Return_Name() << endl;
	cout << "备注:" << QQ[sub]->Return_Friend_List()[friendremarks]->ReturnRemarks() << endl;//备注单独打印不能直接通过QQ容器获取
	cout << "性别" << QQ[sub]->Return_Sex() << endl;
	cout << "个性签名:" << QQ[friendsub]->Return_Autograph() << endl;
	cout << "所在地区:" << QQ[friendsub]->Return_Area() << endl;
	cout << "用户的生日:" << QQ[friendsub]->Return_bir() << endl;
	cout << "注册时间:" << QQ[friendsub]->Return_ApplyDate() << endl;
	calculateAge(QQ[friendsub]->Return_ApplyDate());
	cout << endl;
	LogOperation("查看好友具体信息,好友QQ号为"+FriendQQ, qqnumber);
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;

}
//改变好友备注
void QQChatBase_Qfh::ChangeFriendRemarks()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "请输入您想修改的好友QQ号，或输入#返回上一层" << endl;
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
			cout << "您没有其为好友，请重新输入或输入#返回上一层" << endl;
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
	cout << "请输入您想修改的备注" << endl;
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
	cout << "修改备注成功" << endl;
	LogOperation("修改好友备注，好友备注为：" + NewRemarks, qqnumber);
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handleFriendMenu(130);
	return;

}


/*                      
* 功能：QQ群
	*/

//创建QQ群
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
	srand((unsigned)time(&ti));//当前时间为种子
	int temp = QQ[sub]->Return_Group_Number()+1;//随机群号
	stringstream ss;
	ss << temp;
	string ID;
	ss >> ID;

	cout << "请输入群名称: " << endl;
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "您的群号为:" << ID << endl;
	QQgroup = ID;
	//找到后出循环
	QQ[sub]->Return_group_List().push_back(new QQgroups_Qfh(ID, name, qqnumber));
	QQ[sub]->Change_group_num(QQ[sub]->Return_Group_Number() + 1);
	SaveQQGroup();
	//写群号到群文件
	string qq = qqnumber;
	string txt1 = "Groupslist.txt";
	string groupListPath = "QQ\\" + qqnumber + "\\" + qqnumber + "Groupslist.txt";
	ofstream FILE(groupListPath, ios::app);
	FILE << ID << endl;
	//公共列表写入
	fstream GroupListFile;
	string GroupListFileName = "Groupslist.txt";
	GroupListFile.open(GroupListFileName, ios::app);
	GroupListFile << ID << endl;

	GroupListFile.close();
	cout << "创建成功" << endl;
	LogOperation("创建QQ群，群号为：" + ID, qqnumber);
    cout << "按任意键返回上一页" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
}
//退群
void QQChatBase_Qfh::QuitGroup()
{
	bool flag = false;
	string groupid;
	cout << "请输入您想退出的QQ群" << endl;
	cin >> groupid;
	judge_flush(stdin);
	int sub = -1;
	//查找有无其为群
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}
	if (sub == -1)return;
	//检查用户是否在该群
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
		cout << "您没有加入其为群" << endl;
		cout << "请选择重新输入或返回菜单" << endl;
		cout << "1.重新输入QQ群" << endl;
		cout << "0.返回菜单" << endl;
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
	LogOperation("退出QQ群，群号为：" + groupid, qqnumber);
	// 删除群列表中的该群
	string subgrouplistfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Groupslist.txt";
	removeGroupFromFile(subgrouplistfilename, groupid);

	// 从群成员文件中删除当前用户
	string groupfilename = "QQ\\Groups\\" + groupid + "\\" + groupid + ".txt";
	removeUserFromGroupFile(groupfilename, qqnumber);

	// 从管理员文件中删除当前用户
	string groupadminfilename = "QQ\\Groups\\" + groupid + "\\" + groupid + "admin.txt";
	removeUserFromAdminFile(groupadminfilename, qqnumber, groupid);
	return;
}
//添加群管理员
void QQChatBase_Qfh::AddGroupAdmin()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "请输入要管理的群号" << endl;

	string id;
	getline(cin, id);

	string filename = "QQ\\Groups\\" + id + "\\" + id + ".txt";
	ifstream infile(filename, ios::in);

	if (!infile) {
		ShowMenu("没有其为群,请重新输入或返回主页", { "1.重新输入", "0.返回主页" });
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
		if (line == 2) { // 获取群主QQ号
			temp.push_back(c);
		}
	}
	outfile.close();

	if (temp != qqnumber) { // 不是群主无法建立管理员
		cout << "您不是该群的群主,无法使用此功能" << endl;
		cout << "按任意键返回上一层" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);;
		return;
	}

	// 获取群成员
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
		cout << "该群没有成员，按任意键返回上一层" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);;
		return;
	}

	string adminfilename = "QQ\\Groups\\" + id + "\\" + id + "admin.txt";
	fstream adminfile(adminfilename, ios::app);
	Show_Group_InformationNo_Return(id);
	cout << "请输入您想添加的管理员QQ" << endl;
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
		cout << "本群没有其为成员请重新输入" << endl;
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
			ShowMenu("该成员已经是管理员，是否进行删除", { "1.删除", "0.返回主菜单" });
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
				cout << "删除管理员成功,按任意键返回" << endl;
				if (getchar() != EOF)
					handleQQGroupMenu(130);;
				return;
			}
		}
	}

	adminfile << adminid << endl;
	adminfile.close();
	LogOperation("添加群管理员，群号为：" + id + "，管理员QQ号为：" + adminid, qqnumber);
	cout << "添加成功，按任意键返回上一页" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
}
//保存群成员
void QQChatBase_Qfh::SaveQQGroup() //每创建一个群便将该群保存成一个.txt文件
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
	//群ID
	//群名称
	//群主ID
	// *
	//群成员
	n = QQ[sub]->Return_group_List().size();
	file << QQ[sub]->Return_group_List()[n - 1]->Return_Group_ID() << endl;
	file << QQ[sub]->Return_group_List()[n - 1]->Return_Group_Name() << endl;
	file << QQ[sub]->Return_group_List()[n - 1]->ReturnCreatUserID() << endl;
	file << "*" << endl;
	file.close();
}
//邀请入群
void QQChatBase_Qfh::InviteGroupMember()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "请输入您要邀请好友进的群号" << endl;
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
		cout << "未找到您的账号信息，请重新登录。" << endl;
		handleQQGroupMenu(130);
		return;
	}

	int ThisGroup = -1;
	while (ThisGroup == -1)
	{
		ThisGroup = FindGroup(invitegroup, sub);
		if (ThisGroup == -1)
		{
			cout << "您没有加入其为群，请重新输入或输入#返回" << endl;
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
	cout << "请输入您要邀请的好友QQ号" << endl;
	string invitefriend;
	cin >> invitefriend;
	judge_flush(stdin);

	while (!IsFriend(invitefriend, sub))
	{
		cout << "您没有其为好友，请重新输入(或输入#返回)" << endl;
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
		cout << "该好友已在该群中,请重新输入好友QQ号或输入#返回" << endl;
		cin >> invitefriend;
		judge_flush(stdin);
		if (invitefriend == "#")
		{
			handleQQGroupMenu(130);
			return;
		}
	}

	AddMemberToGroup(invitegroup, invitefriend);
	cout << "邀请好友进群成功" << endl;
	LogOperation("邀请好友进群，群号为：" + invitegroup + "，好友QQ号为：" + invitefriend, qqnumber);
	cout << "按任意键继续邀请好友进群（或输入#返回上一层）" << endl;
	getchar() == '#' ? handleQQGroupMenu(130):InviteGroupMember();
	return;
}
//找群
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
//是否是好友
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
//是否是群成员
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
//添加群成员
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
//获取QQ群（从文件读取，压容器
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
			temp.pop_back();//把回车弹出去
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
	//获取群成员
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
	//获取群管理员QQ
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
		QQGroupMemberFileContent.erase(QQGroupMemberFileContent.begin());//群主已经读取完了扔了
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
			QQ[sub]->Return_group_List()[i]->Return_Admins_ID().pop_back();//不等于0才会多读一个因为换行
		}
		adminfile.close();
	}
}
//显示群成员
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
	cout << "您共有" << QQ[sub]->Return_group_List().size() << "个群" << endl;
	for (int i = 0; i < QQ[sub]->Return_group_List().size(); i++)
	{
		if (QQ[sub]->Return_group_List()[i]->Return_Group_ID()[0] == '$' || QQ[sub]->Return_group_List()[i]->Return_Group_ID()[0] == '&')
			cout << "第" << i + 1 << "个群" << endl;
		cout << "群号:" << QQ[sub]->Return_group_List()[i]->Return_Group_ID() << endl;
		cout << "群名称:" << QQ[sub]->Return_group_List()[i]->Return_Group_Name() << endl;
		cout << "群主:" << QQ[sub]->Return_group_List()[i]->ReturnCreatUserID() << endl;
		cout << endl;
	}
}
//加群
void QQChatBase_Qfh::AddInGroupMember()
{
	system("CLS");
	cout << "请输入您想加入的群（或输入#返回上一层）" << endl;
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
			cout << "您已添加其为群" << endl;
			cout << "按任意键返回上一层" << endl;
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
		CheckGroupListFile.open(GetLinkFileName, ios::out);//如果没有就创建
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
		cout << "没有该群，按任意键返回上一层" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);
		return;
	}
	string filename = "QQ\\Groups\\" + groupid + "\\" + groupid + ".txt";
	ofstream ofile;
	ofile.open(filename, ios::app);
	ofile << "$" << qqnumber << endl;
	ofile.close();
	LogOperation( "申请加群，群号："+groupid, qqnumber);
	cout << "申请加群成功,请等待群主或管理员同意" << endl;
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
	return;
}
//查看申请同意入群
void QQChatBase_Qfh::AgreeMember()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "请输入要管理的群号" << endl;
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
		cout << "没有其为群,请重新输入或返回上一层" << endl;
		cout << "1.重新输入" << endl;
		cout << "0.返回上一层" << endl;
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
		if (line == 2) //获取群主QQ号
		{
			temp.push_back(c);
		}

	}
	string OwnerQQ = temp;
	//获取群管理员QQ
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
		cout << "查看入群申请身份：群主" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "查看入群申请身份：管理员" << endl;
	}
	else
	{
		cout << "您不是该群的群主或管理员,无法管理该群" << endl;
		cout << "按任意键返回上一层" << endl;
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
		cout << "没有加群申请" << endl;
		cout << "按任意键返回上一层" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);
		return;
	}
	outfile.close();
	for (int i = 0; i < tempstr.size(); i++)
	{
		cout << "您是否同意" << tempstr[i] << "入群?" << endl;
		cout << "1.同意" << endl;
		cout << "0.拒绝" << endl;
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
					msg.push_back(ch[i]);//读取文件内容
				}
				msg.push_back('\n');

			}
			for (int i = 0; i < size(msg); i++)//将未加入标记删除
			{
				if (msg[i] == '$')
				{
					msg.erase(msg.begin() + i);
					break;
				}
			}
			msg.pop_back();
			outfile.close();
			outfile.open(filename, ios::out, ios::trunc); //清空原有文件内容
			outfile << msg;
			cout << "确认申请成功" << endl;
			LogOperation( "同意入群，群号："+id+"申请人："+tempstr[i], qqnumber);
			outfile.close();
			outfile.open(filename1, ios::app);
			outfile << id << endl;
			outfile.close();
			break;
		default:
			cout << "您已拒绝该请求" << endl;
			outfile.open(filename);
			while (!outfile.eof())
			{

				char ch[1000];
				outfile.getline(ch, 1000);
				for (int i = 0; i < strlen(ch); i++)
				{
					msg.push_back(ch[i]);//读取文件内容
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
						msg.erase(msg.begin() + n); //删除申请人QQ
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
			outfile.open(filename, ios::out, ios::trunc);//清空原有内容
			outfile << msg;
			outfile.close();
		}
	}
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
	return;
}
//删除群成员
void QQChatBase_Qfh::DeleteGroupMember()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "请输入要管理的群号" << endl;
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
		cout << "没有其为群,请重新输入或返回上一层" << endl;
		cout << "1.重新输入" << endl;
		cout << "0.返回上一层" << endl;
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
	//获取群主QQ
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
		if (line == 2) //获取群主QQ号
		{
			temp.push_back(c);
		}
	}
	GroupOwner = temp;//群主QQ
	//获取群管理员QQ
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
	AdminQQ.pop_back();//为了清除换行符号

	//判断是否是管理员或群主
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
		cout << "群成员管理身份：群主" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "群成员管理身份：管理员" << endl;
	}
	else
	{
		cout << "您不是该群的群主或管理员,无法管理该群" << endl;
		cout << "按任意键返回上一层" << endl;
		if (getchar() != EOF)
			handleQQGroupMenu(130);
		return;
	}
	outfile.close();
	temp.clear();
	//获取群成员
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
	GroupMember.pop_back();//清除换行符号
	bool Ownerflag = false;
	Adminflag = false;
	if (qqnumber == GroupOwner)
	{
		cout << "您为其为群群主可以踢出除您外的任何人" << endl;
		Ownerflag = true;
	}
	else
	{
		cout << "您为其为群管理员，可以踢出除群主和管理员以外的人" << endl;
		Adminflag = true;
	}
	Show_Group_InformationNo_Return(id);
	cout << "请输入要踢出的成员QQ号,或输入#返回上一层" << endl;
	string DeleteMemberQQ;
	cin >> DeleteMemberQQ;
	judge_flush(stdin);
	if (DeleteMemberQQ == "#")
	{
		handleQQGroupMenu(130);
		return;
	}
	//检查输入QQ是否是群主或是自己
	bool checkflag = false;//检查是否有其为成员
	while (1)
	{
		if (DeleteMemberQQ == GroupOwner || DeleteMemberQQ == qqnumber)
		{
			cout << "无法踢出群主或自己，请重新输入或输入#返回上一层" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				handleQQGroupMenu(130);
				return;
			}
			continue;
		}

		for (int i = 0; i < size(GroupMember); i++)//检查是否有其为成员
		{
			if (DeleteMemberQQ == GroupMember[i])
			{
				checkflag = true;
				break;
			}
		}

		if (checkflag == false)
		{
			cout << "没有其为成员请重新输入,或输入#返回上一层" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				handleQQGroupMenu(130);
				return;
			}
			continue;
		}

		if (Adminflag == true)//如果本账号是管理员则检查踢出成员是否是管理员
		{
			for (int i = 0; i < AdminQQ.size(); i++)
			{
				if (AdminQQ[i] == DeleteMemberQQ)
				{
					cout << "管理员不能踢出其他管理员,请重新输入" << endl;
					cin >> DeleteMemberQQ;
					judge_flush(stdin);
					continue;
				}
			}
		}


		//检查是否是群主或自己
		if (DeleteMemberQQ != GroupOwner && DeleteMemberQQ != qqnumber)
		{
			break;
		}
		else
		{
			cout << "无法踢出群主或自己，请重新输入或输入#返回上一层" << endl;
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

	//从该成员群列表中删除其为群
	fstream membergrouplistfile;
	string membergrouplistfilename = "QQ\\" + DeleteMemberQQ + "\\" + DeleteMemberQQ + "Groupslist.txt";
	string membergrouplisttemp;
	vector<string> memebergrouplistcontent;
	membergrouplistfile.open(membergrouplistfilename);//打开被删除成员的群列表
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
			memebergrouplistcontent.erase(memebergrouplistcontent.begin() + i);//删除该成员中的群
			break;
		}
	}
	memebergrouplistcontent.shrink_to_fit();
	membergrouplistfile.open(membergrouplistfilename, ios::trunc | ios::out);//清空原来的文件
	for (int i = 0; i < size(memebergrouplistcontent); i++)
	{
		membergrouplistfile << memebergrouplistcontent[i] << endl;//重新写入
	}
	membergrouplistfile.close();

	//从本群成员列表中删除其为成员，原理类似上面
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
	//如果该成员是管理员则从管理员列表中删除该QQ
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
			cout << "踢出" << DeleteMemberQQ << "成功" << endl;
			cout << "按任意键返回上一层" << endl;
			if (getchar() != EOF)
				handleQQGroupMenu(130);
			return;
		}
		else
		{
			cout << "踢出" << DeleteMemberQQ << "成功" << endl;
			LogOperation( "踢出群成员，群号："+id+"被踢出人："+DeleteMemberQQ, qqnumber);
			cout << "按任意键返回上一层" << endl;
			if (getchar() != EOF)
				handleQQGroupMenu(130);
			return;
		}
	}

}
/// <summary>
/// 辅助项
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
	cout << "您共有" << QQ[sub]->Return_Group_Number() << "个群" << endl;
	for (int i = 0; i < QQ[sub]->Return_Group_Number(); i++)
	{
		cout << "第" << i + 1 << "个群" << endl;
		cout << "群号:" << QQ[sub]->Return_group_List()[i]->Return_Group_ID() << endl;
		cout << "群名称:" << QQ[sub]->Return_group_List()[i]->Return_Group_Name() << endl;
		cout << "群主:" << QQ[sub]->Return_group_List()[i]->ReturnCreatUserID() << endl;
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
			cout << "您没有加入其为群，请重新输入或输入#返回上一层" << endl;
			cin >> QQGroupID;
			judge_flush(stdin);
			continue;
		}
	}

	system("CLS");
	bool AdminFlag = false;//表示该成员是否是管理员
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

		Thisqqnumber = QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers()[i];//从群列表获取群成员QQ
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
			cout << "第" << i + 1 << "个成员信息:" << endl;
			cout << "帐号:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "姓名:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "群成员属性:群主" << endl;
			cout << "所在地区:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "个性签名:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
		else if (AdminFlag == true)
		{
			cout << "第" << i + 1 << "个成员信息:" << endl;
			cout << "帐号:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "姓名:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "群成员属性:管理员" << endl;
			cout << "所在地区:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "个性签名:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
			AdminFlag = false;
		}

		else
		{
			cout << "第" << i + 1 << "个成员信息:" << endl;
			cout << "帐号:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "姓名:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "群成员属性:普通成员" << endl;
			cout << "所在地区:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "个性签名:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
	}

	cout << endl;
}
//查找群成员
void QQChatBase_Qfh::ShowGroupInformation()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "请输入QQ群号以查询成员信息,或输入#返回上一层" << endl;
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
			cout << "您没有加入该群，请重新输入或输入#返回上一层" << endl;
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

		Thisqqnumber = QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnGroupMembers()[i];//从群列表获取群成员QQ
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
			cout << "第" << i + 1 << "个成员信息:" << endl;
			cout << "群成员类型:群主" << endl;
			cout << "帐号:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "姓名:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "所在地区:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "个性签名:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
		else if (AdminFlag == true&&(Thisqqnumber != QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnCreatUserID()))
		{
			
			cout << "第" << i + 1 << "个成员信息:" << endl;
			cout << "群成员类型:管理员" << endl;
			cout << "帐号:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "姓名:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "所在地区:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "个性签名:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
			AdminFlag = false;
		}
		else if(AdminFlag == false&&(Thisqqnumber != QQ[sub]->Return_group_List()[ThisQQGroupID]->ReturnCreatUserID()))
		{
			cout << "第" << i + 1 << "个成员信息:" << endl;
			cout << "群成员类型:普通成员" << endl;
			cout << "帐号:" << QQ[ThisQQ]->Return_ID() << endl;
			cout << "姓名:" << QQ[ThisQQ]->Return_Name() << endl;
			cout << "所在地区:" << QQ[ThisQQ]->Return_Area() << endl;
			cout << "个性签名:" << QQ[ThisQQ]->Return_Autograph() << endl;
			cout << endl;
		}
	}

	cout << endl;
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handleQQGroupMenu(130);
	return;
}

/*个人信息模块*/

//展示个人信息
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
	
	cout << "         个人信息如下：             \n";
	cout << "\t昵称: " << QQ[sub]->Return_Name() << "\t性别: " << QQ[sub]->Return_Sex() << endl;
	cout << "\t帐号: " << QQ[sub]->Return_ID() << endl;
	cout << "\t密码: " << QQ[sub]->Return_PassWord() << endl;
	cout << "\t注册日期: " << QQ[sub]->Return_ApplyDate() << endl;

	cout << "\t "; calculateAge(QQ[sub]->Return_ApplyDate());

	cout << "\t生日: " << QQ[sub]->Return_bir() << endl;
	cout << "\t地区: " << QQ[sub]->Return_Area() << endl;
	cout << "\t个性签名: " << QQ[sub]->Return_Autograph() << endl;

}
//改变个人信息
void QQChatBase_Qfh::Change_PassWord()
{
	system("CLS");
	cout << "输入您的新密码" << endl;
	string pw;
	string pwagin;
	cin >> pw;
	judge_flush(stdin);
	cout << "再次确认您的新密码" << endl;
	cin >> pwagin;
	judge_flush(stdin);
	while (1)
	{
		if (pw != pwagin)
		{
			cout << "两次密码不符，请重新输入" << endl;
			cin >> pw;
			judge_flush(stdin);
			cout << "再次确认您的新密码" << endl;
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
	cout << "修改密码成功" << endl;
	LogOperation( "修改密码，新密码："+pw, qqnumber);
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handlePersonalInfoMenu(130);
	return;
}
void QQChatBase_Qfh::Change_Name()
{
	system("CLS");
	string newname;
	cout << "输入您的新名字" << endl;
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

	cout << "修改名称成功" << endl;
	LogOperation( "修改昵称，新昵称："+newname, qqnumber);
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handlePersonalInfoMenu(130);
	return;
}
void QQChatBase_Qfh::Change_AutoGraph()
{
	system("CLS");
	string autograph;
	cout << "输入您的新签名" << endl;
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
	cout << "修改个新签名成功" << endl;
	LogOperation( "修改个性签名，新签名："+autograph, qqnumber);
	SaveChange();
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handlePersonalInfoMenu(130);
	return;
}
void QQChatBase_Qfh::Change_Area()
{
	system("CLS");
	string Area;
	cout << "输入您的地区" << endl;
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
	LogOperation( "修改IP地址，新IP："+Area, qqnumber);
	SaveChange();
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF)
		handlePersonalInfoMenu(130);
	return;
}
//保存修改
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



/*链接接模块*/
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

	//判断是否已经开通微博
	for (int i = 0; i < WeiBoFun.ReturnWeiBolist().size(); i++)
	{
		if (WeiBoFun.ReturnWeiBolist()[i]->Return_ID() == qqnumber)
		{
			cout << "您已开通微博" ;
			cout << "     按任意键返回上一层" << endl;
			if (getchar() != EOF)
				handleServiceMenu(130);
			return;
		}
	}

	cout << "您的微博号:" << qqnumber << endl;
	cout << "姓名:" << QQ[sub]->Return_Name() << endl;
	cout << "是否要开通微博？" << endl;
	cout << "1.确定" << endl;
	cout << "0.取消" << endl;
	int select;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 1);
	switch (select)
	{
	case 1:
		WeiBoFun.ReturnWeiBolist().push_back(new WeiBo_Qfh(qqnumber));
		CreateDirectory(WeiBoDirectory.c_str(), NULL);//创建文件夹
		WeiBoFun.SaveWeiBo();
		cout << "开通微博成功" << endl;
		LogOperation( "开通微博", qqnumber);
		cout << "按任意键返回上一层" << endl;
		if (getchar() != EOF)
			handleServiceMenu(130);
		return;

	default:
		cout << "您取消了开通创建" << endl;
		cout << "按任意键返回上一层" << endl;
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

	// 查找当前QQ号的索引
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	// 判断当前是否已经开通微信
	for (int i = 0; i < WeChatFun.ReturnWeiChatList().size(); i++)
	{
		if (WeChatFun.ReturnWeiChatList()[i]->Return_ID() == qqnumber)
		{
			cout << "您已开通微信" << endl;
			cout << "     按任意键返回上一层" << endl;
			if (getchar() != EOF)
				handleServiceMenu(130);
			return;
		}
	}

	cout << "您的微信号: " << qqnumber << endl;
	cout << "姓名: " << QQ[sub]->Return_Name() << endl;
	cout << "是否要开通微信？" << endl;
	cout << "1.确定" << endl;
	cout << "0.取消" << endl;

	int select;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 1);

	switch (select)
	{
	case 1:
		// 创建微信帐户
		WeChatFun.ReturnWeiChatList().push_back(new Weixin_Qfh(qqnumber));
		CreateDirectory(WeChatDirectory.c_str(), NULL); // 创建文件夹
		WeChatFun.SaveWeChat(); // 保存微信信息
		cout << "开通微信成功" << endl;
		LogOperation( "开通微信", qqnumber);
		cout << "按任意键返回上一层(或按#进入微信页面)" << endl;
		if (getchar() == '#') { SwitchToWeChat(qqnumber); }
			else handleServiceMenu(130);
		return;

	default:
		cout << "您取消了创建" << endl;
		cout << "按任意键返回上一层" << endl;
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
		cout << "您已经绑定微信" << QQ[ThisQQ]->Return_Linked_WeiChat() << endl;
		string temp = QQ[ThisQQ]->Return_Linked_WeiChat();
		for (int i = 0; i < WeChatFun.ReturnWeiChatList().size(); i++)
		{
			if (WeChatFun.ReturnWeiChatList()[i]->Return_ID() == temp)
			{
				WeChatFun.ReturnWeiChatList()[i]->flag = 1;
				cout << "该微信已经自动登录" << endl;
				break;
			}
		}
		cout << "按任意键返回返回上一层(或按#进入微信页面)" << endl;
		if (getchar() == '#'){ SwitchToWeChat(QQ[ThisQQ]->Return_Linked_WeiChat()); }
		else { handleServiceMenu(130); }
		return;
	}
	cout << "请输入您要绑定的微信号" << endl;
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
			cout << "没有其为微信，请重新输入或输入#返回返回上一层" << endl;
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

	cout << "请输入其为微信号的密码" << endl;
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
			cout << "密码输入错误，请重新输入或输入#返回返回上一层" << endl;
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

	//向微信添加QQ
	fstream LinkFile;
	string LinkFileName = "WeChat\\" + linkweichat + "\\Links.txt";
	LinkFile.open(LinkFileName, ios::app);

	LinkFile << "QQ:" + qqnumber;
	LinkFile.close();
	WeChatFun.ReturnWeiChatList()[ThisWeiChat]->Change_LinkedQQ(qqnumber);

	//向QQ添加微信
	fstream QQLinkFile;
	string QQLinkFileName = "QQ\\" + qqnumber + "\\Links.txt";
	QQLinkFile.open(QQLinkFileName, ios::app);

	QQLinkFile << "微信:" + linkweichat;
	QQLinkFile.close();
	QQFun.ReturnQQ()[ThisQQ]->Change_Linked_WeiChat(linkweichat);

	cout << "绑定微信成功" << endl;
	LogOperation( "绑定微信，微信号："+linkweichat, qqnumber);
	cout << "按任意键返回上一层(或按#进入微信页面)" << endl;
	
	if (getchar() == '#') {
		LogOperation( "进入微信页面,用户："+linkweichat, qqnumber);
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

	// 查找当前QQ号的索引
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			ThisQQ = i;
			break;
		}
	}

	// 获取当前绑定的微信号
	linkedWeChat = QQ[ThisQQ]->Return_Linked_WeiChat();
	if (linkedWeChat.empty())
	{
		cout << "您没有绑定任何微信" << endl;
		cout << "按任意键返回上一层" << endl;
		getchar();
		handleServiceMenu(130);
		return;
	}

	cout << "您当前绑定的微信号: " << linkedWeChat << endl;
	cout << "确认解除绑定此微信号吗？" << endl;
	cout << "1. 确定" << endl;
	cout << "0. 取消" << endl;

	int select;
	string tempstr;
	cin >> tempstr;
	judge_flush(stdin);
	select = judge_count_menu(tempstr, 1);

	if (select == 1)
	{
		// 解除绑定操作
		UnlinkQQFromWeChat(ThisQQ, linkedWeChat);
		UnlinkWeChatFromQQ(ThisQQ, linkedWeChat);

		cout << "解绑微信成功" << endl;
		LogOperation("解绑微信，微信号：" + linkedWeChat, qqnumber);
	}
	else
	{
		cout << "您取消了操作" << endl;
	}

	cout << "按任意键返回上一层" << endl;
	getchar();
	handleServiceMenu(130);
}

void QQChatBase_Qfh::UnlinkQQFromWeChat(int thisQQ, const string& linkedWeChat)
{
	QQFun.ReturnQQ()[thisQQ]->Change_Linked_WeiChat(""); // 解除QQ号的绑定

	// 找到对应的微信并解除绑定
	for (auto& weChat : WeChatFun.ReturnWeiChatList())
	{
		if (weChat->Return_ID() == linkedWeChat)
		{
			weChat->Change_LinkedQQ(""); // 解除微信号的绑定
			break;
		}
	}
}

void QQChatBase_Qfh::UnlinkWeChatFromQQ(int thisQQ, const string& linkedWeChat)
{
	// 移除QQ的链接记录
	RemoveLinkRecord("QQ", qqnumber, "微信:" + linkedWeChat);

	// 移除微信的链接记录
	RemoveLinkRecord("WeChat", linkedWeChat, "QQ:" + qqnumber);
}

void QQChatBase_Qfh::RemoveLinkRecord(const string& service, const string& serviceID, const string& linkLine)
{
	string linkFileName = service + "\\" + serviceID + "\\Links.txt";

	// 读取所有行到 vector
	vector<string> lines;
	fstream linkFile(linkFileName);
	string line;
	while (getline(linkFile, line))
	{
		lines.push_back(line);
	}
	linkFile.close();

	// 将不包含要删除的行的内容写回文件
	ofstream out(linkFileName);
	for (const auto& l : lines)
	{
		if (l != linkLine)
		{
			out << l << endl;
		}
	}
}



//Bug：链接不到
void QQChatBase_Qfh::SwitchToWeChat(const string& linkweichat) {
	system("CLS"); // 清屏
	cout << "正在切换到微信界面..." << endl;
	WeiChat_Qfh weichat;
	// 确保linkweichat有效
	string linkId = linkweichat;
	trim(linkId); // 去掉前后空格
	if (linkId.empty()) {
		cout << "错误：微信号不能为空。" << endl;
		return;
	}
	vector<Weixin_Qfh*> WeiChatList=weichat.GetWeChat(linkId); // 获取微信帐户
	
	// 查找指定的微信对象并登录
	for (auto& weixinObj : WeiChatList) {
		if (toLower(weixinObj->Return_ID()) == toLower(linkId)) {
			
			weichat.splogin(weixinObj->Return_ID()); // 调用登录
			return; // 成功登录后退出
		}
	}

	cout << "错误：未找到对应的微信号。" << endl; // 如果未找到微信号

	// 释放内存
	for (auto& weixin : WeiChatList) {
		delete weixin;
	}
}


/*
微信连接好友
*/
//查询并添加QQ共同好友
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

	// 查找当前QQ号索引
	for (size_t i = 0; i < QQ.size(); ++i) {
		if (QQ[i]->Return_ID() == qqnumber) {
			sub = i;
			break;
		}
	}

	// 检查是否找到了有效的sub索引
	if (sub == -1) {
		cout << "未找到当前QQ号！" << endl;
		return;
	}

	const auto& linkedWeiChatID = QQ[sub]->Return_Linked_WeiChat();
	int LinkedWeiChat = -1;

	if (linkedWeiChatID.empty()) {
		cout << "您没有绑定微信，请先绑定微信" << endl;
		if (shouldReturn) {
			cout << "按任意键返回上一层" << endl;
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
		cout << "未找到绑定的微信号！" << endl;
		return;
	}

	cout << "您链接的微信号为" << linkedWeiChatID << endl;
	cout << "您和该微信的共同好友如下" << endl;

	WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Get_Friends();
	auto& friendList = WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List();
	cout << "微信好友列表大小: " << friendList.size() << endl;

	unordered_set<string> QQLinkedIDs;
	for (const auto& qq : QQ) {
		QQLinkedIDs.insert(qq->Return_Linked_WeiChat());
	}

	int CommonFriendNumber = 0;

	for (const auto& wechatFriend : friendList) {
		string wechatID = wechatFriend->Return_ID(); // 微信好友 ID
	//	cout << "检查微信好友 ID: " << wechatID << " (微信好友)" << endl;

		for (const auto& qqFriend : QQ[sub]->Return_Friend_List()) {
			string qqID = qqFriend->Return_ID(); // QQ 好友 ID
		//	cout << "检查 QQ 好友 ID: " << qqID << " (QQ好友)" << endl;

			// 记录即将比较的 ID
		//	cout << "即将比较的微信 ID: " << wechatID << " 和 QQ ID: " << qqID << endl;

			if (qqID == wechatID) {
				cout << "找到共同好友: " << wechatID << endl;
				// 输出共通好友信息
				cout << "第" << ++CommonFriendNumber << "个共同好友: " << endl;
				cout << "帐号: " << qqID << endl; // 更新为对应的 qqID
				cout << "姓名: " << qqFriend->ReturnFriendName() << endl;
				cout << "备注: " << qqFriend->ReturnRemarks() << endl;
				cout << endl;
				break; // 找到后的退出
			}
		}
	}

	if (CommonFriendNumber == 0) {
		cout << "没有找到共同好友！" << endl;
	}
	
	// 清理微信好友列表（可选）
	friendList.clear();
}






void QQChatBase_Qfh::ShowWeiChatCommonFriends() {
	LogOperation("查看微信共同好友", qqnumber);
	DisplayCommonFriends(true);
}

void QQChatBase_Qfh::Show_WeiChat_Common_FriendsNo_Return() {
	DisplayCommonFriends(false);
}

void QQChatBase_Qfh::AddWeiChatCommonFriend() {
	ShowWeiChatCommonFriends();
	string id;
	cout << "输入您要添加的微信好友的QQID" << endl;
	cin >> id;
	judge_flush(stdin);

	if (id == qqnumber) {
		cout << "您不能添加自己为好友" << endl;
		cout << "按任意键返回上一层" << endl;
		getchar();
		handleFriendMenu(130);
		return;
	}

	// 查找当前用户的索引
	int sub = -1;
	for (size_t i = 0; i < QQ.size(); ++i) {
		if (QQ[i]->Return_ID() == qqnumber) {
			sub = i;
			break;
		}
	}

	if (sub == -1) {
		cout << "未找到当前QQ号！" << endl;
		return;
	}

	// 检查是否已经是好友
	for (const auto& friendItem : QQ[sub]->Return_Friend_List()) {
		if (id == friendItem->Return_ID()) {
			cout << "您已添加其为好友,请按任意键返回上一层" << endl;
			getchar();
			handleFriendMenu(130);
			return;
		}
	}

	// 查找目标用户
	int subFriend = -1;
	bool foundFriend = false;
	string name;

	for (size_t i = 0; i < QQ.size(); ++i) {
		if (QQ[i]->Return_ID() == id) {
			foundFriend = true;
			name = QQ[i]->Return_Name();
			subFriend = i;
			LogOperation("查询并添加QQ共同好友 目标QQ号：" + id ,qqnumber);
			cout << "好友申请成功，请等待对方确认" << endl;
			break;
		}
	}

	if (!foundFriend) {
		cout << "该QQ还没有注册：" << endl;
		cout << "1.重新输入QQ号添加好友" << endl;
		cout << "0.返回上一层" << endl;

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

	// 添加好友申请
	string mark = "&";
	string ID = mark + id;
	string friendFileName = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string remarks = "未备注";

	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	ofstream file(friendFileName, ios::app);

	if (file.is_open()) {
		file << ID << endl;
		file << name << endl;
		file << remarks << endl;
		file << " " << endl; // 用作判断几个好友
		file.close();
	}

	// 向好友QQ文件中添加本QQ
	friendFileName = "QQ\\" + id + "\\" + id + "Friendlist.txt";
	string subName = "$" + QQ[sub]->Return_Name();
	QQ[subFriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subName, qqnumber));

	ofstream friendFile(friendFileName, ios::app);
	if (friendFile.is_open()) {
		friendFile << "$" << QQ[sub]->Return_ID() << endl;
		friendFile << QQ[sub]->Return_Name() << endl;
		friendFile << remarks << endl;
		friendFile << " " << endl; // 判断几个好友
		friendFile.close();
	}
	LogOperation("添加微信共同好友,好友ID："+id, qqnumber);
	cout << "按任意键返回上一层" << endl;
	getchar();
	handleFriendMenu(130);
}




//QQ群功能(临时群)（有意向做复联TCP版本）暂存微博部分
void QQChatBase_Qfh::CreatTemporaryGroup() {
	system("CLS");

	// 生成临时讨论组编号
	int temp = AllQQTemporaryGroup.size() + 1;
	string ID = to_string(temp); // to_string简化转换

	cout << "请输入讨论组名称: ";
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "您的临时讨论组号为: " << ID << endl;

	// 找到当前用户索引
	int sub = findUserIndex(qqnumber);
	// 创建临时讨论组并添加到列表
	QQ[sub]->Return_Temporary_GroupList().emplace_back(new QQgroups_Qfh(ID, name, qqnumber));
	AllQQTemporaryGroup.emplace_back(new QQgroups_Qfh(ID, name, qqnumber));
	LogOperation("创建临时讨论组", qqnumber); // 记录创建讨论组的操作
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF) {
		handleQQGroupMenu(130);
	}
}

void QQChatBase_Qfh::JoinTemporaryGroup() {
	system("CLS");

	displayTemporaryGroups(AllQQTemporaryGroup); // 显示讨论组列表

	cout << "请输入您想加入的群号，或输入#返回上一层: ";
	string TemporaryGroup;
	cin >> TemporaryGroup;
	judge_flush(stdin);

	if (TemporaryGroup == "#") {
		handleQQGroupMenu(130);
		return;
	}

	// 验证群号是否有效
	while (!isTemporaryGroupValid(TemporaryGroup)) {
		cout << "没有其为讨论组，请重新输入群号或输入#返回上一层: ";
		cin >> TemporaryGroup;
		judge_flush(stdin);
		if (TemporaryGroup == "#") {
			handleQQGroupMenu(130);
			return;
		}
	}

	// 找到当前用户索引
	int sub = findUserIndex(qqnumber);

	// 找到目标讨论组信息
	auto groupIndex = findTemporaryGroupIndex(TemporaryGroup);
	if (groupIndex == -1) return; // 如果没有找到，直接返回

	string TemporaryName = ReturnAllQQTemporaryGroup()[groupIndex]->Return_Group_Name();
	string TemporaryOwner = ReturnAllQQTemporaryGroup()[groupIndex]->ReturnCreatUserID();

	// 将用户添加到讨论组
	QQ[sub]->Return_Temporary_GroupList().emplace_back(new QQgroups_Qfh(TemporaryGroup, TemporaryName, TemporaryOwner));
	LogOperation("加入临时讨论组", qqnumber); // 记录加入讨论组的操作
	cout << "加入临时讨论组成功" << endl;
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF) {
		handleQQGroupMenu(130);
	}
}

// 辅助函数：查找用户索引
int QQChatBase_Qfh::findUserIndex(const string& userId) {
	for (int i = 0; i < QQ.size(); i++) {
		if (QQ[i]->Return_ID() == userId) {
			return i;
		}
	}
	return -1; // 用户未找到
}

// 辅助函数：显示讨论组
void QQChatBase_Qfh::displayTemporaryGroups(const vector<QQgroups_Qfh*>& groups) {
	for (size_t i = 0; i < groups.size(); i++) {
		cout << "第" << i + 1 << "个临时讨论组" << endl;
		cout << "群号: " << groups[i]->Return_Group_ID() << endl;
		cout << "群名称: " << groups[i]->Return_Group_Name() << endl;
	}
}

// 辅助函数：验证讨论组是否有效
bool QQChatBase_Qfh::isTemporaryGroupValid(const string& groupId) {
	for (const auto& group : AllQQTemporaryGroup) {
		if (group->Return_Group_ID() == groupId) {
			return true;
		}
	}
	return false;
}

// 辅助函数：查找临时讨论组索引
int QQChatBase_Qfh::findTemporaryGroupIndex(const string& groupId) {
	for (size_t i = 0; i < AllQQTemporaryGroup.size(); i++) {
		if (AllQQTemporaryGroup[i]->Return_Group_ID() == groupId) {
			return i;
		}
	}
	return -1; // 未找到
}

template <typename T>
void QQChatBase_Qfh::LogOperation(const T& operation, const string& userId) {
	// 为每个用户创建一个日志文件
	string direcctoryPath = "QQ\\" + userId;
	string logFileName = direcctoryPath + "\\" + userId + "_log.txt"; // 使用用户ID作为文件名
	ofstream logFile(logFileName, ios::app);
	if (logFile.is_open()) {
		time_t now = time(0);
		char* dt = ctime(&now);

		// 移除换行符
		dt[strlen(dt) - 1] = '\0';

		ostringstream oss;
		oss << operation;

		// 按照格式写入日志
		logFile << dt << ": " << userId << ": " << oss.str() << endl;
		logFile.close();
	}
	else {
		cerr << "无法打开日志文件: " << logFileName << "!" << endl;
	}
}

void QQChatBase_Qfh::DisplayLog(const string& userId) {
	string logFileName = "QQ\\" + userId + "\\" + userId + "_log.txt";

	ifstream logFile(logFileName);
	if (logFile.is_open()) {
		string line;
		cout << "日志文件内容如下：" << endl;
		while (getline(logFile, line)) {
			cout << line << endl; // 输出每一行
		}
		logFile.close();
	}
	else {
		cerr << "无法打开日志文件: " << logFileName << "!" << endl;
	}
}

void QQChatBase_Qfh::ShowUserLog(const string& userId) {
	system("CLS");
	LogOperation("查看用户日志", userId); // 记录查看日志的操作
	DisplayLog(userId); // 展示用户日志
	cout << "按任意键返回上一层" << endl;
	if (getchar() != EOF) {
		QQMenu();
	}
}