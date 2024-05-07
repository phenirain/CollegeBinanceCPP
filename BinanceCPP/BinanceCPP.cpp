
#include <iostream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// криптовалюта имеет название, тикер, цену, количество, такжже френд класс бинанс
// у валюты можно получить название, тикер, цену и количество
class CryptoCurrency {
private:    
    string title;
    string ticker;
    double price;
    double amount;
public:
    CryptoCurrency(string title, string ticker, double price, double amount = 0) {
        this->title = title;
        this->ticker = ticker;
        this->price = price;
        this->amount = amount;
    }

    ~CryptoCurrency() {
    }

    double getPrice() {
        return price;
    }

    string getTitle() {
        return title;
    }

    string getTicker() {
        return ticker;
    }

    double getAmount() {
        return amount;
    }

    void buyMe(double amount) {
        this->amount -= amount;
    }
    bool operator<(const CryptoCurrency& other) const {
        return price < other.price;
    }

   /* bool operator==(const CryptoCurrency& other) const {
        return (title == other.title && ticker == other.ticker && price == other.price && amount == other.amount);
    }*/



};

// пользователь у него есть имя, его страна, почта, уникальный адрес, личный счет в валюте его страны, крипта
// пользователь может: пополнить баланс, обналичить баланс, узнать баланс личного счета, узнать баланс крипты
class User {
public:
    User(string& login, string& password, string& country){
        this->login = login;
        this->password = password;
        this->country = country;
    }

    bool operator<(const User& other) const {
        return login < other.login; 
    }

    ~User() {
    }

    User() {}

    double getBalance() {
        return balance;
    }

    string getCountry() {
        return country;
    }

    string getLogin() {
        return login;
    }

    double getCurrenciesBalance() {
        for (auto& pair : currencies) {
            CryptoCurrency currency = pair.first;
            cout << "Currency: " << currency.getTitle() << "Amount: " << pair.second << endl;
        }
    }

    void depositCurrencies(CryptoCurrency& currency, double amount) {
        if (currencies.find(currency) == currencies.end()) {
            currencies[currency] = amount;
        }
        else currencies[currency] += amount;
        cout << "Succesfully deposit\n";
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Succesfully deposit\n";
    }

    void withdraw(double amount) {
        balance -= amount;
        cout << "Succesfully withdraw\n";
    }

private:
    string login;
    string password;
    string country;
    double balance;
    map<CryptoCurrency, double> currencies;
};


// для работы за пользователя нужно авторизоваться: пользователь может пополнять, снимать крипту себе на счет
class Binance {
public:
    bool LogIn(User& who) {
        if (find(availableCountries.begin(), availableCountries.end(), who.getCountry()) != availableCountries.end()) {
            if (balances.find(who) == balances.end()) {
                balances[who][availableCurrencies[0]] = 0;
                return true;
            }
            cout << "Y`ve already registered\n";
            return false;
        }
        else {
            cout << "Your country is banned\n";
            return false;
        }
    }

    bool authorizeOnMe(User& who) {
        if (balances.find(who) != balances.end()) {
            cout << "Successfully authorization\n";
            return true;;
        }
        cout << "Y`re not registered\n";
        return false;
    }

    bool deposit(User& by) {
        double amount;
        cout << "Amount to deposit: ";
        cin >> amount;
        string country = by.getCountry();
        if (country == "RU") {
            amount = amount * ruToUS;
        }
        double balance = by.getBalance();
        if (balance >= amount) {
            if (country == "US") {
                balances[by][availableCurrencies[0]] += amount;
            }
            else {
                balances[by][availableCurrencies[0]] += amount / ruToUS;
            }
            by.withdraw(amount);
            cout << "Succesfully deposit\n";
            getBalance(by);
            return true;
        }
        else {
            cout << "Insufficient funds\n";
            return false;
        }
        // попытка пополнить баланс на бинансе
    }

    bool withdraw(User& by, CryptoCurrency& currency) {
        double amount;
        cout << "Amount: ";
        cin >> amount;
        if (balances[by][currency] >= amount) {
            by.depositCurrencies(currency, amount);
            return true;
        }
        else {
            cout << "Insufficient funds\n";
            return false;
        }
        // вывод средств на баланс пользователя
    }

    void addNewCurrency(CryptoCurrency& currency) {
        availableCurrencies.push_back(currency);
    }

    bool buyCurrency(User& by) {
        while (true) {
            int i = 0;
            double amount;
            for (auto& currency : availableCurrencies) {
                cout << i << ". Currency: " << currency.getTitle() << " Price: " << currency.getPrice() << " Amount: " << currency.getAmount() << endl;
                i++;
            }
            cout << "Amount: ";
            cin >> amount;
            CryptoCurrency currency = availableCurrencies[i - 1];
            double currencyAmount = currency.getAmount();
            double price = currency.getPrice();
            if (currencyAmount <= amount) {
                if (price * amount <= balances[by][availableCurrencies[0]]) {
                    balances[by][currency] = amount;
                    balances[by][availableCurrencies[0]] -= price * amount;
                    currency.buyMe(amount);
                    cout << "Succesfully purchase\n";
                    return true;
                }
                else {
                    cout << "Insufficient funds\n";
                    return false;
                }
            }
            /*cout << "To exit write: " << i << endl;
            if (find(availableCurrencies.begin(), availableCurrencies.end(), availableCurrencies[i]) == availableCurrencies.end()) {
                cout << "Limit exceeded\n";
                return false;
                }
                else {
                    cout << "Amount: ";
                    cin >> amount;
                    CryptoCurrency currency = availableCurrencies[i - 1];
                    double currencyAmount = currency.getAmount();
                    if (currencyAmount <= amount) {
                        if (currency.getPrice() * amount <= balances[by][availableCurrencies[0]]) {
                            balances[by][currency] = amount;
                            double price = currency.getPrice();
                            balances[by][availableCurrencies[0]] -= price * amount;
                            currency.buyMe(amount);
                            cout << "Succesfully purchase\n";
                            return true;
                        }
                        else {
                            cout << "Insufficient funds\n";
                            return false;
                        }
                    }*/
            }
        }
        // покупка пользователем крипты - запись в его крипту по адресу

    vector<CryptoCurrency> getBalance(User& by) {
        double usdt = balances[by][availableCurrencies[0]];
        double sum;
        vector<CryptoCurrency> currencies;
        int i = 1;
        for (auto& pair : balances[by]) {
            CryptoCurrency currency = pair.first;
            cout << i << ". Currency: " << currency.getTicker() << "Amount: " << pair.second << endl;
            i++;
            currencies.push_back(currency);
        }
        cout << "to exit write: " << i << endl;
        return currencies;
    }

    Binance(vector<CryptoCurrency> availableCurrencies) {
        this->availableCurrencies.insert(this->availableCurrencies.end(), availableCurrencies.begin(), availableCurrencies.end());
    }

    ~Binance() {
    }

    vector<CryptoCurrency> getAvailables() {
        return availableCurrencies;
    }

private:
    const double ruToUS = 96.5;
    vector<CryptoCurrency> availableCurrencies = { CryptoCurrency("USDT", "USDT", 1.0) };
    vector<string> availableCountries = { "RU", "US" };
    map<User, map<CryptoCurrency, double>> balances;
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
    while (true) {
        cout << "Welcome!!\nMy commands:\n1 - Create new User\n2 - Log in Binance\nSign in Binance\n4 - Exit";
        cin >> answer;
        if (answer == "1") {
            while (true) {
                string login;
                string password;
                string country;
                cout << "Input login: ";
                cin >> login;
                for (auto& anyUser : users) {
                    if (anyUser.getLogin() == login) {
                        cout << "This login is already exist";
                        continue;
                    }
                }
                cout << "Input password: ";
                cin >> password;
                cout << "Input your country: ";
                cin >> country;
                user = User(login, password, country);
                cout << "Successfully registration";
                break;
            }
        }
        else if (answer == "2") {
            if (user.getLogin() != "") {
                bool registered = binance.LogIn(user);
                if (registered) {
                    cout << "Now u can work with binanace";
                    while (true) {
                        cout << "Hello in binance\nWhat do u want do?\n1 - deposit\n2 - withdraw\n3 - buy any currency\n4 - exit";
                        cin >> answer;
                        if (answer == "1") {
                            binance.deposit(user);
                        }
                        else if (answer == "2") {
                            while (true) {
                                int i;
                                vector<CryptoCurrency> currencies = binance.getBalance(user);
                                cout << "Which: ";
                                cin >> i;
                                binance.withdraw(user, currencies[i - 1]);
                            }
                        }
                        else if (answer == "3") {
                            binance.buyCurrency(user);
                        }
                        else if (answer == "4") {
                            cout << "See u later there\n";
                        }
                    }
                }
            }
            else {
                cout << "Before it u`ve to create user";
            }
        }
        else if (answer == "3") {
            bool authorize = binance.authorizeOnMe(user);
            if (authorize) {
                cout << "Hello in binance\nWhat do u want do?\n1 - deposit\n2 - withdraw\n3 - buy any currency\n4 - exit";
                cin >> answer;
                if (answer == "1") {
                    binance.deposit(user);
                }
                else if (answer == "2") {
                    while (true) {
                        int i;
                        vector<CryptoCurrency> currencies = binance.getBalance(user);
                        cout << "Which: ";
                        cin >> i;
                        binance.withdraw(user, currencies[i - 1]);
                    }
                }
                else if (answer == "3") {
                    binance.buyCurrency(user);
                }
                else if (answer == "4") {
                    cout << "See u later there\n";
                }
            }
        }
        else if (answer == "4") {
            cout << "Bye! See u later!";
            break;
        }
        else {
            cout << "I don`t know what do u meen(\n";
        }
    }
}

