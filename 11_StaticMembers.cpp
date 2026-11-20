/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                               STATIC MEMBERS                              ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What does "static" mean in a class?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ A static member belongs to the CLASS (the type), not to any one
 *    object (instance)
 *  ✔ So you don't need an object to use it:  ClassName::member
 *  ✔ No matter how many objects you create, there is only ONE copy of a
 *    static member, SHARED by all objects
 *  ✔ It exists even if NO object has been created
 *
 *        class Student { string name; static int total; };
 *
 *          s1                  s2                  s3
 *        ┌───────────┐       ┌───────────┐       ┌───────────┐
 *        │ name Amit │       │ name Neha │       │ name Ravi │  ← own copy
 *        └─────┬─────┘       └─────┬─────┘       └─────┬─────┘
 *              └───────────────────┼───────────────────┘
 *                                  ▼
 *                       Student::total = 3              ← ONE shared copy
 *
 *  Static data members
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Shared among all objects of the class
 *  ✔ Only one copy exists, whatever the number of objects
 *  ✔ Declared inside the class, DEFINED (given memory) outside with ::
 *        int Counter::count = 0;
 *    (or use  inline static  in C++17 — no outside line needed)
 *
 *  Static member functions
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Can use ONLY static data members / other static functions
 *  ✔ Have NO "this" pointer (they aren't called on an object)
 *  ✔ Called as  ClassName::functionName()
 *  ✔ Can't be const, can't be virtual
 *
 *  ⚠ In C++, "static" in a class applies to data members and member
 *    functions only. (Static constructors / properties / events are
 *    C# ideas — they don't exist in C++.)
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Static data member           ─► one shared copy
 *   Static member function       ─► ClassName::f(), no this
 *   Lifetime and scope           ─► lives for the whole program
 *   Initialization of static data ─► outside with ::
 *   static const / inline static ─► set inside the class (C++17)
 *   Static local inside a member ─► remembered across calls
 *   Counting objects             ─► created vs currently alive
 *   Static vs non-static         ─► table + example
 *
 *  ✔ Singleton (one object only, built with static) →
 *    18_DesignPatterns.cpp
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Static data member | static member function ->
│      class A { static int count; static int getCount(); };
│      int A::count = 0;               // definition outside the class
│      A::getCount();                  // call with the class name
│
│  ✔ Definition : count is shared by ALL Counter objects. Each new object
│                 increases the SAME count. getCount() reads it without
│                 needing any object.
│  ⚠ Forgetting  int Counter::count = 0;  → "undefined reference" error
│    at link time
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Counter {
private:
    static int count;                    // declaration

public:
    Counter() { count++; }               // every object adds 1

    static int getCount() { return count; }
};

int Counter::count = 0;                  // definition + initialization

int main() {

    cout << Counter::getCount() << endl; // 0   (no object yet — still works)

    Counter c1;
    Counter c2;
    Counter c3;

    cout << "Objects created: " << Counter::getCount() << endl;
    // Objects created: 3

    cout << c1.getCount() << endl;       // 3   (via object also allowed)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Static member function — what it can and can't do
│  ✔ It CAN use static members
│  ✔ It can NOT use normal (non-static) members directly — there is no
│    object, so no "this"
│  ✔ It CAN use non-static members of an object you PASS to it
│  ✔ Common use: helper / factory functions that belong to the class
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
    string owner;
    double balance;
    static double interestRate;          // same for every account

public:
    BankAccount(string o, double b) : owner(o), balance(b) {}

    static void setRate(double r) {
        interestRate = r;                // OK: static
        // balance = 0;                  // ERROR: no object / no this
    }

    static double getRate() { return interestRate; }

    static void printYearly(const BankAccount& a) {      // object passed
        cout << a.owner << " earns " << a.balance * interestRate << endl;
    }
};

double BankAccount::interestRate = 0.04;

int main() {

    BankAccount a("Amit", 10000), b("Neha", 50000);

    BankAccount::printYearly(a);         // Amit earns 400
    BankAccount::setRate(0.05);          // one change → all accounts
    BankAccount::printYearly(b);         // Neha earns 2500
    cout << BankAccount::getRate() << endl;  // 0.05

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Lifetime and scope of static members
│  ✔ Lifetime : a static data member is created BEFORE main() starts and
│               destroyed AFTER main() ends — it lives for the whole
│               program, not tied to any object
│  ✔ Scope    : its name is inside the class → use ClassName::member
│  ✔ Access   : public / private rules still apply. A private static can
│               be used only by the class's own functions.
│  ✔ sizeof   : static members are NOT inside each object
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Logger {
public:
    string name;
    Logger(string n) : name(n) { cout << "Logger " << name << " up" << endl; }
    ~Logger() { cout << "Logger " << name << " down" << endl; }
};

class App {
    int data[4];                         // 16 bytes per object
    static Logger log;                   // NOT inside each object

public:
    static void work() { cout << "working with " << log.name << endl; }
};

Logger App::log("main-log");             // made before main() starts

int main() {

    cout << "main starts" << endl;
    App::work();
    cout << sizeof(App) << endl;         // 16  (static log not counted)
    cout << "main ends" << endl;

    return 0;
}
// Output:
// Logger main-log up
// main starts
// working with main-log
// 16
// main ends
// Logger main-log down


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Initialization of static data ->
│      class A { static int x; };          int A::x = 10;      // classic
│      class A { static const int MAX = 100; };                // const int
│      class A { inline static int x = 10; };                  // C++17
│      class A { static constexpr double PI = 3.14159; };      // constexpr
│
│  ✔ Classic: declare inside, DEFINE once outside (in ONE .cpp file)
│  ✔ static const of an INTEGER type can be set inside the class
│  ✔ inline static (C++17): set inside the class, any type, no outside
│    line needed — the modern, easy way
│  ✔ static constexpr: compile-time constants, inside the class
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Config {
public:
    static int maxUsers;                             // classic
    static const int MAX_RETRY = 3;                  // const integer
    inline static string appName = "ShopApp";        // C++17
    inline static vector<string> admins = {"root"};  // any type
    static constexpr double GST = 0.18;              // constexpr
};

int Config::maxUsers = 500;              // classic needs this line

int main() {

    cout << Config::maxUsers << endl;    // 500
    cout << Config::MAX_RETRY << endl;   // 3
    cout << Config::appName << endl;     // ShopApp
    cout << Config::GST << endl;         // 0.18

    Config::admins.push_back("neha");
    cout << Config::admins.size() << endl;   // 2

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Static local variable inside a member function
│  ✔ A static variable inside a function is created the FIRST time the
│    function runs, and it KEEPS its value between calls
│  ✔ Inside a MEMBER function it is still ONE copy for ALL objects
│    (just like a static data member, but visible only in that function)
│  ✔ Its first initialization is thread-safe since C++11
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Ticket {
public:
    int number;

    Ticket() { number = nextNumber(); }

    static int nextNumber() {
        static int last = 1000;          // set ONCE, remembered after
        return ++last;
    }
};

class Button {
public:
    void click() {
        static int clicks = 0;           // shared by ALL buttons
        clicks++;
        cout << "total clicks: " << clicks << endl;
    }
};

int main() {

    Ticket t1, t2, t3;
    cout << t1.number << " " << t2.number << " " << t3.number << endl;
    // 1001 1002 1003

    Button ok, cancel;
    ok.click();                          // total clicks: 1
    cancel.click();                      // total clicks: 2  (same variable!)
    ok.click();                          // total clicks: 3

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Counting objects with a static counter
│  ✔ created  → goes up in EVERY constructor (normal AND copy)
│  ✔ alive    → up in constructors, DOWN in the destructor
│  ⚠ Don't forget the copy constructor — otherwise copies are not
│    counted, but their destructors still decrease "alive"
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Player {
public:
    inline static int created = 0;
    inline static int alive = 0;

    Player() { created++; alive++; }
    Player(const Player&) { created++; alive++; }
    ~Player() { alive--; }

    static void report() {
        cout << "created " << created << ", alive " << alive << endl;
    }
};

int main() {

    Player p1, p2;
    Player::report();                    // created 2, alive 2

    {
        Player p3 = p1;                  // copy
        Player::report();                // created 3, alive 3
    }                                    // p3 dies

    Player::report();                    // created 3, alive 2

    Player* p4 = new Player;
    Player::report();                    // created 4, alive 3
    delete p4;
    Player::report();                    // created 4, alive 2

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Static vs non-static members
│
│   POINT               STATIC                     NON-STATIC
│   ──────────────────  ─────────────────────────  ─────────────────────────
│   Belongs to          the class                  each object
│   Copies              ONE for all objects        one per object
│   Exists              before any object, until   from object's creation
│                       program ends               to its destruction
│   Access              ClassName::m  (or obj.m)   obj.m only
│   this pointer        NO (functions)             YES
│   Can use             only static members        static AND non-static
│   Inside sizeof(obj)  NO                         YES
│   Can be virtual?     NO                         YES
│
│  ✔ Use static for data that is the SAME for all objects (rate, count,
│    settings) or helper functions that need no object
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    string name;                         // non-static: per employee
    inline static string company = "TechCorp";   // static: shared

    Employee(string n) : name(n) {}

    void show() const {                  // non-static: can use both
        cout << name << " @ " << company << endl;
    }

    static void rename(string c) {       // static: only static members
        company = c;
    }
};

int main() {

    Employee a("Amit"), b("Neha");
    a.show();                            // Amit @ TechCorp
    b.show();                            // Neha @ TechCorp

    Employee::rename("TechCorp Global"); // changes it for EVERYONE
    a.show();                            // Amit @ TechCorp Global
    b.show();                            // Neha @ TechCorp Global

    return 0;
}
