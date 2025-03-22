#include <stdio.h>
#include <locale.h>
#include <stdlib.h>



struct {
	unsigned int divisions : 1;
}remainder;


struct figure {
	int perimeter;
	char colour[25];
};



typedef struct {
	int square;
	char* title;
	struct figure* name;
}GeometricFigure;



void checking_input()
{
	printf("\033[91mОшибка: введено некорректное значение!\033[0m\nПовторите попытку: ");
	rewind(stdin);
}



char my_strcpy(char* str, const char* stc) {

	if (str == NULL || stc == NULL) 
	{
		return NULL;
	}

	char* original_str = str;

	while (*stc != '\0') 
	{
		*str = *stc;
		str++;
		stc++;
	}

	*str = '\0';
	return original_str;
}



int my_len(char* a) {

	int leng = 0;
	while (a[leng] != '\0') {
		leng ++;
	}

	return leng;
}



int my_strcspn(const char* str1, const char* str2) {
	int amount = 0;
	while (str1[amount] != '\0') {
		for (int j = 0; str2[j] != '\0'; j++) {
			if (str1[amount] == str2[j]) {
				return amount;
			}
		}
		amount++;
	}
	return amount;
}



int my_strcmp(const char* a, const char* b) {
	if (a == NULL || b == NULL) return -1; 

	while (*a && (*a == *b)) {
		a++;
		b++;
	}

	return *(unsigned char*)a - *(unsigned char*)b;
}




int my_isdigit(char a) {
	return (a >= '0' && a <='9');
}



int my_isalpha(char a) {
	return(a >= 'A' && a <= 'Z' || a >= 'a' && a <= 'z');
}



char* memory_allocation() {
	char* str;
	int size = 10;
	int len = 0;
	str = malloc(size * sizeof(char));
	if (str == NULL) {
		exit(1);
	}
	char ch;

	while ((ch = getchar()) != '\n' && ch != EOF) 
	{
		if (len == size - 1) 
		{
			size += 2;
			str = realloc(str, size * sizeof(char));

			if (str == NULL) {
				exit(1);
			}
		}
		str[len++] = ch;

	}
	if (len == 0) {
		free(str);
	}
	str[len] = '\0';
	return str;
}



int words() {
	
	int number;
	while (scanf_s("%d", &number) != 1) 
	{
		printf("Ошибка не натуральное число: ");
		rewind(stdin);

	}

	return number;
}





int digit( char str[]) {
	
	for (int i = 0;i < str[i];i++)
	{
		if (!my_isalpha(str[i]))
		{
			
			return 0;
		}
		
	}
	return 1;
}



void information_figure(GeometricFigure* unique) {
	char buffer[100];
	char a;

	unique->name = (struct figure*)malloc(sizeof(struct figure));
	if (unique->name == NULL) {
		perror("Ошибка выделения памяти");
		return;
	}

	printf("\033[35mВведите площадь:\033[0m ");
	unique->square = words();

	while (getchar() != '\n');

	printf("\033[35mВведите название фигуры:\033[0m ");
	
	fgets(buffer, sizeof(buffer), stdin);
	buffer[my_strcspn(buffer, "\n")] = '\0';
		
	
	unique->title = (char*)malloc(my_len(buffer) + 1);

	my_strcpy(unique->title, buffer);
	
	printf("\033[35mВведите периметр: \033[0m");
	unique->name->perimeter = words();

	while (getchar() != '\n');

	printf("\033[35mВведите цвет: \033[0m");
	fgets(unique->name->colour, sizeof(unique->name->colour), stdin);
	unique->name->colour[my_strcspn(unique->name->colour, "\n")] = '\0';

	
}



int task_selection() {
	int number;
	printf("\033[35mВыберите задание для выполния\033[0m:\n\033[36m1\033[0m - Найти и вывести остаток от деления целого числа на 2.\n\033[36m2\033[0m - Работа с геометрическими фигурами.\n\033[0mВаш выбор: ");

	while (scanf_s("%d", &number) != 1 || number < 1 || number > 2 || getchar() != '\n')
	{
		checking_input();
	}
	return number;
}



void finding_remainder_divisions_2() {
	int num;

	printf("\n\033[35mВведите число: \033[0m");
	while (scanf_s("%d", &num) != 1 || getchar() != '\n') 
	{
		checking_input();
	}

	remainder.divisions = num & 1; 
	printf("\n\033[95mОстаток от деления %d на 2 равен:\033[0m %d\n", num, remainder.divisions);
}




void output_screen(GeometricFigure* unique) {
	
	printf("Square: %d\n", unique->square);
	printf("Title: %s\n", unique->title);
	printf("Perimeter: %d\n", unique->name->perimeter);
	printf("Colour: %s\n", unique->name->colour);
	
	
}




void menu() {

	printf("\033[35mМеню: \033[0m\n");
	printf("\033[36m1\033[0m - Вывести геометрические фигуры.\n");
	printf("\033[0m\033[36m2\033[0m - Найти фигуры с площадью, меньше заданной.\n\033[36m3\033[0m - Удалить фигуры с заданным названием.\n");
	printf("\033[36m4\033[0m - Добавить геометрические фигуры.\n");
	printf("\033[36m5\033[0m - Выход.\n");
	printf("Ваш выбор: ");
}


void delete_figure_title(GeometricFigure* unique, char* delete_figure, int* count) {
	int delete_count=0;

	for (int i = 0;i < *count; )
	{
		
		if (unique[i].title && my_strcmp(unique[i].title, delete_figure) == 0)
		{
			free(unique[i].title);
			free(unique[i].name);

			for (int j = i;j <*count - 1;j++)
			{
				unique[j] = unique[j + 1];
			}


			(*count)--;
			delete_count++;

			unique = (GeometricFigure*)realloc(unique, *count * sizeof(GeometricFigure));
			
		}
		else {
			i++;
		}
		
	}

	printf("\033[95mУдалено %d фигур\033[0m\n",delete_count);
}



void finding_min_square(GeometricFigure* unique,int max_square,int* count) {
	int finding=0;

	for (int i = 0;i < *count;i++) 
	{
		if (unique[i].square < max_square) 
		{
			finding++;
			printf("\033[95mФигуры с площадью меньше %d:\033[0m \n", max_square);
			printf("%s c площадью %d\n", unique[i].title, unique[i].square);
		}
	}
	if (finding == 0) 
	{
		printf("Нет фигур с площадью меньше %d\n", max_square);
	}
}





void words_structures() {
	int count=0;
	int number=0;
	int max_square=0;
	char* delete_figure;

	GeometricFigure* unique = malloc(count * sizeof(GeometricFigure));

	do {

		menu();
		while (scanf_s("%d", &number) != 1 || number > 5 || getchar() != '\n') 
		{
			checking_input();
		}

		if (number < 4 && count == 0)
		{
				printf("Недостаточно геометрических фигур.Выберите действие 4 или 5.\n");
				number = 0;
		}

		switch (number)
		{
		case 1:
			for (int i = 0;i < count;i++) 
			{
				printf("\033[35mДанные о геметрической фигуре %d :\033[0m\n", i + 1);
				output_screen(&unique[i]);
			}

			break;

		case 2:
			printf("\033[35mВведите площадь фигуры:\033[0m ");
			max_square = words();

			finding_min_square(unique,max_square,&count);

			break;

		case 3:
			printf("Введите название фигуры\n");
			delete_figure = memory_allocation();

			if (delete_figure != NULL) 
			{
				delete_figure_title(unique, delete_figure, &count);
				free(delete_figure);
			}
			else {
				printf("Ошибка при вводе названия фигуры.\n");
			}
			

			break;

		case 4:
			count += 1;
			

			unique = (GeometricFigure*)realloc(unique, count * sizeof(GeometricFigure));
			information_figure(&unique[count - 1]);
			system("cls");

			break;

		case 5:
			exit(0);
			break;
		}
	} while (1);

}