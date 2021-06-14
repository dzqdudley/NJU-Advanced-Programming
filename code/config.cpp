#include"config.h"
void color_cout(const string& str, int id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), id);
	cout << str;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_color);
}
void color_cout(int num, int id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), id);
	cout << num;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), default_color);
}
void set_coord(int x, int y)//ÉèÖÃ¹â±ê
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}