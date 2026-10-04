/*
 * employees.h - Employee Management module.
 * Owner: Student 1
 */
#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES   50
#define EMP_NAME_LEN    50

void   employeeMenu(void);
void   addEmployee(void);
void   displayEmployees(void);
int    searchEmployee(int id, int ids[], int size);   /* returns index or -1 */
double calculateSalary(double basic, double housing, double transport);

#endif
