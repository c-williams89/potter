#include "../include/potter.h"

int grade_and_print(student * stu_list, int entries, int i, bool ready_to_print)
{
	int num_failed = 0;
	if (ready_to_print) {
		printf("%s\n\n", stu_list->stu_name[i]);
	}

	if (i > 0) {
		for (int j = i, k = 0; j < entries; ++j, ++k) {
			if (stu_list->stu_time[j] > k * 5) {
				(ready_to_print) ? printf("%s\n",
							  stu_list->stu_name[j])
				    : ++num_failed;
			}
		}
		for (int j = 0; j < i; ++j) {
			if (stu_list->stu_time[j] >
			    (stu_list->size - i + j) * 5) {
				(ready_to_print) ? printf("%s\n",
							  stu_list->stu_name[j])
				    : ++num_failed;
			}
		}
	} else {
		for (int j = 0; j < entries; ++j) {
			if (stu_list->stu_time[j] > j * 5) {
				(ready_to_print) ? printf("%s\n",
							  stu_list->stu_name[j])
				    : ++num_failed;
			}
		}
	}
	return num_failed;
}
