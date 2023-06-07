#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define INPUT_FILE "data/Pottery.txt"


typedef struct student {
        char *stu_name;
        int stu_time;
} student;

long get_num_entries (const char file[]) {
        long entries = 0;
        char *curr_line;
        size_t len = 0;

        FILE *fp = fopen(INPUT_FILE, "r");
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

void create_student (student *stu_list, int i, char *curr_line) {
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
                printf("Error allocating %d bytes for student name.\n", name_size);
                exit(1);
        }
        strncpy(stu_list[i].stu_name, curr_line, name_size);
}

int main (void) {
        // const char file[] = INPUT_FILE;
        long entries = get_num_entries(INPUT_FILE);

        struct student *stu_list = malloc(entries * sizeof(student));
        if (!stu_list) {
                printf("Error allocating %ld elements for stu_list\n", entries);
                exit(1);
        }

        char *curr_line;
        size_t len = 0;
        FILE *fp = fopen(INPUT_FILE, "r");

        if (!fp) {
                perror("Could not open file: Pottery.txt\n");
        }

        for (int i = 0; i < entries; ++i) {
                getline(&curr_line, &len, fp);
                create_student(stu_list, i, curr_line);
                printf("Student Name: %s\n", stu_list[i].stu_name);
                printf("Student Time: %d\n", stu_list[i].stu_time);
        }
        fclose(fp);
}