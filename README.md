# MFMS – Group Members

**Course:** PAP521S – Programming in Practice
**Institution:** Namibia University of Science and Technology (NUST)

# Group Members

| Group Member       | Student Number | Responsibility                              |
| ------------------ | -------------- | ------------------------------------------- |
| Paully Nampala     | 226075931      | Employee Management                         |
| William Nathaniel  | 225033550      | Budget Management                           |
| Matheus Iimbangu   | 226088472      | Supplier Management                         |
| Samuel Akah        | 226184250      | Asset Management                            |
| Eva Gideon         | 226038092      | Reports                                     |
| Magdalena Djuulume | 222073071      | Functions, Integration and Validation       |
| Elia Mudumbi       | 211056529      | Testing, Documentation and Git Coordination |

## Project description

A menu-driven console application that helps a municipality record employees,
department budgets, suppliers and assets, and produce summary reports.

## System features

- **Main menu** with validated navigation.
- **Budget Management** – allocate per-department budgets, record expenditure, remaining budget, WITHIN BUDGET / OVER BUDGET status.
- **Supplier Management** – add/display/search suppliers by ID or name, filter by town.
- **Asset Management** – asset register (ID, name, type, value, department, condition, search, and a report.
- **Reports** – per-module summaries, plus a "Generate All Reports" option.
- **Validation** – empty text, non-numeric or out-of-range input and duplicate IDs are all rejected with a re-prompt.

## Compilation

```bash
gcc -std=c99 -Wall -Wextra -o mfms.exe main.c utils.c employees.c budget.c suppliers.c assets.c reports.c
```

## How to run

```bash
.\mfms.exe      # Windows (PowerShell) - run from a terminal
```
