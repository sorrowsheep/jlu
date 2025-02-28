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


};
#endif // !WEIBOCHATBASE_QFH_H
