#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class User {

private:

    int stresslvl = 0;
    int depresslvl = 0;
    int anxietylvl = 0;

public:
    std::string username;
    std::string password;
    int age;
    User(std::string& username, std::string& password, int& age);
    std::string getUsername() const;
    std::string getPassword() const;
    int getAge() const;
    void setAge(int newAge);

    // Display user information
    std::string displayUserInfo();
    static int userAuthentication(const std::string& username, const std::string& password, int login);
    static std::string encrypt(const std::string& data);
    int encrypt(const int& data);
    static std::string decrypt(const std::string& data);
    int decrypt(const int& data);
    void createUser(const User& newUser);
    static std::vector<std::string> getUserData(const std::string& username);



    
};

