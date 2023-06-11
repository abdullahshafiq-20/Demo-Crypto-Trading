#pragma once

#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>

using namespace std;

class Account_setting : public User
{

private:
    string filename;

public:
    void change_password(string filename);
    void change_name(string filename);
    void change_email(string filename);
    void change_phone(string filename);
    void add_balance(string filename);
    void view_history(string filename);
    void display_data(string filename);

};
