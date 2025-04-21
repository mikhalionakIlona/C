#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "functions.h"



int main() {
	setlocale(LC_ALL, "rus");
	int number;

	do {

		printf("\033[35m�������� ������� ��� ��������\033[0m:\n\033[36m1\033[0m - ������� ������ �������,� ���� �� ��������� � �������� ������,�� �� ��������� � �������.\n\033[36m2\033[0m - ������� ������� �����,� ���� �� �� ��������� � ��������� ������,�� ��������� ����� ����������� ������.\n\033[36m3\033[0m - ��������� �� ��������� ��� �������.\n\033[36m4\033[0m - �����.\n\033[35m��� �����:\033[0m ");

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


