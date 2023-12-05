#include "User.h"
#include <sstream>
#include <wx/wx.h>

using namespace std;

User::User(string& username, string& password, int& age)
{
    this->username = username;
    this->password = password;
    this->age = age;
}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

int User::getAge() const
{
    return age;
}

void User::setAge(int newAge)
{
    age = newAge;
}

string User::displayUserInfo()
{
    return this->username + " " + this->password + " " + std::to_string(this->age);
}

int User::userAuthentication(const string& username, const string& password, int login) {
    ifstream file("UserDatabase.txt");
    string line;
    string decryptedName = User::encrypt(username);
    string decrypedPass = User::encrypt(password);
    while (getline(file, line)) {
        if (line.find(decryptedName) != string::npos && login == 0) {
            return 1;
        }
        if (line.find(decryptedName) != string::npos && line.find(decrypedPass) != string::npos) {
            file.close();
            return 2;
            
        }
    }
    file.close();
    return 0;
}

string User::encrypt(const string& data)
{
    string encrypted = data;
    for (char& c : encrypted)
    {
        c += 5;
    }
    return encrypted;
}

int User::encrypt(const int& data)
{
    int encrypted = data;
    encrypted = (encrypted + 7) % 10;
    return encrypted;
}

string User::decrypt(const string& data) {
    string decrypted = data;
    for (char& c : decrypted)
    {
        c -= 5;
    }
    return decrypted;
}

int User::decrypt(const int& data)
{
    int encrypted = data;
    encrypted = (encrypted + 3) % 10;
    return encrypted;
}

void User::createUser(const User& newUser) {
    ofstream file("UserDatabase.txt", ios::app);
    if (file.is_open()) {
        file << encrypt(newUser.getUsername()) << " " << encrypt(newUser.getPassword()) << " " << newUser.getAge() << "\n";
        file.close();
    }
    else {
        wxLogMessage("Error opening the database file.", "Error");
    }
}

std::vector<std::string> User::getUserData(const std::string& username) {
    std::vector<std::string> userData;
    ifstream file("UserData.csv");
    string line;
    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            std::string data;
            std::istringstream stream(line);
            while (getline(stream, data)) {
                userData.push_back(data);
            }
            file.close();
        }
    }
    file.close();
    return userData;
}