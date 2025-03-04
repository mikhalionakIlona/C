#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>


void verification_file(FILE* fp) 
{
	if (fp == NULL) {
		perror("\033[91mОшибка при открытии файла.\033[0m\n");
		return 1;
	}
}

void checking_input() 
{
	printf("\033[91mОшибка: введено некорректное значение!\033[0m\nПовторите попытку: ");
	rewind(stdin);
}

void my_fclose(FILE* fp) 
{
	if (fclose(fp) == EOF) {
		perror("Ошибка закрытия файла");
		return 1;
	}
}

void print_str(FILE* fp)
{
	printf("\033[35m\nВведите стороку:\033[0m\n");
	char a = getchar();
	while (a != '\n')
	{
		fprintf(fp, "%c", a);
		a = getchar();
	}
}

void reading_file(FILE* fp) 
{
	char value;
	printf("\033[35m\nСодержимое файла:\033[0m\n");
	while ((value=fgetc(fp))!=EOF)
	{
		printf("%c",value);
	}
	printf("\n");
}


 void  count_word(FILE* fp)
{
	int count = 0, word = 0, second = -1, current = -1, prelast = -1, last = -1;
	char value;
	
	while ((value = fgetc(fp)) != EOF)
	{
		if (isalpha(value))
		{ 
			if (!word)
			{
				count++;
				word = 1;
				current = ftell(fp) - 1;

				prelast = last;
				last = current;

				if (count == 2) 
				{
					second = current;
                }
			}
		}
		else {
			word = 0;
		}
	}
	
	if (second != -1) {
		fseek(fp, second, SEEK_SET);
		printf("\n\033[35mВторое слово: \033[0m");

		while ((value = fgetc(fp)) != EOF && isalpha(value)||isdigit(value))
		{
			printf("%c", value);
		}
		printf("\n");
	}
	else {
		printf("Второе слово не найдено.\n");
	}

	if (prelast != -1) {
		fseek(fp, prelast, SEEK_SET);
		printf("\n\033[35mПредпоследнее слово: \033[0m");
		while ((value = fgetc(fp)) != EOF && isalpha(value)||isdigit(value))
		{
			printf("%c", value);
		}
		printf("\n");
	}
	else {
		printf("Предпоследнее слово не найдено.\n");
	}

}

 void swap(FILE* fp) 
 {
	 int count = 0, word = 0, current = -1, count_word = 0;
	 char value;
	 int short_len = INT_MAX, short_start = -1;
	 int long_len = 0, long_start=-1;

	 while ((value = fgetc(fp)) != EOF)
	 {
		 if (isalpha(value))
		 {
			 if (!word)
			 {
				 count++;
				 word = 1;
				 current = ftell(fp) - 1;
				 count_word = 1;
			 }
			 else {
				 count_word++;
			 }
		 }
		 else if(word)
		 {
			 if (count_word < short_len)
			 {
				 short_len = count_word;
				 short_start = current;
			 }
			 if (count_word > long_len)
			 {
				 long_len = count_word;
				 long_start = current;
			 }
			 word = 0;
			 
		 }
	 }
	 if (count < 2) {
		 printf("Недостаточно слов для обмена \n");
	 }
	 if (word) 
	 {
		 if (count_word < short_len)
		 {
			 short_len = count_word;
			 short_start = current;
		 }
		 if (count_word > long_len)
		 {
			 long_len = count_word;
			 long_start = current;
		 }
	 }


	 if (short_start == -1 || long_start == -1) 
	 {
		 printf("Не удалось определить короткое и длинное слово\n ");
		 return 1;
	 }

	 char* short_temp = malloc(short_len + 1);
	 char* long_temp = malloc(long_len + 1);
	 if (!short_temp || !long_temp) {
		 printf("Не удалось выделить память\n");
		 free(short_temp);
		 free(long_temp);
		 return 1;
	 }

	 

	 fseek(fp, long_start, SEEK_SET);
	 fread(long_temp, sizeof(char), long_len, fp);
	 long_temp[long_len] = '\0';

	 fseek(fp, short_start, SEEK_SET);
	 fread(short_temp, sizeof(char), short_len, fp);
	 short_temp[short_len] = '\0';


	 fseek(fp, short_start, SEEK_SET);
	 fwrite(long_temp, sizeof(char), long_len, fp);
	 for (int i = 0;i < short_len - long_len;i++) {
		 fputc(' ', fp);
     }
	 
	 fseek(fp, long_start, SEEK_SET);
	 fwrite(short_temp, sizeof(char), short_len, fp);
	 for (int i = 0;i < long_len - short_len;i++) 
	 {
		 fputc(' ', fp);
	 }

	 free(short_temp);
	 free(long_temp);
 }



int main(int argc, char** argv) {
	setlocale(LC_ALL, "rus");
	FILE* fp = NULL;
	char* file = argv[1];
	int n, count=0;


	printf("\033[35mВыберите задание для выполния\033[0m:\n\033[36m1\033[0m - Заполнить файл словами и вывести на экран.\n\033[36m2\033[0m - Распечатать второе и предпоследнее слова.\n\033[36m3\033[0m - Поменять местами самое длинное слово и самое короткое.\n\033[0mВаш выбор: ");

	while (scanf_s("%d", &n) != 1 || n < 1 || n > 3 || getchar() != '\n')
	{
		checking_input();
	}

	switch (n) {
	case 1:

		fp = fopen(file, "w");
		verification_file(fp);
		print_str(fp);
		my_fclose(fp);

		fp = fopen(file, "r");
		verification_file(fp);
		reading_file(fp);
		my_fclose(fp);

		break;
	case 2:

		fp = fopen(file, "w");
		verification_file(fp);
		print_str(fp);
		my_fclose(fp);

		fp = fopen(file, "r");
		verification_file(fp);
		count_word(fp);
		my_fclose(fp);

		break;

	case 3:

		fp = fopen(file, "w");
		verification_file(fp);
		print_str(fp);
		my_fclose(fp);

		fp = fopen(file, "r+");
		verification_file(fp);
		swap(fp);
		my_fclose(fp);

		fp = fopen(file, "r");
		verification_file(fp);
		reading_file(fp);
		my_fclose(fp);

		break;
	}

	return 0;
}
