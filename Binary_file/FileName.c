#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <time.h> 
#include <stdlib.h>

void read_file(FILE*fp) {
	int value;
	printf("\033[35mЗначения в файле:\033[0m \n");

	while (fread(&value, sizeof(int), 1, fp) == 1)
	{
		printf("%d ", value);
	}
	printf("\n");

}

void verification_file(FILE* fp) {
	if (fp == NULL) {
		perror("\033[91mОшибка при открытии файла.\033[0m\n");
		return 1;
	}
}

void checking_input() {
	printf("\033[91mОшибка: введено некорректное значение!\033[0m\nПовторите попытку: ");
	rewind(stdin);
}

void input(FILE*fp,int num,int value) {
	for (int i = 0;i < num;i++)
	{
		printf("%d-й элемент равен:\n", i + 1);

		while (scanf_s("%d", &value) != 1 || getchar() != '\n')
		{
			checking_input();
		}
		if (fwrite(&value, sizeof(int), 1, fp) != 1)
		{
			perror("\033[91mОшибка записи элемента в файл.\033[0m\n");
			fclose(fp);
			return 1;
		}
	}
}


int main(int argc,char**argv) {
	setlocale(LC_ALL, "rus");
	int num = 0, n = 0;
	int value = 0;
	int max_len = 1;
	FILE* fp = NULL;
	char* file = argv[1];

	printf("\033[35mВыберите задание для выполния\033[0m:\n\033[36m1\033[0m - Найти самую длинную последовательность равных элементов.\n\033[36m2\033[0m - Занулить элементы, стоящие на позициях с четными номерами.\n\033[36m3\033[0m - Отсортировать файл.\n\033[0mВаш выбор: ");

	while (scanf_s("%d", &n) != 1 || n < 1 || n > 3 || getchar() != '\n')
	{
		checking_input();
	}

	printf("\n\033[35mВведите количество элементов в файле\033[0m: ");

	while (scanf_s("%d", &num) != 1 || num < 1 || getchar() != '\n')
	{
		checking_input();
	}

	switch (n) {
	case 1:
		fp = fopen(file, "wb");
		verification_file(fp);
		int max_seq_same = 1;
		int sequence = 1;
		int storing;

		for (int i = 0;i < num;i++)
		{
			printf("%d-й элемент равен:\n", i + 1);
			

			while (scanf_s("%d", &value) != 1 || getchar() != '\n')
			{
				checking_input();
			}
			if (fwrite(&value, sizeof(int), 1, fp) != 1)
			{
				perror("\033[91mОшибка записи элемента в файл.\033[0m\n");
				fclose(fp);
				return 1;
			}
			if (i == 0) {
				storing = value;
			}
			else if (value == storing)
			{
				sequence++;
			}
			else
				sequence = 1;

			if (max_seq_same < sequence)
			{
				max_seq_same = sequence;
			}
			storing = value;

		}
		if (fclose(fp) == EOF) {
			perror("Ошибка закрытия файла");
			return 1;
		}

		fclose(fp);

		fp = fopen(file, "rb");
		verification_file(fp);
		read_file(fp);

		printf("\033[35mМаксимальная длина одинаковый элементов\033[0m %d ", max_seq_same);
		fclose(fp);
		break;

	case 2:
		fp = fopen(file, "wb");
		verification_file(fp);
		input(fp, num, value);
		fclose(fp);

		fp = fopen(file, "r+b");
		verification_file(fp);

		for (int i = 0;i < num;i++)
		{
			if (i % 2 == 0)
			{
				value = 0;
			}
			else {
				fseek(fp, i * sizeof(int), SEEK_SET);

				if (fread(&value, sizeof(int), 1, fp) != 1)
				{
					perror("033[91mОшибка чтения элемента из файла.033[0m\n");
					fclose(fp);
					return 1;
				}
			}

			fseek(fp, i * sizeof(int), SEEK_SET);

			if (fwrite(&value, sizeof(int), 1, fp) != 1)
			{
				perror("\033[91mОшибка записи элемента в файл.\033[0m\n");
				fclose(fp);
				return 1;
			}
		}
		fclose(fp);

		fp = fopen(file, "rb");
		verification_file(fp);
		read_file(fp);
		fclose(fp);
		break;
	case 3:
		fp = fopen(file, "wb");
		verification_file(fp);
		input(fp, num, value);
		fclose(fp);

		fp = fopen(file, "r+b");
		verification_file(fp);

		int index = 0;
		int even_element = 0;

		while (index < num) {

			fseek(fp, index * sizeof(int), SEEK_SET);
			if (fread(&value, sizeof(int), 1, fp) != 1)
			{
				perror("033[91mОшибка чтения элемента из файла.033[0m\n");
				fclose(fp);
				return 1;
			}

			if (value % 2 == 0 && value != 0 ) {
				if (index > even_element) {
					for (int i = index; i > even_element; --i) {
						int prev;
						fseek(fp, (i - 1) * sizeof(int), SEEK_SET);
						if (fread(&prev, sizeof(int), 1, fp) != 1) {
							perror("\033[91mОшибка чтения элемента из файла.\033[0m\n");
							fclose(fp);
							return 1;
						}
						fseek(fp, i * sizeof(int), SEEK_SET);
						if (fwrite(&prev, sizeof(int), 1, fp) != 1) {
							perror("\033[91mОшибка записи элемента в файл.\033[0m\n");
							fclose(fp);
							return 1;
						}
					}

					fseek(fp, even_element * sizeof(int), SEEK_SET);
					if (fwrite(&value, sizeof(int), 1, fp) != 1) {
						perror("\033[91mОшибка записи элемента в файл.\033[0m\n");
						fclose(fp);
						return 1;
					}
					even_element++;
				}
				else {
					even_element++;
				}

			}
			
			index++;
		}
		fclose(fp);

		fp = fopen(file, "r+b");
		verification_file(fp);

		int variable;
		int zero_element = even_element;

		for (int i = even_element;i < num;i++) 
		{
			fseek(fp, i * sizeof(int), SEEK_SET);
			if (fread(&variable, sizeof(int), 1, fp) != 1) 
			{
				perror("\033[91mОшибка чтения элемента из файла.\033[0m\n");
				fclose(fp);
				return 1;
			}
			if (variable == 0) 
			{
				if (i > zero_element) 
				{
					int val = 0;
					for (int j = i; j > zero_element; --j)
					{
						int prev_num;
						fseek(fp, (j - 1) * sizeof(int), SEEK_SET);
						if (fread(&prev_num, sizeof(int), 1, fp) !=1 )
						{
							perror("\033[91mОшибка чтения элемента из файла.\033[0m\n");
							fclose(fp);
							return 1;
						}

						fseek(fp, j * sizeof(int), SEEK_SET);
						if (fwrite(&prev_num, sizeof(int), 1, fp) != 1)
						{
							perror("\033[91mОшибка записи элемента в файл.\033[0m\n");
							fclose(fp);
							return 1;
						}
					}
					fseek(fp, zero_element * sizeof(int), SEEK_SET);
					if (fwrite(&val, sizeof(int), 1, fp) != 1) 
					{
						perror("\033[91mОшибка записи элемента в файл.\033[0m\n");
						fclose(fp);
						return 1;
					}

					zero_element++;

				}
				else {
					zero_element++;
				}
			}
		}
		fclose(fp);
		
		fp = fopen(file, "rb");
		verification_file(fp);

		int value1;
		printf("\033[35mЗначения в файле после сортировки:\033[0m \n");
		while (fread(&value1, sizeof(int), 1, fp) == 1)
		{
			printf("%d ", value1);
		}
		printf("\n");

		fclose(fp);
	}
	return 0;

}