#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include "SavingsAccount.h"


class customer
{
    private:
    std::string custId;
    std::string custName;
    std::string custEmail;
    std::string phoneNumber;
    std::string custAddress;
    std::vector<SavingsAccount*> accounts;   //this vector will store all accounts of a customer in a vector.

    public:

    customer()
    {}

    customer(std::string id, std::string name, std:: string email, std::string number, std::string address) : custId(id), custName(name), custEmail(email), phoneNumber(number), custAddress(address)
    {}

    std::string getCustomerID() { return custId; }
    std::string getName() { return custName; }
    std::string getAddress() { return custAddress; }
    std::string getPhoneNumber() { return phoneNumber; }
    std::vector<SavingsAccount*>& getAccounts() 
    {
        return accounts;
    }
    
    ~customer()
    {
        for (auto account : accounts) {
        delete account; // Ensure no memory leaks
    }
        accounts.clear();
    }
    }

    void editCustomer();    

    bool editCustomerHandler();
    
    void printDetails();

    void menuPrint();

    bool openAccount(const std::string& bankChoice);

    bool closeAccount(const std::string& accountNumber);

    bool findAccount(std::string& accountNumber);   
    
    void printStatement();
    
    bool deposit(const std::string& account_number, double amount);
    
    bool withdraw(const std::string& accountNumber, double amount);

};


#endif