#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<unordered_map>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
//帐号基类
class Account_Qfh 
{
public:
	virtual int Return_Friend_Number() = 0;//返回好友数量
	virtual int Return_Group_Number() = 0;//返回群数量
	virtual string Return_ID() = 0;//返回账号的ID
	virtual string  Return_PassWord() = 0;//返回账号的密码
	virtual string  Return_Name() = 0;//返回账号的昵称
	virtual string  Return_Area() = 0;//返回用户的地区
	virtual string  Return_Autograph() = 0;//返回个性签名
	virtual string Return_ApplyDate() = 0;//返回注册时间
	virtual string Return_Sex() = 0;//返回用户性别
	virtual string Return_bir() = 0;//返回用户的生日
	virtual void Change_group_num(int num) = 0;//设定群数量，如在在群退群时候要进行更改
	virtual void Change_Friends_Number(int num) = 0;//设定好友数量
	virtual void Change_PassWord(string pw) = 0;//改变密码
	virtual void Change_Name(string newname) = 0;//改变名字
	virtual void Change_AutoGraph(string newautograph) = 0;//改变个性签名
	virtual void Change_Area(string newarea) = 0;//改变地区
protected:
	int Friend_Number; //好友数量
	int Group_Number; //群数量
	string ID;  //帐号
	string Name;  //用户姓名
	string PassWord; //用户密码
	string Area;//用户所在地区
	string Autograph;//用户个性签名
	string Sex;//用户的性别
	string ApplyDate;//用户注册日期
	string birthday;//用户的生日
	struct SexType
	{
		string SexFlag;
	}Man{ "男" }, WoMan{ "女" };
private:
};













