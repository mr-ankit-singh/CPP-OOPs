/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                 VIRTUAL FUNCTIONS AND ABSTRACT CLASSES                    ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is a Virtual Function?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ A member function declared in the BASE class with the keyword
 *    "virtual", and redefined (overridden) in a derived class
 *  ✔ It enables RUN-TIME polymorphism (dynamic binding) through a base
 *    class POINTER or REFERENCE
 *
 *  How does it work?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Normally the compiler decides which function to call at COMPILE
 *    time — "static binding" (by the pointer's type)
 *  ✔ If the function is virtual, the decision is made at RUN time —
 *    "dynamic binding" (by the REAL object the pointer points to)
 *
 *  Why is it needed?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ A base pointer can point to a derived object. Without virtual, the
 *    BASE function is ALWAYS called, even if the object is derived —
 *    that is wrong behaviour.
 *  ✔ virtual fixes it — the correct (derived) function runs
 *
 *        Base* p = &derivedObj;
 *        p->show();     without virtual → Base::show()     ✘
 *                       with virtual    → Derived::show()  ✔
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   VIRTUAL FUNCTIONS
 *   ─────────────────
 *   Virtual function basics      ─► virtual void show();
 *   Late binding                 ─► chosen at run time
 *   vtable and vptr              ─► how it works inside
 *   Rules for virtual functions  ─► what can / can't be virtual
 *   Overriding and hiding        ─► virtual stays virtual; wrong
 *                                   signature hides instead
 *
 *   PURE VIRTUAL / ABSTRACT
 *   ───────────────────────
 *   Pure virtual function        ─► virtual void f() = 0;
 *   Pure virtual WITH a body     ─► default code children may call
 *   Abstract classes             ─► at least one pure virtual
 *   Rules for abstract classes   ─► pointer OK, object not
 *
 *   DESTRUCTORS
 *   ───────────
 *   Virtual destructor           ─► delete through base pointer safely
 *   Pure virtual destructor      ─► needs a body!
 *
 *   TRAPS AND COST
 *   ──────────────
 *   ⚠ Virtual call in ctor / dtor   ─► child version does NOT run
 *   ⚠ Default arguments in virtual  ─► taken from the POINTER type
 *   Cost of virtual                 ─► vptr per object, one extra jump
 *
 *   PUTTING IT TOGETHER
 *   ───────────────────
 *   Virtual vs pure virtual      ─► comparison table
 *   Example hierarchy            ─► Shape → Circle / Rectangle
 *   Interview points
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Virtual function — basics ->
│      class Base    { public: virtual void show(); };
│      class Derived : public Base { public: void show() override; };
│
│  ✔ Definition : A base class function marked virtual. When called
│                 through a base pointer / reference, the REAL object's
│                 version runs.
│  ✔ "override" in the child is optional but strongly recommended
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class show()" << endl; }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void show() override { cout << "Derived class show()" << endl; }
};

int main() {

    Base* basePtr;
    Derived derivedObj;

    basePtr = &derivedObj;
    basePtr->show();                     // Derived class show()
    // without virtual it would print:  Base class show()

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Late binding — the choice is made while the program RUNS
│  ✔ Here the compiler can NOT know which shape the user will pick —
│    it depends on input at run time. Still the right draw() runs.
│  ✔ That is "late" (dynamic) binding — only possible with virtual
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() const { cout << "generic shape" << endl; }
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    void draw() const override { cout << "drawing a circle" << endl; }
};

class Square : public Shape {
public:
    void draw() const override { cout << "drawing a square" << endl; }
};

Shape* makeShape(int choice) {           // decided at run time
    if (choice == 1) return new Circle;
    if (choice == 2) return new Square;
    return new Shape;
}

int main() {

    int userChoices[] = {2, 1, 9};       // pretend these came from cin

    for (int c : userChoices) {
        Shape* s = makeShape(c);
        s->draw();
        delete s;
    }
    // drawing a square
    // drawing a circle
    // generic shape

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  vtable and vptr — how virtual works inside
│  ✔ vtable (virtual table) : a hidden table made by the compiler, ONE
│                             PER CLASS that has virtual functions. It
│                             holds the addresses of that class's
│                             virtual functions.
│  ✔ vptr (virtual pointer) : a hidden pointer added to EVERY OBJECT of
│                             such a class. It points to its class's
│                             vtable.
│
│      Dog object              Dog's vtable
│      ┌──────────┐            ┌─────────────────────┐
│      │ vptr ────┼──────────► │ speak → Dog::speak  │
│      │ age      │            │ eat   → Animal::eat │  (not overridden)
│      └──────────┘            └─────────────────────┘
│
│  ✔ A call  p->speak()  does:  follow p's vptr → look in the vtable →
│    jump to that address. This lookup happens at RUN time.
│  ✔ That's why a class with virtual functions is BIGGER by one
│    pointer (8 bytes on 64-bit) — see sizeof below
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class NoVirtual {
    int age = 0;

public:
    void speak() {}
};

class Animal {
    int age = 0;

public:
    virtual void speak() { cout << "..." << endl; }
    virtual void eat() { cout << "Animal eats" << endl; }
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() override { cout << "Woof" << endl; }     // replaced
};                                                       // eat() kept

int main() {

    cout << sizeof(NoVirtual) << endl;   // 4   (just the int)
    cout << sizeof(Animal) << endl;      // 16  (vptr 8 + int 4 + padding)

    Dog d;
    Animal* p = &d;
    p->speak();                          // Woof         (Dog's vtable)
    p->eat();                            // Animal eats  (inherited slot)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Rules for virtual functions
│  ✔ 1. A function becomes virtual by writing "virtual" in the BASE.
│       Children don't need to repeat it (but write "override").
│  ✔ 2. Once virtual, it stays virtual in ALL lower classes.
│  ✔ 3. Run-time choice happens only through a POINTER or REFERENCE.
│       Calling on a plain object uses that object's own type.
│  ✔ 4. Constructors can NOT be virtual (the object isn't built yet),
│       but DESTRUCTORS SHOULD be virtual in a polymorphic base.
│  ✔ 5. Static member functions can NOT be virtual (no object / this).
│  ✔ 6. A virtual function can be private in the base and still be
│       overridden; it can also be a friend of another class.
│  ✔ 7. The override must have the same signature (name, params,
│       const). Return type must match (or be covariant).
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class A {
public:
    virtual void hello() { cout << "A" << endl; }
    // static virtual void s();          // ERROR: static can't be virtual
    // virtual A() {}                    // ERROR: ctor can't be virtual
    virtual ~A() {}
};

class B : public A {
public:
    void hello() override { cout << "B" << endl; }       // no "virtual"
};

class C : public B {
public:
    void hello() override { cout << "C" << endl; }       // still virtual
};

int main() {

    C c;
    A* pa = &c;
    B* pb = &c;
    pa->hello();                         // C   (rule 2)
    pb->hello();                         // C

    A plain = c;                         // plain object (sliced)
    plain.hello();                       // A   (rule 3)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Overriding and hiding
│  ✔ Overriding : same name + SAME signature + base function virtual
│                 → child version runs through a base pointer
│  ✔ Hiding     : same name but the base is NOT virtual, OR the
│                 signature is DIFFERENT → it's a NEW function that only
│                 HIDES the base one; a base pointer still calls base
│  ⚠ A different parameter type (int vs double) silently makes hiding.
│    "override" turns that mistake into a compile error.
│  ✔ g++ -Wall warns "was hidden" for Child below — that's the point
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base {
public:
    virtual void area(int x) { cout << "Base area(int) " << x << endl; }
    void info() { cout << "Base info" << endl; }
    virtual ~Base() {}
};

class Child : public Base {
public:
    void area(double x) { cout << "Child area(double) " << x << endl; }
    //       ↑ different parameter → HIDES, does not override
    void info() { cout << "Child info" << endl; }        // hides (no virtual)
};

class GoodChild : public Base {
public:
    void area(int x) override { cout << "GoodChild area " << x << endl; }
};

int main() {

    Child c;
    Base* p = &c;
    p->area(5);                          // Base area(int) 5     (hidden!)
    p->info();                           // Base info
    c.info();                            // Child info

    GoodChild g;
    p = &g;
    p->area(5);                          // GoodChild area 5     (override)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Pure virtual function ->
│      virtual ReturnType functionName() = 0;
│
│  ✔ Definition : A virtual function with no implementation in the base,
│                 declared by writing "= 0". Any class with at least one
│                 becomes an ABSTRACT class.
│  ✔ "= 0" means: there's only a declaration here — every derived class
│    MUST implement it
│  ✔ If a derived class doesn't override it, that class is ALSO
│    abstract (no objects of it either)
│  ✔ It works like a CONTRACT: "every child must define this function"
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() = 0;           // pure virtual
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;

public:
    Circle(double r) : radius(r) {}
    double area() override { return 3.14159 * radius * radius; }
};

class Blob : public Shape {};            // area() NOT overridden

int main() {

    Circle circ(7.0);                    // OK: Circle completed the contract
    cout << circ.area() << endl;         // 153.938

    // Blob b;                           // ERROR: Blob is still abstract
    // Shape s;                          // ERROR: Shape is abstract

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Pure virtual function WITH a body
│  ✔ Yes, a pure virtual function CAN have a body (written outside the
│    class). The class is STILL abstract and children MUST still
│    override it.
│  ✔ Use: give COMMON / default code that children can call with
│    Base::function()
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Logger {
public:
    virtual void log(const string& msg) = 0;     // pure virtual ...
    virtual ~Logger() {}
};

void Logger::log(const string& msg) {            // ... with a body
    cout << "[2026-11-20] " << msg << endl;
}

class FileLogger : public Logger {
public:
    void log(const string& msg) override {
        cout << "file: ";
        Logger::log(msg);                        // reuse the common part
    }
};

int main() {

    // Logger l;                         // ERROR: still abstract
    FileLogger f;
    f.log("server started");             // file: [2026-11-20] server started

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Abstract class
│  ✔ Definition : A class with at least ONE pure virtual function. It
│                 can't be instantiated; it is a blueprint for children,
│                 which must implement ALL pure virtual functions to
│                 become concrete (creatable) classes.
│  ✔ You can NOT make its object:      Animal a;              ✘
│  ✔ You CAN make a pointer/reference: Animal* a = new Dog(); ✔
│  ✔ It may also have normal (non-pure) functions — one pure virtual
│    is enough to make it abstract
│  ✔ In C++, an abstract class is how you build an "interface"
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() = 0;            // makes the class abstract
    void eat() { cout << "Animal is eating..." << endl; }    // normal fn
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void sound() override { cout << "Woof Woof!" << endl; }
};

int main() {

    // Animal a;                         // ERROR: abstract
    // Animal* p = new Animal();         // ERROR: abstract

    Animal* ptr = new Dog();             // pointer to abstract: OK
    ptr->sound();                        // Woof Woof!
    ptr->eat();                          // Animal is eating...
    delete ptr;

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Rules for abstract classes
│  ✔ 1. Why no object? At least one function has no implementation —
│       calling it on an object would mean nothing. So the compiler
│       stops you.
│  ✔ 2. Why are pointers / references allowed? They only store an
│       address; at run time they point to a CONCRETE child object.
│  ✔ 3. It can have a constructor, data members and normal functions.
│  ✔ 4. It can't be passed / returned BY VALUE (that needs an object).
│  ✔ 5. It can have many pure virtual functions. If ALL are pure and
│       there's no data → "pure abstract class" = interface.
│  ✔ 6. Always give it a virtual destructor.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Vehicle {                          // abstract, with ctor + data
protected:
    string number;

public:
    Vehicle(string n) : number(n) {}
    virtual int wheels() const = 0;
    virtual double toll() const = 0;
    void receipt() const {
        cout << number << ": " << wheels() << " wheels, toll Rs."
             << toll() << endl;
    }
    virtual ~Vehicle() {}
};

class Bike : public Vehicle {
public:
    Bike(string n) : Vehicle(n) {}
    int wheels() const override { return 2; }
    double toll() const override { return 0; }
};

class Truck : public Vehicle {
public:
    Truck(string n) : Vehicle(n) {}
    int wheels() const override { return 6; }
    double toll() const override { return 350; }
};

void printReceipt(const Vehicle& v) { v.receipt(); }  // by reference: OK
// void bad(Vehicle v);                               // ERROR: by value

int main() {

    Bike b("MH12-AB-1234");
    Truck t("GJ05-ZZ-9999");

    printReceipt(b);                     // MH12-AB-1234: 2 wheels, toll Rs.0
    printReceipt(t);                     // GJ05-ZZ-9999: 6 wheels, toll Rs.350

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Virtual destructor ->
│      virtual ~Base() { }
│
│  ✔ Definition : If you delete a derived object through a BASE pointer
│                 and the base destructor is NOT virtual, only the base
│                 destructor runs. The derived destructor is skipped →
│                 MEMORY LEAK (and undefined behaviour).
│  ✔ Best practice: every class meant to be a base (has any virtual
│    function) gets a virtual destructor
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() = 0;
    virtual ~Animal() { cout << "~Animal" << endl; }
};

class Dog : public Animal {
    int* bones;

public:
    Dog() : bones(new int[100]) {}
    void sound() override { cout << "Woof" << endl; }
    ~Dog() {
        delete[] bones;
        cout << "~Dog (bones freed)" << endl;
    }
};

int main() {

    Animal* a = new Dog();
    a->sound();                          // Woof
    delete a;
    // ~Dog (bones freed)
    // ~Animal

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Pure virtual destructor ->
│      virtual ~Base() = 0;              // inside the class
│      Base::~Base() { }                 // body is REQUIRED (outside)
│
│  ✔ Definition : Makes a class abstract even when it has NO other
│                 function to make pure.
│  ⚠ It MUST still have a body — every child's destructor calls the
│    base destructor. Without a body → linker error.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Resource {                         // nothing else to make pure
public:
    virtual ~Resource() = 0;
    void use() { cout << "using resource" << endl; }
};

Resource::~Resource() {                  // required body
    cout << "~Resource" << endl;
}

class Socket : public Resource {
public:
    ~Socket() { cout << "~Socket" << endl; }
};

int main() {

    // Resource r;                       // ERROR: abstract
    Resource* r = new Socket();
    r->use();                            // using resource
    delete r;
    // ~Socket
    // ~Resource

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  ⚠ Virtual call inside a constructor / destructor
│  ✔ While the BASE constructor runs, the child part is NOT built yet.
│    So a virtual call there runs the BASE version, not the child's.
│  ✔ Same in the base destructor — the child part is already gone.
│  ✔ Rule: don't depend on virtual calls in constructors / destructors.
│    Call such setup functions AFTER the object is fully made.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base ctor -> ";
        whoAmI();                        // calls Base::whoAmI !
    }

    virtual void whoAmI() { cout << "I am Base" << endl; }

    virtual ~Base() {
        cout << "Base dtor -> ";
        whoAmI();                        // Base version again
    }
};

class Derived : public Base {
public:
    void whoAmI() override { cout << "I am Derived" << endl; }
};

int main() {

    Derived d;                           // Base ctor -> I am Base
    d.whoAmI();                          // I am Derived

    return 0;                            // Base dtor -> I am Base
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  ⚠ Default arguments in virtual functions
│  ✔ The FUNCTION BODY is chosen at run time (child's), but the DEFAULT
│    ARGUMENT is chosen at compile time from the POINTER type (base's)
│  ✔ Result: child's code runs with the BASE's default value — confusing
│  ✔ Rule: never give different defaults in an override. Best: don't use
│    default arguments on virtual functions at all.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Printer {
public:
    virtual void print(int copies = 1) {
        cout << "Printer: " << copies << " copies" << endl;
    }
    virtual ~Printer() {}
};

class OfficePrinter : public Printer {
public:
    void print(int copies = 10) override {
        cout << "OfficePrinter: " << copies << " copies" << endl;
    }
};

int main() {

    OfficePrinter op;
    op.print();                          // OfficePrinter: 10 copies

    Printer* p = &op;
    p->print();                          // OfficePrinter: 1 copies  ⚠
                                         // child body, BASE default
    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Cost of virtual functions
│  ✔ Memory : each object gets one hidden vptr (8 bytes on 64-bit);
│             each class gets one vtable
│  ✔ Speed  : one extra pointer jump per call, and the compiler usually
│             can't INLINE a virtual call
│  ✔ In most programs the cost is tiny — use virtual when you NEED
│    run-time polymorphism; don't make everything virtual "just in case"
│  ✔ When the type is known at compile time, CRTP / templates avoid the
│    cost (see 07_Polymorphism.cpp)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

struct Point {                           // no virtual: small and fast
    float x, y;
    float sum() const { return x + y; }
};

struct VPoint {                          // virtual: extra vptr
    float x, y;
    virtual float sum() const { return x + y; }
    virtual ~VPoint() {}
};

int main() {

    cout << sizeof(Point) << endl;       // 8
    cout << sizeof(VPoint) << endl;      // 16

    // 1 million points → about 8 MB vs 16 MB just for the vptrs
    cout << sizeof(Point) * 1000000 / (1024 * 1024) << " MB" << endl;
    // 7 MB
    cout << sizeof(VPoint) * 1000000 / (1024 * 1024) << " MB" << endl;
    // 15 MB

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Virtual vs pure virtual vs abstract class — quick comparison
│
│   FEATURE                 VIRTUAL FUNCTION        PURE VIRTUAL FUNCTION
│   ──────────────────────  ──────────────────────  ──────────────────────
│   Body in base            yes                     no (= 0), optional body
│   Override needed?        optional                MANDATORY in children
│   Makes class abstract?   no                      YES
│   Object of the class     can be made             can NOT be made
│
│  ✔ Abstract class = has at least one pure virtual function
│  ✔ Interface      = ALL functions pure virtual, no data
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Media {
public:
    virtual void play() { cout << "playing media" << endl; }  // virtual
    virtual void stop() = 0;                                  // pure
    virtual ~Media() {}
};

class Song : public Media {                  // overrides only stop()
public:
    void stop() override { cout << "song stopped" << endl; }
};

class Video : public Media {                 // overrides both
public:
    void play() override { cout << "playing video" << endl; }
    void stop() override { cout << "video stopped" << endl; }
};

int main() {

    Song s;
    Video v;
    Media* list[] = {&s, &v};

    for (Media* m : list) {
        m->play();
        m->stop();
    }
    // playing media      (Song kept the base version)
    // song stopped
    // playing video
    // video stopped

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Full example hierarchy — Shape → Rectangle / Circle / Triangle
│  ✔ Combines: pure virtual functions, virtual destructor, override,
│    a normal function using virtual ones, and a polymorphic container
│  ✔ Adding a new shape needs NO change to printAll()
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual string name() const = 0;
    void describe() const { cout << name() << " area = " << area() << endl; }
    virtual ~Shape() {}
};

class Rectangle : public Shape {
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
    string name() const override { return "Rectangle"; }
};

class Circle : public Shape {
    double radius;

public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    string name() const override { return "Circle"; }
};

class Triangle : public Shape {
    double base, height;

public:
    Triangle(double b, double h) : base(b), height(h) {}
    double area() const override { return 0.5 * base * height; }
    string name() const override { return "Triangle"; }
};

void printAll(const vector<unique_ptr<Shape>>& shapes) {
    double total = 0;
    for (const auto& s : shapes) {
        s->describe();
        total += s->area();
    }
    cout << "Total = " << total << endl;
}

int main() {

    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Rectangle>(10.0, 5.0));
    shapes.push_back(make_unique<Circle>(7.0));
    shapes.push_back(make_unique<Triangle>(6.0, 4.0));

    printAll(shapes);
    // Rectangle area = 50
    // Circle area = 153.938
    // Triangle area = 12
    // Total = 215.938

    return 0;                            // unique_ptr + virtual dtor
}                                        // → everything freed correctly


/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   🎯 INTERVIEW POINTS                                                     ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Q1  Why can't we make an object of an abstract class?
 *      → At least one function has no implementation (pure virtual).
 *        Calling it on such an object would be undefined, so the
 *        compiler stops it.
 *
 *  Q2  Why are pointers / references to an abstract class allowed?
 *      → They only hold an address and create no object. At run time
 *        they point to a concrete child whose implementation is complete.
 *
 *  Q3  Why is a virtual destructor needed in a base class?
 *      → Deleting a child through a base pointer without it runs only the
 *        base destructor — the child's is skipped → memory leak.
 *        So write:  virtual ~Animal() {}
 *
 *  Q4  Can a pure virtual function have a body?
 *      → Yes (written outside the class). The class stays abstract and
 *        children must still override it; they can call the common code
 *        with Base::functionName().
 *
 *  Q5  How is run-time polymorphism achieved?
 *      → Virtual functions + a base pointer / reference. Inside, each
 *        object has a hidden vptr pointing to its class's vtable, which
 *        stores the real function addresses.
 *
 *  Q6  Overriding vs overloading?
 *      → Overriding: same signature in base and child, decided at run
 *        time (needs virtual). Overloading: same name, different
 *        parameters, same scope, decided at compile time.
 *
 *  Q7  Can a class have many pure virtual functions?
 *      → Yes. If ALL functions are pure virtual (and no data), it is a
 *        "pure abstract class" — C++'s version of an interface.
 *
 *  Q8  Can a constructor be virtual? A destructor?
 *      → Constructor: NO (the object and its vptr don't exist yet).
 *        Destructor: YES, and it SHOULD be in a polymorphic base.
 *
 *  Q9  What happens if you call a virtual function in a constructor?
 *      → The BASE version runs, because the child part isn't built yet.
 *
 *  Q10 Real-world use?
 *      → Design patterns (Factory, Strategy, Observer), plugins,
 *        frameworks: one common interface (Shape, Payment, Logger) that
 *        many classes implement in their own way.
 *
 *  KEY TAKEAWAYS
 *  ────────────────────────────────────────────────────────────────────────────
 *   Virtual function       ─► enables run-time polymorphism
 *   Pure virtual function  ─► declared with = 0, body is optional
 *   Abstract class         ─► at least one pure virtual function
 *   Abstract class object  ─► not allowed — only pointer / reference
 *   Virtual destructor     ─► always, if you delete through a base pointer
 *   Real use               ─► designing interfaces / blueprints
 */
