#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include<iostream>
#include<string>

class Authentication {
private:
    static std::string userName;
    static std::string password;
    static std::string userRole; // Member to store the user's role

    public:

    static std::tuple<bool, std::string> login(const std::string& username, const std::string& password);

    // static void logout();

    // static bool resetPassword(const std::string& oldPassword, const std::string& newPassword);

    // std::string getRole()   // Method to get the user's role
    // {
    //     return userRole;
    // } 
};

#endif