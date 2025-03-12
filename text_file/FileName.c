#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>


void verification_file(FILE* fp) 
{
	if (fp == NULL) {
		perror("\033[91mÎøèáêà ïðè îòêðûòèè ôàéëà.\033[0m\n");
		return 1;
	}
}

void checking_input() 
{
	printf("\033[91mÎøèáêà: ââåäåíî íåêîððåêòíîå çíà÷åíèå!\033[0m\nÏîâòîðèòå ïîïûòêó: ");
	rewind(stdin);
}

void my_fclose(FILE* fp) 
{
	if (fclose(fp) == EOF) {
		perror("Îøèáêà çàêðûòèÿ ôàéëà");
		return 1;
	}
}

void print_str(FILE* fp)
{
	printf("\033[35m\nÂâåäèòå ñòîðîêó:\033[0m\n");
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
	printf("\033[35m\nÑîäåðæèìîå ôàéëà:\033[0m\n");
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
		printf("\n\033[35mÂòîðîå ñëîâî: \033[0m");

		while ((value = fgetc(fp)) != EOF && isalpha(value)||isdigit(value))
		{
			printf("%c", value);
		}
		printf("\n");
	}
	else {
		printf("Âòîðîå ñëîâî íå íàéäåíî.\n");
	}

	if (prelast != -1) {
		fseek(fp, prelast, SEEK_SET);
		printf("\n\033[35mÏðåäïîñëåäíåå ñëîâî: \033[0m");
		while ((value = fgetc(fp)) != EOF && isalpha(value)||isdigit(value))
		{
			printf("%c", value);
		}
		printf("\n");
	}
	else {
		printf("Ïðåäïîñëåäíåå ñëîâî íå íàéäåíî.\n");
	}

}

 void find_min_max_word_indexes(char words[50][100], int word_count, int* min_index, int* max_index) {
	 if (word_count == 0) {
		 *min_index = -1;
		 *max_index = -1;
		 return;
	 }

	 *min_index = 0;
	 *max_index = 0;
	 size_t min_length = strlen(words[0]);
	 size_t max_length = strlen(words[0]);

	 for (int i = 1; i < word_count; i++) {
		 size_t length = strlen(words[i]);

		 if (length < min_length) {
			 min_length = length;
			 *min_index = i;
		 }

		 if (length > max_length) {
			 max_length = length;
			 *max_index = i;
		 }
	 }
 }

 void swap_min_max_words(char words[50][100], int word_count) {
	 int min_index, max_index;
	 find_min_max_word_indexes(words, word_count, &min_index, &max_index);

	 if (min_index != -1 && max_index != -1) {
		 char temp[100];
		 strcpy(temp, words[min_index]);
		 strcpy(words[min_index], words[max_index]);
		 strcpy(words[max_index], temp);
	 }
 }

 void write_words_to_file(FILE* file, char words[50][100], int word_count) {
	 for (int i = 0; i < word_count; i++) {
		 fprintf(file, "%s ", words[i]);
	 }
 }

 int read_words(FILE* file, char words[50][100]) {
	 int count = 0;
	 while (count < 50 && fscanf(file, "%49s", words[count]) == 1) {
		 count++;
	 }
	 return count;
 }



int main(int argc, char** argv) {
	setlocale(LC_ALL, "rus");
	FILE* fp = NULL;
	char* file = argv[1];
	int n, count=0;


	printf("\033[35mÂûáåðèòå çàäàíèå äëÿ âûïîëíèÿ\033[0m:\n\033[36m1\033[0m - Çàïîëíèòü ôàéë ñëîâàìè è âûâåñòè íà ýêðàí.\n\033[36m2\033[0m - Ðàñïå÷àòàòü âòîðîå è ïðåäïîñëåäíåå ñëîâà.\n\033[36m3\033[0m - Ïîìåíÿòü ìåñòàìè ñàìîå äëèííîå ñëîâî è ñàìîå êîðîòêîå.\n\033[0mÂàø âûáîð: ");

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

                fp = fopen(file, "r");
                verification_file(fp);
                int word_count = read_words(fp, words);
                my_fclose(fp);

                if (word_count == 0) {
            	printf("Файл пуст или не содержит слов.\n");
             	return 1;
}
                swap_min_max_words(words, word_count);

                FILE* output_file = fopen("output.txt", "w");
                verification_file(output_file);

                write_words_to_file(output_file, words, word_count);
                my_fclose(output_file);

                output_file = fopen("output.txt", "r");
                verification_file(output_file);
                reading_file(output_file);
                my_fclose(output_file);


		break;
	}

	return 0;
}
