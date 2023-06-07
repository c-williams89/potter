#include <stdlib.h>

typedef struct student {
        char *stu_name;
        int stu_time;
} student;

int main (void) {
        struct student *stu_list = malloc(sizeof(*stu_list));
}