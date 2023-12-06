#include <iostream>
#include <string>
#include <conio.h>
//#include <stdio.h>
#include <Windows.h>
//#include <locale.h>

class Creature {
private:
	std::string TYPE;
	bool ALIVE;
	int LEVEL;
	int STRENGTH;
	int DEXTERITY;
	int INTELLIGENCE;
	int HP;
public:
	// Рандомное существо 1-50 уровень
	Creature(std::string TYPE = "enemy") : TYPE(TYPE), ALIVE(1) {
		double rlvl = rand() % 50 + 1;
		this->LEVEL = rlvl;
		this->STRENGTH = rlvl * (rand() % 20 + 1) / 10.0;		// Уровень на коэфф. 0.1 - 2.0
		this->DEXTERITY = rlvl * (rand() % 20 + 1) / 10.0;
		this->INTELLIGENCE = rlvl * (rand() % 20 + 1) / 10.0;
		this->HP = 100 + 100 * rlvl;			// Базовые 100 + 100 за каждый уровень

		if (TYPE != "enemy" || TYPE != "hero")
			throw std::runtime_error("Wrong type!");
	}
	// Самописное существо 
	Creature(std::string TYPE, int LEVEL, int STRENGTH, int DEXTERITY, int INTELLIGENCE) : TYPE(TYPE), ALIVE(1), LEVEL(LEVEL), STRENGTH(STRENGTH), DEXTERITY(DEXTERITY), INTELLIGENCE(INTELLIGENCE) {
		HP = 100 + 100 * LEVEL;
		if (TYPE != "enemy" || TYPE != "hero")
			throw std::runtime_error("Wrong type!");
	}

	long attack() {
		return ((STRENGTH + DEXTERITY + INTELLIGENCE) * (1 + double(LEVEL) / 100.0));
	}
	void get_damage(long DMG) {
		HP -= DMG;
		if (HP <= 0)
			HP = ALIVE = 0;
	}
};

HANDLE hConsole;
enum ColorConsole {
	Black = 0, Blue, Green, Cyan, Red, Purple, Yellow, White, Grey, GlowBlue, GlowGreen, GlowCyan, GlowRed, GlowPurple, GlowYellow, GlowWhite, Black_WhiteBack = 112
};
enum MainKeys {
	Left = 75, Up = 72, Right = 77, Down = 80, Enter = 13
};

void DRAW_MainMenuChoice(short POS) {

	std::cout << std::endl << std::endl /*CoolRPG*/
	<<"\t          _              _            _            _             _           _          _    		" << std::endl
	<<"\t        /\\ \\           /\\ \\         /\\ \\         _\\ \\          /\\ \\        /\\ \\       /\\ \\			" << std::endl
	<<"\t       /  \\ \\         /  \\ \\       /  \\ \\       /\\__ \\        /  \\ \\      /  \\ \\     /  \\ \\ 		" << std::endl
	<<"\t      / /\\ \\ \\       / /\\ \\ \\     / /\\ \\ \\     / /_ \\_\\      / /\\ \\ \\    / /\\ \\ \\   / /\\ \\_\\  		" << std::endl
	<<"\t     / / /\\ \\ \\     / / /\\ \\ \\   / / /\\ \\ \\   / / /\\/_/     / / /\\ \\_\\  / / /\\ \\_\\ / / /\\/_/ 		" << std::endl
	<<"\t    / / /  \\ \\_\\   / / /  \\ \\_\\ / / /  \\ \\_\\ / / /         / / /_/ / / / / /_/ / // / / ______ 		" << std::endl
	<<"\t   / / /    \\/_/  / / /   / / // / /   / / // / /         / / /__\\/ / / / /__\\/ // / / /\\_____\\ 	" << std::endl
	<<"\t  / / /          / / /   / / // / /   / / // / / ____    / / /_____/ / / /_____// / /  \\/____ / 	" << std::endl
	<<"\t / / /________  / / /___/ / // / /___/ / // /_/_/ ___/\\ / / /\\ \\ \\  / / /      / / /_____/ / / 		" << std::endl
	<<"\t/ / /_________\\/ / /____\\/ // / /____\\/ //_______/\\__\\// / /  \\ \\ \\/ / /      / / /______\\/ /  		" << std::endl
	<<"\t\\/____________/\\/_________/ \\/_________/ \\_______\\/    \\/_/    \\_\\/\\/_/       \\/___________/   		" << std::endl << std::endl << std::endl;

	const char* lines[]{
		/*New Battle*/ "\t\t\t     __                  ___       _   _   _      \n\t\t\t  /\\ \\ \\_____      __   / __\\ __ _| |_| |_| | ___ \n\t\t\t /  \\/ / _ \\ \\ /\\ / /  /__\\/// _` | __| __| |/ _ \\\n\t\t\t/ /\\  /  __/\\ V  V /  / \\/  \\ (_| | |_| |_| |  __/\n\t\t\t\\_\\ \\/ \\___| \\_/\\_/   \\_____/\\__,_|\\__|\\__|_|\\___|\n\n",
		/*Quit*/ "\t\t\t   ____       _ _   \n\t\t\t  /___ \\_   _(_) |_ \n\t\t\t //  / / | | | | __|\n\t\t\t/ \\_/ /| |_| | | |_ \n\t\t\t\\___,_\\ \\__,_|_|\\__|\n"
	};
	short i = 1;
	for (auto l : lines) {
		// Выводит окрашенный пункт, если он выбран в данный момент
		if (i == POS) {
			SetConsoleTextAttribute(hConsole, GlowYellow);
			std::cout << l << std::endl;
			SetConsoleTextAttribute(hConsole, White);
		}
		else
			std::cout << l << std::endl;

		i += 1;
	}
}
void MainMenuChoice(short& MenuChosen)
{
	short POS = 1;
	while (1) {
		// Рисует текущее состояние интерфейса с выделением выбранных строк
		DRAW_MainMenuChoice(POS);

		// Для получения нажатой стрелки
		short inp = _getch();
		if (inp == 0 || inp == 224) {
			short key = _getch();
			if (key == Up) {
				if (POS - 1 == 0)
					POS = 2;
				else
					POS -= 1;
			}
			if (key == Down) {
				if (POS + 1 == 3)
					POS = 1;
				else
					POS += 1;
			}
		}
		// Для выхода из функции
		// Также возвращает выбранный пункт
		if (inp == Enter) {
			MenuChosen = POS;
			system("cls");
			break;
		}

		system("cls");
	}
}

void Battle()
{
	
}

int main()
{
	srand(time(NULL));
	/*setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	short MenuChosen;
	MainMenuChoice(MenuChosen); // 1 - new battle	2 - quit

	switch (MenuChosen)
	{
	case 1:
		std::cout << "Creating a new battle..." << std::endl;
		Sleep(1500);
		Battle();
		break;

	case 2:
		std::cout << "Closing the program...";
		Sleep(1500);
		break;
	}

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.