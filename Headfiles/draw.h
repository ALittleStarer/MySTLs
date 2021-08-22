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
void SetCursorPosition(const int x, const int y)//输出
{
	COORD   position; //定义结构体变量 
	position.X = 2 * x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void HideCursor()//刷新
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}