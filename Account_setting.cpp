#include "Account_setting.h"
#include"User.h"
using namespace std;
void Account_setting::change_password(string filename)
{
    string prev_password;
    int count = 0;
    char ch1;

retry1:
    cout << "Enter previous password: ";
    cin >> prev_password;

    string current_password;
    vector<string> lines;

    fstream file(filename + ".txt", ios::in);
    if (file.fail())
    {
        cout << "Error opening file!\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
        if (lines.size() == 9)
        {
            current_password = line;
        }
    }
    file.close();

    cout << "current: " << current_password << endl;
    if (prev_password == current_password)
    {
        string new_pass;
        cout << "Enter new password: ";
        cin >> new_pass;

        lines[8] = new_pass;

        fstream file(filename + ".txt", ios::out | ios::trunc);
        if (file.fail())
        {
            cout << "Error opening file!\n";
            return;
        }

        for (int i = 0; i < lines.size(); i++)
        {
            file << lines[i] << endl;
        }
        file.close();

        set_password(new_pass);
        cout << "Password changed successfully!\n";
    }
    else
    {
        count++;
        cout << "Previous password does not match!\n";
        if (count < 3)
        {
            goto retry1;
        }
        else
        {
            cout << "You have entered the wrong password 3 times. Please try again later\n";
        }
    }
}

void Account_setting::change_name(string filename)
{
    string new_firstname, new_lastname;
    cout << "Enter new first name: ";
    cin >> new_firstname;
    cout << "Enter new last name: ";
    cin >> new_lastname;
    set_first_name(new_firstname);
    set_last_name(new_lastname);
    // Read the existing data from the file
    fstream read_file(filename + ".txt", ios::in);
    if (read_file.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(read_file, line))
        lines.push_back(line);

    read_file.close();

    // Write the new data to the file
    fstream write_file(filename + ".txt", ios::out | ios::trunc);
    if (write_file.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }

    // Write the new first name to the first line
    write_file << new_firstname << endl;

    // Write the new last name to the second line
    write_file << new_lastname << endl;

    // Copy the remaining lines from the vector to the file
    for (int i = 2; i < lines.size(); i++)
        write_file << lines[i] << endl;

    write_file.close();

    cout << "Name changed successfully!\n";
}

void Account_setting::change_email(string filename)
{
    string new_email;
    cout << "Enter new email: ";
    cin >> new_email;
    set_email(new_email);

    fstream read_file(filename + ".txt", ios::in);
    if (read_file.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(read_file, line))
        lines.push_back(line);

    read_file.close();

    if (lines.size() < 4)
    {
        cout << "Error: File does not have at least 4 lines." << endl;
        return;
    }
    lines[3] = new_email;

    fstream write_file(filename + ".txt", ios::out | ios::trunc);
    if (write_file.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }

    for (int i = 0; i < lines.size(); i++)
        write_file << lines[i] << endl;

    write_file.close();

    cout << "Email changed successfully!\n";
}

void Account_setting::change_phone(string filename)
{
    string new_phone;
    cout << "Enter new phone number: ";
    cin >> new_phone;

    fstream read_file(filename + ".txt", ios::in);
    if (read_file.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }

    vector<string> lines;
    string line;
    while (getline(read_file, line))
        lines.push_back(line);

    read_file.close();

    if (lines.size() < 5)
    {
        cout << "Error: File does not have at least 4 lines." << endl;
        return;
    }
    lines[4] = new_phone;

    fstream write_file(filename + ".txt", ios::out | ios::trunc);
    if (write_file.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }
    for (int i = 0; i < lines.size(); i++)
        write_file << lines[i] << endl;

    write_file.close();

    cout << "Phone Number changed successfully!\n";
}

void Account_setting::add_balance(string filename)
{
    // Read the account information from the file into a vector
    vector<string> lines;
    ifstream read_file(filename + ".txt");
    if (read_file.is_open())
    {
        string line;
        while (getline(read_file, line))
        {
            lines.push_back(line);
        }
        read_file.close();
    }
    else
    {
        cout << "Error opening file!\n";
        return;
    }

    // Get the current balance from the vector and update it with user input

    double balance = stod(lines[9]);
    cout << "Current balance: " << balance << endl;
    double amount;
    cout << "Enter the amount to add: ";
    cin >> amount;
    balance += amount;
    // Update the balance in the vector and write the new information to the file

    lines[9] = to_string(balance);

    ofstream write_file(filename + ".txt");
    if (write_file.is_open())
    {
        for (int i = 0; i < lines.size(); i++)
        {
            write_file << lines[i] << endl;
        }
        write_file.close();
        cout << "Balance added successfully! New balance: " << balance << endl;
    }
    else
    {
        cout << "Error opening file!\n";
    }
}

void Account_setting::view_history(string filename)
{
    int counter = 0;
    int counter1 = 1;
    ifstream file(filename + ".txt");
    string line;
    while (getline(file, line))
    {
        counter++;
        if (counter > 10)
        {
            cout << counter1 << "-" << line << endl;
            counter1++;
        }
    }
}

void Account_setting::display_data(string filename)
{
    string firstName1;
    string lastName1;
    string username1;
    string email1;
    string phoneNumber1;
    string password1;
    string creditCardNumber1;
    string expiry1;
    string cvv1;
    double balance1;
    string file = filename + ".txt";
    ifstream read(file, ios::in);
    string line;
    while (!read.eof())
    {
        getline(read, firstName1);
        getline(read, lastName1);
        getline(read, username1);
        getline(read, email1);
        getline(read, phoneNumber1);
        getline(read, creditCardNumber1);
        getline(read, expiry1);
        getline(read, cvv1);
        getline(read, password1);
        read >> balance1;
        break;
    }
    set_first_name(firstName1);
    set_last_name(lastName1);
    set_username(username1);
    set_email(email1);
    set_phone_number(phoneNumber1);
    set_credit_card_number(creditCardNumber1);
    set_expiry(expiry1);
    set_cvv(cvv1);
    set_password(password1);
    set_balance(balance1);

    cout << "First name: " << get_first_name() << endl;
    cout << "Last name: " << get_last_name() << endl;
    cout << "Username: " << get_username() << endl;
    cout << "Email: " << get_email() << endl;
    cout << "Phone number: " << get_phone_number() << endl;
    cout << "Credit card number: " << get_credit_card_number() << endl;
    cout << "Expiry: " << get_expiry() << endl;
    cout << "CVV: " << get_cvv() << endl;
    cout << "Password: " << get_password() << endl;
    cout << "Balance: " << get_balance() << endl;

    read.close();
}