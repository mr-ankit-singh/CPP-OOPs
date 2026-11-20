/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                               POLYMORPHISM                                ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is Polymorphism?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Polymorphism means "MANY FORMS" — the SAME function / operator /
 *    name behaves DIFFERENTLY depending on the context (the arguments,
 *    or the ACTUAL object type it is working with)
 *  ✔ Real life: one person is a student in college, a customer in a
 *    shop, a son at home. Same person, different behaviour.
 *  ✔ In code: one call  shape->draw()  draws a circle, a square or a
 *    triangle — depending on what the shape really is
 *
 *  2 main types
 *  ────────────────────────────────────────────────────────────────────────────
 *
 *                          POLYMORPHISM
 *                ┌──────────────┴──────────────┐
 *          COMPILE-TIME                     RUN-TIME
 *        (static / early binding)        (dynamic / late binding)
 *          ├── Function overloading         ├── Virtual functions
 *          ├── Operator overloading         ├── Function overriding
 *          ├── Constructor overloading      ├── Abstract classes
 *          └── Templates                    └── Virtual destructors
 *
 *   POINT           COMPILE-TIME                RUN-TIME
 *   ──────────────  ──────────────────────────  ──────────────────────────
 *   Decided when    while compiling             while the program runs
 *   Decided by      arguments / types           real object type
 *   Speed           FASTER (no lookup)          tiny cost (vtable lookup)
 *   Flexibility     less                        MORE (new types later)
 *   Needs           nothing special             virtual + pointer / ref
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   COMPILE-TIME
 *   ────────────
 *   Function overloading         ─► add(int,int), add(double,double)
 *   Operator overloading         ─► c1 + c2  for Complex
 *   Constructor overloading      ─► Rectangle(), Rectangle(s), (l, w)
 *   Templates                    ─► one function for every type
 *
 *   RUN-TIME
 *   ────────
 *   Without virtual (the bug)    ─► base pointer calls base version
 *   Virtual + overriding         ─► base pointer calls the REAL version
 *   override keyword             ─► compiler checks your override
 *   Abstract classes             ─► pure virtual, can't make objects
 *   Virtual destructors          ─► delete through base pointer safely
 *   Dynamic binding              ─► one function works for all types
 *
 *   COMPARE AND MORE
 *   ────────────────
 *   Static vs dynamic binding    ─► same pointer, two behaviours
 *   Overloading vs overriding vs hiding ─► table + example
 *   Covariant return types       ─► override may return Child*
 *   Static polymorphism (CRTP)   ─► polymorphism with templates
 *   std::variant + std::visit    ─► polymorphism without inheritance
 *
 *  ✔ vtable / vptr and rules of virtual functions → 10_VirtualFunction.cpp
 *  ✔ Operator overloading in depth → 09_OperatorOverloading.cpp
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Function overloading (compile-time) ->
│      int add(int a, int b);
│      double add(double a, double b);
│      int add(int a, int b, int c);
│
│  ✔ Definition : SAME function name, DIFFERENT parameters (number or
│                 type). The compiler picks the right version AT COMPILE
│                 TIME by looking at the arguments.
│  ⚠ Different RETURN type alone is NOT overloading → error
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Calculator {
public:
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }
    int add(int a, int b, int c) { return a + b + c; }
    // double add(int a, int b);         // ERROR: only return type differs
};

int main() {

    Calculator calc;
    cout << calc.add(2, 3) << endl;          // 5
    cout << calc.add(2.5, 3.5) << endl;      // 6
    cout << calc.add(1, 2, 3) << endl;       // 6

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Operator overloading (compile-time) ->
│      ReturnType operator+(const ClassName& other);
│
│  ✔ Definition : Give an EXISTING operator (+, -, ==, <<) a NEW meaning
│                 for your own class. The compiler picks which "+" to
│                 use by the TYPES of the operands.
│  ✔ 2 + 3 → int addition,  c1 + c2 → your Complex addition
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    void display() const { cout << real << " + " << imag << "i" << endl; }
};

int main() {

    Complex c1(2, 3), c2(4, 5);
    Complex c3 = c1 + c2;                // our +
    c3.display();                        // 6 + 8i

    cout << 2 + 3 << endl;               // 5   (normal int +)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Constructor overloading (compile-time) ->
│      Rectangle();   Rectangle(double side);   Rectangle(double l, double w);
│
│  ✔ Definition : SAME class, MANY constructors with different parameter
│                 lists. The compiler picks one by how many / what type
│                 of arguments you give when creating the object.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Rectangle {
public:
    double length, width;

    Rectangle() : length(1.0), width(1.0) {}             // default
    Rectangle(double side) : length(side), width(side) {} // square-like
    Rectangle(double l, double w) : length(l), width(w) {}

    double area() const { return length * width; }
};

int main() {

    Rectangle r1;                        // default constructor
    Rectangle r2(5);                     // one argument
    Rectangle r3(4, 6);                  // two arguments

    cout << r1.area() << endl;           // 1
    cout << r2.area() << endl;           // 25
    cout << r3.area() << endl;           // 24

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Templates (compile-time) ->
│      template <typename T>  T biggest(T a, T b);
│
│  ✔ Definition : Write ONE function / class, and the compiler makes a
│                 separate version for each type you use it with.
│  ✔ Same name works for int, double, string ... → "many forms",
│    decided at compile time
│  ✔ Whole STL (vector<T>, sort) is built this way
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

template <typename T>
T biggest(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>
class Box {
    T value;

public:
    Box(T v) : value(v) {}
    void show() const { cout << "Box holds: " << value << endl; }
};

int main() {

    cout << biggest(3, 9) << endl;                       // 9
    cout << biggest(2.5, 1.5) << endl;                   // 2.5
    cout << biggest(string("apple"), string("mango")) << endl;  // mango

    Box<int> b1(42);
    Box<string> b2("gift");
    b1.show();                           // Box holds: 42
    b2.show();                           // Box holds: gift

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  WITHOUT virtual — the #1 beginner mistake
│  ✔ Without "virtual", C++ uses STATIC binding: it looks at the POINTER
│    TYPE (Animal*), not at the real object
│  ✔ So even though a points to a Dog, Animal's version runs
│  ✔ Next block fixes this with virtual
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Animal {
public:
    void makeSound() { cout << "Some generic animal sound" << endl; }
};

class Dog : public Animal {
public:
    void makeSound() { cout << "Woof! Woof!" << endl; }
};

int main() {

    Dog dog;
    dog.makeSound();                     // Woof! Woof!   (object: fine)

    Animal* a = &dog;
    a->makeSound();                      // Some generic animal sound  ⚠

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Virtual function + function overriding (run-time) ->
│      class Base    { public: virtual void f(); };
│      class Derived : public Base { public: void f() override; };
│      Base* p = &derivedObj;   p->f();    // Derived::f() runs
│
│  ✔ Virtual function : a BASE class function marked "virtual" that a
│                       derived class is EXPECTED to redefine
│  ✔ Overriding       : the derived class gives its OWN version of that
│                       function (same name, same parameters)
│  ✔ With virtual, the call is decided AT RUN TIME by the REAL object,
│    not by the pointer type
│  ✔ Works only through a POINTER or REFERENCE to the base
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() { cout << "Some generic animal sound" << endl; }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void makeSound() override { cout << "Woof! Woof!" << endl; }
};

class Cat : public Animal {
public:
    void makeSound() override { cout << "Meow!" << endl; }
};

int main() {

    Dog dog;
    Cat cat;
    Animal* animalPtr;

    animalPtr = &dog;
    animalPtr->makeSound();              // Woof! Woof!

    animalPtr = &cat;
    animalPtr->makeSound();              // Meow!

    Animal& ref = cat;                   // reference works too
    ref.makeSound();                     // Meow!

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  override keyword (C++11) ->
│      void f() override;
│
│  ✔ Definition : override tells the compiler "this function MUST replace
│                 a virtual function of the base". If it doesn't match
│                 (typo, wrong parameter, missing const) → ERROR.
│  ✔ Optional, but ALWAYS use it — it catches silent bugs
│  ⚠ Without override, a small mistake makes a NEW function, and the
│    base version keeps running — no error, just wrong output
│  ✔ BuggyCircle below shows that bug on purpose. g++ -Wall gives only a
│    warning "was hidden" — with override it would be a real ERROR.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() const { cout << "Shape" << endl; }
    virtual ~Shape() {}
};

class BuggyCircle : public Shape {
public:
    void draw() { cout << "Circle" << endl; }    // ⚠ forgot const →
};                                               // NEW function, no error

// class CheckedCircle : public Shape {
// public:
//     void draw() override { ... }              // ERROR: doesn't override
// };                                            // → bug caught early

class Circle : public Shape {
public:
    void draw() const override { cout << "Circle" << endl; }    // ✔
};

int main() {

    BuggyCircle b;
    const Shape& s1 = b;
    s1.draw();                           // Shape    (silent bug!)

    Circle c;
    const Shape& s2 = c;
    s2.draw();                           // Circle

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Abstract class (pure virtual functions) ->
│      virtual double area() = 0;
│
│  ✔ Pure virtual function : a virtual function with "= 0". The base
│                            gives NO body, so every child MUST give one.
│  ✔ Abstract class        : has AT LEAST ONE pure virtual function. You
│                            can't write  Shape s;  — only concrete
│                            children can be created.
│  ✔ A base function (describe) can call area() — the CHILD's version
│    runs. The base writes the common steps, children fill the gaps.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() = 0;           // pure virtual → Shape is abstract

    virtual void describe() {
        cout << "This shape has an area of " << area() << endl;
    }

    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;

public:
    Circle(double r) : radius(r) {}
    double area() override { return 3.14159 * radius * radius; }
};

class Square : public Shape {
    double side;

public:
    Square(double s) : side(s) {}
    double area() override { return side * side; }
};

int main() {

    // Shape s;                          // ERROR: abstract class
    Circle circle(5);
    Square square(4);

    circle.describe();                   // This shape has an area of 78.5397
    square.describe();                   // This shape has an area of 16

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Virtual destructor ->
│      virtual ~Base() { ... }
│
│  ✔ Definition : If you delete a CHILD object through a BASE pointer and
│                 the base destructor is NOT virtual, only the BASE
│                 destructor runs. The child's destructor is SKIPPED →
│                 memory leak.
│  ✔ RULE: if a class has ANY virtual function (or is meant to be a base
│    for polymorphism), make its destructor virtual too
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class BadBase {
public:
    ~BadBase() { cout << "BadBase destructor" << endl; }     // NOT virtual
};

class BadDerived : public BadBase {
public:
    ~BadDerived() { cout << "BadDerived destructor" << endl; }
};

class Base {
public:
    virtual ~Base() { cout << "Base destructor called" << endl; }
};

class Derived : public Base {
    int* data;

public:
    Derived() {
        data = new int[10];
        cout << "Derived constructor called" << endl;
    }

    ~Derived() {
        delete[] data;                   // MUST run, or memory leaks
        cout << "Derived destructor called" << endl;
    }
};

int main() {

    BadBase* bad = new BadDerived();
    delete bad;                          // BadBase destructor
                                         // (BadDerived's is SKIPPED ⚠)

    Base* basePtr = new Derived();       // Derived constructor called
    delete basePtr;
    // Derived destructor called
    // Base destructor called

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Dynamic binding (late binding)
│  ✔ Definition : The function that runs is chosen AT RUN TIME by the
│                 REAL object the pointer / reference points to — not by
│                 the declared type.
│  ✔ This is the real power: ONE function (or one loop) works for ALL
│    types — even new types added later, with NO change to that code
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Notification {
public:
    virtual void send(const string& msg) = 0;
    virtual ~Notification() {}
};

class SMS : public Notification {
public:
    void send(const string& m) override { cout << "SMS: " << m << endl; }
};

class Email : public Notification {
public:
    void send(const string& m) override { cout << "Email: " << m << endl; }
};

class Push : public Notification {           // added later — nothing
public:                                      // else had to change
    void send(const string& m) override { cout << "Push: " << m << endl; }
};

void alertAll(const vector<unique_ptr<Notification>>& list) {
    for (const auto& n : list)
        n->send("Order shipped");                // decided at run time
}

int main() {

    vector<unique_ptr<Notification>> channels;
    channels.push_back(make_unique<SMS>());
    channels.push_back(make_unique<Email>());
    channels.push_back(make_unique<Push>());

    alertAll(channels);
    // SMS: Order shipped
    // Email: Order shipped
    // Push: Order shipped

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Static vs dynamic binding — side by side
│  ✔ Static binding (early) : decided AT COMPILE TIME. Used for normal,
│                             overloaded and NON-virtual functions.
│  ✔ Dynamic binding (late) : decided AT RUN TIME by the real object.
│                             Used for VIRTUAL functions called through
│                             a base pointer / reference.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Parent {
public:
    void staticBindDemo() {                      // NOT virtual
        cout << "Parent's staticBindDemo()" << endl;
    }

    virtual void dynamicBindDemo() {             // virtual
        cout << "Parent's dynamicBindDemo()" << endl;
    }

    virtual ~Parent() {}
};

class Child : public Parent {
public:
    void staticBindDemo() { cout << "Child's staticBindDemo()" << endl; }

    void dynamicBindDemo() override {
        cout << "Child's dynamicBindDemo()" << endl;
    }
};

int main() {

    Child childObj;
    Parent* parentPtr = &childObj;

    parentPtr->staticBindDemo();         // Parent's staticBindDemo()
                                         // (by POINTER type)
    parentPtr->dynamicBindDemo();        // Child's dynamicBindDemo()
                                         // (by REAL object)
    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Overloading vs Overriding vs Hiding
│
│   POINT        OVERLOADING          OVERRIDING           HIDING
│   ───────────  ───────────────────  ───────────────────  ──────────────────
│   Where        same class (scope)   base + child         base + child
│   Name         same                 same                 same
│   Parameters   DIFFERENT            SAME                 same or different
│   virtual?     not needed           base fn is virtual   base fn NOT virtual
│   Decided      compile time         run time             compile time
│   Via base*    —                    child version runs   base version runs
│
│  ✔ Hiding happens when the child reuses a name WITHOUT virtual — it
│    looks like overriding but isn't (see 06: name hiding)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base {
public:
    void print(int x) { cout << "Base print int " << x << endl; }
    void print(double x) { cout << "Base print double " << x << endl; }

    virtual void speak() { cout << "Base speak" << endl; }
    void walk() { cout << "Base walk" << endl; }

    virtual ~Base() {}
};

class Derived : public Base {
public:
    void speak() override { cout << "Derived speak" << endl; }  // overriding
    void walk() { cout << "Derived walk" << endl; }             // hiding
};

int main() {

    Base b;
    b.print(5);                          // Base print int 5      overloading
    b.print(2.5);                        // Base print double 2.5 overloading

    Derived d;
    Base* p = &d;

    p->speak();                          // Derived speak   (overriding)
    p->walk();                           // Base walk       (hiding)
    d.walk();                            // Derived walk

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Covariant return types ->
│      virtual Base* clone();                    // in Base
│      Derived* clone() override;                // in Derived  ✔ allowed
│
│  ✔ Definition : Normally an override must have the SAME return type.
│                 Exception: if the base returns Base* (or Base&), the
│                 override may return Derived* (or Derived&).
│  ✔ Classic use: clone() — copy an object when you only have a base
│    pointer, and still get the exact type back
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Document {
public:
    virtual Document* clone() const { return new Document(*this); }
    virtual void print() const { cout << "Plain document" << endl; }
    virtual ~Document() {}
};

class Invoice : public Document {
public:
    int number = 501;

    Invoice* clone() const override { return new Invoice(*this); }  // ✔
    void print() const override { cout << "Invoice #" << number << endl; }
};

int main() {

    Document* original = new Invoice();
    Document* copy = original->clone();          // real Invoice copied
    copy->print();                               // Invoice #501

    Invoice inv;
    Invoice* exact = inv.clone();                // no cast needed
    cout << exact->number << endl;               // 501

    delete original;
    delete copy;
    delete exact;

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Static polymorphism with CRTP ->
│      template <typename Derived>
│      class Base { void run() { static_cast<Derived*>(this)->step(); } };
│      class Child : public Base<Child> { void step(); };
│
│  ✔ Definition : CRTP (Curiously Recurring Template Pattern) — the child
│                 passes ITSELF as a template argument to the base. The
│                 base can then call the child's function WITHOUT virtual.
│  ✔ Decided at compile time → no vtable, no extra cost, can be inlined
│  ⚠ You can't store different children in one vector<Base*> — each
│    Base<Child> is a different type. Use virtual when you need that.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

template <typename Derived>
class Report {
public:
    void generate() {                            // common steps
        cout << "== header ==" << endl;
        static_cast<Derived*>(this)->body();     // child's part
        cout << "== footer ==" << endl;
    }
};

class SalesReport : public Report<SalesReport> {
public:
    void body() { cout << "Sales: Rs.5,00,000" << endl; }
};

class StockReport : public Report<StockReport> {
public:
    void body() { cout << "Items in stock: 320" << endl; }
};

int main() {

    SalesReport s;
    s.generate();
    // == header ==
    // Sales: Rs.5,00,000
    // == footer ==

    StockReport k;
    k.generate();
    // == header ==
    // Items in stock: 320
    // == footer ==

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  std::variant + std::visit (C++17) ->
│      variant<Circle, Square> s = Circle{2};
│      visit([](auto& x) { x.area(); }, s);
│
│  ✔ Definition : A variant holds ONE of a fixed list of types. visit()
│                 calls the right code for whatever type is inside.
│  ✔ Polymorphism WITHOUT inheritance and WITHOUT virtual / pointers
│  ✔ Good when the list of types is FIXED and known
│  ✔ Header: <variant>
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <variant>
#include <vector>
using namespace std;

struct Circle {
    double r;
    double area() const { return 3.14 * r * r; }
};

struct Square {
    double side;
    double area() const { return side * side; }
};

using Shape = variant<Circle, Square>;

int main() {

    vector<Shape> shapes = {Circle{1}, Square{3}, Circle{2}};

    for (const Shape& s : shapes) {
        double a = visit([](const auto& x) { return x.area(); }, s);
        cout << a << endl;
    }
    // 3.14
    // 9
    // 12.56

    return 0;
}
