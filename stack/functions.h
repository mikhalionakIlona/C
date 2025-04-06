
typedef struct {
	int* element;
	int top;
	int max_element;
}stack;


void checking_input();
stack* create_stack(int max_element);
int empty_stack(stack* Stack);
int full_stack(stack* Stack);
void push(stack* Stack, int element);
void finding_identical_elements();
void identical_elements(stack* Stack1, stack* Stack2);
int pop(stack* Stack);


void transfer(stack* Stack1, stack* Stack2);
int input_inum(short* found);
void form_ascending_stack();