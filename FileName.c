#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

void verification_file(FILE* fp) {
	if (fp == NULL) {
		perror("\033[91m������ ��� �������� �����.\033[0m\n");
		return 1;
	}
}

void checking_input() {
	printf("\033[91m������: ������� ������������ ��������!\033[0m\n��������� �������: ");
	rewind(stdin);
}

int main() {
	setlocale(LC_ALL, "rus");
	int num=0,n=0;

	printf("\033[35m�������� ������� ��� ��������\033[0m:\n\033[36m1\033[0m - ����� ����� ������� ������������������ ������ ���������.\n\033[36m2\033[0m - �������� ��������, ������� �� �������� � ������� ��������\n\033[36m3\033[0m - ������������� ����\n\033[0m��� �����: ");
	
	while (scanf_s("%d", &n) != 1 || n < 1 || n > 3 || getchar() != '\n') 
	{
		checking_input();
	}

	printf("\n\033[35m������� ���������� ��������� � �����\033[0m: ");

	while (scanf_s("%d", &num) != 1 || num < 1 || getchar() != '\n')
	{
		checking_input();
	}

	FILE* fp = NULL;
	fp = fopen("my_file.bin", "wb");
	verification_file(fp);

	for (int i = 0;i < num;i++) 
	{
		int value;
		printf("%d-� ������� �����:\n", i);

		while (scanf_s("%d", &value) != 1 || getchar() != '\n')
		{
			checking_input();
		}

		if (fwrite(&value, sizeof(int), 1, fp) != 1) 
		{
			perror("\033[91m������ ������ �������� � ����.\033[0m\n");
			fclose(fp);
			return 1;
		}
	}
	if (fclose(fp) == EOF) {
		perror("������ �������� �����");
		return 1;
	}

	fp = fopen("my_file.bin", "rd");
	verification_file(fp);

	int value1;
	printf("\033[35m�������� � �����:\033[0m \n");

	while (fread(&value1, sizeof(int), 1, fp) == 1)
	{
		printf("%d", value1);
	}
	printf("\n");
	fclose(fp);

	return 0;
}
