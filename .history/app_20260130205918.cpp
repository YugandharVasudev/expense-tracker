#include<iostream>
#include<string>
#include<vector>
#include<limits>
#include<fstream>
#include<sstream>

struct Expense{
    double amount;
    std::string category;
    std::string description;
    std::string date;
};

void addExpense(std::vector<Expense>& expenses){
    std::cout<<"Add Expense selected\n";
    Expense e;

    std::cout<<"Enter date (DD-MM-YYYY): ";
    std::getline(std::cin, e.date);
    
    std::cout<<"Enter Category: ";
    std::getline(std::cin,e.category);

    while(!(std::cin>>e.amount) || e.amount<0){
        std::cout << "Invalid amount. Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');


    std::cout<<"Enter description: ";
    std::getline(std::cin,e.description);

    expenses.push_back(e);
}
void viewExpenses(const std::vector<Expense>& expenses){
    std::cout<<"View Expenses selected\n";
    if(expenses.empty()){
        std::cout<<"No expenses recorded yet.\n";
        return;
    }
    for(size_t i=0;i<expenses.size();i++){
        std::cout<<i+1<<'.'
                 <<"Amount: "<<expenses[i].amount
                 <<",Category: "<<expenses[i].category
                 <<", Description: "<<expenses[i].description
                 <<", Date: "<<expenses[i].date<<std::endl;
    }
}
void editExpense(std::vector<Expense>& expenses){
    std::cout<<"Edit Expense selected\n";
    if(expenses.empty()){
        std::cout<<"No expenses to edit.\n";
        return;
    }
    viewExpenses(expenses);

    size_t index;
    std::cout<<"Enter expense number to edit: ";
    if(!(std::cin>>index)){
        std::cout<<"Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return;
    }
    if(index==0||index>expenses.size()){
        std::cout<<"Invalid expense number.\n";
        return;
    }

    Expense& e = expenses[index-1];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::string input;

    std::cout<<"New amount("<<e.amount<<"): ";
    std::getline(std::cin,input);
    if(!input.empty()){
        double newAmount;
        std::stringstream ss(input);
        if(ss >> newAmount && newAmount>=0) e.amount = newAmount;
        else std::cout<<"Invalid amount. Keeping old value.\n";
    }

    // while(!(std::cin>>e.amount)||e.amount<0){
    //     std::cout<<"Invalid amount. Try again: ";
    //     std::cin.clear();
    //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    // }

    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    std::cout<<"New category (" <<e.category<<"): ";
    std::getline(std::cin, input);
    if(!input.empty()) e.category = input;

    
    std::cout<<"New description ("<<e.description<<"): ";
    std::getline(std::cin, input);
    if(!input.empty()) e.description = input;

    std::cout<<"New date: ("<<e.date<<"): ";
    std::getline(std::cin, input);
    if(!input.empty()) e.date = input;

    std::cout<<"Expense updated successfully.\n";
}
void deleteExpense(std::vector<Expense>& expenses){
    std::cout<<"Delete Expense selected\n";
    if(expenses.empty()){
        std::cout<<"No expenses to delete.\n";
        return;
    }
    viewExpenses(expenses);
    size_t index;
    std::cout<<"Enter expense number to delete: ";

    if(!(std::cin>>index)){
        std::cout<<"Invalid input.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    if(index==0||index>expenses.size()){
        std::cout<<"Invalid expense number.\n";
        return;
    }
    char confirm;
    std::cout<<"Are you sure? (y/n):";
    std::cin>>confirm;
    
    if(confirm=='y'||confirm=='Y'){
        expenses.erase(expenses.begin()+(index-1));
        std::cout<<"Expense deleted successfully.\n";
    }
    else{
        std::cout<<"Deletion cancelled.\n";
    }
}
//file format: date|category|amount|description
bool saveExpensesToFile(const std::string& filename, const std::vector<Expense>& expenses){
    std::ofstream outFile(filename);
    if(!outFile.is_open()) return false;
    
    for(const Expense& e:expenses){
        outFile <<e.date<<"|"
        <<e.category<<"|"
        <<e.amount<<"|"
        <<e.description<<"\n";
    }
    return true;
}
//file format: date|category|amount|description
bool parseExpenseLine(const std::string& line, Expense& e){
    std::stringstream ss(line);
    std::string token;

    if(!std::getline(ss,e.date, '|')) return false;
    if(!std::getline(ss,e.category, '|')) return false;
    if(!std::getline(ss,token, '|')) return false;

    try {
        e.amount = std::stod(token);
    } catch(...){
        return false;
    }
    if(!std::getline(ss, e.description)) return false;
    
    return true;
}
bool loadExpensesFromFile(const std::string& filename, std::vector<Expense>& expenses){
    expenses.clear();
    std::ifstream inFile(filename);
    if(!inFile.is_open()) return false;

    std::string line;
    while(std::getline(inFile, line)){
        Expense e;
        if(parseExpenseLine(line,e)){
            expenses.push_back(e);
        }
    }
    
    return true;
}

int main(){
    std::vector<Expense> expenses;

    loadExpensesFromFile("expenses.txt", expenses);
    int choice;
    while(true){
        std::cout<<"\n--- Expense Tracker ---\n";
        std::cout<<"1. Add Expense\n";
        std::cout<<"2. View Expenses\n";
        std::cout<<"3. Edit Expense\n";
        std::cout<<"4. Delete Expense\n";
        std::cout<<"5. Save Expenses\n";
        std::cout<<"6. Load Expenses\n";
        std::cout<<"7. Exit Program\n";
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
                            if(!saveExpensesToFile("expenses.txt", expenses)){
                                std::cerr << "Warning: Failed to save expenses.\n";
                            }
                            break;
                        case 2:
                            std::cout<<"Returning to Menu:";
                            break;
                        default:
                            std::cout<<"Invalid choice:";
                    }
                }while(option!=2);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                editExpense(expenses);
                if(!saveExpensesToFile("expenses.txt", expenses)){
                                std::cerr << "Warning: Failed to save expenses.\n";
                            }
                break;
            case 4:
                deleteExpense(expenses);
                if(!saveExpensesToFile("expenses.txt", expenses)){
                                std::cerr << "Warning: Failed to save expenses.\n";
                            }
                break;
            case 5:
                if(!saveExpensesToFile("expenses.txt", expenses)){
                                std::cerr << "Warning: Failed to save expenses.\n";
                            }
                break;
            case 6:
                loadExpensesFromFile("expenses.txt", expenses);
                break;
            case 7:
                std::cout<<"Exiting program ...\n";
                return 0;
            default:
                std::cout<<"Invalid Choice. Try again\n";
        }
    }
}