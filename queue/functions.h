#pragma once


typedef struct {
	int* element;
	int max_element;
	int size;
	int head;
	int tail;
}Queue;



void checking_input();
Queue* create_queue(int max_element);
int empty_queue(Queue* queue);
int full_queue(Queue* queue);
void enqueue(Queue* queue, int num);
int dequeue(Queue* queue);
void queue_contents(Queue* queue);
void delete_item_matches();


void endec(Queue* dec, int num);
int de_dec(Queue* dec);
void dec_contents(Queue* dec);
void mode_deleting_element_different(Queue* dec);
void delete_item_different();


int comparison(Queue* queue1, Queue* queue2);
void equality_queues();

