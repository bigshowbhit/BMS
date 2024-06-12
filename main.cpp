#include "db_Management.h"
#include"Authentication.h"
#include<tuple>
#include <cstdlib>  // Include for srand and rand
#include <ctime>    // Include for time
#include"customer.h"

int main()
{
    std::srand(std::time(nullptr));  // Use current time as seed for random generator;
    std::string cust_username, manager_username, governor_username;
    std::string cust_password, manager_password, governor_password;
    
    db_Management db;
    customer cust("07876", "Shobhit", "shobhit@gmail.com", "36703223465", "Budapest");
    
    // Load accounts from file into customer's accounts vector
    db.loadAccountsFromFile(cust.getAccounts()); 
    
    // Display welcome message
    std::cout << "Welcome to the Banking System" << std::endl;
    
    while (true) {  // Continuous loop to allow re-selection if needed
        std::cout << "\nLogin Screen" << std::endl;
        std::cout << "Please select your role:" << std::endl;
        std::cout << "1. Customer" << std::endl;
        std::cout << "2. Bank Manager" << std::endl;
        std::cout << "3. Central Bank Governor" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice (1-4): ";

        int choice;
        std::cin >> choice;  // Get user input

        std::tuple<bool, std::string> result;
        std::tuple<bool, std::string> result2;
        //std::tuple<bool, std::string> result3 = Authentication::login(governor_username, governor_password);

        // Respond to user input
        switch (choice) {
            case 1:
                system("clear");
                std::cout << "Welcome, Customer!" << std::endl;

                std::cout<<"Enter the username: "<<std::endl;
                std::cin>>cust_username;

                std::cout<<"Enter the password for customer: "<<std::endl;
                std::cin>>cust_password;
                
                result = Authentication::login(cust_username, cust_password);

                if (std::get<0>(result))    // Check login success
                {   
                    std::cout << "Login successful! Role: " << std::get<1>(result) << std::endl;
                    cust.menuPrint(); 

                }
                else
                {
                    std::cerr << "Login failed, please check your username and password." << std::endl;
                }
                break;

            case 2:
                system("clear");
                std::cout << "Welcome, Bank Manager!" << std::endl;

                std::cout<<"Enter the username: "<<std::endl;
                std::cin>>manager_username;

                std::cout<<"Enter the password for Bank Manager: "<<std::endl;
                std::cin>>manager_password;
                
                result2 = Authentication::login(manager_username, manager_password);

                if (std::get<0>(result2))    // Check login success
                {   
                    std::cout << "Login successful! Role: " << std::get<1>(result2) << std::endl;
                    //Print bank manager methods here
                }
                else
                {
                    std::cerr << "Login failed, please check your username and password." << std::endl;
                }
                break;

            // case 3:
                
            //     system("clear");
            //     std::cout << "Welcome, Central Bank Governor!" << std::endl;

            //     std::cout<<"Enter the username: "<<std::endl;
            //     std::cin>>governor_username;

            //     std::cout<<"Enter the password for Central Bank Governor: "<<std::endl;
            //     std::cin>>governor_password;

            //     if (std::get<0>(result3))    // Check login success
            //     {   
            //         std::cout << "Login successful! Role: " << std::get<1>(result3) << std::endl;
            //         //Print bank manager methods here
            //     }
            //     else
            //     {
            //         std::cerr << "Login failed, please check your username and password." << std::endl;
            //     }
            //     break;

            case 4:
            {
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                return 0;  // Exit the loop and end the program
            }    

            default:
                std::cout << "Invalid choice, please try again." << std::endl;
                break;
        }
    }




    return 0;
}