#pragma once

typedef struct Node {
	int element;
	struct Node* left;
	struct Node* right;
}Node;


void checking_input();
Node* create_node(int element);
void finding_node(Node* root, Node* current, int* max_element);
Node* insertion_node(Node* root, int element);
void printf_tree(Node* root, int interval);
Node* min_node(Node* root);
Node* create_binary_tree();
void arbitrary_bin_tree();
Node* delete_node(Node* root, int element);
void delete_element_bin_tree();
int max_count(Node* root);
void similar_element();