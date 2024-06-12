#include"Authentication.h"
#include<iostream>
#include"db_Management.h"



// //Static Member initialization
// std::string Authentication::userName = "";
// std::string Authentication::password = "";
// std::string Authentication::userRole = "";

std::tuple<bool, std::string> Authentication::login(const std::string& username, const std::string& password) {
    try {
        std::string filename = "Authentication.txt";
        db_Management db(filename);
        std::vector<std::tuple<std::string, std::string, std::string>> users = db.readUser(filename); // Attempt to read user data
        

        for (const auto& user : users) {
            if (std::get<0>(user) == username && std::get<1>(user) == password) {
                return std::make_tuple(true, std::get<2>(user)); // Return true and role
            }
        }
        return std::make_tuple(false, ""); // Login failed
    } 

    catch (const std::exception& e) 
    {
        std::cerr << "An error occurred during login: " << e.what() << std::endl;
        return std::make_tuple(false, ""); // Return failure with an error message
    } 
    
    catch (...) 
    {
        std::cerr << "An unknown error occurred during login." << std::endl;
        return std::make_tuple(false, ""); // Return failure for unspecified exceptions
    }
}

// void Authentication::logout() 
// {
//     userName.clear();
//     password.clear();
//     userRole.clear();
// }

// bool Authentication::resetPassword(const std::string& oldPassword, const std::string& newPassword)
// {
//     if(password == oldPassword)
//     {
//         //updating in the memory
//         password = newPassword;

//         //now updating it in the database as well

//         db_Management db;
//         if(db.updateUser(userName, password, userRole))
//         {
//             return true;
//         }
//         else{
//             password = oldPassword; //if the updation fails then it gets back to the old password.
//             return false;
//         }
//     }
//     return false; //oldpassword that is current password does not match
// }

