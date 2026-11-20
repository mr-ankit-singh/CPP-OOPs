/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                      CONSTRUCTORS AND DESTRUCTORS                         ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is a Constructor?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ A special member function that runs AUTOMATICALLY when an object
 *    is created
 *  ✔ Its job: give the object correct starting values (initialize it)
 *  ✔ Same name as the class, NO return type (not even void)
 *  ✔ It can be defined inside or outside the class
 *  ✔ Usually placed in the public section
 *  ✔ It can take parameters, so objects can start with different values
 *
 *  What is a Destructor?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ A special member function that runs AUTOMATICALLY when an object
 *    is destroyed (goes out of scope, or is deleted)
 *  ✔ Its job: clean up — free memory, close files, release locks
 *  ✔ Name = ~ClassName, no return type, NO parameters
 *
 *        {
 *            Car c;          ← constructor runs  (object is born)
 *            c.drive();
 *        }                   ← destructor runs   (object dies)
 *
 *  Characteristics of Constructors
 *  ────────────────────────────────────────────────────────────────────────────
 *   Name             ─► same as the class name
 *   Return type      ─► none, not even void
 *   Called           ─► automatically when an object is created
 *   Purpose          ─► initialize the data members
 *   Access           ─► usually public
 *   Overloading      ─► yes, many constructors with different parameters
 *   Explicit call    ─► you don't call it like a normal function
 *   Inherited?       ─► no (but C++11 can "bring" them: see 06)
 *   virtual?         ─► no, a constructor can't be virtual
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   TYPES OF CONSTRUCTORS
 *   ─────────────────────
 *   Default constructor        ─► A()
 *   Parameterized constructor  ─► A(int x, int y)
 *   Copy constructor           ─► A(const A& other)
 *   Move constructor           ─► A(A&& other)            (C++11)
 *   Conversion constructor     ─► A(int x)  → allows  A a = 5;
 *   Default arguments          ─► A(int x = 0)
 *   Constructor overloading    ─► many constructors in one class
 *   Outside the class          ─► A::A() { ... }
 *
 *   INITIALIZING MEMBERS
 *   ────────────────────
 *   Initialization list        ─► A(int v) : x(v) { }
 *   Init order                 ─► order of DECLARATION, not of the list
 *   In-class initializers      ─► int x = 0;               (C++11)
 *   Delegating constructor     ─► A() : A(0, 0) { }        (C++11)
 *   = default / = delete       ─► ask for / forbid a special function
 *   explicit                   ─► stop silent conversions
 *   Uniform init { }           ─► A a{1, 2};  no narrowing
 *   Dynamic constructor        ─► new inside / new A(...)
 *
 *   DESTRUCTOR AND COPYING
 *   ──────────────────────
 *   Destructor                 ─► ~A()
 *   Order of calls             ─► destroy in REVERSE order of creation
 *   Implicit copy constructor  ─► compiler-made, copies member by member
 *   Shallow vs deep copy       ─► share memory vs own copy
 *   Copy vs move assignment    ─► a = b;   a = std::move(b);
 *   Rule of 0 / 3 / 5          ─► which special functions to write
 *   Copy elision / RVO         ─► compiler skips useless copies
 *   Private constructor        ─► stop others from creating objects
 *   RAII                       ─► constructor gets, destructor frees
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Constructor — introduction ->
│      class A { public: A() { ... } };      A obj;   // A() runs here
│
│  ✔ Definition : A constructor is called by itself when the object is
│                 created. You never write obj.A().
│  ✔ Same name as class, no return type
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Sample {
public:
    Sample() {                           // constructor
        cout << "Constructor called!" << endl;
    }
};

int main() {

    Sample obj;                          // Constructor called!
    Sample obj2;                         // Constructor called!

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Constructor gives the starting value
│  ✔ Without a constructor, data would hold garbage until you set it
│  ✔ With one, the object is READY to use from the first line
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Demo {
private:
    int data;

public:
    Demo(int value) {
        data = value;
        cout << "Data initialized to " << data << endl;
    }
};

int main() {

    Demo obj(42);                        // Data initialized to 42

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Default constructor ->
│      ClassName() { ... }
│
│  ✔ Definition : A constructor with NO parameters. Used to give default
│                 values.
│  ✔ If you write NO constructor at all, the compiler makes an empty
│    default constructor for you
│  ⚠ If you write ANY constructor, the compiler stops making the default
│    one → then  ClassName obj;  gives an error
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    string name;
    double salary;

    Employee() {                         // default constructor
        name = "New Joinee";
        salary = 25000;
        cout << "Default Constructor Invoked" << endl;
    }
};

class OnlyParam {
public:
    OnlyParam(int) {}                    // only a parameterized one
};

int main() {

    Employee e1;                         // Default Constructor Invoked
    Employee e2;                         // Default Constructor Invoked
    cout << e1.name << " " << e1.salary << endl;     // New Joinee 25000

    // OnlyParam x;                      // ERROR: no default constructor
    OnlyParam y(5);                      // OK
    (void)y;

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Parameterized constructor ->
│      ClassName(type a, type b) { ... }
│      ClassName obj(10, 20);      ClassName obj = ClassName(10, 20);
│
│  ✔ Definition : A constructor that takes parameters, so each object can
│                 start with DIFFERENT values.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int xCoord, int yCoord) {
        x = xCoord;
        y = yCoord;
    }

    void display() { cout << "Point(" << x << ", " << y << ")" << endl; }
};

int main() {

    Point p1(10, 20);                    // implicit call
    Point p2 = Point(30, 40);            // explicit call

    p1.display();                        // Point(10, 20)
    p2.display();                        // Point(30, 40)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Constructor defined outside the class ->
│      class A { public: A(); };           // declare
│      A::A() { ... }                      // define with ::
│
│  ✔ Definition : Same as other member functions — declare inside, write
│                 the body outside with ClassName::ClassName.
│  ✔ Keeps the class declaration short (used with .h / .cpp files)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    int rno;
    char name[50];
    double fee;

public:
    Student();                           // declaration
    void display();
};

Student::Student() {                     // definition outside
    rno = 0;
    strcpy(name, "Unknown");
    fee = 0.0;
}

void Student::display() {
    cout << "Roll No: " << rno << ", Name: " << name
         << ", Fee: " << fee << endl;
}

int main() {

    Student s;
    s.display();                         // Roll No: 0, Name: Unknown, Fee: 0

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Constructor with default arguments ->
│      ClassName(type a = value) { ... }
│
│  ✔ Definition : If an argument is not passed, its default value is used.
│                 One constructor can then work for many calls.
│  ✔ Defaults go from RIGHT to left:  A(int a, int b = 2)  ✔
│                                     A(int a = 1, int b)  ✘
│  ⚠ Don't also write A() when A(int x = 1) exists — then  A obj;
│    matches BOTH and the compiler gives an "ambiguous" error
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Circle {
private:
    double radius;

public:
    // Circle() {}                       // ⚠ would make  Circle c3;  ambiguous
    Circle(double r = 1.0) {             // works as default constructor too
        radius = r;
    }

    double area() { return 3.14159 * radius * radius; }
};

class Account {
public:
    Account(string owner, double balance = 0, string type = "Savings") {
        cout << owner << " | " << balance << " | " << type << endl;
    }
};

int main() {

    Circle c1(10);                       // radius 10
    Circle c2;                           // radius 1 (default)
    cout << c1.area() << endl;           // 314.159
    cout << c2.area() << endl;           // 3.14159

    Account a("Amit");                   // Amit | 0 | Savings
    Account b("Neha", 5000);             // Neha | 5000 | Savings
    Account c("Ravi", 900, "Current");   // Ravi | 900 | Current

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Constructor overloading ->
│      ClassName() { ... }
│      ClassName(type a) { ... }
│      ClassName(type a, type b) { ... }
│
│  ✔ Definition : Many constructors in one class with the SAME name but
│                 DIFFERENT parameter lists (number or types).
│  ✔ The compiler picks the one that matches the arguments you pass
│  ✔ Works just like function overloading
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Box {
private:
    double length;
    double breadth;

public:
    Box() {                              // default
        length = 1.0;
        breadth = 1.0;
    }

    Box(double l, double b) {            // parameterized
        length = l;
        breadth = b;
    }

    void display() {
        cout << "Length: " << length << ", Breadth: " << breadth << endl;
    }
};

int main() {

    Box box1;                            // calls Box()
    Box box2(5.0, 3.0);                  // calls Box(double, double)

    box1.display();                      // Length: 1, Breadth: 1
    box2.display();                      // Length: 5, Breadth: 3

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Constructor overloading — 3 ways to make a Room
│  ✔ 0 arguments → standard size,  2 arguments → custom,
│    1 argument  → custom length, fixed breadth
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Room {
private:
    double length;
    double breadth;

public:
    Room() {                             // 1. no arguments
        length = 6.9;
        breadth = 4.2;
    }

    Room(double l, double b) {           // 2. two arguments
        length = l;
        breadth = b;
    }

    Room(double len) {                   // 3. one argument
        length = len;
        breadth = 7.2;
    }

    double calculateArea() { return length * breadth; }
};

int main() {

    Room room1, room2(8.2, 6.6), room3(8.2);

    cout << room1.calculateArea() << endl;   // 28.98
    cout << room2.calculateArea() << endl;   // 54.12
    cout << room3.calculateArea() << endl;   // 59.04

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Copy constructor ->
│      ClassName(const ClassName& obj) { ... }
│      ClassName b = a;        ClassName b(a);
│
│  ✔ Definition : Makes a NEW object as a copy of an existing object of
│                 the same class.
│  ✔ It is called in 3 cases:
│        1. ClassName b = a;   or   ClassName b(a);
│        2. passing an object BY VALUE to a function
│        3. returning an object by value (often skipped, see RVO)
│  ⚠ The parameter MUST be a reference. By value → it would need a copy
│    to make a copy → endless loop → compile error.
│  ⚠ b = a; for an EXISTING b is NOT the copy constructor — that is
│    the copy ASSIGNMENT operator
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int xCoord, int yCoord) {
        x = xCoord;
        y = yCoord;
    }

    Point(const Point& p) {              // copy constructor
        x = p.x;
        y = p.y;
        cout << "copy made" << endl;
    }

    void display() { cout << "Point(" << x << ", " << y << ")" << endl; }
    void translate(int dx, int dy) { x += dx; y += dy; }
};

void movePoint(Point p, int dx, int dy) {        // by value → copy
    p.translate(dx, dy);
    p.display();
}

int main() {

    Point p1(10, 20);
    Point p2 = p1;                       // copy made           (case 1)
    Point p3(p1);                        // copy made           (case 1)

    p2.display();                        // Point(10, 20)
    p3.display();                        // Point(10, 20)

    movePoint(p1, 5, 5);                 // copy made           (case 2)
                                         // Point(15, 25)
    p1.display();                        // Point(10, 20)  unchanged

    p3 = p1;                             // nothing printed: this is
                                         // assignment, not copy ctor
    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Copy constructor — copy a Wall
│  ✔ wall2 starts with the same length and height as wall1
│  ✔ Prefer  const Wall&  — it also lets you copy a const object
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Wall {
private:
    double length;
    double height;

public:
    Wall(double len, double hgt) {
        length = len;
        height = hgt;
    }

    Wall(const Wall& obj) {              // copy constructor
        length = obj.length;
        height = obj.height;
    }

    double calculateArea() { return length * height; }
};

int main() {

    Wall wall1(10.5, 8.6);
    Wall wall2 = wall1;                  // copy

    cout << "Area of Wall 1: " << wall1.calculateArea() << endl;  // 90.3
    cout << "Area of Wall 2: " << wall2.calculateArea() << endl;  // 90.3

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Conversion constructor ->
│      ClassName(type x) { ... }           // ONE argument
│      ClassName obj = value;              // value → object, silently
│
│  ✔ Definition : A constructor that can be called with ONE argument
│                 also works as a converter: the compiler can turn that
│                 type into your class by itself.
│  ✔ Handy:  Rupees r = 500;   pay(500);  (500 becomes Rupees)
│  ⚠ Sometimes the silent conversion is a BUG → mark it explicit
│    (next blocks)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Rupees {
public:
    int amount;
    Rupees(int a) { amount = a; }        // conversion constructor
};

void pay(Rupees r) {
    cout << "Paid Rs." << r.amount << endl;
}

int main() {

    Rupees r = 500;                      // int → Rupees
    cout << r.amount << endl;            // 500

    pay(250);                            // Paid Rs.250  (250 → Rupees)

    r = 900;                             // a temp Rupees(900) is assigned
    cout << r.amount << endl;            // 900

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  explicit constructor ->
│      explicit ClassName(type x) { ... }
│
│  ✔ Definition : explicit stops the compiler from using the constructor
│                 for SILENT (implicit) conversions and copy-init (= x).
│  ✔ Use it on one-argument constructors where a silent conversion would
│    be confusing
│        explicit Vector(int size);   // v = 10;  should NOT mean size 10
│  ✔ Direct init still works:  A a(42);   A a{42};
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class ExplicitExample {
private:
    int value;

public:
    explicit ExplicitExample(int val) { value = val; }
    void display() { cout << "Value: " << value << endl; }
};

void show(ExplicitExample e) { e.display(); }

int main() {

    ExplicitExample obj1(42);            // direct init: allowed
    obj1.display();                      // Value: 42

    // ExplicitExample obj2 = 42;        // ERROR: copy-init blocked
    // show(7);                          // ERROR: silent int → class blocked

    show(ExplicitExample(7));            // Value: 7  (you asked clearly)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Constructor initialization list ->
│      ClassName(type a, type b) : member1(a), member2(b) { ... }
│
│  ✔ Definition : Members are given their values BEFORE the constructor
│                 body runs. (Inside the body = first made, then changed.)
│  ✔ Faster for objects like string (no "make empty, then assign")
│  ✔ REQUIRED for:
│        • const members          • reference members
│        • members with no default constructor
│        • calling a base class constructor (see 06)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Rectangle {
private:
    double length;
    double width;

public:
    Rectangle(double len, double wid) : length(len), width(wid) {}
    double area() { return length * width; }
};

class Order {
private:
    const int orderId;                   // const → MUST use the list
    string& customer;                    // reference → MUST use the list

public:
    Order(int id, string& c) : orderId(id), customer(c) {
        // orderId = id;                 // ERROR: can't assign a const
    }

    void show() { cout << "#" << orderId << " for " << customer << endl; }
};

int main() {

    Rectangle rect(10.0, 5.0);
    cout << "Area: " << rect.area() << endl;     // Area: 50

    string name = "Amit";
    Order o(101, name);
    o.show();                                    // #101 for Amit

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Initialization order = DECLARATION order
│  ✔ Members are always set in the order they are WRITTEN in the class,
│    NOT the order you write them in the initialization list
│  ⚠ In class Bad (in a comment below) b is declared first, so b(a * 2)
│    runs while a is still garbage
│  ✔ Fix: write the list in the same order as the declarations, and
│    don't use one member to set another unless it is declared earlier
│  ✔ g++ -Wall warns about this: "will be initialized after"
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Good {
public:
    int a;                               // declared 1st
    int b;                               // declared 2nd
    Good(int x) : a(x), b(a * 2) {}      // a is ready before b → OK
};

// class Bad {
// public:
//     int b;                            // declared 1st → set FIRST
//     int a;
//     Bad(int x) : a(x), b(a * 2) {}    // b uses a before a is set!
// };

class Price {
public:
    double base;                         // declared 1st
    double tax;                          // declared 2nd
    double total;                        // declared 3rd → uses base, tax
    Price(double b) : base(b), tax(b * 0.18), total(base + tax) {}
};

int main() {

    Good g(5);
    cout << g.a << " " << g.b << endl;   // 5 10

    Price p(100);
    cout << p.total << endl;             // 118

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  In-class member initializers (C++11) ->
│      class A { int x = 0;  string s = "none"; };
│
│  ✔ Definition : Give a default value right where the member is written.
│                 Every constructor uses it, unless that constructor's
│                 initialization list gives another value.
│  ✔ No more "forgot to set it in one constructor" bugs
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Settings {
public:
    string theme = "Light";              // default values
    int fontSize = 14;
    bool notifications = true;

    Settings() {}                                    // uses all defaults
    Settings(string t) : theme(t) {}                 // only theme changes
};

int main() {

    Settings s1;
    Settings s2("Dark");

    cout << s1.theme << " " << s1.fontSize << endl;  // Light 14
    cout << s2.theme << " " << s2.fontSize << endl;  // Dark 14
    cout << boolalpha << s2.notifications << endl;   // true

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Delegating constructor (C++11) ->
│      ClassName() : ClassName(0, 0) { }
│
│  ✔ Definition : One constructor calls ANOTHER constructor of the same
│                 class in its initialization list. The common code is
│                 written once only.
│  ✔ The called constructor runs first, then this body runs
│  ⚠ When delegating, you can't also set members in the same list
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class User {
    string name;
    string role;
    int age;

public:
    User(string n, string r, int a) : name(n), role(r), age(a) {
        cout << "Main ctor: " << name << ", " << role << ", " << age
             << endl;
    }

    User(string n) : User(n, "guest", 18) {          // delegate
        cout << "Guest created" << endl;
    }

    User() : User("Anonymous") {}                    // delegate again
};

int main() {

    User a("Amit", "admin", 30);         // Main ctor: Amit, admin, 30

    User b("Neha");
    // Main ctor: Neha, guest, 18
    // Guest created

    User c;
    // Main ctor: Anonymous, guest, 18
    // Guest created

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  = default | = delete ->
│      ClassName() = default;                  // "compiler, make it"
│      ClassName(const ClassName&) = delete;   // "nobody may copy"
│
│  ✔ Definition : = default asks the compiler to write that special
│                 function for you (useful after writing other ctors).
│                 = delete forbids a function — using it is a compile
│                 error.
│  ✔ = delete common use: objects that must NOT be copied
│    (a file handle, a database connection, a unique ID)
│  ✔ = delete can also block a bad overload, e.g. f(double) = delete;
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Point {
public:
    int x = 0, y = 0;
    Point() = default;                   // keep the default one too
    Point(int a, int b) : x(a), y(b) {}
};

class DatabaseConnection {
    string url;

public:
    DatabaseConnection(string u) : url(u) {}
    DatabaseConnection(const DatabaseConnection&) = delete;  // no copy
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

    void query() { cout << "Query on " << url << endl; }
};

void setAge(int age) { cout << "Age " << age << endl; }
void setAge(double) = delete;            // block 25.5 → 25 by mistake

int main() {

    Point p;                             // OK because of = default
    Point q(3, 4);
    cout << p.x << " " << q.x << endl;   // 0 3

    DatabaseConnection db("mysql://shop");
    db.query();                          // Query on mysql://shop
    // DatabaseConnection db2 = db;      // ERROR: copy is deleted

    setAge(25);                          // Age 25
    // setAge(25.5);                     // ERROR: deleted overload

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Uniform / brace initialization { } (C++11) ->
│      ClassName obj{a, b};      ClassName obj = {a, b};
│      int x{5};                 vector<int> v{1, 2, 3};
│
│  ✔ Definition : One { } style to initialize EVERYTHING — ints, arrays,
│                 objects, containers.
│  ✔ Blocks narrowing:  int x{3.7};  → ERROR (would silently cut to 3)
│  ✔ Fixes the "most vexing parse":  A a();  declares a FUNCTION,
│                                     A a{};  makes an object
│  ⚠ If the class has an initializer_list constructor (like vector),
│    { } picks it:  vector<int> v{3, 0} → {3, 0}  (2 elements)
│                   vector<int> v(3, 0) → {0, 0, 0} (3 elements)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
using namespace std;

class Point {
public:
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};

int main() {

    Point p1{3, 4};
    Point p2 = {5, 6};
    cout << p1.x << " " << p2.y << endl;         // 3 6

    int a{10};
    // int b{3.7};                               // ERROR: narrowing
    cout << a << endl;                           // 10

    vector<int> v1{3, 0};
    vector<int> v2(3, 0);
    cout << v1.size() << " " << v2.size() << endl;   // 2 3

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Dynamic constructor (using new) ->
│      ClassName* p = new ClassName(args);   ...   delete p;
│      inside a ctor:  data = new int[n];    (free it in the destructor)
│
│  ✔ Definition : (1) Create an object at run time on the heap with new.
│                 (2) A constructor that itself uses new to get memory
│                     of the size it needs.
│  ⚠ Every new needs ONE delete (new[] → delete[])
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Circle {
private:
    double radius;

public:
    Circle(double r) { radius = r; }
    double area() { return 3.14159 * radius * radius; }
};

class Marks {
    int* data;
    int size;

public:
    Marks(int n) {                       // dynamic constructor
        size = n;
        data = new int[size];            // memory of the needed size
        for (int i = 0; i < size; i++) data[i] = (i + 1) * 10;
    }

    ~Marks() { delete[] data; }

    void show() {
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << endl;
    }
};

int main() {

    Circle* circ = new Circle(5.0);              // object on heap
    cout << "Area: " << circ->area() << endl;    // Area: 78.5397
    delete circ;

    Marks m(4);
    m.show();                                    // 10 20 30 40

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Destructor ->
│      ~ClassName() { ... }                    // inside the class
│      ClassName::~ClassName() { ... }         // or outside with ::
│
│  ✔ Definition : Called automatically when the object goes out of
│                 scope (or is deleted). Used to release resources the
│                 object took during its life.
│  ✔ If you don't write one, the compiler makes an empty one
│  ✔ No return type, NO parameters → so it CAN'T be overloaded
│    (only ONE destructor per class)
│  ✔ Not inherited. Can be virtual / pure virtual (see 10)
│  ✔ Can't be const, volatile or static
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Test {
public:
    Test() { cout << "Constructor executed" << endl; }
    ~Test() { cout << "Destructor executed" << endl; }
};

int main() {

    Test t;                              // Constructor executed
    cout << "main working..." << endl;   // main working...

    return 0;                            // Destructor executed
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Destructor defined outside the class
│  ✔ Same as other members: declare inside, define with ClassName::~
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Test {
public:
    Test() { cout << "Constructor executed" << endl; }
    ~Test();                             // declaration
};

Test::~Test() {                          // definition outside
    cout << "Destructor executed" << endl;
}

int main() {

    Test t;                              // Constructor executed
    return 0;                            // Destructor executed
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Destructor + copy constructor — every object gets destroyed
│  ✔ The copy wall2 is a separate object → it gets its own destructor
│  ✔ Destroyed in reverse order: wall2 first, then wall1
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Wall {
private:
    string name;
    double length;
    double height;

public:
    Wall(string n, double len, double hgt) {
        name = n;
        length = len;
        height = hgt;
    }

    Wall(const Wall& obj) {
        name = obj.name + "-copy";
        length = obj.length;
        height = obj.height;
    }

    double calculateArea() { return length * height; }

    ~Wall() { cout << "Destructor for " << name << endl; }
};

int main() {

    Wall wall1("wall1", 10.5, 8.6);
    Wall wall2 = wall1;

    cout << "Area 1: " << wall1.calculateArea() << endl;     // Area 1: 90.3
    cout << "Area 2: " << wall2.calculateArea() << endl;     // Area 2: 90.3

    return 0;
    // Destructor for wall1-copy
    // Destructor for wall1
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Order of constructor / destructor calls
│  ✔ Constructors run in the order objects are CREATED
│  ✔ Destructors run in REVERSE order (last made = first destroyed),
│    like plates on a stack
│  ✔ An object inside { } dies at the closing }
│  ✔ A heap object dies only when you call delete
│  ✔ Members are built BEFORE the owner's constructor body, and
│    destroyed AFTER the owner's destructor body
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Sample {
    string name;

public:
    Sample(string n) : name(n) { cout << "ctor " << name << endl; }
    ~Sample() { cout << "dtor " << name << endl; }
};

class Engine {
public:
    Engine() { cout << "ctor Engine" << endl; }
    ~Engine() { cout << "dtor Engine" << endl; }
};

class Car {
    Engine e;                            // member object

public:
    Car() { cout << "ctor Car" << endl; }
    ~Car() { cout << "dtor Car" << endl; }
};

int main() {

    Sample a("A");                       // ctor A
    Sample b("B");                       // ctor B

    {
        Sample c("C");                   // ctor C
    }                                    // dtor C   (block ends)

    Sample* h = new Sample("Heap");      // ctor Heap
    delete h;                            // dtor Heap

    {
        Car car;
        // ctor Engine   (member first)
        // ctor Car
    }
    // dtor Car
    // dtor Engine      (member last)

    return 0;
    // dtor B
    // dtor A
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Implicit (compiler-made) copy constructor
│  ✔ If you don't write a copy constructor, the compiler makes one
│  ✔ It copies every member one by one (member-wise copy)
│  ✔ Perfect for normal members: int, double, string, vector ...
│  ⚠ For a RAW POINTER member it copies only the ADDRESS (shallow copy)
│    → see the next 2 blocks
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Profile {
public:
    string name;
    int age;
    vector<string> hobbies;
};

int main() {

    Profile a{"Amit", 25, {"cricket", "music"}};
    Profile b = a;                       // implicit copy constructor

    b.name = "Bunty";
    b.hobbies.push_back("chess");

    cout << a.name << " " << a.hobbies.size() << endl;   // Amit 2
    cout << b.name << " " << b.hobbies.size() << endl;   // Bunty 3

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Shallow copy — the problem
│  ✔ Shallow copy: copies member values AS THEY ARE. For a pointer,
│    only the address is copied → BOTH objects point to the SAME memory
│  ✔ So a change through one object shows in the other
│  ⚠ If both destructors do delete[] data → the same memory is freed
│    TWICE → crash (double delete). That's why the delete is commented
│    out here, so the demo can run. In real code → write a deep copy.
│  ✔ The compiler-made copy constructor does exactly this shallow copy
│
│        obj1.data ──┐
│                    ├──►  [ H e l l o ]     (ONE memory block)
│        obj2.data ──┘
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstring>
using namespace std;

class Shallow {
private:
    char* data;

public:
    Shallow(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    Shallow(const Shallow& obj) {
        data = obj.data;                 // only the address is copied
    }

    void change(char c) { data[0] = c; }
    void display() { cout << "Data: " << data << endl; }

    ~Shallow() {
        // delete[] data;                // ⚠ would delete twice → crash
    }
};

int main() {

    Shallow obj1("Hello");
    Shallow obj2 = obj1;                 // shallow copy

    obj2.change('J');                    // change only obj2 ...

    obj1.display();                      // Data: Jello   (obj1 changed!)
    obj2.display();                      // Data: Jello

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Deep copy — the fix
│  ✔ Deep copy: allocate NEW memory and copy the DATA into it
│  ✔ Each object owns its own block → changes don't leak, and each
│    destructor frees its own block safely
│  ✔ Needed whenever a class owns memory through a raw pointer
│
│        obj1.data ──►  [ H e l l o ]
│        obj2.data ──►  [ H e l l o ]      (TWO separate blocks)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstring>
using namespace std;

class Deep {
private:
    char* data;

public:
    Deep(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    Deep(const Deep& obj) {                          // deep copy
        data = new char[strlen(obj.data) + 1];       // new memory
        strcpy(data, obj.data);                      // copy the data
    }

    void change(char c) { data[0] = c; }
    void display() { cout << "Data: " << data << endl; }

    ~Deep() { delete[] data; }                       // safe now
};

int main() {

    Deep obj1("Hello");
    Deep obj2 = obj1;                    // deep copy

    obj2.change('J');

    obj1.display();                      // Data: Hello   (not affected)
    obj2.display();                      // Data: Jello

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Copy assignment operator ->
│      ClassName& operator=(const ClassName& other) {
│          if (this != &other) { free old; copy new; }
│          return *this;
│      }
│
│  ✔ Definition : Runs for  a = b;  when a ALREADY exists.
│                 (Copy constructor = make a NEW object from another.)
│  ✔ Steps: 1. check self-assignment (a = a)
│           2. free the old memory   3. deep copy   4. return *this
│
│      Buffer a("x");
│      Buffer b = a;        // copy CONSTRUCTOR  (b is new)
│      b = a;               // copy ASSIGNMENT   (b already exists)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstring>
using namespace std;

class Buffer {
    char* data;

public:
    Buffer(const char* s) {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    Buffer(const Buffer& o) {                        // copy constructor
        data = new char[strlen(o.data) + 1];
        strcpy(data, o.data);
        cout << "copy ctor" << endl;
    }

    Buffer& operator=(const Buffer& o) {             // copy assignment
        cout << "copy assign" << endl;
        if (this == &o) return *this;                // 1. self check
        delete[] data;                               // 2. free old
        data = new char[strlen(o.data) + 1];         // 3. deep copy
        strcpy(data, o.data);
        return *this;                                // 4. for a = b = c
    }

    ~Buffer() { delete[] data; }

    void show() { cout << data << endl; }
};

int main() {

    Buffer a("Hello");
    Buffer b = a;                        // copy ctor
    Buffer c("Bye");

    c = a;                               // copy assign
    c.show();                            // Hello

    c = c;                               // copy assign  (self, safe)
    c.show();                            // Hello

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Move constructor | Move assignment (C++11) ->
│      ClassName(ClassName&& other) noexcept { steal; other.ptr = nullptr; }
│      ClassName& operator=(ClassName&& other) noexcept { ... }
│      ClassName b = std::move(a);
│
│  ✔ Definition : Instead of COPYING the data, STEAL it from an object
│                 that is about to die (a temporary, or one you mark
│                 with std::move). Only the pointer is taken → very fast.
│  ✔ After a move, the old object is empty but still safe to destroy
│  ✔ Mark them noexcept → vector then moves (not copies) on resize
│  ⚠ Don't use an object after std::move(obj) except to give it a new
│    value or let it die
│
│      COPY : a ──► [data]       b ──► [data copy]   (slow, 2 blocks)
│      MOVE : a ──► nullptr      b ──► [data]        (fast, 1 block)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <utility>
using namespace std;

class Video {
    int* frames;
    int size;

public:
    Video(int n) : frames(new int[n]), size(n) {
        cout << "load " << size << " frames" << endl;
    }

    Video(const Video& o) : frames(new int[o.size]), size(o.size) {
        for (int i = 0; i < size; i++) frames[i] = o.frames[i];
        cout << "COPY (slow)" << endl;
    }

    Video(Video&& o) noexcept : frames(o.frames), size(o.size) {
        o.frames = nullptr;              // leave the old one empty
        o.size = 0;
        cout << "MOVE (fast)" << endl;
    }

    Video& operator=(Video&& o) noexcept {
        if (this != &o) {
            delete[] frames;
            frames = o.frames;
            size = o.size;
            o.frames = nullptr;
            o.size = 0;
        }
        cout << "MOVE assign" << endl;
        return *this;
    }

    ~Video() { delete[] frames; }

    int getSize() const { return size; }
};

int main() {

    Video a(1000);                       // load 1000 frames
    Video b = a;                         // COPY (slow)
    Video c = std::move(a);              // MOVE (fast)

    cout << a.getSize() << " " << c.getSize() << endl;   // 0 1000

    Video d(5);                          // load 5 frames
    d = std::move(c);                    // MOVE assign
    cout << d.getSize() << endl;         // 1000

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Rule of 0 / Rule of 3 / Rule of 5
│  ✔ The 5 special functions: destructor, copy ctor, copy assign,
│    move ctor, move assign
│
│   RULE        WHEN                              WHAT TO DO
│   ──────────  ────────────────────────────────  ─────────────────────────
│   Rule of 3   class owns a raw resource         write dtor + copy ctor +
│               (new, file, socket)                copy assign
│   Rule of 5   same, in C++11 and later          + move ctor + move assign
│   Rule of 0   use string / vector / smart ptr   write NONE of them —
│               instead of raw pointers           the compiler's are right
│
│  ✔ Best advice: aim for Rule of 0. Let members manage themselves.
│  ⚠ If you write ONE of the 5, think about ALL of them
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// Rule of 0 — no special functions written, everything is still correct
class Playlist {
public:
    string name;
    vector<string> songs;
    unique_ptr<int> plays = make_unique<int>(0);     // owns memory safely
};

int main() {

    Playlist a;
    a.name = "Gym";
    a.songs = {"Song1", "Song2"};

    Playlist b = std::move(a);           // compiler-made move works
    cout << b.name << " " << b.songs.size() << endl;     // Gym 2
    cout << *b.plays << endl;                            // 0

    // Playlist c = b;                   // ERROR: unique_ptr can't copy
                                         // (compiler knows it, safely)
    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Copy elision / RVO (Return Value Optimization)
│  ✔ Definition : When a function returns an object by value, the
│                 compiler builds it DIRECTLY in the caller's variable.
│                 No copy and no move happens at all.
│  ✔ C++17: guaranteed when you return a temporary  (return Big(...);)
│  ✔ Usually also done for a named local (NRVO)
│  ✔ So returning big objects by value is fine — don't fear it
│  ⚠ Don't write  return std::move(local);  — it can BLOCK this
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Report {
public:
    Report() { cout << "build report" << endl; }
    Report(const Report&) { cout << "copy" << endl; }
    Report(Report&&) noexcept { cout << "move" << endl; }
};

Report makeReport() {
    return Report();                     // built straight into r
}

int main() {

    Report r = makeReport();             // build report
                                         // (no "copy", no "move")
    (void)r;
    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Private constructor — control who can create objects
│  ✔ If the constructor is private, outside code can't write  A a;
│  ✔ Objects are made only through a public static function
│  ✔ Used for: Singleton (one object only), factory functions, and
│    classes that should be created only in a valid way
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Temperature {
    double celsius;
    Temperature(double c) : celsius(c) {}            // private

public:
    static Temperature fromCelsius(double c) { return Temperature(c); }
    static Temperature fromFahrenheit(double f) {
        return Temperature((f - 32) * 5 / 9);
    }

    double get() const { return celsius; }
};

int main() {

    // Temperature t(30);                // ERROR: constructor is private
    Temperature a = Temperature::fromCelsius(30);
    Temperature b = Temperature::fromFahrenheit(212);

    cout << a.get() << endl;             // 30
    cout << b.get() << endl;             // 100

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  RAII (Resource Acquisition Is Initialization)
│  ✔ Definition : Take a resource in the CONSTRUCTOR, give it back in the
│                 DESTRUCTOR. Because the destructor always runs when the
│                 object dies, you can never "forget" to clean up.
│  ✔ Works even if the function returns early or an exception is thrown
│  ✔ STL uses this everywhere: vector, string, fstream, unique_ptr,
│    lock_guard
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class FileHandle {
    string name;

public:
    FileHandle(string n) : name(n) { cout << "open " << name << endl; }
    ~FileHandle() { cout << "close " << name << endl; }

    void write(string text) { cout << name << " << " << text << endl; }
};

bool saveData(bool fail) {
    FileHandle f("data.txt");            // open data.txt
    f.write("hello");                    // data.txt << hello

    if (fail) return false;              // early return: still closed!

    f.write("world");
    return true;
}                                        // close data.txt (always)

int main() {

    saveData(false);
    // open data.txt
    // data.txt << hello
    // data.txt << world
    // close data.txt

    saveData(true);
    // open data.txt
    // data.txt << hello
    // close data.txt

    return 0;
}
