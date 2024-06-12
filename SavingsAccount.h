#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include<string>
#include "db_Management.h"
#include "RegularBank.h"


class SavingsAccount
{
    private:
    std::string custId;  
    std::string account_number;
    double current_balance;
    double interest;
    std::string bankName; 

    public:

    SavingsAccount()
    {}

    SavingsAccount(const std::string& id, std::string& accountNo, double balance, double interest, const std::string& bankName) : custId(id), account_number(accountNo), current_balance(balance), interest(interest), bankName(bankName)
    {}    
    
    ~SavingsAccount()
    {
        this->account_number = "";
        this->current_balance = 0;
        this->interest = 0;
        this->bankName = "";
    }

    std::string getAccountNumber() const //Returns the account number associated with the savings account.
    {
        return account_number;
    }

    double getBalance() const  // Returns the current balance of the savings account.
    {
        return current_balance;
    }

    double getInterestRate() const //Sets the interest rate for the savings account.
    {
        return interest;
    }
    
    std::string getBankName() const 
    { 
        return bankName; 
    }
    
    void adjustInterestRate(double newRate) //Adjusts the interest rate of the savings account to a new specified rate.
    {
        this->interest = newRate;
    }
    
    void setBalance(double newAmount)
    {
        this->current_balance = newAmount;
    }

    // bool isBalanceBelowMinimum() const; //Checks if the account balance is below the minimum required balance.


    // void transferTo(SavingsAccount& destination, double amt);    //Transfers the specified amount from the current savings account to another savings account (destination).

    
    // void isWithdrawalLimitExceeded() const; //Checks if the number of withdrawals made in a certain period exceeds the withdrawal limit.

    

    // void deposit(double amount);    // Adds the specified amount to the account's balance.

    // bool withdraw(double amount);   // Subtracts the specified amount from the account's balance if there are sufficient funds. Returns true if the withdrawal is successful, and false otherwise.

    //void printstatement();   //Opens the file associated with the account from the database, reads the contents, and outputs them to the console. This method provides a way to generate a statement of account activity for the user.

    // bool operator==(const SavingsAccount& acc)
    // {
    //     return this->account_number == acc.getAccountNumber();
    // }

};


#endif