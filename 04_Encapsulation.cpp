/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                               ENCAPSULATION                               ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is Encapsulation?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Encapsulation = WRAP data and the methods that use it into ONE unit
 *    (a class), and STOP direct access to the data using access
 *    specifiers like private
 *  ✔ Outside code talks to the object only through its public methods
 *  ✔ Real life: a medicine capsule — the powder is packed inside, you
 *    just swallow the capsule. Or an ATM — you can't touch the cash
 *    box, you can only use the buttons.
 *
 *              ┌─────────────────────────────────────┐
 *              │           class BankAccount         │
 *              │   ┌─────────────────────────────┐   │
 *              │   │  private:  balance          │   │ ← hidden data
 *              │   └─────────────────────────────┘   │
 *              │   public:  deposit()  withdraw()    │ ← the only doors
 *              │            getBalance()             │
 *              └─────────────────────────────────────┘
 *                         ▲
 *              outside code (main) uses ONLY the doors
 *
 *  Key words
 *  ────────────────────────────────────────────────────────────────────────────
 *   Encapsulation     ─► bundling data + methods inside a class
 *   Data hiding       ─► stopping direct access to an object's data
 *   Access modifiers  ─► public, private, protected
 *   Interface         ─► the public methods used to safely read / change
 *                        private data
 *   Invariant         ─► a rule that must ALWAYS be true for the object
 *                        (balance >= 0, age between 0 and 150)
 *
 *  Advantages
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Data security — nobody can put wrong values directly
 *  ✔ Data hiding — users see only what they need
 *  ✔ Controlled access using getters / setters
 *  ✔ Validation can be added in setters (validation laga sakte hain)
 *  ✔ Code is easier to maintain and reuse
 *  ✔ Change the INSIDE of the class → outside code doesn't need changes
 *
 *  ⚠ Encapsulation ≠ only "make everything private + add get/set for all".
 *    Give only the methods that make sense (deposit, not setBalance).
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Introduction (BankAccount)   ─► data + rules inside one class
 *   Data binding                 ─► data + functions together
 *   Data hiding                  ─► private data, public functions
 *   Interfaces for safe access   ─► getters / setters
 *   Setters with validation      ─► keep the invariant always true
 *   const-correctness            ─► getters are const, params const&
 *   Returning a reference ⚠      ─► leaks private data, breaks it
 *   Change inside, not outside   ─► the biggest benefit
 *   Real-life: Student info      ─► marks, grade, read-only roll no
 *   Benefits                     ─► security, maintainability
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Introduction — Bank Account
│  ✔ accountNumber and balance are private → can't be changed directly
│  ✔ deposit() / withdraw() check the amount before changing balance
│  ✔ getBalance() / getAccountNumber() only READ (marked const)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    double balance;

public:
    BankAccount(string accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew: " << amount << endl;
        } else {
            cout << "Invalid withdrawal amount!" << endl;
        }
    }

    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
};

int main() {

    BankAccount myAccount("123456789", 1000.0);
    cout << "Account: " << myAccount.getAccountNumber() << endl;
    // Account: 123456789

    myAccount.deposit(500.0);                    // Deposited: 500
    cout << myAccount.getBalance() << endl;      // 1500

    myAccount.withdraw(200.0);                   // Withdrew: 200
    cout << myAccount.getBalance() << endl;      // 1300

    myAccount.withdraw(2000.0);                  // Invalid withdrawal amount!
    myAccount.deposit(-50);                      // Invalid deposit amount!

    // myAccount.balance = 1000000;              // ERROR: private

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Data binding (data + function)
│  ✔ Definition : Encapsulation BINDS data members and member functions
│                 together in one class.
│  ✔ Data members hold the STATE, member functions define the BEHAVIOUR
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;                         // state
    int age;

public:
    void setDetails(string studentName, int studentAge) {    // behaviour
        name = studentName;
        age = studentAge;
    }

    void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {

    Student student1;
    student1.setDetails("Alice", 20);
    student1.displayDetails();           // Name: Alice, Age: 20

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Data hiding using access modifiers
│  ✔ Definition : Make data members private so they are HIDDEN from
│                 outside. Public member functions give controlled access.
│  ✔ setSalary() refuses a negative salary
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    double salary = 0;

public:
    void setName(string empName) { name = empName; }

    void setSalary(double empSalary) {
        if (empSalary >= 0) salary = empSalary;
        else cout << "Invalid salary!" << endl;
    }

    void displayInfo() {
        cout << "Employee: " << name << ", Salary: " << salary << endl;
    }
};

int main() {

    Employee emp;
    emp.setName("Bob");
    emp.setSalary(50000);
    emp.setSalary(-100);                 // Invalid salary!
    emp.displayInfo();                   // Employee: Bob, Salary: 50000

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Interfaces for safe access — getters and setters ->
│      Type getX() const { return x; }
│      void setX(Type v) { if (valid(v)) x = v; }
│
│  ✔ Definition : Public getter methods READ private data, public setter
│                 methods CHANGE it — after checking the new value.
│  ✔ The public methods are the "interface" of the class
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string productName;
    double price = 0;

public:
    void setProductName(string name) { productName = name; }    // setters

    void setPrice(double productPrice) {
        if (productPrice >= 0) price = productPrice;
        else cout << "Invalid price!" << endl;
    }

    string getProductName() const { return productName; }       // getters
    double getPrice() const { return price; }
};

int main() {

    Product prod;
    prod.setProductName("Laptop");
    prod.setPrice(1200.50);
    prod.setPrice(-1);                   // Invalid price!

    cout << "Product: " << prod.getProductName()
         << ", Price: " << prod.getPrice() << endl;
    // Product: Laptop, Price: 1200.5

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Setters with validation — keep the object ALWAYS correct
│  ✔ An invariant is a rule that must be true for the whole life of the
│    object. Here:  0 <= stock  and  price > 0
│  ✔ Check it in the CONSTRUCTOR too, not only in setters — otherwise a
│    wrong object can be created on day one
│  ✔ Give meaningful methods (addStock, sell) instead of a raw setStock
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class InventoryItem {
private:
    string name;
    int stock;
    double price;

public:
    InventoryItem(string n, int s, double p) : name(n), stock(0), price(1) {
        addStock(s);                     // reuse the same checks
        setPrice(p);
    }

    void setPrice(double p) {
        if (p <= 0) { cout << "Price must be > 0" << endl; return; }
        price = p;
    }

    void addStock(int qty) {
        if (qty < 0) { cout << "Bad quantity" << endl; return; }
        stock += qty;
    }

    bool sell(int qty) {
        if (qty <= 0 || qty > stock) {
            cout << "Can't sell " << qty << " " << name << endl;
            return false;
        }
        stock -= qty;
        return true;
    }

    void show() const {
        cout << name << ": " << stock << " left @ Rs." << price << endl;
    }
};

int main() {

    InventoryItem pen("Pen", 10, 5);
    pen.sell(3);
    pen.show();                          // Pen: 7 left @ Rs.5

    pen.sell(50);                        // Can't sell 50 Pen
    pen.addStock(-4);                    // Bad quantity
    pen.setPrice(0);                     // Price must be > 0
    pen.show();                          // Pen: 7 left @ Rs.5

    InventoryItem bad("Ink", -2, -9);
    // Bad quantity
    // Price must be > 0
    bad.show();                          // Ink: 0 left @ Rs.1

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  const-correctness
│  ✔ Definition : Mark everything that does NOT change data as const:
│        • getters / show functions          → int get() const
│        • object parameters you only read   → const T& obj
│  ✔ Then the compiler itself stops accidental changes
│  ✔ And const objects can still use your read-only functions
│  ⚠ If a getter is NOT const, a const object can't call it
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    string title;
    double rating;

public:
    Movie(string t, double r) : title(t), rating(r) {}

    string getTitle() const { return title; }        // read only
    double getRating() const { return rating; }

    void setRating(double r) { rating = r; }         // changes data
};

void printCard(const Movie& m) {                     // read-only param
    cout << m.getTitle() << " - rating " << m.getRating() << endl;
    // m.setRating(1);                               // ERROR: m is const
}

int main() {

    const Movie classic("Sholay", 8.1);
    printCard(classic);                  // Sholay - rating 8.1
    // classic.setRating(9);             // ERROR: const object

    Movie m("Dangal", 8.3);
    m.setRating(8.4);
    printCard(m);                        // Dangal - rating 8.4

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  ⚠ Returning a reference / pointer to private data breaks encapsulation
│  ✔ If a getter returns  T&  (non-const), outside code gets a "remote
│    control" to the private member and can change it, skipping every
│    check
│  ✔ Fix: return by value, or return  const T&  (read-only)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
using namespace std;

class Classroom {
private:
    vector<int> marks{70, 85, 90};

public:
    vector<int>& badGetMarks() { return marks; }             // ⚠ leak
    const vector<int>& getMarks() const { return marks; }    // ✔ safe

    void addMark(int m) {
        if (m >= 0 && m <= 100) marks.push_back(m);
    }
};

int main() {

    Classroom c;

    c.badGetMarks().push_back(-500);     // no check! private data changed
    cout << c.getMarks().back() << endl; // -500  (broken)

    // c.getMarks().push_back(1);        // ERROR: const reference

    c.addMark(95);                       // the correct way
    cout << c.getMarks().back() << endl; // 95

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  The BIG benefit — change the inside, outside code stays the same
│  ✔ Version 1 stored money as double rupees.
│  ✔ Version 2 (below) stores it as long long paise (no rounding errors)
│  ✔ main() did NOT change at all, because it only used the public
│    methods. That's maintainability.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Wallet {
private:
    long long paise = 0;                 // inside changed: was double rupees

public:
    void add(double rupees) { paise += (long long)(rupees * 100 + 0.5); }
    double getRupees() const { return paise / 100.0; }
};

int main() {                             // same main for both versions

    Wallet w;
    w.add(0.10);
    w.add(0.20);
    cout << w.getRupees() << endl;       // 0.3

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Real life — Student info
│  ✔ rollNo is set once in the constructor → getter only, NO setter
│  ✔ marks can change, but only between 0 and 100
│  ✔ grade is NOT stored — it is worked out from marks, so it can never
│    be out of date
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class StudentInfo {
private:
    const int rollNo;
    string name;
    int marks = 0;

public:
    StudentInfo(int r, string n) : rollNo(r), name(n) {}

    int getRollNo() const { return rollNo; }
    string getName() const { return name; }

    void setMarks(int m) {
        if (m < 0 || m > 100) { cout << "Marks 0-100 only" << endl; return; }
        marks = m;
    }

    char getGrade() const {
        if (marks >= 90) return 'A';
        if (marks >= 75) return 'B';
        if (marks >= 50) return 'C';
        return 'F';
    }
};

int main() {

    StudentInfo s(7, "Neha");
    s.setMarks(92);
    cout << s.getRollNo() << " " << s.getName() << " "
         << s.getGrade() << endl;        // 7 Neha A

    s.setMarks(130);                     // Marks 0-100 only
    s.setMarks(60);
    cout << s.getGrade() << endl;        // C

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Benefits of encapsulation (security, maintainability)
│  ✔ Security        : data is protected from wrong / unauthorised access
│  ✔ Maintainability : easier to change and fix — only one class to look at
│  ✔ Modularity      : the class can be reused in other projects
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Square {
private:
    double side = 0;

public:
    void setSide(double s) {
        if (s >= 0) side = s;
        else cout << "Invalid side length!" << endl;
    }

    double area() const { return side * side; }
};

int main() {

    Square sq;
    sq.setSide(5.0);
    sq.setSide(-3);                      // Invalid side length!
    cout << "Area: " << sq.area() << endl;   // Area: 25

    return 0;
}
