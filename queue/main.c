#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "functions.h"



int main() {
	setlocale(LC_ALL, "rus");
	int number;

	do {

		printf("\033[35mВыберите задание для выполния\033[0m:\n\033[36m1\033[0m - Удалить первый элемент,и если он совпадает с введеным числом,то он заносится в очередь.\n\033[36m2\033[0m - Удалить элемент слева,и если он не совпадает с введенным числом,то введенное число добавляется справа.\n\033[36m3\033[0m - Проверить на равенство две очереди.\n\033[36m4\033[0m - Выход.\n\033[35mВаш выбор:\033[0m ");

		while (scanf_s("%d", &number) != 1 || number < 1 || number > 4 || getchar() != '\n')
		{
			checking_input();
		}

		switch (number)
		{
		case 1:
			delete_item_matches();
			break;
		case 2:
			delete_item_different();
			break;
		case 3:
			equality_queues();
			break;
		}
	} while (number != 4);

	return 0;
}


