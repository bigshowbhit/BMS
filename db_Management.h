#ifndef DB_MANAGEMENT
#define DB_MANAGEMENT

#include<iostream>
#include<tuple>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

class SavingsAccount;

class db_Management
{
    private:
    std::string fileName;
    static int lastCustomerId; // Static variable to hold the last customer ID across instances
    std::string getCurrentDate() {
        // Implement logic to get current date
        return "2023-10-10"; // Placeholder for current date
    }

    public:

    db_Management()
    {}
    //this will make the program understand the current file.
    db_Management(std::string fName) : fileName(fName)
    {}
    
    void loadAccountsFromFile(std::vector<SavingsAccount*>& accounts);
    
    //created a vector of tuples so that to read the userName, password and userRole from the file and store inside a vector.
    std::vector<std::tuple<std::string, std::string, std::string>> readUser(const std::string& filename);  

    bool updateUser(const std::string& username, const std::string& newPassword, const std::string& userRole);

    bool writeAccountToFile(const std::string& accountNumber, const double initialBalance, const float interest, const std::string& bankName);

    static int loadCustomerId();

    static void saveCustomerId();

    static int generateCustomerId();
    
    std::vector<std::tuple<std::string, std::string, double, float, std::string>> updateAccountToFile(const std::string& filename, const std::string& accountNumber);
    
    bool loadFromFile(std::string& filename, std::string& accountNumber);
    
    void printStatement(const std::string& filename);
    
    bool recordTransaction(const std::string& filename, const std::string& accountNumber, double amount, const std::string& type);

};

#endif