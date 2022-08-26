#pragma once

#include "Header.h"


size_t random(size_t n);		// для рандомізації ходу
bool fate();					// для жеребкування

void display(char field[][3]);			// вивід ігрового поля
bool check(char field[][3]);			// перевірка чи хтось переміг
void clear(char field[][3]);			// очищення ігрового поля

char* random_move(char field[][3], size_t n);			// випадковий хід комп*ютера
char* foresight(char field[][3], bool cross);			// передбачення виграша
char* foresight2(char field[][3], bool cross);			// передбачення виграша
size_t computer_move(char field[][3], bool cross, size_t n, bool hard);	// оптимальный хід комп*ютера

int player_move(char field[][3], const char* input, bool cross);		// хід гравця

void run();			// запуск початкового меню гри

void PvC_menu(char field[][3]);			// меню вибора складності гри
// easy - випадкові ходи, medium - прогнозування, hard - оптимальна стратерія

void PvC(char field[][3], const char* dificulty);		//гра проти ПК

void PvP(char field[][3]);								//гравець проти гравця