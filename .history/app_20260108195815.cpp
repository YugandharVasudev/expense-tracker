#include<iostream>
#include<string>
#include<vector>
#include<limits>

struct Expense{
    double amount;
    std::string category;
    std::string description;
    std::string date;
};
std::vector<Expense> expenses;

void addExpense(std::vector<Expense> expenses){
    Expense e;
    while(!(std::cin>>e.amount || e.amount<0)){
        std::cout << "Invalid amount. Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    std::cout<<"Add Expense selected\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::cout<<"Enter Category: ";
    std::getline(std::cin,e.category);

    std::cout<<"Enter description: ";
    std::getline(std::cin,e.description);

    std::cout<<"Enter date (DD-MM-YYYY): ";
    std:getline(std::cin,e.date);
}
void viewExpenses(){
    std::cout<<"View Expenses selected\n";    
}
void editExpense(){
    std::cout<<"Edit Expense selected\n";
}
void deleteExpense(){
    std::cout<<"Delete Expense selected\n";
}

int main(){
    int choice;
    while(true){
        std::cout<<"\n--- Expense Tracker ---\n";
        std::cout<<"1. Add Expense\n";
        std::cout<<"2. View Expenses\n";
        std::cout<<"3. Edit Expense\n";
        std::cout<<"4. Delete Expense\n";
        std::cout<<"5. Exit Program\n";
        std::cout<<"Enter Choice: \n";

        std::cin>>choice;
        
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
                std::cout<<"Exiting program...\n";
                return 0;
            default:
                std::cout<<"Invalid Choice. Try again\n";
        }
    }
    return 0;
}