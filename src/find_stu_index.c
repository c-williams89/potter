#include "../include/potter.h"

void find_stu_index(student * stu_list, char *person_to_find)
{
	int start_index = 0;
	bool found_successful = false;
	for (int i = 0; i < stu_list->size; ++i) {
		if (strncmp
		    (stu_list->stu_name[i], person_to_find,
		     strlen(stu_list->stu_name[i])) == 0) {
			start_index = i;
			found_successful = true;
		}
	}
	if (found_successful) {
		grade_and_print(stu_list, stu_list->size, start_index, true);
		clean(stu_list);
		exit(1);

	} else {
		printf("Unable to locate student by name: %s\n",
		       person_to_find);
		clean(stu_list);
		exit(1);
	}
}
