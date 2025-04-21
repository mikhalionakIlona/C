#include <stdio.h>
#include <locale.h>
#include <stdlib.h>



typedef struct {
	int* element;
	int max_element;
	int size;
	int head;
	int tail;
}Queue;



void checking_input()
{
	printf("\033[91mОшибка: введено некорректное значение!\033[0m\nПовторите попытку: ");
	rewind(stdin);
}



Queue* create_queue(int max_element) {
	Queue* queue = malloc(sizeof(Queue));
	if (!queue)
	{
		printf("Ошибка выделения памяти.\n");
		exit(1);
	}


	queue->head = 0;
	queue->size = 0;
	queue->tail = 0;
	queue->max_element = max_element;

	queue->element = malloc(queue->max_element * sizeof(int));
	if (!queue->element)
	{
		printf("Ошибка выделения памяти.\n");
		exit(1);
	}


	return queue;
}



int empty_queue(Queue* queue) {
	return(queue->size == 0);
}



int full_queue(Queue* queue) {
	return(queue->size==queue->max_element);
}



void enqueue(Queue* queue,int num) {
	if (full_queue(queue)) 
	{
		printf("\033[91mОчередь полна.Добавить элемент нельзя.\033[0m");
		exit(1);
	}

	queue->element[queue->tail] = num;
	queue->tail = (queue->tail + 1) % queue->max_element;
	queue->size++;
}



int dequeue(Queue* queue) {
	if (empty_queue(queue)) 
	{
		printf("\033[91mОчередь пуста.Удалить элемент нельзя.\033[0m");
		exit(1);
	}

	int value = queue->element[queue->head];
	queue->head = (queue->head + 1) % queue->max_element;
	queue->size--;

	return value;
}




void queue_contents(Queue* queue) {
	if (empty_queue(queue))
	{
		printf("\033[91mОчередь пуста.\033[0m");
		exit(1);
	}
	
	printf("\033[32mСодержимое очереди:\033[0m ");
	int i = queue->head; 
	for (int j = 0; j < queue->size; j++) 
	{
		printf("%d ", queue->element[i]);
		i = (i + 1) % queue->max_element; 
	}
	printf("\n");
}




void mode_deleting_element_matching(Queue* queue) {
	printf("\033[35mВведите число ( 0 для завершения):\033[0m\n");
	int value;

	while (1) 
	{
		if (scanf_s("%d", &value) != 1)
		{
			printf("\033[91mНекорректный ввод.\033[0m\n");
			while (getchar() != '\n');
			continue;
		}

		if (value == 0) 
		{
			break;
		}

		if (!empty_queue(queue)) 
		{
			int num = dequeue(queue);
			if (value == num)
			{
				enqueue(queue, num);
				printf("\033[33mПервый элемент удален и добавлен в конец очереди.\n\033[0m");
			}
			else 
			printf("\033[91mПервый элемент не совпадает с введенным числом.\n\033[0m");
		}
		else {
			printf("\033[91mОчередь пуста.Нет элементов для сравнения.\033[0m\n");
		}

		queue_contents(queue);
	}
	
	printf("\033[95mВыход из интерактивного режима.\033[0m\n");
 }




void delete_item_matches() {
	int max_element;

	printf("\033[95mВведите максимальный размер очереди: \033[0m");
	while (scanf_s("%d", &max_element) != 1 || max_element <=0 || getchar() != '\n')
	{
		checking_input();
	}

	Queue* queue = create_queue(max_element);
	
	
	printf("\033[35mВведите элементы очереди (0 для завершения):\033[0m\n");
	int value;
	while (scanf_s("%d", &value) == 1 && value != 0) 
	{
		enqueue(queue, value);
		if (full_queue(queue)) 
		{
			printf("\033[91mОчередь заполнена. Дальнейший ввод невозможен.\033[0m\n");
			break;
		}
			
	}
	
	queue_contents(queue);
	mode_deleting_element_matching(queue);
	
	free(queue->element);
	free(queue);

}




void endec(Queue* dec, int num) {
	if (full_queue(dec))
	{
		printf("\033[91mДек полный.Добавить элемент нельзя.\033[0m");
		exit(1);
	}

	dec->element[dec->tail] = num;
	dec->tail = (dec->tail + 1) % dec->max_element;
	dec->size++;
}




int de_dec(Queue* dec) {
	if (empty_queue(dec))
	{
		printf("\033[91mДек пустой.Удалить элемент нельзя.\033[0m");
		exit(1);
	}

	int value = dec->element[dec->head];
	dec->head = (dec->head + 1) % dec->max_element;
	dec->size--;

	return value;
}




void dec_contents(Queue* dec) {
	if (empty_queue(dec))
	{
		printf("\033[91mДек пуст.\033[0m");
		exit(1);
	}

	printf("\033[32mСодержимое дека:\033[0m ");
	int i = dec->head;
	for (int j = 0; j < dec->size; j++)
	{
		printf("%d ", dec->element[i]);
		i = (i + 1) % dec->max_element;
	}
	printf("\n");
}





void mode_deleting_element_different(Queue* dec) {
	printf("\033[35mВведите число ( 0 для завершения):\033[0m\n");
	int value;

	while (1)
	{
		if (scanf_s("%d", &value) != 1)
		{
			printf("\033[91mНекорректный ввод.\033[0m\n");
			while (getchar() != '\n');
			continue;
		}

		if (value == 0)
		{
			break;
		}

		if (!empty_queue(dec))
		{
			int num = de_dec(dec);
			if (value != num)
			{
				endec(dec, num);
				printf("\033[33mПервый элемент удален и добавлен cправа.\n\033[0m");
			}
			else
				printf("\033[91mПервый элемент удален.\n\033[0m");
		}
		else {
			
			printf("\033[91mДек пустой.\033[0m\n");
		}

		dec_contents(dec);
	}

	printf("\033[95mВыход из интерактивного режима.\033[0m\n");
}






void delete_item_different() {
	int max_element;

	printf("\033[95mВведите максимальный размер дека: \033[0m");
	while (scanf_s("%d", &max_element) != 1 || max_element <= 0 || getchar() != '\n')
	{
		checking_input();
	}

	Queue* dec = create_queue(max_element);


	printf("\033[35mВведите элементы очереди (0 для завершения):\033[0m\n");
	int value;
	while (scanf_s("%d", &value) == 1 && value != 0)
	{
		endec(dec, value);
		if (full_queue(dec))
		{
			printf("\033[91mОчередь заполнена. Дальнейший ввод невозможен.\033[0m\n");
			break;
		}

	}

	dec_contents(dec);
	mode_deleting_element_different(dec);

	free(dec->element);
	free(dec);

}



int comparison(Queue* queue1,Queue* queue2) {
	if (queue1->size != queue2->size)
	{
		return 0;
	}

	if (queue1->max_element != queue2->max_element)
	{
		return 0;
	}


	int i = queue1->head;
	int j = queue2->head;

	for (int k = 0;k < queue1->size;k++) 
	{
		if (queue1->element[i] != queue2->element[j]) 
		{
			return 0;
        }

		i = (i + 1) % queue1->max_element;
		j = (j + 1) % queue2->max_element;
	}
	return 1;
}




void equality_queues() {
	int max_element1, max_element2;

	printf("\033[95mВведите максимальный размер первой очереди: \033[0m");
	while (scanf_s("%d", &max_element1) != 1 || max_element1 <= 0 || getchar() != '\n')
	{
		checking_input();
	}

	Queue* queue1 = create_queue(max_element1);


	printf("\033[35mВведите элементы  первой очереди ( 0 для завершения):\033[0m\n");
	int value;
	while (scanf_s("%d", &value) == 1 && value != 0)
	{
		enqueue(queue1, value);
		if (full_queue(queue1))
		{
			printf("\033[91mОчередь заполнена. Дальнейший ввод невозможен.\033[0m\n");
			break;
		}

	}

	queue_contents(queue1);

	printf("\033[95mВведите максимальный размер второй очереди: \033[0m");
	while (scanf_s("%d", &max_element2) != 1 || max_element2 <= 0 || getchar() != '\n')
	{
		checking_input();
	}

	Queue* queue2 = create_queue(max_element2);


	printf("\033[35mВведите элементы  второй очереди ( 0 для завершения):\033[0m\n");
	int num;
	while (scanf_s("%d", &num) == 1 && num != 0)
	{
		enqueue(queue2, num);
		if (full_queue(queue2))
		{
			printf("\033[91mОчередь заполнена. Дальнейший ввод невозможен.\033[0m\n");
			break;
		}

	}

	queue_contents(queue2);

	if (comparison(queue1, queue2)) 
	{
		printf("----------------------------------------------------\n");
		printf("\033[95mОчереди равны.\033[0m\n");
		printf("----------------------------------------------------\n");
	}
	else {
		printf("----------------------------------------------------\n");
		printf("\033[95mОчереди не равны.\033[0m\n");
		printf("----------------------------------------------------\n");
	}

	free(queue1->element);
	free(queue1);

	free(queue2->element);
	free(queue2);
}






















































