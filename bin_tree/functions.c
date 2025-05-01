#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct Node {
	int element;
	struct Node* left;
	struct Node* right;
	int count;
	int value;
}Node;



void checking_input()
{
	printf("\033[91mОшибка: введено некорректное значение!\033[0m\nПовторите попытку: ");
	rewind(stdin);
}



Node* create_node(int element) {
	Node* node = malloc(sizeof(Node));
	if (!node)
	{
		printf("Ошибка выделения памяти.\n");
		exit(1);
	}

	node->element = element;

	node->left = node->right = NULL;

	return node;
}



void finding_node(Node* root,Node* current,int* max_element) {
	if (root == NULL) 
	{
		return root;
	}

	finding_node(root->left, current, max_element);

	if(root->element==current->value)
	{
		current->count++;
	}
	else {

		if (current->count > *max_element)
		{
			*max_element = current->count;
        }

		current->value = root->element;
		current->count = 1;
	}


	return finding_node(root->right,current,max_element);
}


Node* insertion_node(Node* root, int element) {
	if (root == NULL)
	{
		return create_node(element);
	}


	if (element<root->element) {
		root->left = insertion_node(root->left, element);
	}
	else {
		root->right = insertion_node(root->right, element);
	}

	return root;
}




void printf_tree(Node* root, int interval) {
	if (root == NULL) 
	{
		return;
	}

	interval += 5;

	printf_tree(root->right, interval);

	printf("\n");
	for (int i = 5; i < interval; i++) 
		printf(" ");
	printf("%d", root->element);

	printf("\n");


	printf_tree(root->left, interval);
}



Node* min_node(Node* node) {
	Node* min = node;
	while (min && min->left!=NULL)
	{
		min = min->left;
	}

	return min;
}



Node* delete_node(Node* root, int element) {
	if (root == NULL) 
	{
		return root;
	}

	if (element < root->element)
	{
		root->left = delete_node(root->left, element);
	}
	else if (element > root->element)
	{
		root->right = delete_node(root->right, element);
	}
	else {

		if (root->left = NULL)
		{
			Node* temp = root->right;
			free(root);

			return temp;
		}

		else if (root->right == NULL)
		{
			Node* temp = root->left;
			free(root);

			return temp;
		}

			
		Node* temp = min_node(root->right);

		root->element = temp->element;

		root->right = delete_node(root->right, temp->element);

		return root;
			
		
	}
	return root;
}



Node* create_binary_tree() {
	Node* root = NULL;
	int data;

	printf("\033[95mВведите значения для узлов дерева (введите 1000 для завершения):\033[0m\n");
	while (1) 
	{
		printf("\033[35mВведите значение узла: \033[0m");
		if (scanf_s("%d", &data) != 1) 
		{
			printf("\033[91mНекорректный ввод. Пожалуйста, введите целое число.\033[0m\n");
			while (getchar() != '\n'); 
			continue;
		}

		if (data == 1000) 
		{
			break;
		}

		root = insertion_node(root, data);
	}

	return root;
}



void arbitrary_bin_tree() {
	Node* root = create_binary_tree();
	printf("\n\033[33mСозданное бинарное дерево\033[0m\n");
	printf_tree(root, 0);
}



void delete_element_bin_tree() {
	Node* root = create_binary_tree();
	printf("\n\033[33mСозданное бинарное дерево\033[0m\n");
	printf_tree(root, 0);

	printf("\n\033[95mВведите значение узла, который хотите удалить: \033[0m");

	int deleteValue;
	if (scanf_s("%d", &deleteValue) == 1)
	{
		root = delete_node(root, deleteValue);
		
		printf("\n\033[95mДерево после удаления:\033[0m\n");
		printf_tree(root,0);
	}
	else {
		printf("Некорректный ввод.\n");
		while (getchar() != '\n');
	}
}



int max_count(Node* root) {
	if (root == NULL) {
		return 0;
	}

	Node current;
	current.value = INT_MIN; 
	current.count = 0;

	int maxCount = 0;
	finding_node(root, &current, &maxCount);

	
	if (current.count > maxCount) {
		maxCount = current.count;
	}

	return maxCount;
}




void similar_element() {
	
	Node* root = create_binary_tree();
	printf("\n\033[33mСозданное бинарное дерево\033[0m\n");
	printf_tree(root, 0);

	int maxCount = max_count(root);

	printf("\033[33mМаксимальное количество одинаковых элементов: %d\n\033[0m", maxCount);
}