#pragma once
#include<windows.h>
#include<stdlib.h>
#include<ctime>
#include<conio.h>
#include<iostream>
using namespace std;
void SetCursorPosition(const int x, const int y);
void HideCursor();
void SetColor(WORD p);

void SetColor(WORD p)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, p);
}
void SetCursorPosition(const int x, const int y)//���
{
	COORD   position; //����ṹ����� 
	position.X = 2 * x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void HideCursor()//ˢ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}