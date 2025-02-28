#include"judge.h"
#include<iostream>
#include<string>
#include<sstream>
#include <windows.h>
#include<ctime>
#include<iomanip>
#include<cstdlib>
#include <stdlib.h>
#include <algorithm>
#include <cctype>
using namespace std;
#pragma once
// ȥ���ַ���ǰ��Ŀո�
void trim(string& str) {
	
	auto start = str.find_first_not_of(" \t");
	auto end = str.find_last_not_of(" \t");

	if (start == string::npos) { // ȫ�ǿո�
		str = "";
	}
	else {
		str = str.substr(start, end - start + 1);
	}
}
// �ַ���תСд
string toLower(const string& str) {
	string lowercaseStr = str;
	transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(), ::tolower);
	return lowercaseStr;
}
void printCentered(const string& text, int width) {
	int padding = (width - text.length()) / 2;
	cout << setw(padding + text.length()) << text << endl;
}
// �����������ע��ʱ�䵽���ڵ����䣬���ظ�ʽ "X��Y����Z��"
void calculateAge(const std::string& applyDateStr) {
	std::tm registerDate = parseDate(applyDateStr);

	// �жϽ����Ƿ���Ч
	if (registerDate.tm_year == 0 && registerDate.tm_mon == 0 && registerDate.tm_mday == 0) {
		cout << "���ڽ���ʧ�ܣ��޷��������䡣" << endl;
		return;
	}

	time_t registerTime = mktime(&registerDate); // ת��Ϊ time_t ����
	time_t currentTime = time(NULL); // ��ǰʱ��� time_t

	// ����ʱ���
	double secondsDifference = difftime(currentTime, registerTime);

	// ��������
	int daysDifference = static_cast<int>(secondsDifference / (60 * 60 * 24));

	// ת��Ϊ���ʣ�����������Ƽ���
	int years = daysDifference / 365;
	int remainingDays = daysDifference % 365;

	// �����º���
	int months = remainingDays / 30;
	remainingDays = remainingDays % 30; // ʣ�������

	cout << "T�䣺" << years << "�� " << months << "�� " << remainingDays << "��" << endl;
}
// ����ʵ�ʵ����ڸ�ʽ�޸�
std::tm parseDate(const std::string& dateStr) {
	std::tm tm = {};
	std::istringstream ss(dateStr);
	ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");

	// ���������
	if (ss.fail()) {
		tm = {}; // ����ʧ��ʱ���� tm ����ΪĬ��
	}

	return tm;
}
//��ȫ�ж�
void judge_flush(FILE* fp)
{
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n');
}
//�˵�ѡ����
int  judge_count_menu(string str, int n)
{
	int select = 0;
	int flag;
	int len = str.size();
	if (len != 1 && len != 2)
	{
		cout << "������ĸ�ʽ���󣬰�������������˵�\n";
		if (getchar() != EOF)
			return -1;
	}
	if (len == 1)
	{
		select = str[0] - '0';
		if (select<0 || select>n)
		{
			cout << "������ķ�Χ�������ⷵ����һ���˵�\n";
			if (getchar() != EOF)
				return -1;
		}
	}
	else if (len == 2)
	{
		select = 10 * (str[0] - '0') + str[1] - '0';
		if (select != 10 && select != 11)
		{
			cout << "������ķ�Χ�������ⷵ����һ���˵�\n";
			if (getchar() != EOF)
				return -1;
		}
	}
	return select;
}
//�������ո�ʽ
bool isValidDate(int year, int month, int day) {
	int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
		return (day >= 1 && day <= 29);
	}
	return (day >= 1 && day <= daysInMonth[month - 1]);
}

string birthday_input() {
	string temp;
	while (true) {
		cout << "���������� (��ʽ: YYYYMMDD): ";
		cin >> temp;
		judge_flush(stdin); // ����������

		// ��鳤��
		if (temp.size() != 8) {
			cout << "��Ч�����ڸ�ʽ�������ԡ�" << endl;
			continue;
		}

		int year = stoi(temp.substr(0, 4));
		int month = stoi(temp.substr(4, 2));
		int day = stoi(temp.substr(6, 2));

		if (year < 1900 || year > 2020 || month < 1 || month > 12 || !isValidDate(year, month, day)) {
			cout << "��������ȷ��������ʽ����ʽ: YYYYMMDD" << endl;
			continue;
		}

		break; // �Ϸ����ڣ��˳�ѭ��
	}
	return temp;
}
