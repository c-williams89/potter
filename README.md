# potter

## Description
`potter` will take a list of students and the time left to complete their pottery
projects, either from a provided file when executing the program, or manually from the user.

It takes 5 minutes to grade each project, so the teacher needs to determine the student to
start grading with that will result in the most amount of failures.

`potter` will then print the student that the teacher should begin with, followed by the
students who will fail.

## Installation
The entire project can be pulled from Git.

Developed with C18 and compiled with gcc-9.

---

### Build
`potter` can easily be built using the make tool.

To build and compile the program:
```sh
<project_root_dir>$ make
```
to create the executable `potter`.

---

### Run
`potter` can be run with none, or two optional arguments.
```sh
<project_root_dir>$ ./potter [file] [option]
```
If [file] is provided, `potter` will look for that file and use the contents to
generate the list of students to iterate over.

if the [option] `-s` is provided, followed by a name, the program will only determine
failing students starting with the provided student. Ex:
```sh
<project_root_dir>$ ./potter data/Pottery.txt -s Herodotus
```
Will result in the output
```sh
Herodotus

Herodotus
Carl    Sagan
Hassan-i Sabbah
```
**NOTE: If the `-s` flag is provided, it must accompany a provided file**
Names passed via `-s` that are space separated must be wrapped in quotes:
```sh
<project_root_dir>$ ./potter data/Pottery.txt -s "Carl Sagan"
```

Running `potter` without any optional arguments will allow the user to manually enter student info at the command line.
```sh
<project_root_dir>$ ./potter 
Names must be entered at the command line.

Please enter a student and their time to finish the project using the 'name time' format. Press 'Q' to quit. ==> 
```
Student info must be entered in the following format `<student_name> <time>` and will not exceed 34 characters.

---

### Debug/Error Checking
To build `potter` with debug flags:
```sh
<project_root_dir>$ make debug
```
to be able to debug with gdb.
```sh
<project_root_dir>$ gdb ./potter [file] [option]
```

To check `potter` against valgrind:
```sh
<project_root_dir>$ make valgrind [file] [option]
```
to build and launch valgrind.

---

### Cleanup
After running the program, execute:
```sh
<project_root_dir>$ make clean
```
to delete object files.

---

## Support
Additional support can be found in the man page:
```sh
<project_rood_dir>$ man ./doc/potter.1
```