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
// 去掉字符串前后的空格
void trim(string& str) {
	
	auto start = str.find_first_not_of(" \t");
	auto end = str.find_last_not_of(" \t");

	if (start == string::npos) { // 全是空格
		str = "";
	}
	else {
		str = str.substr(start, end - start + 1);
	}
}
// 字符串转小写
string toLower(const string& str) {
	string lowercaseStr = str;
	transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(), ::tolower);
	return lowercaseStr;
}
void printCentered(const string& text, int width) {
	int padding = (width - text.length()) / 2;
	cout << setw(padding + text.length()) << text << endl;
}
// 函数：计算从注册时间到现在的年龄，返回格式 "X年Y个月Z天"
void calculateAge(const std::string& applyDateStr) {
	std::tm registerDate = parseDate(applyDateStr);

	// 判断解析是否有效
	if (registerDate.tm_year == 0 && registerDate.tm_mon == 0 && registerDate.tm_mday == 0) {
		cout << "日期解析失败，无法计算年龄。" << endl;
		return;
	}

	time_t registerTime = mktime(&registerDate); // 转换为 time_t 类型
	time_t currentTime = time(NULL); // 当前时间的 time_t

	// 计算时间差
	double secondsDifference = difftime(currentTime, registerTime);

	// 计算天数
	int daysDifference = static_cast<int>(secondsDifference / (60 * 60 * 24));

	// 转换为年和剩余天数，近似计算
	int years = daysDifference / 365;
	int remainingDays = daysDifference % 365;

	// 估算月和日
	int months = remainingDays / 30;
	remainingDays = remainingDays % 30; // 剩余的天数

	cout << "T龄：" << years << "年 " << months << "月 " << remainingDays << "天" << endl;
}
// 根据实际的日期格式修改
std::tm parseDate(const std::string& dateStr) {
	std::tm tm = {};
	std::istringstream ss(dateStr);
	ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");

	// 检查解析结果
	if (ss.fail()) {
		tm = {}; // 解析失败时，将 tm 设置为默认
	}

	return tm;
}
//安全判断
void judge_flush(FILE* fp)
{
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n');
}
//菜单选择函数
int  judge_count_menu(string str, int n)
{
	int select = 0;
	int flag;
	int len = str.size();
	if (len != 1 && len != 2)
	{
		cout << "您输入的格式有误，按任意键返回主菜单\n";
		if (getchar() != EOF)
			return -1;
	}
	if (len == 1)
	{
		select = str[0] - '0';
		if (select<0 || select>n)
		{
			cout << "您输入的范围有误按任意返回上一级菜单\n";
			if (getchar() != EOF)
				return -1;
		}
	}
	else if (len == 2)
	{
		select = 10 * (str[0] - '0') + str[1] - '0';
		if (select != 10 && select != 11)
		{
			cout << "您输入的范围有误按任意返回上一级菜单\n";
			if (getchar() != EOF)
				return -1;
		}
	}
	return select;
}
//输入生日格式
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
		cout << "请输入日期 (格式: YYYYMMDD): ";
		cin >> temp;
		judge_flush(stdin); // 清理输入流

		// 检查长度
		if (temp.size() != 8) {
			cout << "无效的日期格式，请重试。" << endl;
			continue;
		}

		int year = stoi(temp.substr(0, 4));
		int month = stoi(temp.substr(4, 2));
		int day = stoi(temp.substr(6, 2));

		if (year < 1900 || year > 2020 || month < 1 || month > 12 || !isValidDate(year, month, day)) {
			cout << "请输入正确的日期形式，格式: YYYYMMDD" << endl;
			continue;
		}

		break; // 合法日期，退出循环
	}
	return temp;
}
