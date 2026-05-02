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

void addExpense(std::vector<Expense>& expenses){
    Expense e;
    std::cout<<"Add Expense selected\n";
    while(!(std::cin>>e.amount) || e.amount<0){
        std::cout << "Invalid amount. Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::cout<<"Enter Category: ";
    std::getline(std::cin,e.category);

    std::cout<<"Enter description: ";
    std::getline(std::cin,e.description);

    std::cout<<"Enter date (DD-MM-YYYY): ";
    std:getline(std::cin,e.date);
}
void viewExpenses(const std::vector<Expense>& expenses){
    std::cout<<"View Expenses selected\n";
    if(expenses.empty()){
        std::cout<<"No expenses recorded yet.\n";
        return;
    }
    for(size_t i=0;i<expenses.size();i++){
        const Expense& e = expenses[i];
        
        std::cout<<i+1<<'.'<<"Amount: "<<e.category<<", Description: "<<e.description<<", Date: "<<e.date<<endl;
    }
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

        // std::cin>>choice;
        
        if(!(std::cin>>choice)){
            std::cout<<"Invalid input. Please enter a number.\n";

            std::cin.clear(); //clear fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        switch(choice){
            case 1:
                int option;
                do{
                    std::cout<<"\n1. Add Expense\n2. Exit\n   Choice:";
                    // std::cin>>option; //Invalid input like "c" breaks cin here. It puts it into a weird repeating "stuck" state. 
                    if(!(std::cin>>option)){
                        std::cout<<"Invalid input. Please enter a number.\n";

                        std::cin.clear(); //clear fail state
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                        continue;
                    }
                    switch(option){
                        case 1:
                            addExpense(expenses);
                            break;
                        case 2:
                            std::cout<<"Returning to Menu:";
                            break;
                        default:
                            std::cout<<"Invalid choice:";
                    }
                }while(option!=2);
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                editExpense();
                break;
            case 4:
                deleteExpense();
                break;
            case 5:
                std::cout<<"Exiting program ...\n";
                return 0;
            default:
                std::cout<<"Invalid Choice. Try again\n";
        }
    }
}