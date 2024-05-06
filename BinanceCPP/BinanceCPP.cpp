
#include <iostream>
#include <string>
#include <vector>
#include<unordered_map>
#include <random>
using namespace std;

// криптовалюта имеет название, тикер, цену, количество, такжже френд класс бинанс
// у валюты можно получить название, тикер, цену и количество
class CryptoCurrency {
    friend Binance;
private:    
    string title;
    string ticker;
    double price;
    double amount;
public:
    CryptoCurrency(string title, string ticker, double price, double amount = 0):
    title(title), ticker(ticker), price(price), amount(amount) {}

    double getPrice() {
        return this->price;
    }

    string getTitle() {
        return this->title;
    }

    string getTicker() {
        return this->ticker;
    }

    void buyMe(double amount) {
        this->amount -= amount;
    }

};

// пользователь у него есть имя, его страна, почта, уникальный адрес, личный счет в валюте его страны, крипта
// пользователь может: пополнить баланс, обналичить баланс, узнать баланс личного счета, узнать баланс крипты
class User {
public:
    User(string login, string password, string name, string country, string email) :
        login(login), password(password), name(name), country(country), email(email) {
        // рандом генерация уникального адреса пользователя
    }

    User() {}

    string getAddress() {
        return this->address;
    }

    double getBalance() {
        return this->balance;
    }

    string getAddress() {
        this->address;
    }

    double getCurrenciesBalance() {
        // красивый вывод всех валют пользователя со стоимостью и общим балансом
    }

    void deposit(double amount) {
        this->balance += amount;
    }

    void withdraw(double amount) {
        this->balance -= amount;
    }

private:
    string login;
    string password;
    string name;
    string country;
    string email;
    string address;
    double balance;
    unordered_map<CryptoCurrency, double> currencies;
};


// для работы за пользователя нужно авторизоваться: пользователь может пополнять, снимать крипту себе на счет
class Binance {
public:
    bool LogIn(User& who) {
        if (balances.find(who) == balances.end()) {
            balances[who][availableCurrencies[0]] =  0;
            return true;
        }
        cout << "Y`ve already registered";
        return false;
    }

    void authorizeOnMe(User& who) {
        this->user = who;
    }

    void deposit(double amount) {
        // попытка пополнить баланс на бинансе
    }

    void withdraw() {
        // вывод средств на баланс пользователя
    }

    void addNewCurrency(CryptoCurrency& currency) {
        this->availableCurrencies.push_back(currency);
    }

    void buyCurrency(CryptoCurrency& currency, User& by) {
        // покупка пользователем крипты - запись в его крипту по адресу
    }

    pair<double, double> getBalance(User& by) {
        double usdt = balances[by][availableCurrencies[0]];
        double sum;
        for (const auto& pair : balances[by]) {
            sum += pair.second;
        }
        return make_pair(usdt, sum - usdt);
    }

    Binance(vector<CryptoCurrency> availableCurrencies) {
        this->availableCurrencies.insert(this->availableCurrencies.end(), availableCurrencies.begin(), availableCurrencies.end());
    }

private:
    const double ruToUS = 96.5;
    User user;
    vector<CryptoCurrency> availableCurrencies = { CryptoCurrency("USDT", "USDT", 1.0) };
    vector<string> availableCountries = { "RU", "US" };
    unordered_map<User, unordered_map<CryptoCurrency, double>> balances;
};

int main()
{
    vector<User> users;
    User user;
    CryptoCurrency BTC("Bitcoin", "BTC", 66000.0, 20000.0);
    CryptoCurrency ETH("Ethereumm", "ETH", 3700.0, 20000.0);
    CryptoCurrency ARB("Arbitrum", "ARB", 1.1, 20000.0);
    CryptoCurrency OP("Optimism", "OP", 2.9, 20000.0);
    Binance binance({ BTC, ETH, ARB, OP });
    string answer;
    // Доделать так чтобы можно было использовать все функции 
    while (true) {
        cout << "Welcome!!\nMy commands:\n1 - Create new User\n2 - Log in Binance\nSign in Binance\n4 - Exit";
        cin >> answer;
        if (answer == "1") {
            cout << "";
        }
        else if (answer == "2") {
            if (user.getAddress() != "") {
                bool registered = binance.LogIn(user);
                if (registered) {

                }
            }
            else {
                cout << "Before it u`ve to create user";
            }
        }
        else if (answer == "3") {
            cout << "Hello in binance\nWhat do u want do?\n1 - deposit\n2 - withdraw\n3 - buy any currency\n4 - exit";
            cin >> answer;
            if (answer == "1") {

            }
            else if (answer == "2") {

            }
            else if (answer == "3") {

            }
            else if (answer == "4") {

            }
        }
        else if (answer == "4") {
            cout << "Bye! See u later!";
            break;
        }
        else {
            cout << "I don`t know what do u meen(";
        }
    }
}

