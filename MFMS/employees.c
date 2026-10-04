#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#include "employees.h"

#define INPUT_BUFFER_SIZE 256
#define MAX_EMPLOYEE_ID 999999
#define TABLE_WIDTH 92
#define SLIP_WIDTH 48

#define SOCIAL_SECURITY_RATE 0.009 /* 0.9% of basic salary (simplified) */

static Employee employees[MAX_EMPLOYEES];
static int employeeCount = 0;

typedef struct
{
    double upperLimit; /* band applies while income <= upperLimit */
    double lowerLimit;
    double baseTax;
    double rate;
} TaxBand;

static const TaxBand taxBands[] = {
    {100000.0, 0.0, 0.0, 0.00},
    {150000.0, 100000.0, 0.0, 0.18},
    {350000.0, 150000.0, 9000.0, 0.25},
    {550000.0, 350000.0, 59000.0, 0.28},
    {850000.0, 550000.0, 115000.0, 0.30},
    {1550000.0, 850000.0, 205000.0, 0.32},
    {-1.0, 1550000.0, 429000.0, 0.37} /* -1 = no upper limit */
};
#define TAX_BAND_COUNT ((int)(sizeof(taxBands) / sizeof(taxBands[0])))

static void trim(char *text)
{
    size_t len = strlen(text);
    size_t start = 0;

    while (len > 0 && isspace((unsigned char)text[len - 1]))
    {
        text[--len] = '\0';
    }
    while (text[start] != '\0' && isspace((unsigned char)text[start]))
    {
        start++;
    }
    if (start > 0)
    {
        memmove(text, text + start, len - start + 1);
    }
}


static void readLine(const char *prompt, char *buffer, size_t size)
{
    int ch;

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        printf("\nInput closed. Exiting program.\n");
        exit(EXIT_SUCCESS);
    }

    if (strchr(buffer, '\n') == NULL)
    {
        /* Input was longer than the buffer: throw away the rest. */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }
    trim(buffer);
}

/* Reads a whole number in [min, max]; repeats until valid. */
static int readInt(const char *prompt, int min, int max)
{
    char buffer[INPUT_BUFFER_SIZE];
    char *end;
    long value;

    for (;;)
    {
        readLine(prompt, buffer, sizeof(buffer));

        if (buffer[0] == '\0')
        {
            printf("  Error: input cannot be empty.\n");
            continue;
        }

        errno = 0;
        value = strtol(buffer, &end, 10);

        if (end == buffer || *end != '\0' || errno == ERANGE)
        {
            printf("  Error: please enter a whole number.\n");
        }
        else if (value < min || value > max)
        {
            printf("  Error: value must be between %d and %d.\n", min, max);
        }
        else
        {
            return (int)value;
        }
    }
}

/* Reads a money amount in [min, max]; repeats until valid. */
static double readAmount(const char *prompt, double min, double max)
{
    char buffer[INPUT_BUFFER_SIZE];
    char *end;
    double value;

    for (;;)
    {
        readLine(prompt, buffer, sizeof(buffer));

        if (buffer[0] == '\0')
        {
            printf("  Error: input cannot be empty.\n");
            continue;
        }

        errno = 0;
        value = strtod(buffer, &end);

        if (end == buffer || *end != '\0' || errno == ERANGE || !isfinite(value))
        {
            printf("  Error: please enter a valid number (e.g. 12500.50).\n");
        }
        else if (value < 0.0)
        {
            printf("  Error: negative amounts are not accepted.\n");
        }
        else if (value < min || value > max)
        {
            printf("  Error: amount must be between %.2f and %.2f.\n", min, max);
        }
        else
        {
            return value;
        }
    }
}

/* STRING VALIDATION                                                   */

static int isValidName(const char *s)
{
    int hasLetter = 0;

    for (; *s != '\0'; s++)
    {
        unsigned char c = (unsigned char)*s;

        if (isalpha(c))
        {
            hasLetter = 1;
        }
        else if (c != ' ' && c != '-' && c != '\'' && c != '.')
        {
            return 0;
        }
    }
    return hasLetter;
}

/* Printable characters only, with at least one letter or digit. */
static int isValidLabel(const char *s)
{
    int hasAlnum = 0;

    for (; *s != '\0'; s++)
    {
        unsigned char c = (unsigned char)*s;

        if (!isprint(c))
        {
            return 0;
        }
        if (isalnum(c))
        {
            hasAlnum = 1;
        }
    }
    return hasAlnum;
}

/* 7-15 digits; spaces, hyphens and one leading '+' are allowed. */
static int isValidPhone(const char *s)
{
    size_t i;
    int digits = 0;
    size_t len = strlen(s);

    if (len > MAX_PHONE_LEN)
    {
        return 0;
    }
    for (i = 0; i < len; i++)
    {
        unsigned char c = (unsigned char)s[i];

        if (isdigit(c))
        {
            digits++;
        }
        else if (!((c == '+' && i == 0) || c == ' ' || c == '-'))
        {
            return 0;
        }
    }
    return digits >= 7 && digits <= 15;
}

/* Copies src to dest in lower case (dest must be large enough). */
static void toLowerCopy(char *dest, const char *src)
{
    while (*src != '\0')
    {
        *dest++ = (char)tolower((unsigned char)*src++);
    }
    *dest = '\0';
}

/* Case-insensitive "contains" test. */
static int containsIgnoreCase(const char *text, const char *part)
{
    char a[INPUT_BUFFER_SIZE];
    char b[INPUT_BUFFER_SIZE];

    toLowerCopy(a, text);
    toLowerCopy(b, part);
    return strstr(a, b) != NULL;
}

/* Reads a text field (name or label) with length and content checks. */
static void readText(const char *prompt, const char *field,
                     char *dest, size_t maxLen, int isName)
{
    char buffer[INPUT_BUFFER_SIZE];

    for (;;)
    {
        readLine(prompt, buffer, sizeof(buffer));

        if (buffer[0] == '\0')
        {
            printf("  Error: %s cannot be empty.\n", field);
        }
        else if (strlen(buffer) > maxLen)
        {
            printf("  Error: %s must be at most %lu characters.\n",
                   field, (unsigned long)maxLen);
        }
        else if (isName && !isValidName(buffer))
        {
            printf("  Error: %s may only contain letters, spaces, '-', '.' and apostrophes.\n",
                   field);
        }
        else if (!isName && !isValidLabel(buffer))
        {
            printf("  Error: %s contains invalid characters.\n", field);
        }
        else
        {
            strcpy(dest, buffer);
            return;
        }
    }
}

/* Optional phone number; "N/A" is stored when skipped. */
static void readPhone(char *dest)
{
    char buffer[INPUT_BUFFER_SIZE];

    for (;;)
    {
        readLine("Enter phone number (optional, press Enter to skip): ",
                 buffer, sizeof(buffer));

        if (buffer[0] == '\0')
        {
            strcpy(dest, "N/A");
            return;
        }
        if (isValidPhone(buffer))
        {
            strcpy(dest, buffer);
            return;
        }
        printf("  Error: phone must have 7-15 digits (spaces, '-' and a leading '+' allowed).\n");
    }
}


static void printLine(char symbol, int width)
{
    int i;

    for (i = 0; i < width; i++)
    {
        putchar(symbol);
    }
    putchar('\n');
}

static void printTableHeader(void)
{
    printLine('=', TABLE_WIDTH);
    printf("%-6s %-24s %-18s %-14s %14s %14s\n",
           "ID", "NAME", "DEPARTMENT", "JOB TITLE", "BASIC (N$)", "GROSS (N$)");
    printLine('-', TABLE_WIDTH);
}

static void printTableRow(const Employee *emp)
{
    printf("%-6d %-24.24s %-18.18s %-14.14s %14.2f %14.2f\n",
           emp->id, emp->name, emp->department, emp->jobTitle,
           emp->basicSalary, calculateGrossSalary(emp));
}

static void printMoneyRow(const char *label, double amount)
{
    printf("%-28s N$ %12.2f\n", label, amount);
}

double calculateGrossSalary(const Employee *emp)
{
    if (emp == NULL)
    {
        return 0.0;
    }
    return emp->basicSalary + emp->housingAllowance +
           emp->transportAllowance + emp->otherAllowance;
}

double calculateAnnualTax(double annualGross)
{
    int i;

    if (annualGross <= 0.0)
    {
        return 0.0;
    }
    for (i = 0; i < TAX_BAND_COUNT; i++)
    {
        const TaxBand *b = &taxBands[i];

        if (b->upperLimit < 0.0 || annualGross <= b->upperLimit)
        {
            return b->baseTax + (annualGross - b->lowerLimit) * b->rate;
        }
    }
    return 0.0;
}

double calculateMonthlyTax(double monthlyGross)
{
    return calculateAnnualTax(monthlyGross * 12.0) / 12.0;
}

double calculateSocialSecurity(double basicSalary)
{
    return basicSalary * SOCIAL_SECURITY_RATE;
}

double calculateNetSalary(const Employee *emp)
{
    double gross;

    if (emp == NULL)
    {
        return 0.0;
    }
    gross = calculateGrossSalary(emp);
    return gross - calculateMonthlyTax(gross) - calculateSocialSecurity(emp->basicSalary);
}

int findEmployeeIndexById(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (employees[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

int getEmployeeCount(void)
{
    return employeeCount;
}

const Employee *getEmployeeAt(int index)
{
    if (index < 0 || index >= employeeCount)
    {
        return NULL;
    }
    return &employees[index];
}

double getTotalGrossSalary(void)
{
    int i;
    double total = 0.0;

    for (i = 0; i < employeeCount; i++)
    {
        total += calculateGrossSalary(&employees[i]);
    }
    return total;
}

double getAverageSalary(void)
{
    if (employeeCount == 0)
    {
        return 0.0;
    }
    return getTotalGrossSalary() / employeeCount;
}

static int findExtremeIndex(int wantHighest)
{
    int i;
    int best = 0;

    if (employeeCount == 0)
    {
        return -1;
    }
    for (i = 1; i < employeeCount; i++)
    {
        double current = calculateGrossSalary(&employees[i]);
        double bestValue = calculateGrossSalary(&employees[best]);

        if (wantHighest ? (current > bestValue) : (current < bestValue))
        {
            best = i;
        }
    }
    return best;
}

double getHighestSalary(void)
{
    int i = findExtremeIndex(1);

    return (i < 0) ? 0.0 : calculateGrossSalary(&employees[i]);
}

double getLowestSalary(void)
{
    int i = findExtremeIndex(0);

    return (i < 0) ? 0.0 : calculateGrossSalary(&employees[i]);
}


/* CORE OPERATIONS                                                     */

int addEmployee(void)
{
    Employee e;
    int id;

    printf("\n--- ADD EMPLOYEE ---\n");

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Error: employee list is full (maximum %d employees).\n", MAX_EMPLOYEES);
        return 0;
    }

    for (;;)
    {
        id = readInt("Enter employee ID (1-999999, or 0 to cancel): ", 0, MAX_EMPLOYEE_ID);

        if (id == 0)
        {
            printf("Add employee cancelled.\n");
            return 0;
        }
        if (findEmployeeIndexById(id) == -1)
        {
            break;
        }
        printf("  Error: employee ID %d already exists.\n", id);
    }

    memset(&e, 0, sizeof(e));
    e.id = id;
    readText("Enter full name: ", "Name", e.name, MAX_NAME_LEN, 1);
    readText("Enter department: ", "Department", e.department, MAX_DEPARTMENT_LEN, 0);
    readText("Enter job title: ", "Job title", e.jobTitle, MAX_JOB_TITLE_LEN, 0);
    readPhone(e.phone);

    e.basicSalary = readAmount("Enter monthly basic salary (N$): ",
                               0.01, MAX_SALARY_VALUE);
    e.housingAllowance = readAmount("Enter monthly housing allowance (N$, 0 if none): ",
                                    0.0, MAX_SALARY_VALUE);
    e.transportAllowance = readAmount("Enter monthly transport allowance (N$, 0 if none): ",
                                      0.0, MAX_SALARY_VALUE);
    e.otherAllowance = readAmount("Enter other monthly allowances (N$, 0 if none): ",
                                  0.0, MAX_SALARY_VALUE);

    employees[employeeCount++] = e;

    printf("\nEmployee '%s' (ID %d) added successfully.\n", e.name, e.id);
    return 1;
}

void displayEmployees(void)
{
    int i;

    printf("\n--- EMPLOYEE LIST ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    printTableHeader();
    for (i = 0; i < employeeCount; i++)
    {
        printTableRow(&employees[i]);
    }
    printLine('=', TABLE_WIDTH);
    printf("Total employees: %d\n", employeeCount);
}

void searchEmployee(void)
{
    int choice;
    int i;
    int found = 0;
    char query[INPUT_BUFFER_SIZE];

    printf("\n--- SEARCH EMPLOYEE ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    printf("1. Search by employee ID\n");
    printf("2. Search by name (partial match)\n");
    printf("3. Search by department (partial match)\n");
    printf("4. Cancel\n");
    choice = readInt("Enter your choice: ", 1, 4);

    if (choice == 4)
    {
        printf("Search cancelled.\n");
        return;
    }

    if (choice == 1)
    {
        int id = readInt("Enter employee ID to search for: ", 1, MAX_EMPLOYEE_ID);

        i = findEmployeeIndexById(id);
        if (i == -1)
        {
            printf("No employee found with ID %d.\n", id);
        }
        else
        {
            printf("\nEmployee found:\n");
            displayEmployeeInfo(&employees[i]);
        }
        return;
    }

    readLine(choice == 2 ? "Enter name (or part of a name): "
                         : "Enter department (or part of it): ",
             query, sizeof(query));

    if (query[0] == '\0')
    {
        printf("  Error: search text cannot be empty.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++)
    {
        const char *field = (choice == 2) ? employees[i].name : employees[i].department;

        if (containsIgnoreCase(field, query))
        {
            if (found == 0)
            {
                printf("\nMatching employees:\n");
                printTableHeader();
            }
            printTableRow(&employees[i]);
            found++;
        }
    }

    if (found > 0)
    {
        printLine('=', TABLE_WIDTH);
        printf("%d employee(s) found.\n", found);
    }
    else
    {
        printf("No employees matched '%s'.\n", query);
    }
}

void calculateSalary(void)
{
    int id;
    int index;
    const Employee *emp;
    double gross, tax, ssc;
    char title[MAX_NAME_LEN + 16];

    printf("\n--- CALCULATE SALARY ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    id = readInt("Enter employee ID: ", 1, MAX_EMPLOYEE_ID);
    index = findEmployeeIndexById(id);
    if (index == -1)
    {
        printf("No employee found with ID %d.\n", id);
        return;
    }

    emp = &employees[index];
    gross = calculateGrossSalary(emp);
    tax = calculateMonthlyTax(gross);
    ssc = calculateSocialSecurity(emp->basicSalary);

    strcpy(title, "PAYSLIP - ");
    strcat(title, emp->name);

    printf("\n");
    printLine('=', SLIP_WIDTH);
    printf("%s\n", title);
    printf("Employee ID : %d\n", emp->id);
    printf("Department  : %s\n", emp->department);
    printLine('-', SLIP_WIDTH);
    printMoneyRow("Basic salary", emp->basicSalary);
    printMoneyRow("Housing allowance", emp->housingAllowance);
    printMoneyRow("Transport allowance", emp->transportAllowance);
    printMoneyRow("Other allowances", emp->otherAllowance);
    printLine('-', SLIP_WIDTH);
    printMoneyRow("GROSS SALARY", gross);
    printMoneyRow("Income tax (PAYE)", tax);
    printMoneyRow("Social security", ssc);
    printLine('-', SLIP_WIDTH);
    printMoneyRow("NET SALARY", gross - tax - ssc);
    printLine('=', SLIP_WIDTH);
    printf("Note: tax and social security use simplified rates.\n");
}

void displayEmployeeInfo(const Employee *emp)
{
    if (emp == NULL)
    {
        printf("No employee information available.\n");
        return;
    }

    printLine('-', SLIP_WIDTH);
    printf("Employee ID         : %d\n", emp->id);
    printf("Name                : %s\n", emp->name);
    printf("Department          : %s\n", emp->department);
    printf("Job title           : %s\n", emp->jobTitle);
    printf("Phone               : %s\n", emp->phone);
    printf("Basic salary        : N$ %.2f\n", emp->basicSalary);
    printf("Housing allowance   : N$ %.2f\n", emp->housingAllowance);
    printf("Transport allowance : N$ %.2f\n", emp->transportAllowance);
    printf("Other allowances    : N$ %.2f\n", emp->otherAllowance);
    printf("Gross salary        : N$ %.2f\n", calculateGrossSalary(emp));
    printf("Net salary (approx) : N$ %.2f\n", calculateNetSalary(emp));
    printLine('-', SLIP_WIDTH);
}

void displayEmployeeDetails(void)
{
    int id;
    int index;

    printf("\n--- EMPLOYEE DETAILS ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    id = readInt("Enter employee ID: ", 1, MAX_EMPLOYEE_ID);
    index = findEmployeeIndexById(id);
    if (index == -1)
    {
        printf("No employee found with ID %d.\n", id);
        return;
    }
    displayEmployeeInfo(&employees[index]);
}

void displayEmployeeReport(void)
{
    int hi, lo;

    printf("\n========================================\n");
    printf("EMPLOYEE REPORT\n");
    printf("========================================\n");

    if (employeeCount == 0)
    {
        printf("Total Employees: 0\n");
        printf("No salary statistics available.\n");
        return;
    }

    hi = findExtremeIndex(1);
    lo = findExtremeIndex(0);

    printf("Total Employees : %d\n", employeeCount);
    printf("Average Salary  : N$%.2f\n", getAverageSalary());
    printf("Highest Salary  : N$%.2f (%s)\n", calculateGrossSalary(&employees[hi]), employees[hi].name);
    printf("Lowest Salary   : N$%.2f (%s)\n", calculateGrossSalary(&employees[lo]), employees[lo].name);
    printf("(Salaries shown are gross monthly: basic + allowances)\n");
}



static void showEmployeeMenu(void)
{
    printf("\n========================================\n");
    printf("          EMPLOYEE MANAGEMENT\n");
    printf("========================================\n");
    printf("1. Add an employee\n");
    printf("2. Display all employees\n");
    printf("3. Search for an employee\n");
    printf("4. Calculate employee salary\n");
    printf("5. Display employee information\n");
    printf("6. Return to main menu\n");
}

void employeeMenu(void)
{
    int choice;

    do
    {
        showEmployeeMenu();
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice)
        {
        case 1:
            addEmployee();
            break;
        case 2:
            displayEmployees();
            break;
        case 3:
            searchEmployee();
            break;
        case 4:
            calculateSalary();
            break;
        case 5:
            displayEmployeeDetails();
            break;
        default:
            break;
        }
    } while (choice != 6);

    printf("Returning to main menu...\n");
}