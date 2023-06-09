#ifndef POTTER_H
	#define POTTER_H
		#define _GNU_SOURCE
		#include <stdio.h>
		#include <stdio_ext.h>
		#include <stdlib.h>
		#include <stdbool.h>
		#include <string.h>
		#include <ctype.h>

		enum { PTR_SIZE = 8, MAX_INPUT_SIZE = 35 };

		typedef struct student{
			int size;
			int capacity;
			char **stu_name;
			int *stu_time;
		} student;
		#include "struct_helper.h"
		#include "io_helper.h"
		#include "clean.h"
		#include "grade_and_print.h"
		#include "find_stu_index.h"

#endif



