/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                 INTRODUCTION TO OBJECT ORIENTED PROGRAMMING               ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is OOP?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ OOP (Object-Oriented Programming) is a way of writing programs where
 *    we build the program around OBJECTS, not around functions
 *  ✔ An object is a thing from real life that we put into code:
 *        a Student, a Car, a Bank Account, a Mobile Phone ...
 *  ✔ Every object has 2 parts:
 *        a. Attributes → the DATA it has      (fields / properties)
 *        b. Methods    → the WORK it can do   (functions / operations)
 *
 *              ┌────────────────────────────────────┐
 *              │            OBJECT : Car            │
 *              ├────────────────────────────────────┤
 *              │  Attributes   brand  = "BMW"       │  ← what it HAS
 *              │               speed  = 120         │
 *              ├────────────────────────────────────┤
 *              │  Methods      start()              │  ← what it DOES
 *              │               brake()              │
 *              └────────────────────────────────────┘
 *
 *  ✔ Goal → make code modular, reusable, scalable and easy to maintain,
 *    by keeping data and the functions that use it together in one place
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   1)  WHY OOP?  (BENEFITS)                                                ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Modularity       ─► code is split into separate, logical objects
 *   Reusability      ─► classes can be reused in many projects
 *   Maintainability  ─► change one class without breaking other parts
 *   Encapsulation    ─► internal data is protected with access control
 *   Inheritance      ─► make new classes from existing ones
 *   Polymorphism     ─► one interface, many implementations
 *
 *  ✔ Real example: in a shopping app, "Cart", "Product", "User" and
 *    "Payment" are separate classes. A bug in Payment is fixed inside
 *    Payment only — Cart and Product stay untouched.
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   2)  POP vs OOP                                                          ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  ✔ POP (Procedure-Oriented Programming)
 *        • Focus is on FUNCTIONS (steps to do the task)
 *        • Data is usually global — any function can change it
 *  ✔ OOP (Object-Oriented Programming)
 *        • Focus is on OBJECTS (data + behaviour together)
 *        • Data is hidden and changed only through the object's methods
 *
 *   POINT            POP                        OOP
 *   ───────────────  ─────────────────────────  ─────────────────────────
 *   Focus            functions / steps          objects / data
 *   Program split    into functions             into classes & objects
 *   Data             global, open to all        hidden (private)
 *   Security         less                       more
 *   Approach         top-down                   bottom-up
 *   Reuse            hard (copy-paste)          easy (inheritance)
 *   New feature      change many functions      add a new class
 *   Real-life model  weak                       strong
 *   Languages        C, Pascal, Fortran         C++, Java, Python, C#
 *
 *  ⚠ C++ supports BOTH. You can write POP or OOP code in C++.
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   3)  CORE FEATURES OF OOP                                                ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Class            ─► blueprint for making objects
 *   Object           ─► a real instance of a class, holding real data
 *   Abstraction      ─► hide the complex part, show only what is needed
 *   Encapsulation    ─► wrap data + methods together and protect the data
 *   Inheritance      ─► build a new class on top of an existing one
 *   Polymorphism     ─► one name, many behaviours
 *   Message Passing  ─► objects talk to each other by calling methods
 *   Dynamic Binding  ─► which function runs is decided at RUN time,
 *                       based on the real type of the object
 *
 *  ✔ Easy real-life picture:
 *        Abstraction    → you press the TV remote button, you don't know
 *                         the circuit inside
 *        Encapsulation  → medicine capsule: the powder is packed inside
 *        Inheritance    → a child gets features from the parents
 *        Polymorphism   → one person: student in class, customer in shop
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   4)  RELATIONSHIP : CLASS & OBJECT                                       ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  ✔ Class  → a design / template. It says WHAT data and methods exist.
 *             No memory is used for data until an object is made.
 *  ✔ Object → a real thing made from the class. It holds actual values.
 *  ✔ One class → as many objects as you want
 *
 *                       ┌─────────────────────┐
 *                       │    class Student    │   (blueprint)
 *                       │  name, roll, marks  │
 *                       └──────────┬──────────┘
 *                ┌─────────────────┼─────────────────┐
 *                ▼                 ▼                 ▼
 *         ┌────────────┐    ┌────────────┐    ┌────────────┐
 *         │ s1         │    │ s2         │    │ s3         │
 *         │ "Amit", 1  │    │ "Neha", 2  │    │ "Ravi", 3  │
 *         └────────────┘    └────────────┘    └────────────┘
 *
 *  ✔ Like a house map (class) and the real houses built from it (objects)
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   5)  COMMON TERMS                                                        ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Data Members      ─► variables that store data inside a class
 *   Member Functions  ─► functions that work on the data members
 *   Methods           ─► another name for member functions
 *   Messages          ─► calling a method of an object (obj.method())
 *   Instance          ─► another name for an object
 *   Instantiation     ─► the act of creating an object from a class
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   6)  C++ IS MULTI-PARADIGM                                               ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  ✔ "Paradigm" = a style of writing programs
 *  ✔ C++ is not ONLY OOP. It lets you mix 3 styles:
 *        a. Procedural → plain functions (like C)
 *        b. OOP        → classes and objects
 *        c. Generic    → templates (one code for many types, like STL)
 *  ✔ Java forces everything inside a class. C++ does not.
 *  ✔ Good C++ code picks the right style for each part.
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   SUMMARY                                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  ✔ OOP gives a clean, structured and scalable way to build software
 *  ✔ By keeping data and behaviour together, it improves:
 *        code organization, reusability, maintainability,
 *        flexibility and readability
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  POP style — Bank Account with global data
│  ✔ Data (balance) is global, functions work on it from outside
│  ✔ It works, but ANY code can change balance directly
│  ⚠ Problem: no protection — balance can become wrong (negative)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

double balance = 0;                      // global data — open to everyone

void deposit(double amount) {
    balance += amount;
}

void withdraw(double amount) {
    if (amount <= balance) balance -= amount;
    else cout << "Not enough money" << endl;
}

int main() {

    deposit(1000);
    withdraw(300);
    cout << "Balance: " << balance << endl;     // Balance: 700

    withdraw(5000);                             // Not enough money

    // nothing stops this — the rule inside withdraw() is skipped
    balance = -99999;
    cout << "Balance: " << balance << endl;     // Balance: -99999  (bug!)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  OOP style — the SAME Bank Account as a class
│  ✔ balance is private → only the class's own methods can touch it
│  ✔ Outside code must use deposit() / withdraw(), so the rules always run
│  ✔ Many accounts = many objects, each with its own balance
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string owner;
    double balance = 0;                  // hidden data

public:
    BankAccount(string name) { owner = name; }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) balance -= amount;
        else cout << owner << ": Not enough money" << endl;
    }

    double getBalance() { return balance; }
};

int main() {

    BankAccount a("Amit");
    BankAccount b("Neha");               // separate object, separate data

    a.deposit(1000);
    a.withdraw(300);
    b.deposit(500);

    cout << a.getBalance() << endl;      // 700
    cout << b.getBalance() << endl;      // 500

    b.withdraw(2000);                    // Neha: Not enough money

    // a.balance = -99999;               // ERROR: balance is private

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Class & Object — one blueprint, many objects
│  ✔ class Student is written ONCE
│  ✔ s1, s2, s3 are 3 objects; each keeps its own name and marks
│  ✔ Calling s1.show() is "sending a message" to the object s1
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;                         // data members
    int marks;

    void show() {                        // member function (method)
        cout << name << " got " << marks << endl;
    }

    bool passed() { return marks >= 40; }
};

int main() {

    Student s1, s2, s3;                  // 3 objects (instances)

    s1.name = "Amit";  s1.marks = 85;
    s2.name = "Neha";  s2.marks = 92;
    s3.name = "Ravi";  s3.marks = 35;

    s1.show();                           // Amit got 85
    s2.show();                           // Neha got 92
    s3.show();                           // Ravi got 35

    cout << boolalpha;
    cout << s3.passed() << endl;         // false

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Message Passing — objects talk by calling each other's methods
│  ✔ Order does not handle money itself; it sends a message to Payment
│  ✔ Each class does its own job → easy to change one without the other
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Payment {
public:
    bool pay(string user, double amount) {
        cout << "Charging " << user << " Rs." << amount << endl;
        return true;
    }
};

class Order {
private:
    string user;
    double total;

public:
    Order(string u, double t) { user = u; total = t; }

    void placeOrder(Payment& p) {
        if (p.pay(user, total))                 // message to Payment
            cout << "Order placed for " << user << endl;
    }
};

int main() {

    Payment upi;
    Order o("Amit", 499);

    o.placeOrder(upi);
    // Charging Amit Rs.499
    // Order placed for Amit

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  All 4 pillars in one small program (a quick preview)
│  ✔ Abstraction    → Shape only says "every shape has area()"
│  ✔ Encapsulation  → radius / side are private, set via constructor
│  ✔ Inheritance    → Circle and Square are made from Shape
│  ✔ Polymorphism + Dynamic Binding → s->area() calls the RIGHT version
│                     at run time, even though s is a Shape pointer
│  ⚠ Each idea has its own file later — this is only a first look
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Shape {                                   // abstraction
public:
    virtual double area() = 0;                  // "every shape has area"
    virtual ~Shape() {}
};

class Circle : public Shape {                   // inheritance
private:
    double r;                                   // encapsulation
public:
    Circle(double radius) { r = radius; }
    double area() override { return 3.14 * r * r; }
};

class Square : public Shape {
private:
    double side;
public:
    Square(double s) { side = s; }
    double area() override { return side * side; }
};

int main() {

    Shape* shapes[] = { new Circle(1), new Square(4) };

    for (Shape* s : shapes)
        cout << s->area() << endl;              // polymorphism
    // 3.14
    // 16

    for (Shape* s : shapes) delete s;

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  C++ is multi-paradigm — one task in 3 styles
│  ✔ Task: find the total price of items in a cart
│  ✔ Procedural → a plain function
│  ✔ OOP        → a Cart class that owns its items
│  ✔ Generic    → a template that works for int, double, ... any type
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
using namespace std;

// 1. Procedural
double totalOf(const vector<double>& prices) {
    double sum = 0;
    for (double p : prices) sum += p;
    return sum;
}

// 2. OOP
class Cart {
private:
    vector<double> prices;
public:
    void add(double p) { prices.push_back(p); }
    double total() { return totalOf(prices); }
};

// 3. Generic
template <typename T>
T sumAll(const vector<T>& items) {
    T sum = 0;
    for (const T& x : items) sum += x;
    return sum;
}

int main() {

    cout << totalOf({100, 250.5}) << endl;      // 350.5

    Cart c;
    c.add(100);
    c.add(50);
    cout << c.total() << endl;                  // 150

    cout << sumAll<int>({1, 2, 3}) << endl;     // 6
    cout << sumAll<double>({1.5, 2.5}) << endl; // 4

    return 0;
}
