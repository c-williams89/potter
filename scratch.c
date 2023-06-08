#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum { PTR_SIZE = 8 };
typedef struct student {
	int size;
	int capacity;
	char **stu_name;
	int *stu_time;
} student;

// void clean();

student *create_struct()
{
	student *stu_list = malloc(sizeof(*stu_list));
	if (!stu_list) {
		printf("Error creating stu_list\n");
		exit(1);
	}
	stu_list->capacity = 1;
	stu_list->size = 0;
	stu_list->stu_name = malloc(stu_list->capacity * PTR_SIZE);
	if (!stu_list->stu_name) {
		printf("Error allocating stu_name array of size 1\n");
		// clean();
		exit(1);
	}
	stu_list->stu_time = calloc(stu_list->capacity, sizeof(int));
	// stu_list->stu_time = malloc(stu_list->capacity * sizeof(int));
	if (!stu_list->stu_time) {
		printf("Error allocating stu_time array of size 1\n");
		// clean();
		exit(1);
	}
	return stu_list;
}

void reallocate_stu_list(student * stu_list)
{
	printf("Reallocating array.\n");
	int next_size = stu_list->capacity * 2;
	char **tmp_name = realloc(stu_list->stu_name, next_size * PTR_SIZE);
	if (!tmp_name) {
		printf("Error reallocating stu_name array to size %d.\n",
		       next_size);
		exit(1);
	}

	int *tmp_time = realloc(stu_list->stu_time, next_size * PTR_SIZE);
	if (!tmp_time) {
		printf("Error allocating stu_time array of size %d.\n",
		       next_size);
		exit(1);
	}
	stu_list->stu_name = tmp_name;
	stu_list->stu_time = tmp_time;
	stu_list->capacity *= 2;
}

void create_student(student * stu_list, char *curr_input)
{
	char delim[] = "1234567890";
	/*
	   Uses a pointer to the space when searching from end of string to isolate
	   digits for stu_time.
	 */
	char *ptr;
	char *space_loc = strrchr(curr_input, ' ');
	space_loc++;
	stu_list->stu_time[stu_list->size] = strtol(space_loc, &ptr, 10);

	/*
	   Use strcspn to find bytes before digit. Use that value to copy that 
	   number of bytes to stu_name.
	 */
	int name_size = strcspn(curr_input, delim);
	stu_list->stu_name[stu_list->size] = malloc(name_size);
	if (!stu_list->stu_name[stu_list->size]) {
		printf("Error allocating %d bytes for student name.\n",
		       name_size);
		exit(1);
	}
	strncpy(stu_list->stu_name[stu_list->size], curr_input, name_size);
}

student *get_user_input(student * stu_list)
{
	char *user_input;
	while (true) {
		printf
		    ("Please enter a student and their time to finish the project. Press 'Q' to quit. ==> ");
		fgets(user_input, 20, stdin);
		__fpurge(stdin);
		if (strncmp(user_input, "Q", strlen(user_input) - 1) == 0) {
			break;
		}
		if (stu_list->size == stu_list->capacity) {
			reallocate_stu_list(stu_list);
		}
		printf("Did we get here?");
		create_student(stu_list, user_input);
		stu_list->size++;
	}
	return stu_list;
}

int grade_and_print(student * stu_list, int entries, int i, bool ready_to_print)
{
	int num_failed = 0;
	if (ready_to_print) {
		printf("%s\n\n", stu_list->stu_name[i]);
	}

	if (i > 0) {
		for (int j = i, k = 0; j < entries; ++j, ++k) {
                        if (stu_list->stu_time[j] > k * 5) {
				(ready_to_print) ? printf("%s\n", stu_list->stu_name[j])
				    : ++num_failed;
			}
		}
		for (int j = 0; j < i; ++j) {
			if (stu_list->stu_time[j] > (stu_list->size - i + j) * 5) {
				(ready_to_print) ? printf("%s\n", stu_list->stu_name[j])
				    : ++num_failed;
			}
		}
	} else {
		for (int j = 0; j < entries; ++j) {
                        if (stu_list->stu_time[j] > j * 5) {
				(ready_to_print) ? printf("%s\n", stu_list->stu_name[j])
				    : ++num_failed;
			}
		}
	}
	return num_failed;
}

int main(int argc, char *argv[])
{
	const char *file;
	student *stu_list = create_struct();

	if (argc == 1) {
		printf("Names must be entered at the command line.\n\n");
		stu_list = get_user_input(stu_list);
	} else if (argc == 2) {
		file = argv[1];
	}

	printf("Total entries: %d\n", stu_list->size);
	bool ready_to_print = false;
	int max_failed = 0, num_failed = 0, max_failed_idx = 0;

	for (int i = 0; i < stu_list->size; ++i) {
		num_failed =
		    grade_and_print(stu_list, stu_list->size, i,
				    ready_to_print);
		if (num_failed > max_failed) {
			max_failed = num_failed;
			max_failed_idx = i;
		}
	}
	ready_to_print = true;
	grade_and_print(stu_list, stu_list->size, max_failed_idx,
			ready_to_print);

}
