
typedef struct {
	int square;
	char* title;
	struct figure* name;
}GeometricFigure;


void checking_input();
int my_strcpy(char* str, char* stc);
int my_len(char* a);
int my_strcspn(const char* str1, const char* str2);
int my_strcmp(const char* a, const char* b);
int my_isdigit(char a);
int my_isalpha(char a);

char* memory_allocation();
int words();
int digit(char str[]);
int task_selection();
void finding_remainder_divisions_2();
void output_screen(GeometricFigure* unique);

void menu();
void words_structures();
void finding_min_square(GeometricFigure* unique, int max_square, int* count);
void information_figure(GeometricFigure* unique);
void delete_figure_title(GeometricFigure* unique, char* delete_figure, int* count);