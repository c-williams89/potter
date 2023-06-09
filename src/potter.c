#include "../include/potter.h"

int main(int argc, char *argv[])
{
	char *file;
	student *stu_list = create_struct();

	if (argc == 1) {
		printf("Names must be entered at the command line.\n\n");
		stu_list = get_user_input(stu_list);
	} else {
		file = argv[1];
		long entries = get_num_entries(file);
		reallocate_stu_list(stu_list, (int)entries, false);
		FILE *fp = fopen(file, "r");
		if (!fp) {
			printf("Unable to open file: '%s'\n", file);
			exit(1);
		}
		char *curr_entry = NULL;
		size_t len = 0;
		for (int i = 0; i < entries; ++i) {
			getline(&curr_entry, &len, fp);
			create_student(stu_list, curr_entry);
		}
		free(curr_entry);
		fclose(fp);

		if (argc > 2) {
			if (((strncmp(argv[2], "-s", 2) == 0)
			     || strncmp(argv[2], "--start", 7) == 0)
			    && argv[3]) {
				find_stu_index(stu_list, argv[3]);
			} else {
				printf
				    ("Invalid invocation of program options.\n");
				exit(1);
			}
		}
	}

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
	clean(stu_list);
}
