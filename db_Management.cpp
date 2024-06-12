#include<iostream>
#include<fstream>
#include<sstream>
#include"customer.h"
#include"SavingsAccount.h"
#include"db_Management.h"

//initialization of lastCustomerId as it is static
int db_Management::lastCustomerId = db_Management::loadCustomerId();


std::vector<std::tuple<std::string, std::string, std::string>> db_Management::readUser(const std::string& filename)
{
    std::vector<std::tuple<std::string, std::string, std::string>> users;
    std::ifstream readFromFile(filename);
    if (!readFromFile) 
    {
        std::cerr << "Failed to open file." << std::endl;
        return users;  // Return empty vector if file cannot be opened
    }
    std::string line;

    try
    {
        while(std::getline(readFromFile, line)) 
        {
            std::istringstream ss(line);    //it uses istringstream to parse the line to ss into 3 strings
            std::string user, pass, role;

            if(!(ss>>user, ss>>pass, ss>>role)) 
            {
                std::cerr << "Parsing failed for line: " << line << std::endl;
                continue;   // Skip to next iteration on failure to extract all three
            }

            users.push_back(std::make_tuple(user, pass, role)); //pushes the newly made tuple into the vector
        }
    }
    catch (const std::ios_base::failure& e) 
    {
        // Handle input/output errors
        std::cerr << "I/O error while reading file: " << e.what() << std::endl;
    } 
    catch (const std::exception& e) 
    {
        // Handle all other exceptions
        std::cerr << "An error occurred: " << e.what() << std::endl;
    } 
    catch (...) 
    {
        // Catch-all handler for any other exceptions
        std::cerr << "An unknown error occurred." << std::endl;
    }
    
return users;   //return vector of tuples which contains 3 strings - userName, password and the userRole. 
  
}

bool db_Management::updateUser(const std::string& username, const std::string& newPassword, const std::string& userRole)
{
    auto users = readUser("Authentication.txt");
    bool updated = false;

    std::ofstream outfile;
    outfile.open("Authentication.txt");

    if(!(outfile.is_open()))
    {
        std::cerr<<"File cannot be opened for updating the credentials\n";
        return false;
    } 

    //Remaking the user tuple list with the updated credentials
    for(auto& user: users)
    {
        if(std::get<0>(user)==username)
        {
            user = make_tuple(username, newPassword, std::get<2>(user));
            updated = true;
        }

        //write agin into the file
        outfile<<std::get<0>(user)<<"    "<<std::get<1>(user)<<"    "<<std::get<2>(user)<<std::endl;
    }
    outfile.close();
    
    return updated;
}

int db_Management::loadCustomerId() {
    std::ifstream inFile("lastCustomerId.txt");
    if (inFile >> lastCustomerId) 
    {
        return lastCustomerId;
        inFile.close();
    } else {
        lastCustomerId = 1000;  // Default start ID if file is not found or is unreadable
    }
    return lastCustomerId;
}

void db_Management::saveCustomerId() {
    std::ofstream outFile("lastCustomerId.txt");    //we are opening it in writing mode as we dont have to deal with the old cust id's, only the latest one shoould persist.
    if (outFile) 
    {
        outFile << lastCustomerId;
        outFile.close();
    }
     else 
    {
        // Handle the case where the file could not be opened
        std::cerr << "Failed to save the last customer ID to file." << std::endl;
    }
}

int db_Management::generateCustomerId()
{
    lastCustomerId++;   //increment the last customer id.
    saveCustomerId();  // Save the new ID back to the file

    return lastCustomerId;
}

bool db_Management::writeAccountToFile(const std::string& accountNumber, const double initialBalance, const float interest, const std::string& bankName)
{
    // std::string s1;
    // std::cout<<"\nEnter your Customer ID: ";
    // std::cin>>s1;
    int custId = db_Management::generateCustomerId();
   
    std::ofstream outFile("savingsAccount.txt", std::ios::app);  // Open the file in append mode

        if (!outFile) 
        {
            std::cerr << "Unable to open file for writing." << std::endl;
            return false;
        }

        outFile << custId <<" "<< accountNumber <<" "<< initialBalance << " "<<interest<<" "<<bankName<<"\n";
        outFile.close();

        return true;
}

std::vector<std::tuple<std::string, std::string, double, float, std::string>> db_Management::updateAccountToFile(const std::string& filename, const std::string& accountNumber)
{
    std::ifstream infile;
    infile.open(filename); 
    std::vector<std::tuple<std::string, std::string, double, float, std::string>> readFromFile, updatedAccounts;
    std:: string line;
    
    while(getline(infile, line))
    {
        std::istringstream ss(line);
        std::string custId, account_number, bankName;
        double balance;
        float interest;
        
        ss >> custId >> account_number >> balance >> interest >> bankName;
        //std::cout << custId << account_number << balance << interest << std::endl; -> for debugging
        
        if(ss.fail())
        {
            std::cerr<<"Parsing failed for line: "<< line <<std::endl;
            continue;
        }
        
        // Only add to the vector if it's not the account to remove
        if (account_number != accountNumber) 
        {
            updatedAccounts.push_back(std::make_tuple(custId, account_number, balance, interest, bankName));
        }
    }    
    infile.close();
    
        //now reopen the file in write mode and fill the file with the data stored in the vector!
        std::ofstream outfile(filename); // Open file in truncate mode to rewrite it completely
        if (!outfile) 
        {
            std::cerr << "Failed to open the accounts file for writing." << std::endl;
            return updatedAccounts; // Return the updated list even if file writing fails
        }

        for (const auto& account : updatedAccounts) {
            outfile << std::get<0>(account) << " "
                    << std::get<1>(account) << " "
                    << std::get<2>(account) << " "
                    << std::get<3>(account) << " "
                    << std::get<4>(account) << std::endl;
        }
        outfile.close();
    
    return updatedAccounts; //returns the updatedAccount list without the account number that was passed!
}

bool db_Management::loadFromFile(std::string& filename, std::string& accountNumber)
{
    std::ifstream infile;
    infile.open(filename); 
    std::vector<std::tuple<std::string, std::string, double, float, std::string>> readFromFile;
    std:: string line;
    
    while(getline(infile, line))
    {
        std::istringstream ss(line);
        std::string custId, account_number, bankName;
        double balance;
        float interest;
        
        ss >> custId >> account_number >> balance >> interest >> bankName;
        
        if(ss.fail())
        {
            std::cerr<<"Parsing failed for line: "<< line <<std::endl;
            continue;
        }
        readFromFile.push_back(std::make_tuple(custId, account_number, balance, interest, bankName));
    }    
        
        for(const auto& acc : readFromFile)
        {
            if(std::get<1>(acc)==accountNumber)
            {
                return true;
            }
        }
   return false;
}

void db_Management::printStatement(const std::string& fileName)
{
    std::ifstream file(fileName);
    
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
        std::string line;
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
}

bool db_Management::recordTransaction(const std::string& filename, const std::string& accountNumber, double amount, const std::string& type)
{
    std::ofstream out(filename, std::ios::app); // Opening the file in append mode
        
        if (!out) 
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return false;
        }
        out << type <<"  "<< accountNumber <<"  "<< getCurrentDate() << "  "<< amount << std::endl;
        out.close();
        return true;
    
}

void db_Management::loadAccountsFromFile(std::vector<SavingsAccount*>& accounts) {
    std::ifstream inFile("savingsAccount.txt");
    if (!inFile) {
        std::cerr << "Failed to open savings account file for reading." << std::endl;
        return;
    }
    std::string line;
    while (getline(inFile, line)) {
        std::istringstream iss(line);
        std::string custId, accountNo, bankName;
        double balance;
        float interest;
        if (!(iss >> custId >> accountNo >> balance >> interest >> bankName)) {
            continue;  // handle error or malformed line
        }
        //DMA used
        accounts.push_back(new SavingsAccount(custId, accountNo, balance, interest, bankName));
    }
    inFile.close();
}