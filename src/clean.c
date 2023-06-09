#include "../include/potter.h"

void clean(student * stu_list)
{
	for (int i = 0; i < stu_list->capacity; ++i) {
		free(stu_list->stu_name[i]);
	}
	free(stu_list->stu_name);
	free(stu_list->stu_time);
	free(stu_list);
}
