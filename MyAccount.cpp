#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <map>
#include <limits>
#include <random>
#include <chrono>
#include <iomanip>
#include <windows.h>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;
using std::setw;
using std::setprecision;
using std::fixed;
using std::left;
using std::right;

// Colors for console output
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Transaction structure to store transaction history
struct Transaction {
    string date;
    string type;
    double amount;
    double balance;
    string description;
    string category;  // New field for transaction category
    string location;  // New field for transaction location
    string reference; // New field for transaction reference
};

// Loan structure
struct Loan {
    string loanId;
    double amount;
    double interestRate;
    int termMonths;
    string status;
    string startDate;
    double remainingAmount;
    string purpose;      // New field for loan purpose
    string collateral;   // New field for loan collateral
    double monthlyPayment; // New field for monthly payment
    vector<string> paymentHistory; // New field for payment history
};

// Card structure
struct Card {
    string cardNumber;
    string cardType;
    string expiryDate;
    string cvv;
    double limit;
    bool isActive;
    string pin;          // New field for card PIN
    vector<string> recentTransactions; // New field for recent transactions
    double availableCredit; // New field for available credit
    string cardHolderName; // New field for card holder name
};

// Investment structure
struct Investment {
    string investmentId;
    string type;         // Stocks, Bonds, Mutual Funds, etc.
    double amount;
    double currentValue;
    string startDate;
    double returnRate;
    string status;
    vector<string> transactionHistory;
};

// Bill structure
struct Bill {
    string billId;
    string type;         // Utility, Rent, Insurance, etc.
    double amount;
    string dueDate;
    bool isPaid;
    string provider;
    string accountNumber;
};

// Beneficiary structure
struct Beneficiary {
    string name;
    string accountNumber;
    string bankName;
    string swiftCode;
    string relationship;
    double transferLimit;
};

class Account {
    private:
        string accountNumber;
        string accountHolderName;
        double balance;
        string user, pass;
        string accountType;  // Savings, Checking, Business
        double interestRate;
        vector<Transaction> transactions;
        vector<Loan> loans;
        vector<Card> cards;
        vector<Investment> investments;  // New field for investments
        vector<Bill> bills;             // New field for bills
        vector<Beneficiary> beneficiaries; // New field for beneficiaries
        bool isActive;
        string creationDate;
        string lastLoginDate;
        int failedLoginAttempts;
        double dailyWithdrawalLimit;
        double monthlyWithdrawalLimit;
        double dailyWithdrawn;
        double monthlyWithdrawn;
        string email;
        string phone;
        string address;
        string nationalId;      // New field for national ID
        string occupation;      // New field for occupation
        double creditScore;     // New field for credit score
        vector<string> notifications; // New field for notifications
        map<string, double> currencyBalances; // New field for multi-currency support
        vector<string> documents; // New field for account documents
        bool isPremium;         // New field for premium status
        vector<string> favoriteTransactions; // New field for favorite transactions
        map<string, string> securityQuestions; // New field for security questions

    public:
        Account(string user, string pass, double balance, string accountNumber, 
                string accountHolderName, string accountType = "Savings") {
            this->user = user;
            this->pass = pass;
            this->balance = balance;
            this->accountNumber = accountNumber;
            this->accountHolderName = accountHolderName;
            this->accountType = accountType;
            this->interestRate = (accountType == "Savings") ? 0.05 : 0.02;
            this->isActive = true;
            this->failedLoginAttempts = 0;
            this->dailyWithdrawalLimit = 1000.0;
            this->monthlyWithdrawalLimit = 10000.0;
            this->dailyWithdrawn = 0.0;
            this->monthlyWithdrawn = 0.0;
            
            // Set creation date
            auto now = chrono::system_clock::now();
            time_t current_time = chrono::system_clock::to_time_t(now);
            this->creationDate = ctime(&current_time);
            this->creationDate = this->creationDate.substr(0, this->creationDate.length()-1);
        }

        // Getters
        string getAccountNumber() const { return accountNumber; }
        string getAccountHolderName() const { return accountHolderName; }
        double getBalance() const { return balance; }
        string getUsername() const { return user; }
        string getPassword() const { return pass; }
        string getAccountType() const { return accountType; }
        bool getIsActive() const { return isActive; }
        vector<Transaction> getTransactions() const { return transactions; }
        vector<Loan> getLoans() const { return loans; }
        vector<Card> getCards() const { return cards; }

        // Account operations
        bool deposit(double amount) {
            if (amount > 0) {
                balance += amount;
                addTransaction("Deposit", amount, "Cash deposit");
                return true;
            }
            return false;
        }

        bool withdraw(double amount) {
            if (amount > 0 && amount <= balance && 
                amount <= (dailyWithdrawalLimit - dailyWithdrawn) &&
                amount <= (monthlyWithdrawalLimit - monthlyWithdrawn)) {
                balance -= amount;
                dailyWithdrawn += amount;
                monthlyWithdrawn += amount;
                addTransaction("Withdrawal", -amount, "Cash withdrawal");
                return true;
            }
            return false;
        }

        void addTransaction(string type, double amount, string description) {
            Transaction t;
            auto now = chrono::system_clock::now();
            time_t current_time = chrono::system_clock::to_time_t(now);
            t.date = ctime(&current_time);
            t.date = t.date.substr(0, t.date.length()-1);
            t.type = type;
            t.amount = amount;
            t.balance = balance;
            t.description = description;
            transactions.push_back(t);
        }

        bool applyForLoan(double amount, int termMonths) {
            if (amount <= 0 || termMonths <= 0) return false;
            
            Loan loan;
            loan.loanId = "LOAN" + to_string(loans.size() + 1000);
            loan.amount = amount;
            loan.interestRate = 0.08; // 8% annual interest
            loan.termMonths = termMonths;
            loan.status = "Pending";
            auto now = chrono::system_clock::now();
            time_t current_time = chrono::system_clock::to_time_t(now);
            loan.startDate = ctime(&current_time);
            loan.startDate = loan.startDate.substr(0, loan.startDate.length()-1);
            loan.remainingAmount = amount;
            
            loans.push_back(loan);
            return true;
        }

        bool issueCard(string cardType) {
            Card card;
            // Generate random card number
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, 9);
            string cardNumber = "4";
            for(int i = 0; i < 15; i++) {
                cardNumber += to_string(dis(gen));
            }
            
            card.cardNumber = cardNumber;
            card.cardType = cardType;
            
            // Set expiry date (2 years from now)
            auto now = chrono::system_clock::now();
            time_t current_time = chrono::system_clock::to_time_t(now);
            tm* timeinfo = localtime(&current_time);
            timeinfo->tm_year += 2;
            char buffer[11];
            strftime(buffer, 11, "%m/%Y", timeinfo);
            card.expiryDate = buffer;
            
            // Generate CVV
            card.cvv = to_string(dis(gen)) + to_string(dis(gen)) + to_string(dis(gen));
            
            card.limit = (cardType == "Platinum") ? 10000.0 : 5000.0;
            card.isActive = true;
            
            cards.push_back(card);
            return true;
        }

        void displayAccountInfo() const {
            cout << "\n=== Account Information ===" << endl;
            cout << "Account Number: " << accountNumber << endl;
            cout << "Account Holder: " << accountHolderName << endl;
            cout << "Account Type: " << accountType << endl;
            cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
            cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
            cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
            cout << "Creation Date: " << creationDate << endl;
            cout << "Last Login: " << lastLoginDate << endl;
            cout << "========================\n" << endl;
        }

        void displayTransactionHistory() const {
            cout << "\n=== Transaction History ===" << endl;
            for(const auto& t : transactions) {
                cout << "Date: " << t.date << endl;
                cout << "Type: " << t.type << endl;
                cout << "Amount: $" << fixed << setprecision(2) << t.amount << endl;
                cout << "Balance: $" << fixed << setprecision(2) << t.balance << endl;
                cout << "Description: " << t.description << endl;
                cout << "------------------------" << endl;
            }
        }

        void displayLoans() const {
            cout << "\n=== Loan Information ===" << endl;
            for(const auto& loan : loans) {
                cout << "Loan ID: " << loan.loanId << endl;
                cout << "Amount: $" << fixed << setprecision(2) << loan.amount << endl;
                cout << "Interest Rate: " << (loan.interestRate * 100) << "%" << endl;
                cout << "Term: " << loan.termMonths << " months" << endl;
                cout << "Status: " << loan.status << endl;
                cout << "Start Date: " << loan.startDate << endl;
                cout << "Remaining Amount: $" << fixed << setprecision(2) << loan.remainingAmount << endl;
                cout << "------------------------" << endl;
            }
        }

        void displayCards() const {
            cout << "\n=== Card Information ===" << endl;
            for(const auto& card : cards) {
                cout << "Card Number: " << card.cardNumber << endl;
                cout << "Card Type: " << card.cardType << endl;
                cout << "Expiry Date: " << card.expiryDate << endl;
                cout << "CVV: " << card.cvv << endl;
                cout << "Limit: $" << fixed << setprecision(2) << card.limit << endl;
                cout << "Status: " << (card.isActive ? "Active" : "Inactive") << endl;
                cout << "------------------------" << endl;
            }
        }

        void updateLastLogin() {
            auto now = chrono::system_clock::now();
            time_t current_time = chrono::system_clock::to_time_t(now);
            lastLoginDate = ctime(&current_time);
            lastLoginDate = lastLoginDate.substr(0, lastLoginDate.length()-1);
        }

        void resetDailyWithdrawal() {
            dailyWithdrawn = 0.0;
        }

        void resetMonthlyWithdrawal() {
            monthlyWithdrawn = 0.0;
        }

        void setAccountType(string type) {
            accountType = type;
            interestRate = (type == "Savings") ? 0.05 : 0.02;
        }

        void setDailyLimit(double limit) {
            dailyWithdrawalLimit = limit;
        }

        void setMonthlyLimit(double limit) {
            monthlyWithdrawalLimit = limit;
        }

        void setEmail(string newEmail) {
            email = newEmail;
        }

        void setPhone(string newPhone) {
            phone = newPhone;
        }

        void setAddress(string newAddress) {
            address = newAddress;
        }

        void deactivateAccount() {
            isActive = false;
        }

        void activateAccount() {
            isActive = true;
        }

        // New methods for investments
        bool addInvestment(string type, double amount) {
            Investment inv;
            inv.investmentId = "INV" + to_string(investments.size() + 1000);
            inv.type = type;
            inv.amount = amount;
            inv.currentValue = amount;
            inv.startDate = getCurrentDate();
            inv.returnRate = 0.0;
            inv.status = "Active";
            investments.push_back(inv);
            return true;
        }

        // New method for bill payment
        bool payBill(string billId) {
            for (auto& bill : bills) {
                if (bill.billId == billId && !bill.isPaid) {
                    if (withdraw(bill.amount)) {
                        bill.isPaid = true;
                        addTransaction("Bill Payment", -bill.amount, "Payment for " + bill.type);
                        return true;
                    }
                }
            }
            return false;
        }

        // New method for adding beneficiaries
        bool addBeneficiary(string name, string accountNumber, string bankName, 
                          string swiftCode, string relationship) {
            Beneficiary ben;
            ben.name = name;
            ben.accountNumber = accountNumber;
            ben.bankName = bankName;
            ben.swiftCode = swiftCode;
            ben.relationship = relationship;
            ben.transferLimit = 10000.0; // Default limit
            beneficiaries.push_back(ben);
            return true;
        }

        // New method for international transfer
        bool internationalTransfer(string beneficiaryName, double amount, string currency) {
            for (const auto& ben : beneficiaries) {
                if (ben.name == beneficiaryName) {
                    if (amount <= ben.transferLimit && withdraw(amount)) {
                        addTransaction("International Transfer", -amount, 
                                     "Transfer to " + ben.name + " in " + currency);
                        return true;
                    }
                }
            }
            return false;
        }

        // New method for currency exchange
        bool exchangeCurrency(string fromCurrency, string toCurrency, double amount) {
            // Simplified exchange rate calculation
            double rate = 1.0; // This should be fetched from a real exchange rate API
            if (currencyBalances[fromCurrency] >= amount) {
                currencyBalances[fromCurrency] -= amount;
                currencyBalances[toCurrency] += amount * rate;
                addTransaction("Currency Exchange", amount, 
                             "Exchange from " + fromCurrency + " to " + toCurrency);
                return true;
            }
            return false;
        }

        // New method for setting up recurring payments
        bool setupRecurringPayment(string billId, string frequency) {
            for (auto& bill : bills) {
                if (bill.billId == billId) {
                    // Add recurring payment logic here
                    return true;
                }
            }
            return false;
        }

        // New method for investment portfolio summary
        void displayInvestmentPortfolio() const {
            setColor(11); // Light cyan
            cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
            cout << "║                    Investment Portfolio                     ║" << endl;
            cout << "╚════════════════════════════════════════════════════════════╝" << endl;
            
            double totalValue = 0.0;
            for (const auto& inv : investments) {
                cout << "┌──────────────────────────────────────────────────────────┐" << endl;
                cout << "│ Investment ID: " << setw(40) << left << inv.investmentId << "│" << endl;
                cout << "│ Type: " << setw(47) << left << inv.type << "│" << endl;
                cout << "│ Amount: $" << setw(43) << left << fixed << setprecision(2) << inv.amount << "│" << endl;
                cout << "│ Current Value: $" << setw(39) << left << inv.currentValue << "│" << endl;
                cout << "│ Return Rate: " << setw(41) << left << (inv.returnRate * 100) << "%│" << endl;
                cout << "└──────────────────────────────────────────────────────────┘" << endl;
                totalValue += inv.currentValue;
            }
            cout << "\nTotal Portfolio Value: $" << fixed << setprecision(2) << totalValue << endl;
            setColor(7); // Reset to default color
        }

        // New method for bill management
        void displayBills() const {
            setColor(14); // Yellow
            cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
            cout << "║                        Bill Management                      ║" << endl;
            cout << "╚════════════════════════════════════════════════════════════╝" << endl;
            
            for (const auto& bill : bills) {
                cout << "┌──────────────────────────────────────────────────────────┐" << endl;
                cout << "│ Bill ID: " << setw(44) << left << bill.billId << "│" << endl;
                cout << "│ Type: " << setw(47) << left << bill.type << "│" << endl;
                cout << "│ Amount: $" << setw(43) << left << fixed << setprecision(2) << bill.amount << "│" << endl;
                cout << "│ Due Date: " << setw(43) << left << bill.dueDate << "│" << endl;
                cout << "│ Status: " << setw(45) << left << (bill.isPaid ? "Paid" : "Pending") << "│" << endl;
                cout << "└──────────────────────────────────────────────────────────┘" << endl;
            }
            setColor(7); // Reset to default color
        }

        // New method for beneficiary management
        void displayBeneficiaries() const {
            setColor(10); // Light green
            cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
            cout << "║                    Beneficiary Management                   ║" << endl;
            cout << "╚════════════════════════════════════════════════════════════╝" << endl;
            
            for (const auto& ben : beneficiaries) {
                cout << "┌──────────────────────────────────────────────────────────┐" << endl;
                cout << "│ Name: " << setw(47) << left << ben.name << "│" << endl;
                cout << "│ Account Number: " << setw(37) << left << ben.accountNumber << "│" << endl;
                cout << "│ Bank: " << setw(47) << left << ben.bankName << "│" << endl;
                cout << "│ Relationship: " << setw(39) << left << ben.relationship << "│" << endl;
                cout << "│ Transfer Limit: $" << setw(39) << left << fixed << setprecision(2) << ben.transferLimit << "│" << endl;
                cout << "└──────────────────────────────────────────────────────────┘" << endl;
            }
            setColor(7); // Reset to default color
        }

        // New method for currency management
        void displayCurrencyBalances() const {
            setColor(13); // Light magenta
            cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
            cout << "║                    Currency Balances                       ║" << endl;
            cout << "╚════════════════════════════════════════════════════════════╝" << endl;
            
            for (const auto& currency : currencyBalances) {
                cout << "┌──────────────────────────────────────────────────────────┐" << endl;
                cout << "│ Currency: " << setw(43) << left << currency.first << "│" << endl;
                cout << "│ Balance: " << setw(44) << left << fixed << setprecision(2) << currency.second << "│" << endl;
                cout << "└──────────────────────────────────────────────────────────┘" << endl;
            }
            setColor(7); // Reset to default color
        }

        // New method for notifications
        void displayNotifications() const {
            setColor(12); // Light red
            cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
            cout << "║                        Notifications                       ║" << endl;
            cout << "╚════════════════════════════════════════════════════════════╝" << endl;
            
            for (const auto& notification : notifications) {
                cout << "┌──────────────────────────────────────────────────────────┐" << endl;
                cout << "│ " << setw(58) << left << notification << "│" << endl;
                cout << "└──────────────────────────────────────────────────────────┘" << endl;
            }
            setColor(7); // Reset to default color
        }

        // Helper method to get current date
        string getCurrentDate() const {
            auto now = chrono::system_clock::now();
            time_t current_time = chrono::system_clock::to_time_t(now);
            string date = ctime(&current_time);
            return date.substr(0, date.length()-1);
        }
};

class BankSystem {
    private:
        vector<Account> accounts;
        Account* currentAccount = nullptr;
        map<string, string> adminCredentials;
        bool isAdmin = false;

    public:
        BankSystem() {
            // Set up admin account
            adminCredentials["admin"] = "admin123";
        }

        void registerAccount() {
            string username, password, name, email, phone, address, accType;
            double initialBalance;

            cout << "\n=== Register New Account ===" << endl;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter full name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter email: ";
            cin >> email;
            cout << "Enter phone: ";
            cin >> phone;
            cout << "Enter address: ";
            cin.ignore();
            getline(cin, address);
            cout << "Enter initial balance: $";
            cin >> initialBalance;
            cout << "Select account type (Savings/Checking/Business): ";
            cin >> accType;

            // Generate account number
            string accNumber = "ACC" + to_string(accounts.size() + 1000);

            Account newAccount(username, password, initialBalance, accNumber, name, accType);
            newAccount.setEmail(email);
            newAccount.setPhone(phone);
            newAccount.setAddress(address);
            
            accounts.push_back(newAccount);
            cout << "\nAccount created successfully!" << endl;
            cout << "Your account number is: " << accNumber << endl;
        }

        bool login() {
            string username, password;
            cout << "\n=== Login ===" << endl;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            // Check for admin login
            if (adminCredentials.find(username) != adminCredentials.end() && 
                adminCredentials[username] == password) {
                isAdmin = true;
                cout << "\nAdmin login successful!" << endl;
                return true;
            }

            for (auto& account : accounts) {
                if (account.getUsername() == username && account.getPassword() == password) {
                    currentAccount = &account;
                    currentAccount->updateLastLogin();
                    cout << "\nLogin successful!" << endl;
                    return true;
                }
            }
            cout << "\nInvalid username or password!" << endl;
            return false;
        }

        void showMenu() {
            while (true) {
                cout << "\n=== Bank System Menu ===" << endl;
                cout << "1. Register New Account" << endl;
                cout << "2. Login" << endl;
                cout << "3. Exit" << endl;
                cout << "Choose an option: ";

                int choice;
                cin >> choice;

                switch (choice) {
                    case 1:
                        registerAccount();
                        break;
                    case 2:
                        if (login()) {
                            if (isAdmin) {
                                showAdminMenu();
                            } else {
                                showAccountMenu();
                            }
                        }
                        break;
                    case 3:
                        cout << "\nThank you for using our banking system!" << endl;
                        return;
                    default:
                        cout << "\nInvalid option! Please try again." << endl;
                }
            }
        }

        void showAccountMenu() {
            while (true) {
                cout << "\n=== Account Menu ===" << endl;
                cout << "1. Check Balance" << endl;
                cout << "2. Deposit" << endl;
                cout << "3. Withdraw" << endl;
                cout << "4. Display Account Info" << endl;
                cout << "5. Transaction History" << endl;
                cout << "6. Apply for Loan" << endl;
                cout << "7. View Loans" << endl;
                cout << "8. Issue New Card" << endl;
                cout << "9. View Cards" << endl;
                cout << "10. Update Personal Information" << endl;
                cout << "11. Change Account Type" << endl;
                cout << "12. Set Withdrawal Limits" << endl;
                cout << "13. Logout" << endl;
                cout << "Choose an option: ";

                int choice;
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "\nCurrent Balance: $" << fixed << setprecision(2) 
                             << currentAccount->getBalance() << endl;
                        break;
                    case 2: {
                        double amount;
                        cout << "Enter amount to deposit: $";
                        cin >> amount;
                        if (currentAccount->deposit(amount)) {
                            cout << "Deposit successful!" << endl;
                        } else {
                            cout << "Invalid amount!" << endl;
                        }
                        break;
                    }
                    case 3: {
                        double amount;
                        cout << "Enter amount to withdraw: $";
                        cin >> amount;
                        if (currentAccount->withdraw(amount)) {
                            cout << "Withdrawal successful!" << endl;
                        } else {
                            cout << "Invalid amount or insufficient balance!" << endl;
                        }
                        break;
                    }
                    case 4:
                        currentAccount->displayAccountInfo();
                        break;
                    case 5:
                        currentAccount->displayTransactionHistory();
                        break;
                    case 6: {
                        double amount;
                        int term;
                        cout << "Enter loan amount: $";
                        cin >> amount;
                        cout << "Enter term in months: ";
                        cin >> term;
                        if (currentAccount->applyForLoan(amount, term)) {
                            cout << "Loan application submitted successfully!" << endl;
                        } else {
                            cout << "Invalid loan details!" << endl;
                        }
                        break;
                    }
                    case 7:
                        currentAccount->displayLoans();
                        break;
                    case 8: {
                        string cardType;
                        cout << "Enter card type (Standard/Platinum): ";
                        cin >> cardType;
                        if (currentAccount->issueCard(cardType)) {
                            cout << "Card issued successfully!" << endl;
                        } else {
                            cout << "Failed to issue card!" << endl;
                        }
                        break;
                    }
                    case 9:
                        currentAccount->displayCards();
                        break;
                    case 10: {
                        string email, phone, address;
                        cout << "Enter new email: ";
                        cin >> email;
                        cout << "Enter new phone: ";
                        cin >> phone;
                        cout << "Enter new address: ";
                        cin.ignore();
                        getline(cin, address);
                        currentAccount->setEmail(email);
                        currentAccount->setPhone(phone);
                        currentAccount->setAddress(address);
                        cout << "Personal information updated successfully!" << endl;
                        break;
                    }
                    case 11: {
                        string newType;
                        cout << "Enter new account type (Savings/Checking/Business): ";
                        cin >> newType;
                        currentAccount->setAccountType(newType);
                        cout << "Account type updated successfully!" << endl;
                        break;
                    }
                    case 12: {
                        double dailyLimit, monthlyLimit;
                        cout << "Enter new daily withdrawal limit: $";
                        cin >> dailyLimit;
                        cout << "Enter new monthly withdrawal limit: $";
                        cin >> monthlyLimit;
                        currentAccount->setDailyLimit(dailyLimit);
                        currentAccount->setMonthlyLimit(monthlyLimit);
                        cout << "Withdrawal limits updated successfully!" << endl;
                        break;
                    }
                    case 13:
                        currentAccount = nullptr;
                        cout << "\nLogged out successfully!" << endl;
                        return;
                    default:
                        cout << "\nInvalid option! Please try again." << endl;
                }
            }
        }

        void showAdminMenu() {
            while (true) {
                cout << "\n=== Admin Menu ===" << endl;
                cout << "1. View All Accounts" << endl;
                cout << "2. Deactivate Account" << endl;
                cout << "3. Activate Account" << endl;
                cout << "4. View Transaction History" << endl;
                cout << "5. View Loan Applications" << endl;
                cout << "6. Process Loan Application" << endl;
                cout << "7. View Card Issuance Requests" << endl;
                cout << "8. Logout" << endl;
                cout << "Choose an option: ";

                int choice;
                cin >> choice;

                switch (choice) {
                    case 1:
                        for (const auto& account : accounts) {
                            account.displayAccountInfo();
                        }
                        break;
                    case 2: {
                        string accNumber;
                        cout << "Enter account number to deactivate: ";
                        cin >> accNumber;
                        for (auto& account : accounts) {
                            if (account.getAccountNumber() == accNumber) {
                                account.deactivateAccount();
                                cout << "Account deactivated successfully!" << endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 3: {
                        string accNumber;
                        cout << "Enter account number to activate: ";
                        cin >> accNumber;
                        for (auto& account : accounts) {
                            if (account.getAccountNumber() == accNumber) {
                                account.activateAccount();
                                cout << "Account activated successfully!" << endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 4: {
                        string accNumber;
                        cout << "Enter account number to view transactions: ";
                        cin >> accNumber;
                        for (const auto& account : accounts) {
                            if (account.getAccountNumber() == accNumber) {
                                account.displayTransactionHistory();
                                break;
                            }
                        }
                        break;
                    }
                    case 5: {
                        for (const auto& account : accounts) {
                            account.displayLoans();
                        }
                        break;
                    }
                    case 6: {
                        string accNumber, loanId;
                        cout << "Enter account number: ";
                        cin >> accNumber;
                        cout << "Enter loan ID: ";
                        cin >> loanId;
                        // Process loan application logic here
                        cout << "Loan application processed!" << endl;
                        break;
                    }
                    case 7: {
                        for (const auto& account : accounts) {
                            account.displayCards();
                        }
                        break;
                    }
                    case 8:
                        isAdmin = false;
                        cout << "\nLogged out successfully!" << endl;
                        return;
                    default:
                        cout << "\nInvalid option! Please try again." << endl;
                }
            }
        }
};

int main() {
    BankSystem bank;
    cout << "Welcome to the Advanced Banking System!" << endl;
    bank.showMenu();
    return 0;
}


























