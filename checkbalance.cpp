#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

class Money {
    public:
    friend Money operator +(const Money& amount1, const Money& amount2);
    //Returns the sum of the values of amount1 and amount2.

    friend Money operator -(const Money& amount1, const Money& amount2);
    //Returns amount1 minus amount2.

    friend Money operator -(const Money& amount);
    //Returns the negative of the value of amount.

    friend bool operator ==(const Money& amount1, const Money& amount2);
    //Returns true if amount1 and amount2 have the same value; false otherwise.

    friend bool operator <(const Money& amount1, const Money& amount2);
    //Returns true if amount1 is less than amount2; false otherwise.

    Money(long dollars, int cents);
    //Initializes the object so its value represents an amount with
    //the dollars and cents given by the arguments. If the amount
    //is negative, then both dollars and cents should be negative.

    Money(long dollars);
    //Initializes the object so its value represents $dollars.00.

    Money( );
    //Initializes the object so its value represents $0.00.

    double get_value( ) const;
    //Returns the amount of money recorded in the data portion of the calling
    //object.

    friend istream& operator >>(istream& ins, Money& amount);
    //Overloads the >> operator so it can be used to input values of type
    //Money. Notation for inputting negative amounts is as in − $100.00.
    //Precondition: If ins is a file input stream, then ins has already been
    //connected to a file.

    friend ostream& operator <<(ostream& outs, const Money& amount);
    //Overloads the << operator so it can be used to output values of type
    //Money. Precedes each output value of type Money with a dollar sign.
    //Precondition: If outs is a file output stream, then outs has already been
    //connected to a file.

    private:
    long all_cents;
 };

class Check{
    private:
        int checkNumber;
        Money checkAmount;
        bool isCashed;
    public:
        Check(int number, Money amount, bool cashed);
        // Initializes the object so its value represents the check number, amount, and whether the check is cashed.

        Check();
        //Initializes the object so its value represents check number 0, amount 0, and the check not being cashed.

        void set(int number, Money amount, bool cashed);
        // Sets the number, amount, and status of the check being cashed to values provided by the user.

        void set(bool cashed);
        // Sets whether the check is cashed to the boolean value provided by the user.

        void output(ostream& outs);
        // Defines how the check value and number are output.

        Money getAmount();
        // Retrieves the check amount.

        int getNumber();
        //Retrieves the check number.

        bool getCashedStatus();
        // Retrieves the status of the check being cashed.

};

int digit_to_int(char c);

Money addCashedChecks(Check checks[], int checksLength);

Money addAllChecks(Check checks[], int checksLength);

Money addDeposits(Money deposits[], int depositsLength);

void swap(Check &a, Check &b);

void checkSort(Check checks[], int checkArrSize);

int main() {
    int numChecks = 0;
    int numDeposits = 0;
    double startingBalance = 0;
    double receivedBalance = 0;
    int checkNumber;
    double checkAmount = 0;
    double depositAmount = 0;
    int numCheckCents = 0;
    int numDepositCents = 0;
    bool isCashed;
    string isCashedInput;

    cout<<"Enter your starting balance:"<<endl;

    cin>>startingBalance;
    Money startingBalanceMoney(startingBalance);

    cout<<"Enter the balance you received from the bank:"<<endl;

    cin>>receivedBalance;
    Money receivedBalanceMoney(receivedBalance);

    cout<<"How many deposits would you like to make?"<<endl;

    cin>>numDeposits;

    Money* depositsArray = new Money[numDeposits];
    int arrayCounterDeposits = 0;

    for (int i = 1; i <= numDeposits; i++) {
        cout<<"How much money is in this deposit?"<<endl;
        cin>>depositAmount;
        if (int(depositAmount) != depositAmount) {
            numDepositCents = (depositAmount - int(depositAmount)) * 100;
        } else {
            numDepositCents = 0;
        }
        Money newDeposit(depositAmount, numDepositCents);
        depositsArray[arrayCounterDeposits] = newDeposit;
        arrayCounterDeposits++;
    }

    cout<<"How many checks would you like to add to your checkbook?"<<endl;

    cin>>numChecks;

    Check* checksArray = new Check[numChecks];
    int arrayCounterChecks = 0;

    for (int i = 1; i <= numChecks; i++) {
        cout<<"What is the check ID?"<<endl;
        cin>>checkNumber;
        cout<<"How much money is in this check?"<<endl;
        cin>>checkAmount;
        if (int(checkAmount) != checkAmount) {
            numCheckCents = (checkAmount - int(checkAmount)) * 100;
        } else {
            numCheckCents = 0;
        }
        Money newAmount(checkAmount, numCheckCents);
        cout<<"Has your check been cashed? Type 1 for true or 0 for false."<<endl;
        cin>>isCashedInput;
        if (isCashedInput == "1") {
            isCashed = true;
        } else if (isCashedInput == "0") {
            isCashed = false;
        }
        Check newCheck(checkNumber, newAmount, isCashed);
        checksArray[arrayCounterChecks] = newCheck;
        arrayCounterChecks++;
    }

    checkSort(checksArray, numChecks);

    cout<<"--------------------"<<endl;
    cout<<"Checkbook and Bank Outputs"<<endl;
    cout<<"--------------------"<<endl;

    Money totalCashedChecks = addCashedChecks(checksArray, numChecks);
    cout<<"Cashed Checks Total: "<<totalCashedChecks<<endl;

    Money totalDeposits = addDeposits(depositsArray, numDeposits);
    cout<<"Deposits Total: "<<totalDeposits<<endl;

    cout<<endl;

    Money newBankBalance = startingBalanceMoney + totalDeposits - totalCashedChecks;
    cout<<"New Bank Balance: "<<newBankBalance<<endl;

    Money totalCheckAmount = addAllChecks(checksArray, numChecks);
    Money checkbookBalance = startingBalanceMoney + totalDeposits - totalCheckAmount;
    cout<<"New Checkbook Amount: "<<checkbookBalance<<endl;

    Money bankCheckbookDifference = newBankBalance - checkbookBalance;
    cout<<"Bank-Checkbook Difference: "<<bankCheckbookDifference<<endl;;
    cout<<endl;

    if (receivedBalanceMoney == newBankBalance) {
        cout<<"Your bank calculated its balance correctly."<<endl;
    } else {
        cout<<"Your bank calculated its balance incorrectly!"<<endl;
        cout<<"Bank's Given-Actual Difference: "<<receivedBalanceMoney - newBankBalance<<endl;
    }
    cout<<endl;

    cout<<"--------------------"<<endl;
    cout<<"List of Cashed Checks"<<endl;
    cout<<"--------------------"<<endl;

    for (int i = 0; i < numChecks; i++) {
        bool isCashed = checksArray[i].getCashedStatus();
        if (isCashed) {
            checksArray[i].output(cout);
        }
    }

    cout<<"--------------------"<<endl;
    cout<<"List of Uncashed Checks"<<endl;
    cout<<"--------------------"<<endl;

    for (int i = 0; i < numChecks; i++) {
        bool isCashed = checksArray[i].getCashedStatus();
        if (!isCashed) {
            checksArray[i].output(cout);
        }
    }

    delete[] checksArray;
    delete[] depositsArray;
    return 0;
}

Check::Check(int number, Money amount, bool cashed) {
    checkNumber = number;
    checkAmount = amount;
    isCashed = cashed;
}

Check::Check() : checkNumber(0), checkAmount(0), isCashed(false) {

};

void Check::set(int number, Money amount, bool cashed) {

    checkNumber = number;
    checkAmount = amount;
    isCashed = cashed;
}

void Check::set(bool cashed) {
    isCashed = cashed;
}

void Check::output(ostream& outs) {
    outs<<"Check Number: "<<getNumber()<<endl;
    outs<<"Check Amount: "<<getAmount()<<endl;
}

Money Check::getAmount() {
    return checkAmount;
}

int Check::getNumber() {
    return checkNumber;
}

bool Check::getCashedStatus() {
    if (isCashed) {
        return true;
    } else {
        return false;
    }
}

Money::Money(long dollars, int cents)
{
    if (dollars * cents < 0) { 
        cout << "Illegal values for dollars and cents.\n";
        exit(1);
    }
    all_cents = dollars * 100 + cents;
}

Money::Money(long dollars) : all_cents(dollars * 100) {
    //Body intentionally blank.
}

Money::Money( ) : all_cents(0) {
    //Body intentionally blank.
}

double Money::get_value( ) const {
    return (all_cents * 0.01);
}

Money operator +(const Money& amount1, const Money& amount2) {
    Money temp;
    temp.all_cents = amount1.all_cents + amount2.all_cents; return temp;
}

bool operator ==(const Money& amount1, const Money& amount2) {
    return (amount1.all_cents == amount2.all_cents); 
}

Money operator -(const Money& amount1, const Money& amount2) {
    Money temp;
    temp.all_cents = amount1.all_cents - amount2.all_cents;
    return temp;
}

Money operator -(const Money& amount) {
    Money temp;
    temp.all_cents = -amount.all_cents; 
    return temp;
}

bool operator <(const Money& amount1, const Money& amount2) {
    return (amount1.all_cents < amount2.all_cents);
}

istream& operator >>(istream& ins, Money& amount) {
    char one_char, decimal_point,
    digit1, digit2; //digits for the amount of cents
    long dollars;
    int cents;
    bool negative;//set to true if input is negative.
    ins >> one_char;
    if (one_char == '-') {
        negative = true;
        ins >> one_char; //read '$'
    }
    else
        negative = false;
    //if input is legal, then one_char == '$'

    ins >> dollars >> decimal_point >> digit1 >> digit2;

    if (one_char != '$' || decimal_point != '.' ||!isdigit(digit1) || !isdigit(digit2)) {
        cout<< "Error illegal form for money input \n";
        exit(1);
    }

    cents = digit_to_int(digit1) * 10 + digit_to_int(digit2);
    
    amount.all_cents = dollars * 100 + cents;
    if (negative)
        amount.all_cents = -amount.all_cents;
    return ins;
}

int digit_to_int(char c) {
    return ( static_cast<int>(c) - static_cast<int>('0') );
}

ostream& operator <<(ostream& outs, const Money& amount) {
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents/100;
    cents = positive_cents%100;

    if (amount.all_cents < 0)
        outs << "- $" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;

    return outs;
}

Money addCashedChecks(Check checks[], int checksLength) {
    Money totalCashedChecks(0);

    for (int i = 0; i < checksLength; i++) {
        bool isCashed = checks[i].getCashedStatus();
        Money amount = checks[i].getAmount();
        if (isCashed) {
            totalCashedChecks = totalCashedChecks + amount;
        }
    }

    return totalCashedChecks;
}

Money addAllChecks(Check checks[], int checksLength) {
     Money totalChecks(0);

    for (int i = 0; i < checksLength; i++) {
        bool isCashed = checks[i].getCashedStatus();
        Money amount = checks[i].getAmount();
        totalChecks = totalChecks + amount;
    }

    return totalChecks;
}
    
Money addDeposits(Money deposits[], int depositsLength) {
    Money totalAmount(0);

    for (int i = 0; i < depositsLength; i++) {
        totalAmount = totalAmount + deposits[i];
    }

    return totalAmount;
}

void swap(Check &a, Check &b) {
    Check temp = a;
    a = b;
    b = temp;
}

void checkSort(Check checks[], int checkArrSize) {
    for (int i = 0; i < checkArrSize - 1; i++) {
        for (int j = 0; j < checkArrSize - i - 1; j++) {
            Money checkAmount1 = checks[j].getAmount();
            Money checkAmount2 = checks[j + 1].getAmount();
            if (checkAmount2 < checkAmount1) {
                swap(checks[j], checks[j + 1]);
            }
        }
    }
}