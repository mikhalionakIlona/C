#include <stdio.h>
#include <locale.h>
#include "functions.h"



void main() {
	setlocale(LC_ALL, "rus");

	int number;
	do {

		printf("\033[35m�������� ������� ��� ��������\033[0m:\n\033[36m1\033[0m - ������� �� ������� ����� ��� �������� ������� ���� �� ������ �����.\n\033[36m2\033[0m - ��� ���������� � ��������������� �������� ������ ������������ ������ ���� ������������� �� �����������.\n\033[36m3\033[0m - �������������� ���������.\n��� �����: ");

		while (scanf_s("%d", &number) != 1 || number < 1 || number > 4 || getchar() != '\n')
		{
			checking_input();
		}

		switch (number)
		{
		case 1:
			finding_identical_elements();
			break;

		case 2:
			form_ascending_stack();
			break;
		case 3:

			break;
		}

	} while (number != 4);
	return 0;
}