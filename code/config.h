#pragma once
#include<Windows.h>
#include<string>
#include<iostream>
using namespace std;
using namespace std;
const int default_color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//豌豆颜色
const int Pea_color = FOREGROUND_GREEN;
//PeaArcher颜色
const int PeaArcher_color = BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//Sunflower颜色
const int Sunflower_color = BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//商店颜色
const int store_color = BACKGROUND_GREEN | BACKGROUND_BLUE | default_color;
// Zombie颜色
const int Zombie_color = BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//寒冰豌豆颜色
const int SnowPea_color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//SnowPea颜色
const int Snow_color = BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
//Zombie被减速后颜色
const int Slowedzombie_color = Snow_color;
void color_cout(const string& str, int id = default_color);
void color_cout(int num, int id = default_color);
void set_coord(int x, int y);
