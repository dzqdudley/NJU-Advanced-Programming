#pragma once
#include<Windows.h>
#include<string>
#include<iostream>
using namespace std;
using namespace std;
const int default_color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//�㶹��ɫ
const int Pea_color = FOREGROUND_GREEN;
//PeaArcher��ɫ
const int PeaArcher_color = BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//Sunflower��ɫ
const int Sunflower_color = BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//�̵���ɫ
const int store_color = BACKGROUND_GREEN | BACKGROUND_BLUE | default_color;
// Zombie��ɫ
const int Zombie_color = BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//�����㶹��ɫ
const int SnowPea_color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//SnowPea��ɫ
const int Snow_color = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//Zombie�����ٺ���ɫ
const int Slowedzombie_color = Snow_color;
void color_cout(const string& str, int id = default_color);
void color_cout(int num, int id = default_color);
void set_coord(int x, int y);
