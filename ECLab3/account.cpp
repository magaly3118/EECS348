/*
    Author: Magaly Camacho
	Creation Date: 11/22/2023
	Lab: Extra Credit 3
	Description: Simple banking system that utilizes inheritance and operator overloading 
        to handle transactions between different types of bank accounts.
*/


/// DIRECTIVES
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

/// ACCOUNT CLASS
class Account {
    protected:
        string type = "Account";

    public:
        // member variables
        string accountNumber, accountHolder;
        double balance;

        /**
         * Constructor to initialize an Account object
         * 
         * @param number the account number
         * @param holder the account holder
         * @param initBalance the initial balance of the account
        */
        Account(string number, string holder, double initBalance) :
            accountNumber(number), accountHolder(holder), balance(initBalance) {};

        /**
         * Virtual method that displays the details of the account
        */
        virtual void displayDetails() {
            cout << "\nAccount Details for " << type << " (ID: " << accountNumber << "):" << endl
                << fixed << setprecision(2)
                << "\tBalance: $" << balance << endl
                << "\tHolder: " << accountHolder << endl;
        };

        /**
         * Method to deposit a given amount
         * 
         * @param amount the amount in dollars to deposit to the account
        */
        void deposit(double amount) {
            balance += amount;
            cout << "\nDeposit of $" << amount << " to account " << accountNumber << " successful!" << endl;
        };

        /**
         * Virtual method to withdraw a given amount, ensures sufficient funds are available
         * 
         * @param amount the amount in dollars to withdraw from the account
        */
        virtual int withdraw(double amount) {
            if (amount > balance) {
                cout << "\nWithdrawal of $" << amount << " canceled due to insufficient funds." << endl;
                return 1;
            }

            else {
                balance -= amount;
                cout << fixed << setprecision(2) 
                    << "\nWithdrawal of $" << amount << " from account " << accountNumber << " successful!" << endl;
                return 0;
            }
        };

        /**
         * Overload + operator to transfer $300 between accounts
         * 
         * @param otherAccount the account to withdraw the $300 from
        */
        void operator+(Account& otherAccount) {
            cout << "\nTransferring $300 from account " << otherAccount.accountNumber << " to account " << accountNumber << "..." << endl;
            int err = otherAccount.withdraw(300.00);

            if (err == 0) {
                deposit(300.00);
            }

            else {
                cout << "\nTransfer cancelled." << endl;
            }
        }

        /**
         * Overload << operator to display account details
         * 
         * @param os std::cout
         * @param account object of type Account
        */ 
        friend ostream& operator<<(ostream& os, const Account& account) {
            os << "\nAccount Details for " << account.type << " (ID: " << account.accountNumber << "):" << endl
                << fixed << setprecision(2)
                << "\tBalance: $" << account.balance << endl
                << "\tHolder: " << account.accountHolder << endl;

            account.extraDetails(os);
            return os;
        }   

        /**
         * Virtual method for derived classes to display extra details, when using the overloaded << operator
         * 
         * @param os std::cout
        */
        virtual void extraDetails(ostream& os) const {};
};      

/// SAVINGS ACCOUNT CLASS
class SavingsAccount: public Account {
    public:
        // member variable
        double interestRate;

        /**
         * Constructor to initialize a SavingsAccount object
         * 
         * @param number the account number
         * @param holder the account holder
         * @param initBalance the initial balance of the account
         * @param rate the decimal interest rate
        */
        SavingsAccount(string number, string holder, double initBalance, double rate) :
            Account(number, holder, initBalance), interestRate(rate) {
                type = "Savings Account"; // update type
            };

        /**
         * Method that displays the details of the account, overrides Account.displayDetails()
        */
        void displayDetails() override {
            Account::displayDetails();
            cout << fixed << setprecision(2) 
                << "\tInterest Rate: " << interestRate * 100 << "%" << endl;
        };

        /**
         * Method to withdraw a given amount, enforces minimum balance of $100.00
         * 
         * @param amount amount to withdraw in dollars
        */
        int withdraw(double amount) override {
            if (balance - amount < 100) {
                cout << "\nWithdrawal of $" << amount << " canceled due to violation of minimum balance requirement." << endl
                    << "\tMinimum Balance Required: $100.00" << endl;
                    return 1;
            }

            else {
                balance -= amount;
                cout << fixed << setprecision(2) 
                    << "\nWithdrawal of $" << amount << " from account " << accountNumber << " successful!" << endl;
                return 0;
            }
        };

        /**
         * Method to display extra details specific to Savings Account, when using << operator, overrides
         * 
         * @param os std::cout
        */
        void extraDetails(ostream& os) const override {
            os << fixed << setprecision(2) 
                << "\tInterest Rate: " << interestRate * 100 << "%" << endl;
        }
};

/// CURRENT ACCOUNT CLASS
class CurrentAccount: public Account {
    public:
        // member variable
        int overdraftLimit;

        /**
         * Constructor to initialize a CurrentAccount object
         * 
         * @param number the account number
         * @param holder the account holder
         * @param initBalance the initial balance of the account
         * @param limit the overdraft limit in dollars
        */
        CurrentAccount(string number, string holder, double initBalance, double limit) :
            Account(number, holder, initBalance), overdraftLimit(limit) {
                type = "Current Account"; // update type
            };

        /**
         * Method that displays the details of the account, overrides Account.displayDetails()
        */
        void displayDetails() override {
            Account::displayDetails();
            cout << fixed << setprecision(2) 
                << "\tOverdraft Limit: $" << overdraftLimit << endl;
        };

        /**
         * Method to withdraw a given amount, enfsures overdraft limit isn't exceeded
         * 
         * @param amount amount to withdraw in dollars
        */
        int withdraw(double amount) override {
            if (amount > balance + overdraftLimit) {
                cout << "\nWithdrawal of $" << amount << " canceled due to overdraft limit exceedance." << endl;
                return 1;
            }

            else {
                balance -= amount;
                cout << fixed << setprecision(2) 
                    << "\nWithdrawal of $" << amount << " from account " << accountNumber << " successful!" << endl;
                return 0;
            }
        };

        /**
         * Method to display extra details specific to Savings Account, when using << operator, overrides
         * 
         * @param os std::cout
        */
        void extraDetails(ostream& os) const override {
            os << fixed << setprecision(2) 
                << "\tOverdraft Limit: $" << overdraftLimit << endl;
        }
};

/// MAIN ENTRY POINT FOR TESTING
int main () {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdraw(1000);
    
    savings.displayDetails();
    current.displayDetails();

    // Transfer 300 from savings to current
    current + savings;

    savings.displayDetails();
    current.displayDetails();

    return 0;
}