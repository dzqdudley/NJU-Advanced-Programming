#pragma once
#include"Garden.h"
#include<string>
#include<vector>
#include<conio.h>
#include"Zombie.h"
#include"Store.h"
using namespace std;

class Game {
public:
	Game();
	//ɾ��ָ��λ��Zombie(���������ؿ���)
	void delete_zombie(int row, int col, Zombie*);
	//����������Zombie
	void zombie_dead();
	//��ȫˢ����Ļ
	void refresh_everything();
	//�̵�������
	bool goto_store();
	//����ֲ��
	bool place_plant();
	//��Ϸ��ѭ��
	void loop();
	//����Zombie
	void add_zombie(int row, int col);
	//ֲ��ִ����������
	void function();
	//����Zombie�ƶ�
	void all_zombies_move();
	//��԰��ֲ�ﱻ����
	void plant_eaten();
	//�ӵ�����Zombie
	void bullet_hit_zombie();
	//������Ϸ״̬
	bool check_game_status();
	//�ӵ��ƶ�
	void all_bullets_move();
	//�ӵ���ʾ
	void display_bullets();
	//��ͣ
	void pause();
	//��ǰ������Ϸ
	void end_game();
	//Catapult_Zombie�Ĵ���
	void basketball_hit_plant();
	//������ͨ�ӵ�
	bool add_ordinary_bullet(int row, int col);
	//���Ӻ����ӵ�
	bool add_snow_bullet(int row, int col);
	//�����Ƿ���Zombie
	static bool cell_has_zombie(int row, int col) { return garden.cells[row][col].has_zombie(); }
	//ɾ��Zombie
	static void cell_delete_zombie(int row, int col, Zombie* i) { garden.cells[row][col].delete_zombie(i); }
	//����Zombie
	static void cell_push_back_zombie(int row, int col, Zombie* i) { garden.cells[row][col].push_back_zombie(i); }
	//��λ
	static void cell_set_this_plant_cause(int row, int col, bool flg){ garden.cells[row][col].set_this_plant_cause(flg); }
	//��λ
	static void cell_set_plant_explode(int row, int col, bool flg) { garden.cells[row][col].set_plant_explode(flg); }
	//��λ
	static void cell_set_has_zombie(int row, int col, bool flg){ garden.cells[row][col].set_has_zombie(flg); }
	//��λ
	static void cell_set_set_has_zombie(int row, int col, bool flg) { garden.cells[row][col].set_has_zombie(flg); }
	//��λ
	static void cell_set_refresh_need(int row,int col,bool flg){ garden.cells[row][col].set_refresh_need(flg); }
	void squash_function(int row, int col);
	void cherrybomb_function(int row, int col);
	void garlic_function(int row, int col);
private:
	//���굱ǰ����λ��
	int cur_row, cur_col;
	//��ǰ�Ļ�԰
	static Garden garden;
	//�̵�
	static Store store;
	//����Zombie
	vector <Zombie*> all_zombies;
	//�����ӵ�
	vector<Bullet*>all_bullets;
	//��ǰ��Ϸ״̬
	int state;
	enum state { normal, shopping, placing };
	//����Zombieʱ������
	clock_t add_zombie_count;
	//����Zombie�ٶ�
	int add_zombie_speed;
};
