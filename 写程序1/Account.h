#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<unordered_map>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
//�ʺŻ���
class Account_Qfh 
{
public:
	virtual int Return_Friend_Number() = 0;//���غ�������
	virtual int Return_Group_Number() = 0;//����Ⱥ����
	virtual string Return_ID() = 0;//�����˺ŵ�ID
	virtual string  Return_PassWord() = 0;//�����˺ŵ�����
	virtual string  Return_Name() = 0;//�����˺ŵ��ǳ�
	virtual string  Return_Area() = 0;//�����û��ĵ���
	virtual string  Return_Autograph() = 0;//���ظ���ǩ��
	virtual string Return_ApplyDate() = 0;//����ע��ʱ��
	virtual string Return_Sex() = 0;//�����û��Ա�
	virtual string Return_bir() = 0;//�����û�������
	virtual void Change_group_num(int num) = 0;//�趨Ⱥ������������Ⱥ��Ⱥʱ��Ҫ���и���
	virtual void Change_Friends_Number(int num) = 0;//�趨��������
	virtual void Change_PassWord(string pw) = 0;//�ı�����
	virtual void Change_Name(string newname) = 0;//�ı�����
	virtual void Change_AutoGraph(string newautograph) = 0;//�ı����ǩ��
	virtual void Change_Area(string newarea) = 0;//�ı����
protected:
	int Friend_Number; //��������
	int Group_Number; //Ⱥ����
	string ID;  //�ʺ�
	string Name;  //�û�����
	string PassWord; //�û�����
	string Area;//�û����ڵ���
	string Autograph;//�û�����ǩ��
	string Sex;//�û����Ա�
	string ApplyDate;//�û�ע������
	string birthday;//�û�������
	struct SexType
	{
		string SexFlag;
	}Man{ "��" }, WoMan{ "Ů" };
private:
};













