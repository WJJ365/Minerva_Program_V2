#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>


struct PlayerStatus {
	char name[100];
	int atk;
	int def;
	int level;
	int expup;
	int expdown;
	int hp;
	int mana;
	int jobS;
	char Skill1N[10];
	int Skill1D;
	int Skill1MU;

};
struct MonsterStatus {
	int LK;
	int hp;
	int atk;
	int def;
	int md;
	int exp;
	int monsterhp;
	int moneydrop;
	int monsteratk;
	int monsterdef;
	int monsterexp;
};

struct matrix {
	int sel1;
	int sel2;
	int sel3;
	int sel4;
	int* num1 = (int*)malloc(sizeof(sel1));
	int* num2 = (int*)malloc(sizeof(sel2));
	int* num3 = (int*)malloc(sizeof(sel3));
	int* num4 = (int*)malloc(sizeof(sel4));
	float a[2][3]; //[��][��], ��� a
	float b[3][3]; //[��][��]��� b
};

void showstat_current(int lv, int exp, int expfull, int atk, int def, int hp, char job);
void printupbar();
void gotoxy(int x, int y);
void loading(int x);
void loading2(int x);
void showstat(PlayerStatus info);
PlayerStatus Input();
MonsterStatus Setting(PlayerStatus info);
void level(PlayerStatus info, MonsterStatus info2);
void dowhat();
void scolor(unsigned short text, unsigned short back);
void printhpbar(int a, int b);
void printintro();
static void softmax(float* input, size_t input_len); //����Ʈ�ƽ� �Լ� ����
char MonsterSel(int n);
int sMonAtk(MonsterStatus info);


//void roomv1();

int main() {
	struct matrix A[40];
	struct matrix B[40];


	int playernum = 0;
	int playerlevel;
	int playermoney;
	int playerhp;
	playerlevel = 1;
	playermoney = 0;
	playerhp = 50;

	PlayerStatus info;
	MonsterStatus info2;


	printupbar();
	printintro();


	info = Input();
	info2 = Setting(info);
	info.level = 1;
	info.expdown = 0;
	info.expup = 0;
	system("cls");
	loading2(1);
	system("cls");

	printf("LEVEL1\n");
	while (true) {
		//void roomv1();
		int k;
		dowhat();
		scanf("%d", &k);
		if (k == 1) {
			system("cls");
			level(info, info2);

		}
		if (k == 2) {
			printf("��: ���Ͱ� ���� ��Ȳ���� ���� ���ǹ��ϴ�..\n");
			loading(2);
			system("cls");
		}
		if (k == 3) {
			printf("------------------------------------------\n");
			printf("%s%10s%10s%10s\n", "�̸�", "���ݷ�", "����", "����");
			printf("%s%10d%10d%10d\n", info.name, info.atk, info.def, info.level);
			printf("------------------------------------------\n");
		}
	}

	while (true) {
		int i;
		i = rand() % 3;

		if (i == 1) {

		}

	}

	system("PAUSE");
	return 0;
}
//main �Լ� ����

PlayerStatus Input() {
	PlayerStatus info;//ĳ���� ���� �Է�
	info.hp = 20;
	int sel;

	for (int i = 1; i >= 1; i--) {
		printf("ĳ���� �̸��� �Է��ϼ���.\n");
		scanf("%s", info.name);
		getchar();

		printf("���ݷ°� ������ ������ 10 �̳� ��� �մϴ�.\n���ݷ��� �Է��ϼ���! (�ڿ����� �Է����ּ���..) ");
		scanf("%d", &info.atk);
		getchar();

		printf("������ �Է��ϼ���! ");
		scanf("%d", &info.def);
		int p = info.atk + info.def;
		if (p > 10) {
			printf("������ 10�� �ѽ��ϴ�. �ٽ� �Է����ּ���!\n");
			i++;
		}
	}
	printf("������ �������� �Ͻðڽ��ϱ�?\n");
	printf("1.���谡\n");
	scanf("%d", &sel);
	if (sel == 1) {
		info.Skill1D = info.atk * 2;
		info.Skill1MU = 5;
		info.jobS = 0;
	}
	return info;
}

MonsterStatus Setting(PlayerStatus info) {
	MonsterStatus info2;
	info2.hp = rand() % (info.level * 30);
	info2.atk = rand() % (info.level * 5);
	info2.def = rand() % (info.level * 3);
	info2.md = rand() % (info.level * 7);
	info2.exp = rand() % (info.level * 40);
	info2.moneydrop = info2.md;
	info2.monsteratk = info2.atk;
	info2.monsterdef = info2.def;
	info2.monsterexp = info2.exp;
	info2.LK = info.level * (rand() % 4);

	return info2;
}

void loading(int x) {//�ε� 
	Sleep(1000 * x);
}

void loading2(int x) {//�ε� +.
	printf("Loading");
	for (int i = 0; i < x; i++) {
		Sleep(1000 * x);
		printf(".");
	}
}

void level(PlayerStatus info, MonsterStatus info2) {//���� 

	int Playerlevel = info.level;
	int point = 0;
	while (true) {

		int choice;
		int criticalpoint;
		int rmonsterhp = 1;
		int rmonsteratk = 0;
		int rmonsterdef = 0;
		int rmonsterexp = 0;
		int PlayerHP = info.hp;
		int Playeratk = info.atk;
		int Playerdef = info.def;
		int leveldown = info.expdown;
		int levelup = info.expup;
		int r2monsterhp;
		int PlayerLk = info.level * (rand() % 4);
		int MonsterLk = info2.LK;
		char Playerjob[11][11] = { "���谡1" ,"���谡2" };
		char Playerskill[10][10][30] = { { "����" } };
		int PlayerskillD = 0;
		int PlayerM = 0;

		while (true) {
			if (PlayerM <= 0) {
				PlayerM = rand() % 100;
			}
			else {
				PlayerM = info.mana;
				break;
			}
		}

		int PlayerskillMU = info.Skill1MU;
		srand((int)time(NULL));
		while (Playerlevel < 5) {//���� ��������

			//moneydrop = info2.md;
			srand((int)time(NULL));

			rmonsterhp = rand() % (Playerlevel * 30);//�÷��̾� ���� *30 = ���� ���� hp �Ѱ� ����

			rmonsteratk = rand() % (Playerlevel * 5);//�÷��̾� ���� * 5 = ���ݷ� �Ѱ����

			rmonsterdef = rand() % (Playerlevel * 3);//�÷��̾� ���� * 5 = ���� �Ѱ����

			rmonsterexp = rand() % (Playerlevel * 20);//�÷��̾� ���� * 5 = ����ġ �Ѱ����

			r2monsterhp = rmonsterhp;
			int n = rand() % 10;
			char monstername = MonsterSel(n);

			printf("%c�� ��Ÿ����!\n", monstername);

			while (rmonsterhp > 0) {
				printf("%10s%10s%10s\n", "monstername", "hp", "Atk");
				printf("%10c%10d%10d\n", monstername, rmonsterhp, rmonsteratk);
				scolor(10, 0);
				gotoxy(0, 10);
				printhpbar(rmonsterhp, r2monsterhp);
				showstat_current(Playerlevel, levelup, leveldown, Playeratk, Playerdef, PlayerHP, *Playerjob[info.jobS]);
				dowhat();//�ൿ ����
				scanf("%d", &choice);


				if (choice == 1) {//����
					int n;
					printf("1. �Ϲݰ���.\t 2.��ų ���.\n");
					scanf("%d", &n);
					if (n == 1) {
						if (PlayerLk < MonsterLk) {
							criticalpoint = rand() % 10;
							printf("%c�� ������!\n", monstername);
							loading(1);

							if (criticalpoint >= 7) {
								printf("ũ��Ƽ��!\n\n");
								loading(2);
								PlayerHP = PlayerHP - rmonsteratk * 2;
								printf("%s�� %d�� �������� �Ծ���!\n", &info.name, rmonsteratk * 2);
								loading(1);
							}
							else if (criticalpoint < 7) {
								PlayerHP = PlayerHP - rmonsteratk;
								printf("%s�� %d�� �������� �Ծ���!\n", &info.name, rmonsteratk);
								loading(1);
							}
							printf("%s�� ����!\n", info.name);
							loading(1);
							criticalpoint = rand() % 10;
							if (criticalpoint >= 7) {
								printf("ũ��Ƽ��!\n\n");
								loading(2);
								rmonsterhp = rmonsterhp - Playeratk * 2;
								printf("%c�� %d�� �������� �Ծ���!\n", monstername, Playeratk * 2);
								loading(1);
							}
							else if (criticalpoint < 7) {
								rmonsterhp = rmonsterhp - Playeratk;
								printf("%c�� %d�� �������� �Ծ���!\n", monstername, Playeratk);
								loading(1);
							}
						}

						if (PlayerLk >= MonsterLk) {
							criticalpoint = rand() % 10;
							printf("%s�� ������!\n", info.name);
							loading(1);

							if (criticalpoint >= 7) {
								printf("ũ��Ƽ��!\n\n");
								loading(2);
								rmonsterhp = rmonsterhp - Playeratk * 2;
								printf("%c�� %d�� �������� �Ծ���!\n", monstername, Playeratk * 2);
								loading(1);
							}
							else if (criticalpoint < 7) {
								rmonsterhp = rmonsterhp - Playeratk;
								printf("%c�� %d�� �������� �Ծ���!\n", monstername, Playeratk);
								loading(1);
							}
							if (rmonsterhp > 0) {
								criticalpoint = rand() % 10;
								printf("%c�� ����!\n", monstername);
								loading(1);
								if (criticalpoint >= 7) {
									printf("ũ��Ƽ��!\n\n");
									loading(2);
									PlayerHP = PlayerHP - rmonsteratk * 2;
									printf("%s�� %d�� �������� �Ծ���!\n", &info.name, rmonsteratk * 2);
									loading(1);
								}
								else if (criticalpoint < 7) {
									PlayerHP = PlayerHP - rmonsteratk;
									printf("%s�� %d�� �������� �Ծ���!\n", &info.name, rmonsteratk);
									loading(1);
								}
							}
						}
						system("cls");
					}

					if (n == 2) {
						if (PlayerLk < MonsterLk) {
							criticalpoint = rand() % 10;
							printf("%c�� ������!\n", monstername);
							loading(1);

							if (criticalpoint >= 7) {
								printf("ũ��Ƽ��!\n\n");
								loading(2);
								PlayerHP = PlayerHP - rmonsteratk * 2;
								printf("%s�� %d�� �������� �Ծ���!\n", &info.name, rmonsteratk * 2);
								loading(1);
							}
							else if (criticalpoint < 7) {
								PlayerHP = PlayerHP - rmonsteratk;
								printf("%s�� %d�� �������� �Ծ���!\n", &info.name, rmonsteratk);
								loading(1);
							}
							loading(1);
							criticalpoint = rand() % 10;

							printf("%s�� %s!\n", &info.name, &Playerskill[info.jobS][0]);
							while (true) {
								if (PlayerskillD <= 0) {
									srand((int)time(NULL));
									PlayerskillD = rand() % (info.Skill1D + 10);
								}
								else {
									break;
								}
							}
							if (criticalpoint >= 7) {
								printf("ũ��Ƽ��!\n\n");
								loading(2);
								rmonsterhp = rmonsterhp - PlayerskillD * 2;
								printf("%c�� %d�� �������� �Ծ���!\n", monstername, PlayerskillD * 2);
								loading(1);
							}
							else if (criticalpoint < 7) {
								rmonsterhp = rmonsterhp - PlayerskillD;
								printf("%c�� %d�� �������� �Ծ���!\n", monstername, PlayerskillD);
								loading(1);
							}
						}
						if (PlayerLk >= MonsterLk) {

							criticalpoint = rand() % 10;
							while (true) {
								if (PlayerskillD <= 0) {
									srand((int)time(NULL));
									PlayerskillD = rand() % (info.Skill1D + 10);
								}
								else {
									break;
								}
							}
							printf("%s�� ������!\n", info.name);
							loading(1);
							printf("%s�� %s!\n", &info.name, &Playerskill[info.jobS][0]);
							if (criticalpoint >= 7) {
								printf("ũ��Ƽ��!\n\n");
								loading(2);
								rmonsterhp = rmonsterhp - PlayerskillD * 2;
								printf("%c�� %d�� �������� �Ծ���!\n", monstername, PlayerskillD * 2);
								loading(1);
							}
							else if (criticalpoint < 7) {
								rmonsterhp = rmonsterhp - PlayerskillD;
								printf("%c�� %d�� �������� �Ծ���!\n", monstername, PlayerskillD);
								loading(1);
							}
							if (rmonsterhp > 0) {
								criticalpoint = rand() % 10;
								printf("%c�� ����!\n", monstername);
								loading(1);
								if (criticalpoint >= 7) {
									printf("ũ��Ƽ��!\n\n");
									loading(2);
									PlayerHP = PlayerHP - rmonsteratk * 2;
									printf("%s�� %d�� �������� �Ծ���!\n", &info.name, rmonsteratk * 2);
									loading(1);
								}
								else if (criticalpoint < 7) {
									PlayerHP = PlayerHP - rmonsteratk;
									printf("%s�� %d�� �������� �Ծ���!\n", &info.name, rmonsteratk);
									loading(1);
								}
							}

						}

						system("cls");
					}
					PlayerskillD = 0;
				}

				else if (choice == 2) {//���
					int randPlayerdef;

					srand((int)time(NULL));
					randPlayerdef = rand() % (Playerdef + 1);

					if (randPlayerdef >= rmonsteratk) {
						printf("�� �����ߴ�!\n");
						loading(1);
					}
					else if (randPlayerdef < rmonsteratk) {
						PlayerHP = PlayerHP - (rmonsteratk - randPlayerdef);
						printf("%d�������� �޾Ҵ�!\n", rmonsteratk - randPlayerdef);
						loading(1);
					}

				}
				else if (choice == 3) {
					system("cls");
					printf("------------------------------------------\n");
					printf("%s%10s%10s%10s%10s\n", "�̸�", "���ݷ�", "����", "����", "����");
					printf("%s%10d%10d%10d%10s\n", info.name, Playeratk, Playerdef, Playerlevel, &Playerjob);
					printf("------------------------------------------\n");
					loading(1);
				}
				//���� ǥ��â

				if (rmonsterhp <= 0) {

					printf(" %c�� �����ƴ�!\n\n", monstername);
					loading(2);
					printf("����ġ %d�� �����!\n\n", rmonsterexp);
					loading(2);
					leveldown = Playerlevel * 50;
					levelup = levelup + rmonsterexp;
					system("cls");
					loading(1);
					if (levelup / leveldown >= 1) {
						Playerlevel = Playerlevel + 1;
						system("cls");
						printf("������!\n");
						loading(2);
						system("cls");
						printf("���ݷ� 2 ����!\n");
						printf("���� 2 ����!\n");
						loading(2);
						system("cls");
						Playeratk = Playeratk + info.level * 2;
						Playerdef = Playerdef + info.level * 2;
						levelup = 0;
					}

				}
				info.hp = PlayerHP;
				point++;
				/*if (info.hp <= 0) {
					goto Label1;*/
			}
		}

	}


}






void showstat(PlayerStatus info) {

}

/*PlayerStatus Input()
{
	return PlayerStatus();
}
*/
void dowhat() {

	printf("������ �ұ��?\n");
	printf("-------------------------------\n");
	printf("1.������ �Ѵ�.\t2.���Ѵ�. \t3.������ ����.\n");
	printf("-------------------------------\n");

}
void scolor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
void printhpbar(int a, int b) {
	if ((a / b) > 0, (a / b) <= 0.1) {
		printf("--\n");
		printf("--\n");
	}
	else if ((a / b) > 0.1, (a / b) <= 0.2) {
		printf("----\n");
		printf("----\n");
	}
	else if ((a / b) > 0.2, (a / b) <= 0.3) {
		printf("------\n");
		printf("------\n");
	}
	else if ((a / b) > 0.3, (a / b) <= 0.4) {
		printf("--------\n");
		printf("--------\n");
	}
	else if ((a / b) > 0.4, (a / b) <= 0.5) {
		printf("----------\n");
		printf("----------\n");
	}
	else if ((a / b) > 0.5, (a / b) <= 0.6) {
		printf("------------\n");
		printf("------------\n");
	}
	else if ((a / b) > 0.6, (a / b) <= 0.7) {
		printf("--------------\n");
		printf("--------------\n");
	}
	else if ((a / b) > 0.7, (a / b) <= 0.8) {
		printf("----------------\n");
		printf("----------------\n");
	}
	else if ((a / b) > 0.8, (a / b) <= 0.9) {
		printf("------------------\n");
		printf("------------------\n");
	}
	else if ((a / b) > 0.9, (a / b) <= 1) {
		printf("--------------------\n");
		printf("--------------------\n");
	}
	scolor(15, 0);
}

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void printupbar() {
	system("cls"); // ȭ���� ����� ó������ ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // ��� ���ڸ� ���� ������� ����
	system("title=`                                                                                          ������Ȱ��������Ʈ");
}
void printintro() {
	printf("�ȳ��ϼ���\n");
	loading(2);
	system("cls");

	printf("������ ��ٸ������� �𸨴ϴ�.\n");
	loading(2);
	system("cls");

	printf("������ ���� ���� ���� 10000�Դϴ�.\n");
	loading(2);
	system("cls");

	printf("������ �ο��ּ���\n");
	loading(2);
}
void showstat_current(int lv, int exp, int expfull, int atk, int def, int hp, char job) {
	scolor(5, 0);
	printf("______________________________________________\n");
	scolor(15, 0);
	printf("%s%10s%10s%10s%10s\n", "HP", "LEVEL", "ATK", "DEF", "JOB");
	printf("%d%10d%10d%10d\n", hp, lv, atk, def, job);
	scolor(5, 0);
	printf("______________________________________________\n");
	scolor(15, 0); 
	printf("����ġ:\t %d% / %d\n", exp, expfull);
	scolor(5, 0);
	printf("______________________________________________\n");
	scolor(15, 0);
}


static void softmax(float* input, size_t input_len) { //����Ʈ�ƽ� �Լ� ����
	assert(input);
	float m = -INFINITY;
	for (size_t i = 1; i < input_len; i++) {
		if (input[i] > m) {
			m = input[i];
		}
	}
	float sum = 0.0;
	for (size_t i = 0; i < input_len; i++) {
		sum += expf(input[i] - m);
	}
	float offset = m + logf(sum);
	for (size_t i = 0; i < input_len; i++) {
		input[i] = expf(input[i] - offset);
	}
}
char MonsterSel(int n) {
	if (n == 1) {
		const char* monstername = "A";
		return *monstername;
	}
	else if (n == 2) {
		const char* monstername = "B";
		return *monstername;
	}
	else if (n == 3) {
		const char* monstername = "C";
		return *monstername;
	}
	else if (n == 4) {
		const char* monstername = "D";
		return *monstername;
	}
	else if (n == 5) {
		const char* monstername = "E";
		return *monstername;
	}
	else if (n == 6) {
		const char* monstername = "F";
		return *monstername;
	}
	else if (n == 7) {
		const char* monstername = "G";
		return *monstername;
	}
	else if (n == 8) {
		const char* monstername = "H";
		return *monstername;
	}
	else if (n == 9) {
		const char* monstername = "I";
		return *monstername;
	}
	else if (n == 10) {
		const char* monstername = "J";
		return *monstername;
	}

}
int sMonAtk(MonsterStatus info) {
	int MonsterAtk = rand() % info.atk;
	return MonsterAtk;
}