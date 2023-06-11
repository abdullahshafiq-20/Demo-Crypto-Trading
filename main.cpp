#include "User.h"
#include "Account_setting.h"
#include "Crypto.h"
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
int main()
{

    int opt, choice;
    char ch;
    string filename;
    string pass, username, password;

    cout << "----------- Welcome to CryptoCurrency Trading platform ------------" << endl;
move:
    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        User user;
        filename = user.login();
        if (user.is_logged_in() == 1)
        {
            goto jump;
        }
        else
        {
            goto move;
        }
    }
    break;
    case 2:
    {
        User user;
        user.signup();
        goto move;
    }
    break;
    case 3:
    {
        exit(0);
    }
    default:
        cout << "Invalid choice!" << endl;
    }
jump:
    do
    {
        cout << "1. View Market Data" << endl;
        cout << "2. Trade" << endl;
        cout << "3. View Trading History" << endl;
        cout << "4. Crypto Wallet" << endl;
        cout << "5. Account Settings" << endl;
        cout << "6. Help/FAQ" << endl;
        cout << "7. logout" << endl;
        cout << "Enter any option: ";
        cin >> opt;

        switch (opt)
        {
        case 1:
        {
            load_data();
            view_market_data();
        }
        break;
        case 2:
        {
            int option;
            load_data();
            do
            {
                cout << "1. Buy Crypto" << endl;
                cout << "2. Sell Crypto" << endl;
                cout << "3. Exit" << endl;
                cout << "Enter option number: ";
                cin >> option;

                switch (option)
                {
                case 1:
                {
                    buy_crypto(filename);
                    break;
                }
                case 2:
                {
                    sell_crypto(filename);
                    break;
                }
                case 3:
                {
                    goto jump;
                }
                default:
                    cout << "Invalid choice!" << endl;
                }
            } while (option != 3);
        }
        break;
        case 3:
        {
            Account_setting account;
            account.view_history(filename);
        }
        break;
        case 4:
        {
            crypto_wallet(filename);
        }
        break;
        case 5:
        {
            Account_setting account;
            int option;
            do
            {
                cout << "1. Change password\n";
                cout << "2. Change name\n";
                cout << "3. Change email\n";
                cout << "4. Change phone number\n";
                cout << "5. Add amount to balance\n";
                cout << "6. Display data\n";
                cout << "7. Exit\n";
                cout << "Enter option number: ";
                cin >> option;

                switch (option)
                {
                case 1:
                {
                    account.change_password(filename);
                    break;
                }
                case 2:
                {
                    account.change_name(filename);
                    break;
                }
                case 3:
                {
                    account.change_email(filename);
                    break;
                }
                case 4:
                {
                    account.change_phone(filename);
                    break;
                }
                case 5:
                {
                    account.add_balance(filename);
                    break;
                }
                case 6:
                {
                    account.display_data(filename);
                    break;
                }
                case 7:
                {
                    goto jump;
                    break;
                }
                default:
                    cout << "Invalid option!\n";
                }
            } while (option <= 7);
        }
        break;
        case 6:
        {
        }
        break;
        case 7:
        {
            goto move;
        }
        break;
        default:
            cout << "Invalid option" << endl;
        }
        cout << "Do you want to continue? (y/n) ";
        cin >> ch;
    } while (ch != 'n');

    return 0;
}