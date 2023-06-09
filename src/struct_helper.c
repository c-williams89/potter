#include "../include/potter.h"

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
		exit(1);
	}
	stu_list->stu_time = calloc(stu_list->capacity, sizeof(int));
	if (!stu_list->stu_time) {
		printf("Error allocating stu_time array of size 1\n");
		exit(1);
	}
	return stu_list;
}

void create_student(student * stu_list, char *curr_input)
{
	// char delim[] = "1234567890";
	/*
	   Uses a pointer to the space when searching from end of string to isolate
	   digits for stu_time.
	 */
	char *ptr;
	char *space_loc = strrchr(curr_input, ' ');
	if (!space_loc) {
		printf
		    ("Invalid format for student information. Please try again.\n");
		return;
	}
	space_loc++;
	int time_to_finsh = strtol(space_loc, &ptr, 10);

	if ((strncmp(space_loc, ptr, strlen(space_loc)) == 0)
	    || strlen(ptr) > 1) {
		printf
		    ("Invalid format for student information. Please try again.\n");
		return;
	}
	stu_list->stu_time[stu_list->size] = time_to_finsh;
	/*
	   Use strcspn to find bytes before digit. Use that value to copy that 
	   number of bytes to stu_name.
	 */

	int name_size = strcspn(curr_input, space_loc);
	int space_to_remove = 0;
	for (int i = (name_size - 1); i > 0; --i) {
		if (curr_input[i] == ' ') {
			space_to_remove++;
		} else {
			break;
		}
	}
	curr_input[name_size - space_to_remove] = '\0';
	stu_list->stu_name[stu_list->size] =
	    calloc(name_size + 1, strlen(curr_input + 1));
	if (!stu_list->stu_name[stu_list->size]) {
		printf("Error allocating %d bytes for student name.\n",
		       name_size);
		exit(1);
	}
	strncpy(stu_list->stu_name[stu_list->size], curr_input, name_size);
	stu_list->size++;
}

void reallocate_stu_list(student * stu_list, int new_size, bool from_user)
{
	int next_size = stu_list->capacity * 2;
	if (from_user) {
		char **tmp_name =
		    realloc(stu_list->stu_name, next_size * PTR_SIZE);
		int *tmp_time =
		    realloc(stu_list->stu_time, next_size * PTR_SIZE);
		if (!tmp_name || !tmp_name) {
			printf
			    ("Error reallocating stu_list array to size %d.\n",
			     next_size);
			exit(1);
		}
		stu_list->stu_name = tmp_name;
		stu_list->stu_time = tmp_time;
		stu_list->capacity *= 2;
	} else {
		char **tmp_name =
		    realloc(stu_list->stu_name, new_size * PTR_SIZE);
		int *tmp_time =
		    realloc(stu_list->stu_time, new_size * PTR_SIZE);
		if (!tmp_name || !tmp_name) {
			printf
			    ("Error reallocating stu_list array to size %d.\n",
			     new_size);
			exit(1);
		}
		stu_list->stu_name = tmp_name;
		stu_list->stu_time = tmp_time;
		stu_list->capacity = new_size;
	}
}
