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

class Crypto : public User
{
private:
    string name;
    string symbol;
    double price;

public:
    Crypto(string n, string s, double p);

    string get_name() const;
    string get_symbol() const;
    double get_price() const;
};

extern vector<Crypto> cryptos;

void load_data();
void view_market_data();
double get_balance(string filename);
void crypto_wallet(string filename);
void deduct_balance(string filename, double amount);
void add_data_tofile(string filename, string cryptoname, double amount, double price, string nature);
void buy_crypto(string filename);
void sell_crypto(string filename);
