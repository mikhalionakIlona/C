#include <stdio.h>
#include <locale.h>
#include "functions.h"


int main() {
	setlocale(LC_ALL, "rus");
	int number;

	do {

		printf("\033[35mВыберите задание для выполния\033[0m:\n\033[36m1\033[0m - Найти и вывести остаток от деления целого числа на 2.\n\033[36m2\033[0m - Работа с геометрическими фигурами.\n\033[36m3\033[0m - Выход.\nВаш выбор: ");

		while (scanf_s("%d", &number) != 1 || number < 1 || number > 3 || getchar() != '\n')
		{
			checking_input();
		}

		switch (number)
		{
		case 1:
			finding_remainder_divisions_2();
			break;

		case 2:
			words_structures();
			break;
		}
	} while (number!=3);

	return 0;
}