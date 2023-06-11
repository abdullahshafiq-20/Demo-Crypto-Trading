#include "User.h"

using namespace std;

User::User()
{
    firstName = "";
    lastName = "";
    username = "";
    email = "";
    phoneNumber = "";
    password = "";
    creditCardNumber = "";
    expiry = "";
    cvv = "";
    balance = 0;
    logged_in = false;
}

bool User::is_logged_in()
{
    return logged_in;
}

void User::set_first_name(string firstName)
{
    this->firstName = firstName;
}

void User::set_last_name(string lastName)
{
    this->lastName = lastName;
}

void User::set_username(string username)
{
    this->username = username;
}

void User::set_email(string email)
{
    this->email = email;
}

void User::set_phone_number(string phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void User::set_password(string password)
{
    this->password = password;
}

void User::set_credit_card_number(string creditCardNumber)
{
    this->creditCardNumber = creditCardNumber;
}

void User::set_expiry(string expiry)
{
    this->expiry = expiry;
}

void User::set_cvv(string cvv)
{
    this->cvv = cvv;
}

void User::set_balance(double balance)
{
    this->balance = balance;
}

string User::get_first_name()
{
    return firstName;
}

string User::get_last_name()
{
    return lastName;
}

string User::get_username()
{
    return username;
}

string User::get_email()
{
    return email;
}

string User::get_phone_number()
{
    return phoneNumber;
}

string User::get_password()
{
    return password;
}

string User::get_credit_card_number()
{
    return creditCardNumber;
}

string User::get_expiry()
{
    return expiry;
}

string User::get_cvv()
{
    return cvv;
}

double User::get_balance()
{
    return balance;
}

string User::login()
{

    // Prompt user to enter username and password
    string username1, password1;
    cout << "Enter username: ";
    cin >> username1;
retry:
    cout << "Enter password: ";
    cin >> password1;
    set_password(password1);
    logged_in = false;

    // Check if user exists in file
    string filename = username1 + ".txt";
    ifstream file(filename, ios::in);
    if (file.good())
    {
        string line;
        string pass;
        while (!file.eof())
        {
            getline(file, line);
            if (line == username1)
            {
                while (getline(file, pass))
                {
                    if (pass == password1)
                    {
                        cout << "Login successful!" << endl;
                        load_account_info(username1);
                        logged_in = 1;
                        return username1;
                    }
                }
                if (logged_in == 0)
                {
                    int opt;
                    cout << "Incorrect password!" << endl;
                    cout << "press 1 to try again or 0 to exit" << endl;
                    cin >> opt;
                    if (opt == 1)
                    {
                        goto retry;
                    }
                    else
                    {
                        logged_in = 0;
                        break;
                    }
                }
            }
        }
        if (logged_in == 0)
        {
            cout << "Username does not exist!" << endl;
        }
        file.close();
    }
    else
    {
        cout << "User does not exist!" << endl;
        logged_in = 0;
    }
    return username1;
}

void User::signup()
{
    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter phone number: ";
    cin >> phoneNumber;
    cout << "Enter credit card number: ";
    cin >> creditCardNumber;
    cout << "Enter expiry: ";
    cin >> expiry;
    cout << "Enter CVV: ";
    cin >> cvv;
    cout << "Set password: ";
    cin >> password;
    cout << "Enter Amount You have in your bankAccount: ";
    cin >> balance;

    // Save user information to file
    string filename = username + ".txt";
    ofstream file(filename, ios_base::app);
    file << firstName << endl;
    file << lastName << endl;
    file << username << endl;
    file << email << endl;
    file << phoneNumber << endl;
    file << creditCardNumber << endl;
    file << expiry << endl;
    file << cvv << endl;
    file << password << endl;
    file << balance;
    file.close();

    cout << "Signup successful!" << endl;
}

void User::load_account_info(string user)
{
    string filename = user + ".txt";
    ifstream file(filename, ios::in);
    string line;
    if (file.good())
    {
        while (!file.eof())
        {
            getline(file, firstName);
            getline(file, lastName);
            getline(file, username);
            getline(file, email);
            getline(file, phoneNumber);
            getline(file, creditCardNumber);
            getline(file, expiry);
            getline(file, cvv);
            getline(file, password);
            file >> balance;
            break;
        }
        file.close();
    }
}


