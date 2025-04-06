#include <stdio.h>
#include <locale.h>
#include <stdlib.h>



typedef struct {
	int* element;
	int top;
	int max_element;
}stack;


void checking_input()
{
	printf("\033[91mОшибка: введено некорректное значение!\033[0m\nПовторите попытку: ");
	rewind(stdin);
}



stack* create_stack(int max_element) {
	stack* Stack = malloc(sizeof(stack));
	if (!Stack)
	{
		printf("Ошибка выделения памяти.\n");
		exit(1);
	}

	Stack->top = -1;
	Stack->max_element = max_element;
	Stack->element = malloc(Stack->max_element * sizeof(int));
	if(!Stack->element)
	{
		printf("Ошибка выделения памяти.\n");
		exit(1);
	}

	return Stack;
}



int empty_stack(stack* Stack) {
	return(Stack->top == -1);
}



int full_stack(stack* Stack) {
	return(Stack->top == Stack->max_element - 1);
}



void push(stack* Stack, int num) {
	if (full_stack(Stack)) 
	{
		printf("Ошибка!Стек полный\n");
		return;
	}

	Stack->element[++(Stack->top)] = num;
}



int pop(stack* Stack) {
	if (empty_stack(Stack)) 
	{
		printf("Стек пуст извлечь элементы нельзя.\n");
		return -1;
	}
	return Stack->element[Stack->top--];
}



int peek(stack* Stack) {
	if (empty_stack(Stack)) 
	{
		printf("Ошибка стек пустой.\n");
		return -1;
	}
	return Stack->element[Stack->top];
}



stack* transfer(stack* Stack1,stack* Stack2)
{
	stack* temp = create_stack(Stack1->max_element + Stack2->max_element);

	
	while (!empty_stack(Stack1) && !empty_stack(Stack2)) 
	{
		if (peek(Stack1) <= peek(Stack2))
		{
			push(temp, pop(Stack2));
		}
		else {
			push(temp, pop(Stack1));
		}
	}

	
	while (!empty_stack(Stack1))
	{
		push(temp, pop(Stack1));
	}


	while (!empty_stack(Stack2)) 
	{
		push(temp, pop(Stack2));
	}


	/*while (!empty_stack(temp)) 
	{
		push(Stack3, pop(temp));
	}*/
	return temp;

}


int input_inum(short* found) {
	int num;
	char input[30]; 

	printf("Введите целое число (или пробел для завершения): ");
	fgets(input, sizeof(input), stdin); 

	if (input[0] == '\n') { 
		*found = 0; 
		return 0;
	}

	if (sscanf_s(input, "%d", &num) == 1) { 
		*found = 1; 
		return num;
	}
	else {
		*found = -1;
		printf("Ошибка: Введено некорректное значение.\n");
		return 0;
	}
}



void identical_elements(stack*Stack1,stack* Stack2) {
	int count=-1;
	if (empty_stack(Stack1) || empty_stack(Stack2)) 
	{
		printf("Один или оба стека пусты.Нет элементов для сравнения.\n");
		return;
	}

	int* temp = malloc(Stack1->top + 1 * sizeof(int));

	if (temp == NULL)
	{
		printf("Ошибка выделения памяти.\n");
		return;
	}

	printf("\033[36mЭлементы которые есть во втором стеке.\033[0m\n");

	while (!empty_stack(Stack1))
	{

		int element = pop(Stack1);
		temp[count++] = element;


		stack* Stack_copy2 = create_stack(Stack2->max_element);

		for (int i = 0;i <= Stack2->top;i++)
		{
			push(Stack_copy2, Stack2->element[i]);
		}

		int found = -1;

		while (!empty_stack(Stack_copy2))
		{
			if (pop(Stack_copy2) == element)
			{
				found = 0;
				break;
			}
		}


		if (found == 0) 
		{
			printf("%d ", element);
		}
	}

	printf("\n");
	free(Stack2->element);
	free(Stack2);


	for (int i = count; i >= 0; i--) 
	{
		push(Stack1, temp[i]);
	}

	free(temp);
	
}






void finding_identical_elements() {
	int max_element1, max_element2, element;

	printf("\033[35mВведите максимальный размер первого стека.\033[0m\n");

	while (scanf_s("%d", &max_element1) != 1 || getchar() != '\n')
	{
		checking_input();
	}

	stack* Stack1 = create_stack(max_element1);

	printf("\033[95mВведите элементы первого стека.\033[0m\n");
	for (int i = 0;i < max_element1;i++)
	{
		while (scanf_s("%d", &element) != 1 || getchar() != '\n')
		{
			checking_input();
		}
		push(Stack1, element);
	}


	printf("\033[35mВведите максимальный размер второго стека.\033[0m\n");

	while (scanf_s("%d", &max_element2) != 1 || getchar() != '\n') 
	{
		checking_input();
	}

	stack* Stack2 = create_stack(max_element2);


	printf("\033[95mВведите элементы второго стека.\033[0m\n");
	for (int i = 0;i < max_element2;i++)
	{
		while (scanf_s("%d", &element) != 1 || getchar() != '\n')
		{
			checking_input();
		}
		push(Stack2, element);
	}


	identical_elements(Stack1,Stack2);

	free(Stack1->element);
	free(Stack1);
	free(Stack2->element);
	free(Stack2);
	

}




void form_ascending_stack() {
	int max_element1, max_element2;

	printf("\033[35mВведите максимальный размер первого стека.\033[0m\n");

	while (scanf_s("%d", &max_element1) != 1 || getchar() != '\n')
	{
		checking_input();
	}

	stack* Stack1 = create_stack(max_element1);

	printf("\033[95mВведите элементы первого стека.\033[0m\n");
	for (int i = 0;i < max_element1;)
	{
		if (Stack1->top == -1) 
		{
			short found = 1;
			int num = input_inum(&found);
			printf("\n");
			if (!found) break;
			push(Stack1, num);
			if (found < 0) break;
			i++;
		}
		else {
			short found = 1;
			int num = input_inum(&found);
			if (num >= Stack1->element[Stack1->top] || found == 0 || found < 0) 
			{
				printf("\n");
				if (!found) break;
				push(Stack1, num);
				if (found < 0) break;
				i++;

			}
			else
				printf("\033[91mВведите число больше передущего.\033[0m\n");
		}
	}

	system("cls");


	printf("\033[35mВведите максимальный размер второго стека.\033[0m\n");

	while (scanf_s("%d", &max_element2) != 1 || getchar() != '\n')
	{
		checking_input();
	}

	stack* Stack2 = create_stack(max_element2);


	printf("\033[95mВведите элементы второго стека.\033[0m\n");
	for (int i = 0;i < max_element2;)
	{
		if (Stack2->top == -1)
		{
			short found = 1;
			int num = input_inum(&found);
			printf("\n");
			if (!found) break;
			push(Stack2, num);
			if (found < 0) break;
			i++;
		}
		else {
			short found = 1;
			int num = input_inum(&found);
			if (num >= Stack2->element[Stack2->top] || found == 0 || found < 0)
			{
				printf("\n");
				if (!found) break;
				push(Stack2, num);
				if (found < 0) break;
				i++;

			}
			else
				printf("\033[91mВведите число больше передущего.\033[0m\n");
		}

	}

	system("cls");
	

	stack* Stack3 = create_stack(Stack1->max_element + Stack2->max_element);

	Stack3 = transfer(Stack1, Stack2);

	printf("\033[95mСодержимое стека номер 3 (по возрастанию):\033[0m\n");
	while (!empty_stack(Stack3))
	{
		printf("%d ", pop(Stack3));
	}

	printf("\n");
}