#include<iostream>
#include<string>
#pragma once
using  namespace std;
void printCentered(const string& text, int width);
void calculateAge(const std::string& applyDateStr);
tm parseDate(const std::string& dateStr);
void judge_flush(FILE* fp);
int  judge_count_menu(string str, int n);//�жϸ�λ��ѡ�����ȷ�Բ�������ȷ��ѡ��
bool isValidDate(int year, int month, int day);
string birthday_input();

void trim(string& str);
string toLower(const string& str);