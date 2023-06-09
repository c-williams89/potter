#ifndef STRUCT_HELPER_H
	#define STRUCT_HELPER_H
	student *create_struct();
	void create_student(student * stu_list, char *curr_input);
	void reallocate_stu_list(student * stu_list, int new_size, bool from_user);
#endif



