#include "../include/potter.h"

long get_num_entries(char *file)
{
	long entries = 0;
	char *curr_line = NULL;
	size_t len = 0;

	FILE *fp = fopen(file, "r");
	if (!fp) {
		printf("Unable to open file: '%s'\n", file);
		exit(1);
	}
	while (getline(&curr_line, &len, fp) != -1) {
		++entries;
	}
	free(curr_line);
	fclose(fp);
	return entries;
}

student *get_user_input(student * stu_list)
{
	while (true) {
		char user_input[MAX_INPUT_SIZE];
		printf
		    ("Please enter a student and their time to finish the project using the 'name time' format. Press 'Q' to quit. ==> ");
		fgets(user_input, MAX_INPUT_SIZE, stdin);
		__fpurge(stdin);
		if (strncmp(user_input, "Q", strlen(user_input) - 1) == 0) {
			system("clear");
			break;
		}
		if (stu_list->size == stu_list->capacity) {
			reallocate_stu_list(stu_list, stu_list->size, true);
		}
		create_student(stu_list, user_input);
	}
	return stu_list;
}
