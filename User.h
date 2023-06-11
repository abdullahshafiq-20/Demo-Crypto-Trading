
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#pragma once
using namespace std;
class User
{
private:
    string firstName;
    string lastName;
    string username;
    string email;
    string phoneNumber;
    string password;
    string creditCardNumber;
    string expiry;
    string cvv;
    double balance;

public:
    bool logged_in;
    User();
    bool is_logged_in();
    void set_first_name(string firstName);
    void set_last_name(string lastName);
    void set_username(string username);
    void set_email(string email);
    void set_phone_number(string phoneNumber);
    void set_password(string password);
    void set_credit_card_number(string creditCardNumber);
    void set_expiry(string expiry);
    void set_cvv(string cvv);
    void set_balance(double balance);
    string get_first_name();
    string get_last_name();
    string get_username();
    string get_email();
    string get_phone_number();
    string get_password();
    string get_credit_card_number();
    string get_expiry();
    string get_cvv();
    double get_balance();
    string login();
    void signup();
    void load_account_info(string user);
};
