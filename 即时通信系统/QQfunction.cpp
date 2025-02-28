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
		cout << "按任意键返回QQ主菜单" << endl;
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
	cout << "按任意键返回QQ主菜单" << endl;
	if (getchar() != EOF)
		QQMenu();
}
// agree函数用：读取文件内容到向量中
void ReadFileToVector(const string& filename, vector<string>& content) {
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		content.push_back(line);
	}
	if (!content.empty()) {
		content.pop_back(); // 删除最后一个空行
	}
}

// agree函数用：写向量内容到文件
void WriteVectorToFile(const string& filename, const vector<string>& content) {
	ofstream file(filename, ios::trunc); // 清空文件内容
	for (const auto& line : content) {
		file << line << endl;
	}
}

// agree函数用：更新好友列表，将带标记的ID去掉
void UpdateFriendApplication(vector<string>& content, const string& prefix, const string& id) {
	for (auto& entry : content) {
		if (entry == (prefix + id)) {
			entry = id; // 去掉标记
		}
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
//通用：找好友递归查找QQ号对应的索引
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
//通用：返回界面
void QQChatBase_Qfh::WaitForUserInput() {
	cout << "按任意键返回QQ主页" << endl;
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
		QQMenu();
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
		file.open(filename, ios::trunc | ios::out);//清空文件内容
		file.close();
	}
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
	cout << "请输入您的选择:" << endl;
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
	select = judge_count_menu(temp, 4);

	// 处理用户选择
	handleMainMenuSelection(select, menuWidth);
}

void QQChatBase_Qfh::displayMainMenu(int menuWidth)
{
	printCentered("|*---------QQ功能菜单--------------*|", menuWidth);
	cout << "         用户: " << qqnumber << endl;
	printCentered("|*        请选择使用的功能         *|", menuWidth);
	printCentered("|*        1.好友功能               *|", menuWidth);
	printCentered("|*        2.群功能                 *|", menuWidth);
	printCentered("|*        3.个人信息               *|", menuWidth);
	printCentered("|*        4.开通服务               *|", menuWidth);
	printCentered("|*        0.返回主菜单             *|", menuWidth);
	printCentered("|*---------------------------------*|", menuWidth);
	printCentered("请输入您的选择", menuWidth);
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
	printCentered("|*--------------好友功能--------------*|", menuWidth);
	printCentered("|*          1.添加好友                *|", menuWidth);
	printCentered("|*          2.显示好友                *|", menuWidth);
	printCentered("|*          3.删除好友                *|", menuWidth);
	printCentered("|*          4.查看好友申请            *|", menuWidth);
	printCentered("|*          5.查看好友信息            *|", menuWidth);
	printCentered("|*          6.修改好友备注            *|", menuWidth);
	printCentered("|*          7.查看微信共同好友        *|", menuWidth);
	printCentered("|*          8.添加微信共同好友        *|", menuWidth);
	printCentered("|*          0.返回QQ主菜单            *|", menuWidth);
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
	printCentered("|*----------------群管理功能-------------*|", menuWidth);
	printCentered("|*              0.QQ类型群               *|", menuWidth);
	printCentered("|*              1.微信类型群             *|", menuWidth);
	printCentered("|*       random_input返回上一级菜单      *|", menuWidth);
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
	printCentered("|*----------请选择使用的群功能----------*|", menuWidth);
	printCentered("|*            1.加群                *|", menuWidth);
	printCentered("|*            2.退群                *|", menuWidth);
	printCentered("|*            3.创建群                *|", menuWidth);
	printCentered("|*            4.查看已加入的群        *|", menuWidth);
	printCentered("|*            5.查看入群申请            *|", menuWidth);
	printCentered("|*            6.添加QQ群管理员          *|", menuWidth);
	printCentered("|*            7.踢出群成员              *|", menuWidth);
	printCentered("|*            8.查看群成员信息          *|", menuWidth);
	printCentered("|*            9.创建临时讨论组          *|", menuWidth);
	printCentered("|*            10.加入临时讨论组         *|", menuWidth);
	printCentered("|*            11.邀请好友进群           *|", menuWidth);
	printCentered("|*            0.返回上一级菜单              *|", menuWidth);
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
	printCentered("|*--------请选择使用的群功能--------*|", menuWidth);
	printCentered("|*          1.退群                  *|", menuWidth);
	printCentered("|*          2.创建群                *|", menuWidth);
	printCentered("|*          3.查看已加入的群        *|", menuWidth);
	printCentered("|*          4.踢出群成员            *|", menuWidth);
	printCentered("|*          5.查看群成员信息        *|", menuWidth);
	printCentered("|*          6.邀请好友进群          *|", menuWidth);
	printCentered("|*          0.返回上级菜单           *|", menuWidth);
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
	printCentered("|*------------个人信息功能--------------*|", menuWidth);
	printCentered("|*           1.查看个人信息             *|", menuWidth);
	printCentered("|*           2.修改密码                 *|", menuWidth);
	printCentered("|*           3.修改名称                 *|", menuWidth);
	printCentered("|*           4.修改签名                 *|", menuWidth);
	printCentered("|*           5.修改地址                 *|", menuWidth);
	printCentered("|*           0.返回上一级菜单           *|", menuWidth);
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
		LinkWeiChat(); // 绑定微信调用link
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
	printCentered("|*------------登录服务功能--------------*|", menuWidth);
	printCentered("|*             1.QQ登录微博               *|", menuWidth);
	printCentered("|*             2.QQ登录微信               *|", menuWidth);
	printCentered("|*             0.返回上一级菜单           *|", menuWidth);
	printCentered("|*--------------------------------------*|", menuWidth);
}


//加好友
void QQChatBase_Qfh::AddFriend()
{
	system("CLS");
	string id;
	bool flag = false;//标志找没找到要添加的QQ
	cout << "请输入要添加好友的QQ号" << endl;
	cin >> id;
	judge_flush(stdin);
	if (id == qqnumber)
	{
		cout << "不能添加自己为好友！" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	// 查找当前QQ的信息

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
	//失败处理
	if (sub == -1) {
		cout << "没有找到当前QQ信息，按任意键返回" << endl;
		if (getchar() != EOF)QQMenu();
		return;
	}


	for (const auto& friendObj : QQ[sub]->Return_Friend_List())
	{
		if (id == friendObj->Return_ID())
		{
			cout << "您已添加此好友,按任意键返回" << endl;
			if (getchar() != EOF)
				QQMenu();
			return;
		}
	}
	//查找要添加的QQ的信息是否存在
	int subfriend = -1;
	string name;
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == id)
		{
			flag = true;
			subfriend = i;
			name = QQ[i]->Return_Name();
			cout << "发送好友申请成功，请等待对方确认" << endl;
			break;
		}
	}

	if (subfriend == -1)
	{
		cout << "该QQ还没有注册，按任意键重新输入QQ号" << endl;
		cout << "1.重新输入QQ号添加好友" << endl;
		cout << "0.返回QQ主页" << endl;
		cout << "请输入您的选择" << endl;
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
	//发送好友申请
	string mark = "&";
	string ID = mark + id;//&表示申请者申请的好友的信息列表
	string friendfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string remarks = "未备注";

	//更新当前用户好友列表
	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	ofstream file(friendfilename, ios::app);//追加好友
	file << ID << endl;
	file << name << endl;
	file << remarks << endl;
	file << " " << endl;//用作判断几个好友
	file.close();

	//向好友QQ文件中添加本QQ
	friendfilename = "QQ\\" + id + "\\" + id + "Friendlist.txt";
	subname = "$" + subname;
	QQ[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subname, qqnumber));

	ofstream friendfile(friendfilename, ios::app);
	friendfile << "$" << QQ[sub]->Return_ID() << endl;
	friendfile << QQ[sub]->Return_Name() << endl;
	friendfile << remarks << endl;
	friendfile << " " << endl;//用作判断几个好友
	friendfile.close();
	cout << "按任意键返回" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

//删好友（BUG：Xstring问题：暂时不修复）
void QQChatBase_Qfh::DeleteFriend()
{
	system("CLS");

	int sub = -1;
	// 一次性查找并保存结果
	for (int i = 0; i < QQ.size(); i++)
	{
		if (QQ[i]->Return_ID() == qqnumber)
		{
			sub = i;
			break;
		}
	}

	// 显示好友列表
	cout << "好友列表如下：" << endl;
	for (int i = 0; i < QQ[sub]->Return_Friend_Number(); i++)
	{
		// 修正好友名称检查逻辑
		if (QQ[sub]->Return_Friend_List()[i]->ReturnFriendName()[0] == '$' ||
			QQ[sub]->Return_Friend_List()[i]->ReturnFriendName()[0] == '&')
			continue;
		cout << "姓名:" << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "QQ:" << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "备注：" << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl << endl;
	}

	// 删除本QQ中的好友
	string delq;
	cout << "请输入要删除好友的QQ号(或按#返回主页)" << endl;
	cin >> delq;
	judge_flush(stdin);
	if (delq == "#")
	{
		QQMenu();
		return;
	}

	// 检查是否有此好友
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
		cout << "您没有此好友" << endl;
		cout << "1.重新输入QQ号" << endl;
		cout << "0.返回主页" << endl;
		cout << "请输入您的选择" << endl;
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

	// 从好友列表中删除好友
	auto& friendList = QQ[sub]->Return_Friend_List();
	friendList.erase(remove_if(friendList.begin(), friendList.end(),
		[&delq](const auto& friendObj) {
			return friendObj->Return_ID() == delq;
		}),
		friendList.end());

	// 修改好友数量
	QQ[sub]->Change_Friends_Number(friendList.size()); // 直接使用当前已更新的好友列表大小

	// 删除对方的好友
	string currentQQ = QQ[sub]->Return_ID();
	int friendIndex = FindQQIndex(delq); // 先查找好友索引

	if (friendIndex != -1) {
		auto& friendOfFriendList = QQ[friendIndex]->Return_Friend_List();
		friendOfFriendList.erase(remove_if(friendOfFriendList.begin(), friendOfFriendList.end(),
			[currentQQ](const auto& friendObj) {
				return friendObj->Return_ID() == currentQQ;
			}),
			friendOfFriendList.end());

		// 更新好友数量
		QQ[friendIndex]->Change_Friends_Number(friendOfFriendList.size());
	}

	// 更新好友文件
	UpdateFriendFile(sub);
	if (friendIndex != -1) {
		UpdateFriendFile(friendIndex);
	}

	cout << "删除好友成功" << endl;
	cout << "按任意键返回QQ主页" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;

}
//展示好友信息
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
	if (sub == -1)return;//失败处理

	int friendsnum = QQ[sub]->Return_Friend_List().size();
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{    //&好友申请列表,$别人添加自己为好友列表
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//判断添加好友标记
		{
			friendsnum--;//去掉添加的$和&标记的好友

		}
	}
	cout << "您的好友个数为：" << friendsnum << endl;
	int count = 0;
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
		{
			continue;//跳过不打印
		}
		cout << "第" << count + 1 << "位好友" << endl;
		cout << "姓名:" << QQ[sub]->Return_Friend_List()[i]->ReturnFriendName() << endl;
		cout << "QQID:" << QQ[sub]->Return_Friend_List()[i]->Return_ID() << endl;
		cout << "备注:" << QQ[sub]->Return_Friend_List()[i]->ReturnRemarks() << endl;
		cout << endl;
		count++;
	}

	cout << "按任意键返回QQ主页" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

//同意好友申请
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
	//获取申请人QQ
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
		cout << "没有好友申请" << endl;
		cout << "按任意键返回QQ主页" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	for (int i = 0; i < temp.size(); i++) {
		fdqq = temp[i];
		friendqqfilename = "QQ\\" + fdqq + "\\" + fdqq + "Friendlist.txt";
		cout << "您是否同意" << temp[i] << "的好友申请?" << endl;
		cout << "1.同意" << endl;
		cout << "0.拒绝" << endl;
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
			//处理申请人信息
			vector<string> myaceptcontent;
			ReadFileToVector(subfilename, myaceptcontent);
			UpdateFriendApplication(myaceptcontent, "$", FriendApplyQQ);
			WriteVectorToFile(subfilename, myaceptcontent);

			// 处理好友信息
			vector<string> friendaceptcontent;
			ReadFileToVector(friendqqfilename, friendaceptcontent);
			UpdateFriendApplication(friendaceptcontent, "&", qqnumber);
			WriteVectorToFile(friendqqfilename, friendaceptcontent);

			// 查找当前用户和申请人的索引
			int sub = FindQQIndex(qqnumber);
			int friendqq = FindQQIndex(fdqq);

			if (sub != -1 && friendqq != -1) {
				string name = QQ[friendqq]->Return_Name();
				string id = QQ[friendqq]->Return_ID();

				// 更新双方的好友列表
				QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, id));
				QQ[sub]->Change_Friends_Number(QQ[sub]->Return_Friend_Number() + 1);

				QQ[friendqq]->Return_Friend_List().push_back(new QQFriends_Qfh(QQ[sub]->Return_Name(), qqnumber));
				QQ[friendqq]->Change_Friends_Number(QQ[friendqq]->Return_Friend_Number() + 1);
			}

			cout << "确认申请成功，按任意键处理下一个" << endl;
			if (getchar() != EOF)
				break;
		}
		case 0:
		{
			cout << "您已拒绝该请求，按任意键处理下一个" << endl;
			//删除申请人文件中的QQ
			subfile.open(subfilename);
			string subfiletemp;
			vector<string> subfilecontent;
			while (!subfile.eof())
			{
				getline(subfile, subfiletemp);
				subfilecontent.push_back(subfiletemp);
			}
			subfilecontent.pop_back();
			//清空原有文件内容和“$”标记
			for (int i = 0; i < size(subfilecontent); i++)
			{
				if (subfilecontent[i] == ("$" + FriendApplyQQ))
				{
					subfilecontent.erase(subfilecontent.begin() + i);//ID
					subfilecontent.erase(subfilecontent.begin() + i);//昵称
					subfilecontent.erase(subfilecontent.begin() + i);//备注
					subfilecontent.erase(subfilecontent.begin() + i);//空行
					break;
				}
			}
			subfile.close();
			subfilecontent.shrink_to_fit();//容器大小减少，减少其容量和size匹配
			subfile.open(subfilename, ios::out | ios::trunc); //清空原有内容

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

			//清空好友申请列表i“&”标记
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
			friendfilecontent.shrink_to_fit();//容器大小减少，减少其容量和size匹配
			friendqqfile.open(friendqqfilename, ios::out, ios::trunc);//清空原有内容
			//更新写入新的申请列表更新文件
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
	cout << "所有的申请处理完毕，按任意键返回QQ主菜单" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
//创建QQ群
void QQChatBase_Qfh::CreatQQgroup()
{
	system("CLS");

	time_t ti;
	srand((unsigned)time(&ti));//当前时间为种子
	int temp = rand() % 99999;//随机群号
	stringstream ss;
	ss << temp;
	string ID;
	ss >> ID;

	cout << "请输入群名称: " << endl;
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "您的群号为:" << ID << endl;

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
	//查找有无此群
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
		cout << "您没有加入此群" << endl;
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
	judge_flush(stdin);

	string filename = "QQ\\Groups\\" + id + "\\" + id + ".txt";
	ifstream infile(filename, ios::in);

	if (!infile) {
		ShowMenu("没有此群,请重新输入或返回主页", { "1.重新输入", "0.返回主页" });
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
		if (line == 2) { // 获取群主QQ号
			temp.push_back(c);
		}
	}
	outfile.close();

	if (temp != qqnumber) { // 不是群主无法建立管理员
		cout << "您不是该群的群主,无法管理该群" << endl;
		cout << "按任意键返回QQ主页" << endl;
		if (getchar() != EOF)
			QQMenu();
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
		cout << "该群没有成员，按任意键返回QQ主页" << endl;
		if (getchar() != EOF)
			QQMenu();
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
		cout << "本群没有此成员请重新输入" << endl;
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
					QQMenu();
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
					QQMenu();
				return;
			}
		}
	}

	adminfile << adminid << endl;
	adminfile.close();
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
			cout << "您没有加入此群，请重新输入或输入#返回" << endl;
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
		cout << "您没有此好友，请重新输入(或输入#返回)" << endl;
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
	cout << "按任意键继续邀请好友进群（或输入#返回QQ主页）" << endl;
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
//获取
void QQChatBase_Qfh::GetQQGroup() //从文件读取该QQ的群，并保存到容器中
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
	system("CLS");
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
	cout << "按任意键返回QQ主页" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
//加人入群
void QQChatBase_Qfh::AddInGroupMember()
{
	system("CLS");
	cout << "请输入您想加入的群,或输入#返回QQ主页" << endl;
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
			cout << "您已添加此群" << endl;
			cout << "按任意键返回QQ主页" << endl;
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
		cout << "没有此群，按任意键返回QQ主页" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}
	string filename = "QQ\\Groups\\" + groupid + "\\" + groupid + ".txt";
	ofstream ofile;
	ofile.open(filename, ios::app);
	ofile << "$" << qqnumber << endl;
	ofile.close();
	cout << "申请入群成功,请等待群主同意" << endl;
	cout << "按任意键返回QQ主页" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}
//同意入群
void QQChatBase_Qfh::AgreeMember()//群主查看申请
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
		cout << "没有此群,请重新输入或返回QQ主页" << endl;
		cout << "1.重新输入" << endl;
		cout << "0.返回QQ主页" << endl;
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
		cout << "群主您好，欢迎查看入群申请" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "管理员您好，欢迎查看入群申请" << endl;
	}
	else
	{
		cout << "您不是该群的群主或管理员,无法管理该群" << endl;
		cout << "按任意键返回QQ主页" << endl;
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
		cout << "没有加群申请" << endl;
		cout << "按任意键返回QQ主页" << endl;
		if (getchar() != EOF)
			QQMenu();
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
	cout << "按任意键返回QQ主页" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

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
		cout << "没有此群,请重新输入或返回QQ主页" << endl;
		cout << "1.重新输入" << endl;
		cout << "0.返回QQ主页" << endl;
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
		cout << "群主您好，欢迎来到群成员管理" << endl;
	}
	else if (Adminflag == true)
	{
		cout << "管理员您好，欢迎来到群成员管理" << endl;
	}
	else
	{
		cout << "您不是该群的群主或管理员,无法管理该群" << endl;
		cout << "按任意键返回QQ主页" << endl;
		if (getchar() != EOF)
			QQMenu();
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
		cout << "您为此群群主可以踢出除您外的任何人" << endl;
		Ownerflag = true;
	}
	else
	{
		cout << "您为此群管理员，可以踢出除群主和管理员以外的人" << endl;
		Adminflag = true;
	}
	Show_Group_InformationNo_Return(id);
	cout << "请输入要踢出的成员QQ号,或输入#返回QQ主页" << endl;
	string DeleteMemberQQ;
	cin >> DeleteMemberQQ;
	judge_flush(stdin);
	if (DeleteMemberQQ == "#")
	{
		QQMenu();
		return;
	}
	//检查输入QQ是否是群主或是自己
	bool checkflag = false;//检查是否有此成员
	while (1)
	{
		if (DeleteMemberQQ == GroupOwner || DeleteMemberQQ == qqnumber)
		{
			cout << "无法踢出群主或自己，请重新输入或输入#返回QQ主页" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				QQMenu();
				return;
			}
			continue;
		}

		for (int i = 0; i < size(GroupMember); i++)//检查是否有此成员
		{
			if (DeleteMemberQQ == GroupMember[i])
			{
				checkflag = true;
				break;
			}
		}

		if (checkflag == false)
		{
			cout << "没有此成员请重新输入,或输入#返回QQ主页" << endl;
			cin >> DeleteMemberQQ;
			judge_flush(stdin);
			if (DeleteMemberQQ == "#")
			{
				QQMenu();
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
			cout << "无法踢出群主或自己，请重新输入或输入#返回QQ主页" << endl;
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

	//从该成员群列表中删除此群
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

	//从本群成员列表中删除此成员，原理类似上面
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
			cout << "按任意键返回QQ主菜单" << endl;
			if (getchar() != EOF)
				QQMenu();
			return;
		}
		else
		{
			cout << "踢出" << DeleteMemberQQ << "成功" << endl;
			cout << "按任意键返回QQ主菜单" << endl;
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
	cout << "以下为您的个人信息:" << endl;
	cout << "帐号:" << QQ[sub]->Return_ID() << endl;
	cout << "密码:" << QQ[sub]->Return_PassWord() << endl;
	cout << "姓名:" << QQ[sub]->Return_Name() << endl;
	cout << "地区:" << QQ[sub]->Return_Area() << endl;
	cout << "性别" << QQ[sub]->Return_Sex() << endl;
	cout << "注册日期:" << QQ[sub]->Return_ApplyDate();
	cout << "个性签名:" << QQ[sub]->Return_Autograph() << endl;
	cout << "您的生日:" << QQ[sub]->Return_bir() << endl;
	cout << endl;
	cout << "按任意键返回QQ主菜单" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}

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
	cout << "按任意键返回QQ主菜单" << endl;
	if (getchar() != EOF)
		QQMenu();
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
	cout << "按任意键返回QQ主菜单" << endl;
	if (getchar() != EOF)
		QQMenu();
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
	SaveChange();
	cout << "按任意键返回QQ主菜单" << endl;
	if (getchar() != EOF)
		QQMenu();
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
	SaveChange();
	cout << "按任意键返回QQ主菜单" << endl;
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
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')//判断添加好友标记
		{
			friendsnum--;
		}
	}

	cout << "您有" << friendsnum << "个好友" << endl;
	int friends = 0;
	for (int i = 0; i < QQ[sub]->Return_Friend_List().size(); i++)
	{
		if ((QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '&' || (QQ[sub]->Return_Friend_List()[i]->Return_ID()[0]) == '$')
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

void QQChatBase_Qfh::ShowFriendInformation()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "请输入您想查询的好友QQ号，或输入#返回QQ主菜单" << endl;
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
			cout << "您没有此好友，请重新输入或输入#返回QQ主菜单" << endl;
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

	cout << "以下为此好友信息" << endl;
	cout << "帐号:" << QQ[friendsub]->Return_ID() << endl;
	cout << "姓名:" << QQ[friendsub]->Return_Name() << endl;
	cout << "备注:" << QQ[sub]->Return_Friend_List()[friendremarks]->ReturnRemarks() << endl;//备注单独打印不能直接通过QQ容器获取
	cout << "性别" << QQ[sub]->Return_Sex() << endl;
	cout << "个性签名:" << QQ[friendsub]->Return_Autograph() << endl;
	cout << "所在地区:" << QQ[friendsub]->Return_Area() << endl;
	cout << "用户的生日:" << QQ[friendsub]->Return_bir() << endl;
	cout << "注册时间:" << QQ[friendsub]->Return_ApplyDate() << endl;

	cout << endl;
	cout << "按任意键返回QQ主菜单" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;

}

void QQChatBase_Qfh::ChangeFriendRemarks()
{
	system("CLS");
	ShowFriendNoReturn();
	cout << "请输入您想修改的好友QQ号，或输入#返回QQ主菜单" << endl;
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
			cout << "您没有此好友，请重新输入或输入#返回QQ主菜单" << endl;
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
	cout << "按任意键返回QQ主菜单" << endl;
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
			cout << "您没有加入此群，请重新输入或输入#返回QQ主菜单" << endl;
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

void QQChatBase_Qfh::ShowGroupInformation()
{
	system("CLS");
	ShowQQGroupNoReturn();
	cout << "请输入您要查询成员信息的QQ群,或输入#返回QQ主菜单" << endl;
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
			cout << "您没有加入此群，请重新输入或输入#返回QQ主菜单" << endl;
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
	cout << "按任意键返回QQ主菜单" << endl;
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

	//判断是否已经开通微博
	for (int i = 0; i < WeiBoFun.ReturnWeiBolist().size(); i++)
	{
		if (WeiBoFun.ReturnWeiBolist()[i]->Return_ID() == qqnumber)
		{
			cout << "您已开通微博，无需重复开通" << endl;
			cout << "按任意键返回QQ主菜单" << endl;
			if (getchar() != EOF)
				QQMenu();
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
		cout << "按任意键返回QQ主菜单" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;

	default:
		cout << "您取消了开通创建" << endl;
		cout << "按任意键返回QQ主菜单" << endl;
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
		cout << "按任意键返回微信主页" << endl;
		if (getchar() != EOF)
			QQMenu();
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
			cout << "没有此微信，请重新输入或输入#返回微信主页" << endl;
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

	cout << "请输入此微信号的密码" << endl;
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
			cout << "密码输入错误，请重新输入或输入#返回微信主页" << endl;
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

	cout << "绑定微信成功,该微信已经自动登录" << endl;
	cout << "按任意键返回QQ主页" << endl;
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
		//中文字符需要erase两次
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
		cout << "您没有绑定微信，请先绑定微信" << endl;
		cout << "按任意键返回QQ主页" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	cout << "您绑定的微信号为" << QQ[sub]->Return_Linked_WeiChat() << endl;
	cout << "您和此微信的共同好友有如下" << endl;

	int FriendFlag = false;
	int CommonFriendNumber = 1;

	WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Get_Friends();
	for (int j = 0; j < size(WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List()); j++)//微信好友列表
	{

		FriendFlag = false;

		for (int k = 0; k < QQ.size(); k++)
		{
			QQ[k]->Get_Links();
			//QQ列表中找到此好友
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
				cout << "第" << CommonFriendNumber << "个共同好友" << endl;
				cout << "帐号:" << QQ[sub]->Return_Friend_List()[j]->Return_ID();
				cout << "姓名:" << QQ[sub]->Return_Friend_List()[j]->ReturnFriendName();
				cout << "备注:" << QQ[sub]->Return_Friend_List()[j]->ReturnRemarks();
				cout << endl;
				CommonFriendNumber++;
				break;
			}
		}
	}
	WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List().clear();
	cout << "按任意键返回QQ主页" << endl;
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
		cout << "您没有绑定微信，请先绑定微信" << endl;
		cout << "按任意键返回QQ主页" << endl;
		if (getchar() != EOF)
			QQMenu();
		return;
	}

	cout << "您绑定的微信号为" << QQ[sub]->Return_Linked_WeiChat() << endl;
	cout << "您和此微信的共同好友有如下" << endl;

	int FriendFlag = false;
	int CommonFriendNumber = 1;

	WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Get_Friends();
	for (int j = 0; j < size(WeChatFun.ReturnWeiChatList()[LinkedWeiChat]->Return_Friend_List()); j++)//微信好友列表
	{

		FriendFlag = false;
		for (int k = 0; k < QQ.size(); k++)
		{
			QQ[k]->Get_Links();
			//QQ列表中找到此好友
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
				cout << "第" << CommonFriendNumber << "个共同好友" << endl;
				cout << "QQ:" << QQ[sub]->Return_Friend_List()[j]->Return_ID();
				cout << "姓名:" << QQ[sub]->Return_Friend_List()[j]->ReturnFriendName();
				cout << "备注:" << QQ[sub]->Return_Friend_List()[j]->ReturnRemarks();
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
	cout << "输入您要添加的微信共同好友的QQ号" << endl;
	cin >> id;
	judge_flush(stdin);
	if (id == qqnumber)
	{
		cout << "您不能添加自己为好友" << endl;
		cout << "按任意键返回QQ主页" << endl;
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
			cout << "您已添加此好友,请按任意键返回QQ主页" << endl;
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
			cout << "好友申请成功，请等待对方确认" << endl;
		}
	}
	if (flag == false)
	{
		cout << "该QQ还没有注册，按任意键重新输入QQ号" << endl;
		cout << "1.重新输入QQ号添加好友" << endl;
		cout << "0.返回QQ主页" << endl;
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
	string ID = mark + id;//&表示申请者申请的好友的信息列表
	fstream file;
	string friendfilename = "QQ\\" + qqnumber + "\\" + qqnumber + "Friendlist.txt";
	string remarks = "未备注";
	QQ[sub]->Return_Friend_List().push_back(new QQFriends_Qfh(name, ID));
	file.open(friendfilename, ios::app);
	file << ID << endl;
	file << name << endl;
	file << remarks << endl;
	file << " " << endl;//用作判断几个好友
	file.close();
	//向好友QQ文件中添加本QQ
	friendfilename = "QQ\\" + id + "\\" + id + "Friendlist.txt";
	subname = "$" + subname;
	QQ[subfriend]->Return_Friend_List().push_back(new QQFriends_Qfh(subname, qqnumber));
	file.open(friendfilename, ios::app);
	file << "$" << QQ[sub]->Return_ID() << endl;
	file << QQ[sub]->Return_Name() << endl;
	file << remarks << endl;
	file << " " << endl;//用作判断几个好友
	file.close();
	cout << "按任意键返回QQ主页" << endl;
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

	cout << "请输入讨论组名称" << endl;
	string name;
	cin >> name;
	judge_flush(stdin);
	cout << "您的临时讨论组号为:" << ID << endl;
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
	cout << "按任意键返回QQ主页" << endl;
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
		cout << "第" << i + 1 << "个临时讨论组" << endl;
		cout << "群号:" << ReturnAllQQTemporaryGroup()[i]->Return_Group_ID();
		cout << "群名称" << ReturnAllQQTemporaryGroup()[i]->Return_Group_Name();
	}
	cout << "请输入您想加入的群号，或输入#返回QQ主页" << endl;
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
				cout << "没有此讨论组" << endl;
				cout << "请重新输入群号或输入#返回QQ主页" << endl;
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

	cout << "加入临时讨论组成功" << endl;
	cout << "按任意键返回QQ主页" << endl;
	if (getchar() != EOF)
		QQMenu();
	return;
}