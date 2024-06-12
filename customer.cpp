#include "customer.h"
#include"SavingsAccount.h"
#include<iostream>
#include<memory>
#include<string>
#include<algorithm>
#include<string>
#include<vector>

void customer::printDetails()
{
    std::cout<<"Customer ID: "
             <<this->custId
             <<"\nName: "
             <<this->custName
             <<"\nEmail: "
             <<this->custEmail
             <<"\nPhone Number: "
             <<this->phoneNumber
             <<"\nAddress: "
             <<this->custAddress;
}

void customer::menuPrint()
{
    system("clear");
    std::cout << "\nCustomer Menu:\n";
    std::cout << "1. Show Customer Details\n";
    std::cout << "2. Edit Customer Details\n";
    std::cout << "3. Open Account\n";
    std::cout << "4. Close Account\n";
    std::cout << "5. Find Account\n";
    std::cout << "6. Deposit\n";
    std::cout << "7. Withdraw\n";
    std::cout << "8. PrintStatement\n";
    std::cout << "9. Exit\n";

    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) 
    {
        case 1: //show the details of the customer fetched from the main
        {
            system("clear");
            printDetails();
            return;
        }
        case 2: // Edit customer details
        {
            editCustomer();
            break;
        }

        case 3: //Add an account of customer in the list of accounts stored (of that particular customer) in the vector
        {
            std::string bank_choice;
            std::cout<<"Write the bank name: \n"
                     <<"  MBH\n"
                     <<"  OTP\n"
                     <<"  Erste\n\n";
    
            std::cin>>bank_choice;
            
            if(openAccount(bank_choice)==true)
            {
                std::cout<<"Account added successfully into the list of accounts\n";
            }
            else
            {
                std::cout<<"Account addition unsuccessful ";
            }
            break;
        }

        case 4:
        {
            std::string account_number;
            std::cout<<"Enter you Account Number: ";
            std::cin>>account_number;
            if(closeAccount(account_number)==true)
            {
                std::cout << "Account closed successfully." << std::endl;
            }
            else
            {
                std::cerr << "Account does not exists closed!"<<std::endl;
            }
            break;
        }

        case 5:
        {
            std::string accnum;
            std::cout<<"Enter the account number you want to find in the list: ";
            std::cin>>accnum;
            if(findAccount(accnum))
            {
                std::cout<<"Account is active!"<<std::endl;
            }

            else
            {
                system("clear");
                std::cout<<"Account does not exists with this "<<accnum<<" account number!"<<std::endl;
                return;
            }
            break;
        }
        
        case 6:
        {
            std::string accountNumber;
            double amount;
            std::cout << "Enter Account Number: ";
            std::cin >> accountNumber;
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            if (!deposit(accountNumber, amount)) 
            {
                std::cout << "Deposit failed." << std::endl;
            }
            break;
        }
        
        case 7:
        {
            std::string accountNumber;
            double amount;
            std::cout << "Enter Account Number: ";
            std::cin >> accountNumber;
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            if (!withdraw(accountNumber, amount)) 
            {
                std::cout << "Withdraw failed." << std::endl;
            }
            break;
        }
        
        case 8:
        {
            printStatement();
            break;
        }
        
        case 9:
        {
            return;
        }

        default:
        {
            std::cout<<"Opt for the correct choice!!"<<std::endl;
        }
        // return;
    } 
}

void customer:: editCustomer()
{
    if(editCustomerHandler())
    {
        std::cout<<"Changed successfully done\n";
    }
    else
    {
        std::cout<<"Modifying not possible\n ";
    }
}

bool customer::editCustomerHandler()
{
    std::cout<<"What will you like to edit?\n";
    std::cout<< "1. Edit customer name: \n"
             << "2. Edit customer email: \n"
             <<" 3. Edit customer phone number: \n"
             <<" 4. Edit customer address: \n";

    int input;
    std::cin>>input;
    switch(input)
    {
        case 1: 
        {
            std::string newName;
            std::cout<<"Enter new name: ";
            std::cin>>newName;
            this->custName = newName;
            break;
        }

        case 2:
        {
            std::string newEmail;
            std::cout<<"Enter new email id: ";
            std::cin>>newEmail;
            this->custEmail = newEmail;
            break;
        }

        case 3:
        {
            std::string newPhone;
            std::cout<<"Enter new phone number: ";
            std::cin>>newPhone;
            this->phoneNumber = newPhone;
            break;
        }

        case 4:
        {
            std::string newAddress;
            std::cout<<"Enter new address: ";
            std::cin>>newAddress;
            this->custAddress = newAddress;
            break;
        }

        default:
        {
            std::cout<<"enter correct value to edit! ";
            return false;
        }
    }
    return true;
}


bool customer::openAccount(const std::string& bankChoice)
{
    bool created;
    SavingsAccount* newAccount = nullptr;
    try
    {
        std::string accountNumber;
        double initialBalance;

        // Generated account number
        accountNumber = std::to_string(rand() % 9000000000 + 1000000000); 

        std::cout << "Generated Account Number: " << accountNumber << std::endl;
        std::cout << "Enter initial balance for the new account: ";
        std::cin >> initialBalance;

        if (initialBalance < 0) 
        {
            throw std::invalid_argument("Initial balance cannot be negative.");
        }
        //using DMA 
        newAccount = new SavingsAccount(this->custId, accountNumber, initialBalance, 0.5, bankChoice);

        accounts.push_back(newAccount);  // Store the pointer in the vector
        newAccount = nullptr;   // Prevent deletion after successful addition
        std::cout << "Account opened successfully with balance: " << initialBalance << std::endl;

        db_Management db;
        created = db.writeAccountToFile(accountNumber, initialBalance, 0.5, bankChoice);
        
        // For debugging 
        std::cout << "\n\nCurrent accounts in system:" << std::endl;
        for (const auto& acc : accounts) {
            std::cout << " - " << acc->getAccountNumber() << std::endl;
        }
        
        return created;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<<"Error: " <<e.what() << "\n";
        delete newAccount;
        return false;
    }

    catch (...) 
    {
        std::cerr << "An unknown error occurred." << std::endl;
        delete newAccount;
        return false;
    }  
}

bool customer::closeAccount(const std::string& accountNumber) 
{
    db_Management db;
    std::string filename = "savingsAccount.txt";
    std::vector<std::tuple<std::string, std::string, double, float, std::string>> updatedacc = db.updateAccountToFile(filename, accountNumber);
    if(!(updatedacc.empty()))
    {
        return true;
    }
    return false;
}

bool customer::findAccount(std::string& accountNumber)
{
    std::string filename = "savingsAccount.txt";
    db_Management db;
    bool found = db.loadFromFile(filename, accountNumber);
    return found;
}

void customer::printStatement()
{
    std::string filename = "Statement.txt";
    db_Management db;
    db.printStatement(filename);
}

bool customer::deposit(const std::string& account_number, double amount)
{
    std::string filename = "Statement.txt";
    if (amount <= 0) 
    {
        std::cerr << "Deposit amount must be positive." << std::endl;
        return false;
    }
    
    // Finding the account
    for (auto& account : accounts) 
    {
        if (account->getAccountNumber() == account_number) 
        {
            // Updating the account balance
            double newBalance = account->getBalance() + amount;
            account->setBalance(newBalance); // Assuming setBalance is a method that sets the account balance
            
            db_Management db;
            if (!db.recordTransaction(filename, account_number, amount, "Income")) 
            {
                std::cerr << "Failed to record transaction in statement file." << std::endl;
                return false;
            }
            std::cout << "Deposit successful. New balance: " << newBalance << std::endl;
            return true;
        }
    }    
    std::cerr << "Account number not found." << std::endl;
    return false;
}

bool customer::withdraw(const std::string& accountNumber, double amount)
{
    if (amount <= 0) 
    {
        std::cerr << "Withdrawal amount must be positive." << std::endl;
        return false;
    }
    
    // Finding the account by account number
    auto it = std::find_if(accounts.begin(), accounts.end(), [&accountNumber](const SavingsAccount* acc) {
        return acc->getAccountNumber() == accountNumber;
    });
    
    if (it == accounts.end()) 
    {
        std::cerr << "Account number not found." << std::endl;
        return false;
    }
    
    SavingsAccount* account = *it;
    if (account->getBalance() < amount) 
    {
        std::cerr << "Insufficient funds for withdrawal." << std::endl;
        return false;
    }
    
    // Perform the withdrawal
    account->setBalance(account->getBalance() - amount); 
    
    //logging the transaction in the database file
    db_Management db;
    std::string filename = "Statement.txt";
    if (!db.recordTransaction(filename, accountNumber, amount, "Withdrawal")) 
    {
        std::cerr << "Failed to record transaction in statement file." << std::endl;
        return false;
    }
    std::cout << "Withdrawal successful. New balance: " << account->getBalance() << std::endl;
    return true;
}