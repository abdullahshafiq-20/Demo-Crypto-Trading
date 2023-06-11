#include"Crypto.h"
#include"User.h"
using namespace std;
Crypto::Crypto(string n, string s, double p):name(n),symbol(s),price(p)
{
}

string Crypto::get_name() const
{
    return name;
}

string Crypto::get_symbol() const
{
    return symbol;
}

double Crypto::get_price() const
{
    return price;
}

vector<Crypto> cryptos;

void load_data()
{
    ifstream file("cryptos.txt");
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string name, symbol;
            double price;
            getline(iss, name, ',');
            getline(iss, symbol, ',');
            iss >> price;
            Crypto crypto(name, symbol, price);
            cryptos.push_back(crypto);
        }
        file.close();
    }
}

void view_market_data()
{
    for (const auto &crypto : cryptos)
    {
        cout << crypto.get_name() << " (" << crypto.get_symbol() << "): $" << crypto.get_price() << endl;
    } 
}

double get_balance(string filename)
{
    double balance;
    string line;
    ifstream file(filename + ".txt");
    if (file.is_open())
    {
        for (int i = 1; i <= 10; i++)
        {
            getline(file, line);
            if (i == 10)
            {
                balance = stod(line);
            }
        }
        file.close();
        return balance;
    }
    else
    {
        cout << "Error opening file!" << endl;
        return -1;
    }
}

void crypto_wallet(string filename)
{
    ifstream file(filename + ".txt");
    string line;
    vector<string> crp_names;
    vector<double> crp_amounts;
    vector<double> crp_prices;
    vector<string> lines;

    string crp_name;
    double crp_amount = 0;
    double crp_price = 0;
    int counter = 0;
    double total = 0;
    while (getline(file, line))
    {
        counter++;
        if (counter > 10)
        {
            istringstream iss(line);
            getline(iss, crp_name, '(');
            iss >> crp_amount;
            iss.ignore(3);
            iss >> crp_price;
            crp_names.push_back(crp_name);
            crp_amounts.push_back(crp_amount);
            crp_prices.push_back(crp_price);
        }
    }
    file.close();
    for (int i = 0; i < crp_names.size(); i++)
    {
        for (int j = i + 1; j < crp_names.size(); j++)
        {
            if (crp_names[i] == crp_names[j])
            {

                crp_amounts[i] += crp_amounts[j];
                crp_prices[i] += crp_prices[j];
                crp_amounts.erase(crp_amounts.begin() + j);
                crp_names.erase(crp_names.begin() + j);
                crp_prices.erase(crp_prices.begin() + j);
                j--;
            }
        }
    }
    for (int i = 0; i < crp_names.size(); i++)
    {
        if (crp_amounts[i] == 0)
        {
            crp_amounts.erase(crp_amounts.begin() + i);
            crp_names.erase(crp_names.begin() + i);
            crp_prices.erase(crp_prices.begin() + i);
        }
    }

    for (int i = 0; i < crp_names.size(); i++)
    {
        cout << i + 1 << "-" << crp_names[i] << " { " << crp_amounts[i] << " } " << endl;
        cout << "Total value is USDT: " << crp_prices[i] << endl;
        cout << endl;
    }
    for (int i = 0; i < crp_names.size(); i++)
    {
        total += crp_prices[i];
    }
    cout << "Total value of your wallet in USDT is : " << total << endl;
    ofstream write_file(filename + "_wallet.txt");
    if (write_file.is_open())
    {
        for (int i = 0; i < crp_names.size(); i++)
        {
            write_file << crp_names[i] + "(" << crp_amounts[i] << ") = " << crp_prices[i] << endl;
        }
        write_file.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }
}
void decuct_balance(string filename, double amount)
{
    vector<string> lines;
    string line;

    // Read all the lines from the file into a vector
    ifstream read_file(filename + ".txt");
    if (read_file.is_open())
    {
        while (getline(read_file, line))
        {
            lines.push_back(line);
        }
        read_file.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // Check if the file contains at least 10 lines
    if (lines.size() < 10)
    {
        cout << "File should contain at least 10 lines!" << endl;
        return;
    }

    // Extract the balance from the 10th line and add the specified amount
    double balance = stod(lines[9]);
    balance -= amount;

    // Update the balance in the 10th line of the file
    ofstream write_file(filename + ".txt");
    if (write_file.is_open())
    {
        for (int i = 0; i < lines.size(); i++)
        {
            if (i == 9)
            {
                write_file << fixed << setprecision(2) << balance << endl;
            }
            else
            {
                write_file << lines[i] << endl;
            }
        }
        write_file.close();
        // cout << "Balance added successfully! Current balance: " << balance << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }

}

void add_data_tofile(string filename, string cryptoname, double amount, double price, string nature)
{
    // Construct the line to add to the file
    string line = cryptoname + "(" + to_string(amount) + ") = " + to_string(price) + " : " + nature;
    // Read all the lines from the file into a vector
    vector<string> lines;
    string current_line;
    ifstream read_file(filename + ".txt");
    if (read_file.is_open())
    {
        while (getline(read_file, current_line))
        {
            lines.push_back(current_line);
        }
        read_file.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }

    // Insert the new line after the 10th line in the vector
    if (lines.size() >= 10)
    {
        lines.insert(lines.begin() + 10, line);
    }
    else
    {
        lines.push_back(line);
    }

    // Write the updated lines back to the file
    ofstream write_file(filename + ".txt");
    int counter = 0;
    if (write_file.is_open())
    {
        for (const string &line : lines)
        {

            write_file << line << endl;
        }
        write_file.close();
        cout << "Data added to file successfully!" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
        return;
    }

}

void buy_crypto(string filename)
{
    string name;
    cout << "Enter the name of the cryptocurrency you want to buy: ";
    cin >> name;
    bool found = false;
    for (const auto &crypto : cryptos)
    {
        if (crypto.get_name() == name)
        {
            found = true;
            double amount, usdt;
            cout << "Enter the amount you want to buy: ";
            cin >> amount;
            usdt = crypto.get_price() * amount;
            cout << "Buying " << amount << " " << crypto.get_symbol() << " will cost you " << usdt << " USDT." << endl;
            cout << "Do you want to confirm the purchase (Y/N)? ";
            char confirm;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                double balance = get_balance(filename);
                amount = amount * (+1);
                usdt = usdt * (+1);
                if (balance < usdt)
                {
                    cout << "You do not have enough balance to buy " << amount << " " << crypto.get_symbol() << "." << endl;
                    return;
                }
                add_data_tofile(filename, crypto.get_name(), amount, usdt, "buy");
                cout << "Purchase confirmed." << endl;
                deduct_balance(filename, usdt);
            }
            else
            {
                cout << "Purchase cancelled." << endl;
            }
            return;
        }
    }
    cout << "Could not find the cryptocurrency with the Name " << name << "." << endl;
}
void sell_crypto(string filename)
{
    crypto_wallet(filename);
    ifstream file(filename + "_wallet.txt");
    vector<string> lines;
    vector<double> f_crp_amounts;
    string line;
    double crp_amount = 0;
    while (getline(file, line))
    {
        istringstream iss(line);
        iss >> crp_amount;
        f_crp_amounts.push_back(crp_amount);
    }
    file.close();
    if (f_crp_amounts.size() == 0)
    {
        cout << "You do not have any cryptocurrencies to sell." << endl;
        return;
    }
    else
    {
        ifstream file(filename + "_wallet.txt");
        vector<string> lines;
        vector<string> f_crp_names;
        vector<double> f_crp_amounts;
        vector<double> f_crp_prices;
        string line;
        string crp_name;
        double crp_amount = 0;
        double crp_price = 0;
        while (getline(file, line))
        {
            istringstream iss(line);
            getline(iss, crp_name, '(');
            iss >> crp_amount;
            iss.ignore(3);
            iss >> crp_price;
            f_crp_names.push_back(crp_name);
            f_crp_amounts.push_back(crp_amount);
            f_crp_prices.push_back(crp_price);
        }
        file.close();
        string name;
        double amount, usdt;
        cout << "Enter the name of the cryptocurrency you want to sell: ";
        cin >> name;
        cout << "Enter the amount you want to sell: ";
        cin >> amount;

        for (int i = 0; i < f_crp_names.size(); i++)
        {
            if (f_crp_names[i] == name)
            {
                if (f_crp_amounts[i] < amount)
                {
                    cout << "You do not have enough balance to sell " << amount << " " << name << "." << endl;
                    return;
                }
                else
                {
                    usdt = amount * (f_crp_prices[i] / f_crp_amounts[i]);
                    cout << "Selling " << amount << " " << name << " will give you " << usdt << " USDT." << endl;
                    cout << "Do you want to confirm the sale (Y/N)? ";
                    char confirm;
                    cin >> confirm;
                    cout << "before";
                    // cout << f_crp_amounts[i] << endl;
                    // cout << f_crp_prices[i] << endl;
                    if (confirm == 'Y' || confirm == 'y')
                    {
                        if (f_crp_amounts[i] == 0)
                        {
                            f_crp_amounts.erase(f_crp_amounts.begin() + i);
                            f_crp_names.erase(f_crp_names.begin() + i);
                            f_crp_prices.erase(f_crp_prices.begin() + i);
                        }
                        amount = amount * (-1);
                        usdt = usdt * (-1);
                        add_data_tofile(filename, name, amount, usdt, "sell");
                        f_crp_amounts[i] -= amount;
                        f_crp_prices[i] -= usdt;
                        // cout << "after";
                        // cout << f_crp_amounts[i] << endl;
                        // cout << f_crp_prices[i] << endl;
                        ofstream file(filename + "_wallet.txt", ios::out);
                        if (file.is_open())
                        {
                            if (f_crp_names[i] == name)
                            {
                                file << f_crp_names[i] << "(" << f_crp_amounts[i] << ")" << f_crp_prices[i] << endl;
                            }
                            file.close();
                        }
                        else
                        {
                            cout << "Error opening file!" << endl;
                            return;
                        }
                        cout << "Sale confirmed." << endl;
                        ifstream read_file(filename + ".txt");
                        vector<string> lines;
                        string line;
                        while (getline(read_file, line))
                        {
                            lines.push_back(line);
                        }
                        read_file.close();
                        usdt = usdt * (-1);
                        double balance = stod(lines[9]);
                        balance += usdt;
                        lines[9] = to_string(balance);
                        ofstream write_file(filename + ".txt");
                        if (write_file.is_open())
                        {
                            for (int i = 0; i < lines.size(); i++)
                            {
                                write_file << lines[i] << endl;
                            }
                            write_file.close();
                        }
                    }
                    else
                    {
                        cout << "Sale cancelled." << endl;
                    }
                    return;
                }
            }
        }

        // for (int i=0; i<f_crp_names.size(); i++)
        // {
        //     cout << i+1 << ". " << f_crp_names[i] << " (" << f_crp_amounts[i] << ") = " << f_crp_prices[i] << endl;
        // }
    }
}








    
