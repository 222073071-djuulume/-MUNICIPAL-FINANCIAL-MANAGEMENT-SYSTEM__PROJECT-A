/*
 * budget.h - Budget Management module.
 * Owner: Student 2
 */
#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 10
#define DEPT_NAME_LEN   30

void   budgetMenu(void);
void   addDepartmentBudget(void);
void   displayBudgets(void);
double calculateBudget(double revenue, double expenditure);

#endif
