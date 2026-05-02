# Expense Tracker

A command-line expense management application written in C++.

## Features
- Add, view, edit, and delete expenses
- Persistent storage via file I/O
- Category-wise and monthly summary reports
- CSV export
- Input validation and error handling

## How to compile and run
```bash
g++ app.cpp -o tracker
./tracker
```

## Data format
Expenses are stored in `expenses.txt` in the following format: DD-MM-YYYY|Category|Amount|Description