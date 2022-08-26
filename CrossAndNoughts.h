#pragma once

#include "Header.h"


size_t random(size_t n);		// ��� ����������� ����
bool fate();					// ��� ������������

void display(char field[][3]);			// ���� �������� ����
bool check(char field[][3]);			// �������� �� ����� ������
void clear(char field[][3]);			// �������� �������� ����

char* random_move(char field[][3], size_t n);			// ���������� ��� ����*�����
char* foresight(char field[][3], bool cross);			// ������������ �������
char* foresight2(char field[][3], bool cross);			// ������������ �������
size_t computer_move(char field[][3], bool cross, size_t n, bool hard);	// ����������� ��� ����*�����

int player_move(char field[][3], const char* input, bool cross);		// ��� ������

void run();			// ������ ����������� ���� ���

void PvC_menu(char field[][3]);			// ���� ������ ��������� ���
// easy - �������� ����, medium - �������������, hard - ���������� ��������

void PvC(char field[][3], const char* dificulty);		//��� ����� ��

void PvP(char field[][3]);								//������� ����� ������