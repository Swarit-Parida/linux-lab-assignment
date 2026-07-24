# Question 3 – Secure File Processing Using Linux System Calls

## Command 1 – Create the C Program

Command:
vi employee_records.c

Program content (typed inside vi):

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct Employee {
    int id;
    char name[20];
    float salary;
};

int main() {
    int fd;
    struct Employee emp;

    fd = open("employee.dat", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct Employee employees[] = {
        {101, "Alice", 50000},
        {102, "Bob", 55000},
        {103, "Charlie", 60000}
    };

    write(fd, employees, sizeof(employees));

    emp.id = 102;
    strcpy(emp.name, "Bob");
    emp.salary = 65000;

    lseek(fd, sizeof(struct Employee), SEEK_SET);

    write(fd, &emp, sizeof(emp));

    lseek(fd, 0, SEEK_SET);

    printf("Employee Records:\n\n");

    while(read(fd, &emp, sizeof(emp)) > 0)
    {
        printf("ID: %d\n", emp.id);
        printf("Name: %s\n", emp.name);
        printf("Salary: %.2f\n\n", emp.salary);
    }

    close(fd);

    return 0;
}


Explanation:
Opens vi to write the program. It uses open(), write(), lseek(), 
read(), and close() to create a file, insert fixed-size employee 
records, update one record directly by seeking to its position, and 
read all records back.

---

## Command 2 – Compile the Program

Command:
gcc employee_records.c -o employee_records

Explanation:
Compiles the program into an executable. No errors confirms the code 
is syntactically correct.

---

## Command 3 – Execute the Program

Command:
./employee_records

Output: Employee Records:

        ID: 101
        Name: Alice
        Salary: 50000.00

        ID: 102
        Name: Bob
        Salary: 65000.00

        ID: 103
        Name: Charlie
        Salary: 60000.00


Explanation:
Creates employee.dat, writes 3 records, updates record 2 in place, 
and displays all records showing the update took effect.

---

## Command 4 – Verify the Generated Files

Command:
ls -l

Output: total 28
        -rw-rw-rw-  1 codespace codespace     0 Jul 24 03:42 Explanation.md
        -rw-r--r--  1 codespace codespace    84 Jul 24 05:37 employee.dat
        -rwxrwxrwx  1 codespace codespace 16320 Jul 24 05:37 employee_records
        -rw-rw-rw-  1 codespace codespace   973 Jul 24 05:35 employee_records.c
        drwxrwxrwx+ 2 codespace codespace  4096 Jul 24 03:42 screenshots

Explanation:
Confirms the source file, executable, and employee.dat were all 
created successfully.

---

## Command 5 – Display File Metadata

Command:
stat employee.dat

Output: File: employee.dat
        Size: 84              Blocks: 8          IO Block: 4096   regular file
        Device: 7,4     Inode: 1310834     Links: 1
        Access: (0644/-rw-r--r--)  Uid: ( 1000/codespace)   Gid: ( 1000/codespace)
        Access: 2026-07-24 05:37:16.018710821 +0000
        Modify: 2026-07-24 05:37:16.018710821 +0000
        Change: 2026-07-24 05:37:16.018710821 +0000
        Birth: 2026-07-24 05:37:16.018710821 +0000

Explanation:
Shows size, permissions, and timestamps of employee.dat, confirming 
the file was written to correctly.

---

## Linux System Calls Used

open()
Creates/opens employee.dat and returns a file descriptor used for 
all further operations.

write()
Writes employee records to the file, including overwriting a specific 
record at a known offset.

lseek()
Moves the file pointer to a specific byte offset, enabling direct 
access to a record without reading through the whole file.

read()
Reads records back from the file sequentially, starting from wherever 
the file pointer is positioned.

close()
Releases the file descriptor and associated system resources once all 
operations are complete.

---

## Explanation: How System Calls Work Together

open() gives a file descriptor to work with. Since each record is a 
fixed size, lseek() can jump straight to any record's byte offset, so 
write() can update just that record instead of the whole file. read() 
then pulls records back from wherever the pointer is. close() releases 
the file descriptor when done. Together, these calls allow fast, 
direct access to any record without rewriting the entire file.