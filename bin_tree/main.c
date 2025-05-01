#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "functions.h"

int main() {
	setlocale(LC_ALL, "rus");
	int number;

	do {

		printf("\033[35m-------- Меню --------\033[0m\n\033[36m1\033[0m - Создание бинарного дерева.\n\033[36m2\033[0m - Произвести удаление элементов дерева.\n\033[36m3\033[0m - Найти максимальное количество одинаковых элементов бинарного дерева.\n\033[36m4\033[0m - Выход.\n\033[35mВаш выбор:\033[0m ");

		while (scanf_s("%d", &number) != 1 || number < 1 || number > 4 || getchar() != '\n')
		{
			checking_input();
		}

		switch (number)
		{
		case 1:
			arbitrary_bin_tree();
			break;
		case 2:
			delete_element_bin_tree();
			break;
		case 3:
			similar_element();
			break;
		}
	} while (number != 4);

	return 0;
}