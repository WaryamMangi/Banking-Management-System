#include <iostream>
#include <string>
using namespace std;

const int MAX_CUSTOMERS = 10;
const int MAX_ACCOUNTS = 5;

class Account {
    string accountNumber;
    double balance;

public:
    Account() : accountNumber(""), balance(0.0) {}

    void createAccount(const string& accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
        cout << "✅ Account created! Account Number: " << accountNumber << ", Balance: $" << balance << endl;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "❌ Invalid deposit amount!" << endl;
            return;
        }
        balance += amount;
        cout << "✅ Deposit successful! New Balance: $" << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "❌ Invalid withdrawal amount!" << endl;
            return;
        }
        if (amount > balance) {
            cout << "❌ Insufficient balance!" << endl;
            return;
        }
        balance -= amount;
        cout << "✅ Withdrawal successful! New Balance: $" << balance << endl;
    }

    void displayAccountInfo() const {
        if (accountNumber.empty()) {
            cout << "❌ No account exists!" << endl;
            return;
        }
        cout << "🔹 Account Number: " << accountNumber << ", Balance: $" << balance << endl;
    }

    bool hasAccount() const {
        return !accountNumber.empty();
    }
};

class Customer {
    string name;
    Account accounts[MAX_ACCOUNTS];
    int accountCount;

public:
    Customer() : name(""), accountCount(0) {}

    void createCustomer(const string& customerName) {
        name = customerName;
        accountCount = 0;
        cout << "✅ Customer created! Name: " << name << endl;
    }

    void addAccount() {
        if (accountCount >= MAX_ACCOUNTS) {
            cout << "❌ Maximum account limit reached!" << endl;
            return;
        }

        string accountNumber;
        double initialBalance;
        cout << "Enter new account number: ";
        cin >> accountNumber;
        cout << "Enter initial balance: ";
        cin >> initialBalance;

        accounts[accountCount].createAccount(accountNumber, initialBalance);
        accountCount++;
    }

    void manageAccounts() {
        if (accountCount == 0) {
            cout << "❌ No accounts available. Create an account first.\n";
            return;
        }

        cout << "🔹 Select an account by index (0 to " << accountCount - 1 << "): ";
        int accountIndex;
        cin >> accountIndex;

        if (accountIndex < 0 || accountIndex >= accountCount || !accounts[accountIndex].hasAccount()) {
            cout << "❌ Invalid account selection!" << endl;
            return;
        }

        int option;
        do {
            cout << "\n--- Account Management Menu ---\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. View Account Info\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> option;

            switch (option) {
                case 1: {
                    double amount;
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    accounts[accountIndex].deposit(amount);
                    break;
                }
                case 2: {
                    double amount;
                    cout << "Enter withdrawal amount: ";
                    cin >> amount;
                    accounts[accountIndex].withdraw(amount);
                    break;
                }
                case 3:
                    accounts[accountIndex].displayAccountInfo();  // ✅ FIXED: Now correctly shows account details
                    break;
                case 4:
                    cout << "Exiting account management.\n";
                    break;
                default:
                    cout << "❌ Invalid choice!\n";
            }
        } while (option != 4);
    }

    string getName() const {
        return name;
    }
};

class BankingService {
    Customer customers[MAX_CUSTOMERS];
    int customerCount;

public:
    BankingService() : customerCount(0) {}

    void addCustomer() {
        if (customerCount >= MAX_CUSTOMERS) {
            cout << "❌ Maximum customer limit reached!" << endl;
            return;
        }
        string name;
        cout << "Enter customer name: ";
        cin >> name;

        customers[customerCount].createCustomer(name);
        customerCount++;
    }

    void manageCustomer() {
        if (customerCount == 0) {
            cout << "❌ No customers available." << endl;
            return;
        }

        cout << "🔹 Select a customer by index (0 to " << customerCount - 1 << "): ";
        int customerIndex;
        cin >> customerIndex;

        if (customerIndex < 0 || customerIndex >= customerCount) {
            cout << "❌ Invalid customer selection!" << endl;
            return;
        }

        int choice;
        do {
            cout << "\n--- Manage Customer Menu ---\n";
            cout << "1. Add Account\n";
            cout << "2. Manage Existing Account\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    customers[customerIndex].addAccount();
                    break;
                case 2:
                    customers[customerIndex].manageAccounts();
                    break;
                case 3:
                    cout << "Exiting customer management.\n";
                    break;
                default:
                    cout << "❌ Invalid choice!\n";
            }
        } while (choice != 3);
    }
};

int main() {
    BankingService service;
    int option;

    do {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Add Customer\n";
        cout << "2. Manage Customer\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                service.addCustomer();
                break;
            case 2:
                service.manageCustomer();
                break;
            case 3:
                cout << "✅ Exiting the system.\n";
                break;
            default:
                cout << "❌ Invalid choice!\n";
        }
    } while (option != 3);

    return 0;
}