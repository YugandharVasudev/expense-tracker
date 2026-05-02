#include<iostream>
using namespace std;

void addExpense(){}
void viewExpenses(){}
void editExpense(){}
void deleteExpense(){}

int main(){
    int choice;
    while(true){
        cout<<"\n--- Expense Tracker ---\n";
        cout<<"1. Add Expense\n";
        cout<<"2. View Expenses\n";
        cout<<"3. Edit Expense\n";
        cout<<"4. Delete Expense\n";
        cout<<"5. Exit Program\n";
        cout<<"Enter Choice\n";

        cin>>choice;

        switch(choice){
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                editExpense();
                break;
            case 4:
                deleteExpense();
                break;
            case 5:
                cout<<"Exiting program...\n";
                return 0;
            default:
                cout<<"Invalid Choice. Try again\n";
        }
    }
}