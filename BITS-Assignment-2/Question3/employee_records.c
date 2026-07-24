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
