#ifndef REGULARBANK_H
#define REGULARBANK_H   

#include "SavingsAccount.h"
#include <string>
#include<vector>

class RegularBank
{
    private:
    std::string name;
    std::string address;
    double interestRate;
    int withdrawalLimit;
    int minimumBalance;
    std:: vector<SavingsAccount> accountList;

    public:

    RegularBank()
    {}

    RegularBank(const std::string& name, const std::string& address, double interestRate, int withdrawalLimit, int minBalance): name(name), address(address), interestRate(interestRate), withdrawalLimit(withdrawalLimit), minimumBalance(minBalance)
    {} //Initializes a RegularBank object with the provided name, address, interest rate, withdrawal limit, and minimum balance.

    ~RegularBank();

    std::string getBankName(std::string& newName); //Sets the name of the bank to the specified value

    void setbankAddress(std::string& newAddress);   //Sets the address of the bank to the specified value.

    std::string getBankAddress();

    double getInterestRate();

    int getMinimumBalance()
    {
        return minimumBalance;
    }

    int getTotalNumberOfAccounts() const;

    std::string& findAccountByNumber(const std::string& accountNumber) const;   //Searches for a savings account with the specified account number and returns a reference to it if found, or nullptr otherwise.

    void closeAllAccounts();    //Closes all savings accounts held by the bank.

    int calculateTotalBalance() const; //Calculates and returns the total balance across all savings accounts held by the bank.

    int calculateTotalInterest() const; //Calculates and returns the total interest earned by all savings accounts held by the bank.

    std::string generateAccountNumber() const; //Generates a unique account number for a new savings account.

    void setWithdrawalLimit(int newWithdrawalLimit);   //Sets the withdrawal limit for accounts held at the bank to the specified value.

    int getWithdrawalLimit()
    {
        return withdrawalLimit;
    }

    void setMinimumBalance(int newMinimumBalance);  //Sets the minimum balance requirement for accounts held at the bank to the specified value.

    void addSavingsAccount(SavingsAccount& account);    //Adds a savings account to the bank's list of accounts.

    void closeAccount(std::string accountNumber);   //Closes the savings account associated with the specified account number.

    void adjustInterestRate();  //Adjusts the interest rates of all savings accounts held at the bank. This method could be used to synchronize the bank's interest rates with changes in the broader economic environment or central bank policies.

};



#endif