#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define MAX_NAME_LEN 50
#define MAX_DEPARTMENT_LEN 40
#define MAX_JOB_TITLE_LEN 40
#define MAX_PHONE_LEN 20

#define MAX_SALARY_VALUE 10000000.0

typedef struct
{
    int id;
    char name[MAX_NAME_LEN + 1];
    char department[MAX_DEPARTMENT_LEN + 1];
    char jobTitle[MAX_JOB_TITLE_LEN + 1];
    char phone[MAX_PHONE_LEN + 1];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
    double otherAllowance;
} Employee;

void employeeMenu(void);

int addEmployee(void);

void displayEmployees(void);

void searchEmployee(void);

void calculateSalary(void);

void displayEmployeeDetails(void);

void displayEmployeeInfo(const Employee *emp);

double calculateGrossSalary(const Employee *emp);
double calculateAnnualTax(double annualGross);
double calculateMonthlyTax(double monthlyGross);
double calculateSocialSecurity(double basicSalary);
double calculateNetSalary(const Employee *emp);

int findEmployeeIndexById(int id);

int getEmployeeCount(void);
const Employee *getEmployeeAt(int index);
double getTotalGrossSalary(void);
double getAverageSalary(void);
double getHighestSalary(void);
double getLowestSalary(void);

void displayEmployeeReport(void);

#endif