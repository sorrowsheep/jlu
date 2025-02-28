#pragma once
#pragma once
#ifndef WEIBOCHATBASE_QFH_H
#define WEIBOCHATBASE_QFH_H
#include "ChatBase_Qfh.h"
#include <vector>
#include <string>
using namespace std;
class WeiBo_Qfh; // 前向声明

class WeiBoChatBase_Qfh : public ChatBase_Qfh
{

public:
	//微博功能未实现除了登录
	virtual vector<WeiBo_Qfh*>& ReturnWeiBolist();
	virtual void SaveWeiBo();

	virtual void GetWeiBo();

	virtual void WeiBoMenu();

	virtual void Menu();

	virtual void Login();

	virtual void Apply();

	virtual void AddFriend();

	virtual void SaveFriends();

	virtual void Get_Friends();

	virtual void ShowFriends();

	virtual void DeleteFriend();

	virtual void AgreeFriend();

	virtual void ShowFriendInformation();

	virtual void ChangeFriendRemarks();

	virtual void SaveChange();

	virtual void AgreeMember();

	virtual void ShowMyInformation();

	virtual void Change_PassWord();

	virtual void Change_Name();

	virtual void Change_AutoGraph();

	virtual void Change_Area();

	virtual void Get_Links();

protected:

	vector<WeiBo_Qfh*> WeiBoList;

	string LoginedWeiBoID;

	
	
private:

};

class WeiBoChat_Qfh : public WeiBoChatBase_Qfh
{
public:
	
	//跳转登录实现
	void splogin(const string& ID) {
		system("CLS"); // 清屏
		cout << "正在登录 " << ID << "..." << endl;

		// 查找微信ID
		auto it = find_if(WeiBoList.begin(), WeiBoList.end(),
			[&](WeiBo_Qfh* weixin) { return weixin->Return_ID() == ID; });

		// 检查是否找到了对应的微信
		if (it != WeiBoList.end()) {
			WeiBo_Qfh* weixinObj = *it;

			// 如果该微信已处于登录状态，直接获取信息
			if (weixinObj->flag == 1) {
				LoginedWeiBoID = ID; // 设置已登录的微信号
				Get_Friends(); // 获取好友
				Get_Links(); // 获取绑定的 QQ
				cout << "登录成功" << endl;
				cout << "按任意键开始使用微信" << endl;
				if (getchar() != EOF)
					WeiBoMenu(); // 进入微信主菜单
				return;
			}

			// 如果微信未登录
			cout << "该微信尚未登录，默认密码进行验证..." << endl;
			string defaultPassword = "1";
			cin >> defaultPassword;
			// 假设有一个默认密码，实际情况请根据需求调整
			if (weixinObj->Return_PassWord() == defaultPassword) {
				LoginedWeiBoID = ID; // 设置已登录的微信号
				Get_Friends(); // 获取好友
				Get_Links(); // 获取绑定的 QQ
				cout << "登录成功" << endl;
				cout << "按任意键开始使用微信" << endl;
				if (getchar() != EOF)
					WeiBoMenu(); // 进入微信主菜单
				return;
			}
			else {
				cout << "默认密码验证失败，无法登录。" << endl;
				return;
			}
		}
		else {
			cout << "未找到对应的微信号：" << ID << endl;
		}
	}

};
#endif // !WEIBOCHATBASE_QFH_H
