#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdio_ext.h>

// #define INPUT_FILE "data/Pottery.txt"

typedef struct student {
	char *stu_name;
	int stu_time;
} student;

student *reallocate_stu_list(student * stu_list, long entries)
{
	printf("Inside realloc func");
	student *tmp = realloc(stu_list, 2 * (entries * sizeof(student)));
	if (!tmp) {
		printf("Error allocating %ld elements for stu_list\n", entries);
		exit(1);
	}
	stu_list = tmp;
	return stu_list;
}

long get_num_entries(const char file[], FILE * fp)
{
	long entries = 0;
	char *curr_line;
	size_t len = 0;
	if (!fp) {
		perror("Unable to open file\n");
		exit(1);
	}
	while (getline(&curr_line, &len, fp) != -1) {
		++entries;
	}
	fclose(fp);
	return entries;
}

student *create_student(student * stu_list, int i, char *curr_line)
{
	char delim[] = "1234567890";
	/*
	   Uses a pointer to the space when searching from end of string to isolate
	   digits for stu_time.
	 */
	char *ptr;
	char *space_loc = strrchr(curr_line, ' ');
	space_loc++;
	stu_list[i].stu_time = strtol(space_loc, &ptr, 10);

	/*
	   Use strcspn to find bytes before digit. Use that value to copy that 
	   number of bytes to stu_name.
	 */
	int name_size = strcspn(curr_line, delim);
	stu_list[i].stu_name = malloc(name_size);
	if (!stu_list[i].stu_name) {
		printf("Error allocating %d bytes for student name.\n",
		       name_size);
		exit(1);
	}
	strncpy(stu_list[i].stu_name, curr_line, name_size);
	return stu_list;
}

int grade_and_print(student * stu_list, long entries, int i,
		    bool ready_to_print)
{
	int num_failed = 0;
	if (ready_to_print) {
		printf("%s\n\n", stu_list[i].stu_name);
	}

	if (i > 0) {
		for (int j = i, k = 0; j < entries; ++j, ++k) {
			if (stu_list[j].stu_time > k * 5) {
				(ready_to_print) ? printf("%s\n",
							  stu_list[j].
							  stu_name) :
				    ++num_failed;
			}
		}
		for (int j = 0; j < i; ++j) {
			if (stu_list[j].stu_time > (entries - i + j) * 5) {
				(ready_to_print) ? printf("%s\n",
							  stu_list[j].
							  stu_name) :
				    ++num_failed;
			}
		}
	} else {
		for (int j = 0; j < entries; ++j) {
			if (stu_list[j].stu_time > j * 5) {
				(ready_to_print) ? printf("%s\n",
							  stu_list[j].
							  stu_name) :
				    ++num_failed;
			}
		}
	}
	return num_failed;
}

student *get_user_input(student * stu_list, long *entries)
{
	char *user_input;
	long i = 0;
	while (true) {
		printf
		    ("Please enter a student and their time to finish the project. Press 'Q' to quit. ==> ");
		fgets(user_input, 20, stdin);
		__fpurge(stdin);
		if (strncmp(user_input, "Q", strlen(user_input) - 1) == 0) {
			break;
		}
		++*entries;
		stu_list = create_student(stu_list, i, user_input);
		++i;
	};
	return stu_list;
}

int main(int argc, char *argv[])
{
	const char *file;
	long entries = 0;
	struct student *stu_list = malloc(sizeof(*stu_list));
	if (!stu_list) {
		printf("Error allocating stu_list\n");
		exit(1);
	}

	if (argc == 2) {
		file = argv[1];
		FILE *fp = fopen(file, "r");
		if (!fp) {
			printf
			    ("Invalid file. Names must be entered at the command line.\n");
			stu_list = get_user_input(stu_list, &entries);
		} else {
			entries = get_num_entries(file, fp);
			printf("Entries are %ld\n", entries);
			FILE *fp = fopen(file, "r");
			stu_list = reallocate_stu_list(stu_list, entries);
			char *curr_line;
			size_t len = 0;
			for (int i = 0; i < entries; ++i) {
				getline(&curr_line, &len, fp);
				stu_list =
				    create_student(stu_list, i, curr_line);
			}
			fclose(fp);

		}
	}

	printf("Total entries: %ld\n", entries);
	bool ready_to_print = false;
	int max_failed = 0, num_failed = 0, max_failed_index = 0;

	for (int i = 0; i < entries; ++i) {
		num_failed =
		    grade_and_print(stu_list, entries, i, ready_to_print);
		if (num_failed > max_failed) {
			max_failed = num_failed;
			max_failed_index = i;
		}
	}
	ready_to_print = true;
	grade_and_print(stu_list, entries, max_failed_index, ready_to_print);
}
