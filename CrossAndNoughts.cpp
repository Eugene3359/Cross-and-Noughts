#include "CrossAndNoughts.h"


//--------------------------------------------------------------------------------

size_t random(size_t n) {
	// ������� ������� ��������� ����� � ������� [1 - n]
	srand(time(NULL));
	return ((rand() % n) + 1);
}

bool fate() {
	// ������� ������� ��������� ��������� true ��� false
	srand(time(NULL));
	return (rand() % 2);
}

//--------------------------------------------------------------------------------

void display(char field[][3]) {
	// ������� �������� ������ ����
	system("cls");
	std::cout << std::setw(49) << "Cross and Noughts\n\n";
	std::cout << "  -------------\n";
	for (size_t i = 0; i < 3; i++) {
		std::cout << i + 1;
		for (size_t j = 0; j < 3; j++) {
			std::cout << " | " << field[i][j];
		}
		std::cout << " |\n";
		std::cout << "  -------------\n";
	}
	std::cout << "    a   b   c\n";
}

bool check(char field[][3]) {
	// ������� �������� ������ ���� �� � 3 � ��� 'x' �� 'o'
	size_t c = 0;
	size_t z = 0;
	// �������� �� ����������
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (field[i][j] == 'x') c++;
			if (field[i][j] == 'o') z++;
		}
		if (c == 3 || z == 3) return true;
		c = 0;
		z = 0;
	}
	// �������� �� ��������
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (field[j][i] == 'x') c++;
			if (field[j][i] == 'o') z++;
		}
		if (c == 3 || z == 3) return true;
		c = 0;
		z = 0;
	}
	// �������� �� ������� �������
	for (size_t i = 0; i < 3; i++) {
		if (field[i][i] == 'x') c++;
		if (field[i][i] == 'o') z++;
	}
	if (c == 3 || z == 3) return true;
	c = 0;
	z = 0;
	// �������� �� ������ �������
	for (size_t i = 0; i < 3; i++) {
		if (field[i][2 - i] == 'x') c++;
		if (field[i][2 - i] == 'o') z++;
	}
	if (c == 3 || z == 3) return true;
	return false;
}

void clear(char field[][3]) {
	// ������� ����� ������ ����
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			field[i][j] = ' ';
		}
	}
}

//--------------------------------------------------------------------------------

char* random_move(char field[][3], size_t n) {
	// ������� ������ ���������� ���
	size_t move = random(n);
	n = 0;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (field[i][j] == ' ') n++;
			if (n == move) return &field[i][j];
		}
	}
	return nullptr;
}

char* foresight(char field[][3], bool cross) {
	// ������� �������� �� ����� ������� ���������� ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (field[i][j] == ' ') {
				field[i][j] = (cross) ? 'o' : 'x';
				if (check(field)) {
					return &field[i][j];
				}
				field[i][j] = ' ';
			}
		}
	}
	return nullptr;
}

char* foresight2(char field[][3], bool cross) {
	// ������� ������ ��� � �����, ���� �� ���� ��������� ���������
	if (field[0][1] == ((cross) ? 'o' : 'x')
		&& field[1][0] == ((cross) ? 'o' : 'x')
		&& field[0][0] == ' ') {
		field[0][0] = ((cross) ? 'o' : 'x');
		return &field[0][0];
	}
	if (field[1][0] == ((cross) ? 'o' : 'x')
		&& field[2][1] == ((cross) ? 'o' : 'x')
		&& field[2][0] == ' ') {
		field[2][0] = ((cross) ? 'o' : 'x');
		return &field[2][0];
	}
	if (field[2][1] == ((cross) ? 'o' : 'x')
		&& field[1][2] == ((cross) ? 'o' : 'x')
		&& field[2][2] == ' ') {
		field[2][2] = ((cross) ? 'o' : 'x');
		return &field[2][2];
	}
	if (field[0][1] == ((cross) ? 'o' : 'x')
		&& field[1][2] == ((cross) ? 'o' : 'x')
		&& field[0][2] == ' ') {
		field[0][2] = ((cross) ? 'o' : 'x');
		return &field[0][2];
	}
	return nullptr;
}


size_t computer_move(char field[][3], bool cross, size_t n, bool hard = false) {
	// ������� ������ ��� �������� �� ��������� ���

	// ���������� ������� ���������� ����
	if (field[1][1] == ' ') {
		field[1][1] = (cross) ? 'o' : 'x';
		return 0;
	}
	// �������� �� ����� ������� � ���� ���
	char* move = foresight(field, cross);
	if (move) return 0;
	// �������� �� ����� �������� � ���� ���
	move = foresight(field, !cross);
	if (move) {
		*move = (cross) ? 'o' : 'x';
		return 0;
	}
	// �������� �������� �� ����������� ����� ��� ������� � hard
	if (hard) {
		move = foresight2(field, cross);
		if (move) return 0;
		move = foresight2(field, !cross);
		if (move) {
			*move = (cross) ? 'o' : 'x';
			return 0;
		}
		// ��� � ���������� �����
		if (field[0][0] == ' ' && field[2][0] == ' ' && field[2][2] == ' ' && field[0][2] == ' ') {
			size_t x = random(4);
			switch (x) {
			case 1:
				field[0][0] = (cross) ? 'o' : 'x';
				break;
			case 2:
				field[2][0] = (cross) ? 'o' : 'x';
				break;
			case 3:
				field[2][2] = (cross) ? 'o' : 'x';
				break;
			case 4:
				field[0][2] = (cross) ? 'o' : 'x';
			}
			return 0;
		}
		// ��� � ����������� �����
		if (field[0][0] == ((cross) ? 'x' : 'o') && field[2][2] == ' ') {
			field[2][2] = (cross) ? 'o' : 'x';
			return 0;
		}
		if (field[2][0] == ((cross) ? 'x' : 'o') && field[0][2] == ' ') {
			field[0][2] = (cross) ? 'o' : 'x';
			return 0;
		}
		if (field[2][2] == ((cross) ? 'x' : 'o') && field[0][0] == ' ') {
			field[0][0] = (cross) ? 'o' : 'x';
			return 0;
		}
		if (field[0][2] == ((cross) ? 'x' : 'o') && field[2][0] == ' ') {
			field[2][0] = (cross) ? 'o' : 'x';
			return 0;
		}
		if (field[0][0] == ((cross) ? 'x' : 'o')
			&& field[1][1] == ((cross) ? 'x' : 'o')
			&& field[0][2] == ' '
			&& field[2][0] == ' ') {
			int x = random(2);
			switch (x) {
			case 1:
				field[0][2] = (cross) ? 'o' : 'x';
				break;
			case 2:
				field[2][0] = (cross) ? 'o' : 'x';
			}
			return 0;
		}
		if (field[2][2] == ((cross) ? 'x' : 'o')
			&& field[1][1] == ((cross) ? 'x' : 'o')
			&& field[0][2] == ' '
			&& field[2][0] == ' ') {
			int x = random(2);
			switch (x) {
			case 1:
				field[0][2] = (cross) ? 'o' : 'x';
				break;
			case 2:
				field[2][0] = (cross) ? 'o' : 'x';
			}
			return 0;
		}
		if (field[0][2] == ((cross) ? 'x' : 'o')
			&& field[1][1] == ((cross) ? 'x' : 'o')
			&& field[2][0] == ' '
			&& field[2][2] == ' ') {
			int x = random(2);
			switch (x) {
			case 1:
				field[2][0] = (cross) ? 'o' : 'x';
				break;
			case 2:
				field[2][2] = (cross) ? 'o' : 'x';
			}
			return 0;
		}
		if (field[2][0] == ((cross) ? 'x' : 'o') && field[1][1] == ((cross) ? 'x' : 'o') && field[0][2] == ' ' && field[2][2] == ' ') {
			int x = random(2);
			switch (x) {
			case 1:
				field[0][2] = (cross) ? 'o' : 'x';
				break;
			case 2:
				field[2][2] = (cross) ? 'o' : 'x';
			}
			return 0;
		}
	}
	*random_move(field, 9 - n) = (cross) ? 'o' : 'x';
	return 0;
}

//--------------------------------------------------------------------------------

int player_move(char field[][3], const char* input, bool cross) {
	// ������� ������ ��� ������

	// �� ���� ������� 2 �������
	if (std::strlen(input) != 2) return -1;
	// ���� � ������� �� ���� ������ � ����� ������
	if (!((isalpha(input[0]) && isdigit(input[1]))
		|| (isalpha(input[1]) && isdigit(input[0])))) return -1;
	// ����� �� ���� � �������� ������
	if (isalpha(input[0])) std::tolower(input[0]);
	if (isalpha(input[1])) std::tolower(input[1]);
	// horizontal, vertical
	int h = -1, v = -1;
	// ������� �� ��������� �� ���� � ����� ������� ���������� ����������� � ���������, ���� ������� ���������
	h = (isdigit(input[0])) ? input[0] - 49 : input[1] - 49;
	v = (isalpha(input[0])) ? input[0] - 97 : input[1] - 97;
	// ���� ���� ��������� �������� -1 �� ��� ������������ ���
	if (h == -1 || v == -1) return -1;
	// ���� ���� ��������� �������� > 2 �� ��� ������������ ���
	if (h > 2 || v > 2) return -1;
	// ���� ������� ������� ����
	if (field[h][v] != ' ') return -1;
	// ��
	char c = (cross) ? 'x' : 'o';
	field[h][v] = c;
	return 0;
}

//--------------------------------------------------------------------------------

void run() {
	int input;
	char field[3][3];
	do {
		clear(field);
		system("cls");
		std::cout << std::setw(49) << "Cross and Noughts\n\n";
		std::cout << "Choose mode\n"
			<< "1 - Player vs Computer\n"
			<< "2 - Player vs Player\n"
			<< "0 - Exit\n\n";
		std::cin >> input;
		std::cout << '\n';
		switch (input) {
		case 1:
			PvC_menu(field);
			break;
		case 2:
			PvP(field);
			break;
		case 0:
			break;
		default:
			std::cout << "Wrong input\n";
			system("pause");
		}
	} while (input != 0);
	std::cout << "Exit";
}

void PvC_menu(char field[][3]) {
	// ������� ������ ���� Player vs Computer
	int input;
	do {
		system("cls");
		std::cout << std::setw(49) << "Cross and Noughts\n\n";
		std::cout << "Choose difficulty\n"
			<< "1 - Easy\n"
			<< "2 - Medium\n"
			<< "3 - Hard\n"
			<< "0 - Back\n\n";
		std::cin >> input;
		std::cout << '\n';
		switch (input) {
		case 1:
			PvC(field, "easy");
			break;
		case 2:
			PvC(field, "medium");
			break;
		case 3:
			PvC(field, "hard");
		case 0:
			return;
		default:
			std::cout << "Wrong input\n";
			system("pause");
		}
	} while (input < 0 && input > 3);
}

//--------------------------------------------------------------------------------

void PvC(char field[][3], const char* dificulty) {
	char input[5] = "";
	bool cross = fate();
	int n = 0, done;
	display(field);
	if (cross) {
		std::cout << "You are playing for cross.\n";
		system("pause");
	}
	else {
		std::cout << "You are playing for noughts.\n";
		system("pause");
		//9-n �� ������� ���������� ����
		*random_move(field, 9 - n) = 'x';
		n++;
	}
	while (n < 9) {
		display(field);
		std::cout << "Your move\n";
		done = -1;
		while (done != 0) {
			std::cin >> input;
			std::cout << '\n';
			//player_move ������� 0 ��� ������� �������� �������
			done = player_move(field, input, cross);
			if (done != 0) std::cout << "Wrong input, try again.\n";
		}
		n++;
		display(field);
		if (check(field)) {
			std::cout << "YOU ARE WIN\n";
			break;
		}
		//�� ���� ��������, ���� �� ������
		if (n == 9) break;
		if (dificulty == "easy") {
			*random_move(field, 9 - n) = (cross) ? 'o' : 'x';
		}
		else if (dificulty == "medium") {
			computer_move(field, cross, n);
		}
		else if (dificulty == "hard") {
			computer_move(field, cross, n, true);
		}
		n++;
		display(field);
		if (check(field)) {
			std::cout << "YOU ARE LOSE\n";
			break;
		}
	}
	if (!check(field) && n == 9) std::cout << "DRAW\n";
	system("pause");
}

//--------------------------------------------------------------------------------

void PvP(char field[][3]) { //������� ����� ���� ���� �� play
	char input[5] = "";
	bool cross = fate();
	int n = 0, done;
	display(field);
	if (cross) {
		std::cout << "Player1 playing for cross and Player2 for noughts.\n";
		system("pause");
	}
	else {
		std::cout << "Player1 playing for noughts and Player2 for cross.\n";
		system("pause");
		display(field);
		std::cout << "Player2 moves.\n";
		done = -1;
		while (done != 0) {
			std::cin >> input;
			std::cout << '\n';
			done = player_move(field, input, !cross);
			if (done != 0) std::cout << "Wrong input, try again.\n";
		}
		n++;
	}
	while (n < 9) {
		display(field);
		std::cout << "Player1 moves\n";
		done = -1;
		while (done != 0) {
			std::cin >> input;
			std::cout << '\n';
			done = player_move(field, input, cross);
			if (done != 0) std::cout << "Wrong input, try again.\n";
		}
		n++;
		display(field);
		if (check(field)) {
			std::cout << "PLAYER1 WINS\n";
			break;
		}
		if (n == 9) break;
		display(field);
		std::cout << "Player2 moves\n";
		done = -1;
		while (done != 0) {
			std::cin >> input;
			std::cout << '\n';
			done = player_move(field, input, !cross);
			if (done != 0) std::cout << "Wrong input, try again.\n";
		}
		n++;
		display(field);
		if (check(field)) {
			std::cout << "PLAYER2 WINS\n";
			break;
		}
	}
	if (!check(field) && n == 9) std::cout << "DRAW\n";
	system("pause");
}

//--------------------------------------------------------------------------------