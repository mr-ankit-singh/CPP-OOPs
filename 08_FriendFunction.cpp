/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                     FRIEND FUNCTION AND FRIEND CLASS                      ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is "friend"?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ By default, PRIVATE and PROTECTED members can be used ONLY by the
 *    class's own member functions — not by outside functions or other
 *    classes
 *  ✔ The "friend" keyword lets a class break this rule ON PURPOSE, for a
 *    SPECIFIC function or a SPECIFIC class — giving it full access to
 *    its private and protected members
 *  ✔ A friend function is defined OUTSIDE the class, yet it can access
 *    all private and protected members. Its prototype appears inside
 *    the class, but it is NOT a member.
 *  ✔ Real life: your house is private, but you give a spare key to ONE
 *    trusted friend — not to the whole street
 *
 *  Types
 *  ────────────────────────────────────────────────────────────────────────────
 *   Friend function         ─► ONE specific function gets access
 *   Friend member function  ─► ONE member function of another class
 *   Friend class            ─► EVERY function of another class
 *
 *  Why does it exist?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Sometimes two closely related classes / functions must work
 *    together (operator overloading, two-class comparison). friend
 *    allows this WITHOUT making the data public for everyone.
 *
 *  Friendship rules  ⭐
 *  ────────────────────────────────────────────────────────────────────────────
 *   NOT inherited    ─► A friend of Base is NOT a friend of Derived
 *   NOT mutual       ─► A is B's friend does NOT mean B is A's friend
 *   NOT transitive   ─► A friend of B, B friend of C → A NOT friend of C
 *   Given, not taken ─► only the class itself can declare its friends
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   FRIEND FUNCTION
 *   ───────────────
 *   Declaration and syntax          ─► friend void f(A& a);
 *   Access to private / protected   ─► reads both directly
 *   Use case: operator overloading  ─► 5 + obj,  cout << obj
 *   Use case: two-class talk        ─► one friend of two classes
 *   Defined inside the class        ─► "hidden friend"
 *
 *   FRIEND CLASS / MEMBER
 *   ─────────────────────
 *   Friend member function          ─► friend void B::f(A&);
 *   Friend class                    ─► friend class B;
 *   Rules: not inherited / mutual / transitive
 *   Advantages and risks
 *
 *   COMPARE
 *   ───────
 *   Friend vs member function       ─► table + example
 *   Interview questions
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Friend function — declaration and syntax ->
│      class A { friend ReturnType f(A& a); };     // inside: declare
│      ReturnType f(A& a) { ... a.privateData ... } // outside: define
│
│  ✔ Definition : A NON-member function that the class allows to use its
│                 private / protected members.
│  ✔ Call it like a NORMAL function: addValue(d1), NOT d1.addValue()
│  ✔ "friend" is written ONLY inside the class giving access — not in
│    the definition, and NO  Distance::  prefix (it's not a member)
│  ✔ It can be declared in public, private or protected section — makes
│    NO difference (access labels only control MEMBERS)
│  ✔ It needs an object as a PARAMETER — it has no "this"
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Distance {
private:
    int meters = 0;

public:
    void displayData() { cout << "Meter value: " << meters << endl; }

    friend void addValue(Distance& d);       // declaration with friend
};

void addValue(Distance& d) {                 // no friend, no Distance::
    d.meters = d.meters + 5;                 // private access: OK
}

int main() {

    Distance d1;
    d1.displayData();                        // Meter value: 0

    addValue(d1);                            // normal function call
    d1.displayData();                        // Meter value: 5

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Access to private AND protected members
│  ✔ A friend function reads private and protected members DIRECTLY,
│    exactly like a member function — no getters needed
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    double salary;                           // private

protected:
    string designation;                      // protected

public:
    Employee(double s, string d) : salary(s), designation(d) {}

    friend void showConfidentialInfo(const Employee& e);
};

void showConfidentialInfo(const Employee& e) {
    cout << "Designation (protected): " << e.designation << endl;
    cout << "Salary (private): " << e.salary << endl;
}

int main() {

    Employee emp(75000, "Software Engineer");
    showConfidentialInfo(emp);
    // Designation (protected): Software Engineer
    // Salary (private): 75000

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Use case — operator overloading (very common real use)
│  ✔ A MEMBER operator always gets the LEFT side as "this". So for
│    5 + c  the left side is an int → a member can't handle it.
│  ✔ A FRIEND operator takes BOTH sides as parameters → works for
│    c1 + c2,  c + 5  AND  5 + c
│  ✔ cout << obj  is the same story: the left side is cout, not your
│    class → operator<< is almost always a friend
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Complex {
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    friend Complex operator+(const Complex& c1, const Complex& c2);
    friend ostream& operator<<(ostream& out, const Complex& c);
};

Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

ostream& operator<<(ostream& out, const Complex& c) {
    out << c.real << " + " << c.imag << "i";
    return out;
}

int main() {

    Complex c1(2, 3), c2(4, 5);

    cout << c1 + c2 << endl;                 // 6 + 8i
    cout << c1 + 5 << endl;                  // 7 + 3i   (5 → Complex(5))
    cout << 5 + c1 << endl;                  // 7 + 3i   (works: friend!)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Use case — two-class communication
│  ✔ ONE function can be a friend of TWO classes at once, and read the
│    private data of both — to compare or combine them
│  ✔ Needs a FORWARD DECLARATION (class Fahrenheit;) because Celsius
│    mentions Fahrenheit before it is defined
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Fahrenheit;                            // forward declaration

class Celsius {
private:
    double temp;

public:
    Celsius(double t) : temp(t) {}
    friend bool isSameTemperature(const Celsius& c, const Fahrenheit& f);
};

class Fahrenheit {
private:
    double temp;

public:
    Fahrenheit(double t) : temp(t) {}
    friend bool isSameTemperature(const Celsius& c, const Fahrenheit& f);
};

bool isSameTemperature(const Celsius& c, const Fahrenheit& f) {
    double converted = (c.temp * 9 / 5) + 32;    // C → F
    return converted == f.temp;
}

int main() {

    Celsius boiling(100);
    Fahrenheit boilingF(212);
    Fahrenheit room(70);

    cout << boolalpha;
    cout << isSameTemperature(boiling, boilingF) << endl;    // true
    cout << isSameTemperature(boiling, room) << endl;        // false

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Friend function defined INSIDE the class ("hidden friend") ->
│      class A { friend void f(const A& a) { ... } };
│
│  ✔ Definition : You can write the friend's whole body inside the class.
│                 It is STILL not a member (no this, called as f(a)).
│  ✔ Found only through its argument (ADL), so it doesn't fill the
│    global namespace → the modern, preferred style for operator<<
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Product {
    string name;
    double price;

public:
    Product(string n, double p) : name(n), price(p) {}

    friend ostream& operator<<(ostream& out, const Product& p) {
        return out << p.name << " (Rs." << p.price << ")";
    }

    friend bool cheaper(const Product& a, const Product& b) {
        return a.price < b.price;
    }
};

int main() {

    Product pen("Pen", 10), book("Book", 250);

    cout << pen << endl;                     // Pen (Rs.10)
    cout << boolalpha << cheaper(pen, book) << endl;   // true

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Friend MEMBER function of another class ->
│      class A;                                   // 1. forward declare A
│      class B { public: void show(A& a); };      // 2. B fully defined
│      class A { friend void B::show(A& a); };    // 3. A gives access
│      void B::show(A& a) { ... }                 // 4. body after A
│
│  ✔ Definition : Instead of the WHOLE class B, only ONE member function
│                 of B gets access to A's private data. Tighter control
│                 than a friend class.
│  ⚠ Order matters: B must be fully defined BEFORE A names B::show
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class BankAccount;                           // 1

class Auditor {                              // 2
public:
    void audit(const BankAccount& acc);      // only this gets access
    void chat() { cout << "Auditor says hi" << endl; }
};

class BankAccount {                          // 3
    double balance = 125000;
    friend void Auditor::audit(const BankAccount& acc);
};

void Auditor::audit(const BankAccount& acc) {    // 4
    cout << "Audited balance: " << acc.balance << endl;
}

int main() {

    BankAccount acc;
    Auditor a;
    a.audit(acc);                            // Audited balance: 125000
    a.chat();                                // Auditor says hi
                                             // (chat can NOT see balance)
    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Friend class ->
│      class A { friend class B; };       // ALL of B's functions can
│                                         // use A's private members
│
│  ✔ Definition : Make a WHOLE other class a friend. Every member
│                 function of that class can access this class's private
│                 and protected members.
│  ✔ Good for classes that naturally work as a PAIR:
│    Engine + Car,  Container + its Iterator,  LinkedList + Node
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Engine {
private:
    int horsepower;
    bool running = false;

public:
    Engine(int hp) : horsepower(hp) {}

    friend class Car;                        // whole Car class is a friend
};

class Car {
public:
    void showEngineSpecs(const Engine& e) {
        cout << "Engine horsepower: " << e.horsepower << " HP" << endl;
    }

    void start(Engine& e) {
        e.running = true;                    // another member: also OK
        cout << "Engine running: " << boolalpha << e.running << endl;
    }
};

int main() {

    Engine engine(450);
    Car car;
    car.showEngineSpecs(engine);             // Engine horsepower: 450 HP
    car.start(engine);                       // Engine running: true

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Friendship is NOT inherited, NOT mutual, NOT transitive
│  ✔ Not inherited : Car is Engine's friend. SportsCar (child of Car) is
│                    NOT Engine's friend.
│  ✔ Not mutual    : Car can see Engine's private data, but Engine can
│                    NOT see Car's private data.
│  ✔ Not transitive: Engine is Battery's friend and Car is Engine's
│                    friend — Car is still NOT Battery's friend.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Battery {
    int charge = 80;
    friend class Engine;                     // Engine may see charge
};

class Engine {
    int hp = 300;
    friend class Car;                        // Car may see hp

public:
    int readCharge(const Battery& b) { return b.charge; }   // OK
};

class Car {
    int fuel = 40;

public:
    int readHp(const Engine& e) { return e.hp; }            // OK
    // int readCharge(const Battery& b) { return b.charge; }
    //                       ↑ ERROR: not transitive
};

class SportsCar : public Car {
public:
    // int hp2(const Engine& e) { return e.hp; }
    //                       ↑ ERROR: not inherited
};

int main() {

    Battery b;
    Engine e;
    Car c;

    cout << e.readCharge(b) << endl;         // 80
    cout << c.readHp(e) << endl;             // 300
    // Engine can't read c.fuel either        → not mutual

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Advantages and risks
│  ✔ Advantages:
│        • closely related classes / functions share data WITHOUT
│          making it public — encapsulation stays for everyone else
│        • needed for some operators (5 + obj,  cout << obj)
│        • natural for pairs like Iterator + Container
│  ⚠ Risks:
│        • breaks encapsulation a little — the friend can change private
│          data in ways the class didn't plan
│        • overusing friend is a "code smell": if many functions need
│          it, the class's public interface should be redesigned
│        • friends depend on private details → changing the inside of
│          the class may break them
│  ✔ Rule: give friendship to as FEW functions as possible; prefer a
│    friend FUNCTION / member over a whole friend CLASS
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Matrix {
    int a[2][2];

public:
    Matrix(int w, int x, int y, int z) {
        a[0][0] = w; a[0][1] = x;
        a[1][0] = y; a[1][1] = z;
    }

    // a small, focused friend — just what is needed
    friend Matrix operator*(const Matrix& m, int k) {
        return Matrix(m.a[0][0] * k, m.a[0][1] * k,
                      m.a[1][0] * k, m.a[1][1] * k);
    }

    void show() const {
        cout << a[0][0] << " " << a[0][1] << " | "
             << a[1][0] << " " << a[1][1] << endl;
    }
};

int main() {

    Matrix m(1, 2, 3, 4);
    (m * 3).show();                          // 3 6 | 9 12

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Friend function vs member function
│
│   POINT                     FRIEND FUNCTION        MEMBER FUNCTION
│   ────────────────────────  ─────────────────────  ─────────────────────
│   Belongs to the class?     NO                     YES
│   How to call               func(obj)              obj.func()
│   Needs object as param?    YES                    NO (has "this")
│   "this" pointer?           NO                     YES
│   Inherited?                NO                     YES
│   Can be virtual?           NO                     YES
│   Left side of an operator  any type (5 + obj)     must be the class
│
│  ✔ Prefer a member function. Use friend only when a member can't do
│    the job (operators with a different left side, two-class access).
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Box {
private:
    double width;

public:
    Box(double w) : width(w) {}

    double getWidthMember() { return width; }        // this->width

    friend double getWidthFriend(const Box& b);
};

double getWidthFriend(const Box& b) {
    return b.width;                          // must say WHICH object
}

int main() {

    Box box(12.5);
    cout << "Member: " << box.getWidthMember() << endl;  // Member: 12.5
    cout << "Friend: " << getWidthFriend(box) << endl;   // Friend: 12.5

    return 0;
}


/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   🎯 INTERVIEW QUESTIONS                                                  ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Q1  What is a friend function? How is it different from a member?
 *      → It can access the class's private / protected members, but it
 *        is NOT a member. So it is called like a normal function
 *        (func(obj), not obj.func()), and the object must be passed as a
 *        parameter.
 *
 *  Q2  Does a friend function break encapsulation?
 *      → A little, yes — private data becomes reachable from outside.
 *        But it is CONTROLLED: only the functions / classes the class
 *        itself names get access. Encapsulation is not destroyed, only
 *        specific exceptions are made.
 *
 *  Q3  Is friendship inherited?
 *      → NO. If A is a friend of B, and C inherits from A, C is NOT
 *        automatically a friend of B. Declare it separately.
 *
 *  Q4  Is friendship transitive?
 *      → NO. A friend of B, B friend of C → A is NOT a friend of C.
 *        Every friendship is independent.
 *
 *  Q5  Is friendship mutual?
 *      → NO. A being B's friend doesn't make B A's friend. Declare both
 *        directions if both are needed.
 *
 *  Q6  When must an operator be a friend instead of a member?
 *      → When the LEFT side is not an object of your class:
 *        5 + complexObj,  cout << obj. A member operator always gets the
 *        left side as "this". A friend takes both sides as parameters.
 *
 *  Q7  Friend class vs friend function?
 *      → Friend function: ONE specific function gets access.
 *        Friend class: ALL member functions of that class get access.
 *
 *  Q8  What are the risks of overusing friend?
 *      → Encapsulation is effectively lost, the code becomes harder to
 *        maintain, and it usually means the public interface should be
 *        redesigned.
 *
 *  Q9  Do we write "friend" again in the definition outside the class?
 *      → NO. "friend" goes only inside the class that GIVES the access.
 *        The definition outside is a normal function — no "friend" and
 *        no "ClassName::" prefix.
 *
 *  Q10 Can a friend function be declared in the private section?
 *      → Yes, and it works the same. Access labels apply only to
 *        members, and a friend is not a member.
 */
