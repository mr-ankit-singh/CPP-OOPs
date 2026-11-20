/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                                INHERITANCE                                ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is Inheritance?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Inheritance is one of the key features of OOP in C++
 *  ✔ The ability of a class to get (inherit) the properties of another
 *    class is called inheritance
 *  ✔ Base class (Parent)    → the class whose properties are inherited
 *  ✔ Derived class (Child)  → the class that inherits them, and can add
 *    its own extra members
 *  ✔ Main benefit: REUSE code — write common code once in the base
 *  ✔ Use inheritance only when there is an IS-A relationship
 *        Car IS-A Vehicle ✔     Dog IS-A Animal ✔     Car IS-A Engine ✘
 *
 *        Syntax:   class Derived : access Base { ... };
 *
 *                     ┌──────────────┐
 *                     │   Vehicle    │  brand, wheels, start()
 *                     └──────┬───────┘
 *                            │  is-a
 *                     ┌──────▼───────┐
 *                     │     Car      │  + model, doors, openTrunk()
 *                     └──────────────┘
 *
 *  Access after inheritance  ⭐
 *  ────────────────────────────────────────────────────────────────────────────
 *   BASE MEMBER    public INHERIT   protected INHERIT   private INHERIT
 *   ───────────    ──────────────   ─────────────────   ───────────────
 *   public         public           protected           private
 *   protected      protected        protected           private
 *   private        NOT accessible   NOT accessible      NOT accessible
 *
 *  ✔ Private members ARE inside the child object, but the child can't
 *    touch them by name — only through the base's public / protected
 *    functions
 *  ✔ Default:  class B : A  → private,   struct B : A  → public
 *
 *  Types of inheritance
 *  ────────────────────────────────────────────────────────────────────────────
 *
 *    SINGLE      MULTIPLE       MULTILEVEL    HIERARCHICAL     HYBRID
 *
 *      A          A     B          A              A              A
 *      │           \   /           │            / | \           / \
 *      B             C             B           B  C  D         B   C
 *                                  │                            \ /
 *                                  C                             D
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   BASICS
 *   ──────
 *   Concept of reusability       ─► Car reuses Vehicle
 *   Base and derived class       ─► Animal → Dog
 *   IS-A vs HAS-A                ─► inherit vs keep as a member
 *   public / protected / private ─► how access changes
 *   protected members            ─► child can use, outside can't
 *
 *   TYPES
 *   ─────
 *   Single, Multiple, Multilevel, Hierarchical, Hybrid
 *
 *   CONSTRUCTORS
 *   ────────────
 *   Order of execution           ─► Base ctor → Derived ctor, dtor reverse
 *   Calling base ctor with args  ─► Car(...) : Vehicle(b, w) { }
 *   Inheriting constructors      ─► using Base::Base;          (C++11)
 *
 *   FUNCTIONS
 *   ─────────
 *   Function overriding          ─► same signature in the child
 *   Calling the base version     ─► Base::show()
 *   Name hiding + using          ─► child's f() hides ALL base f()s
 *
 *   MULTIPLE INHERITANCE ISSUES
 *   ───────────────────────────
 *   Ambiguity + ::               ─► Base1::show() / Base2::show()
 *   Diamond problem              ─► two copies of the top class
 *   Virtual base class           ─► class B : virtual public A
 *
 *   MORE
 *   ────
 *   final                        ─► stop inheriting / overriding (C++11)
 *   Upcasting / downcasting      ─► child → base is safe, base → child not
 *   Object slicing               ─► child copied into base loses its part
 *   What is NOT inherited        ─► ctors, dtor, operator=, friends
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Concept of reusability
│  ✔ Definition : Inheritance lets a new class REUSE code from an existing
│                 class. Less repeated code, less work.
│  ✔ Cars gets displayType() from Vehicles without writing it again
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Vehicles {
public:
    void displayType() { cout << "This is a vehicle." << endl; }
};

class Cars : public Vehicles {
public:
    void displayModel() { cout << "This is a car." << endl; }
};

int main() {

    Cars myCar;
    myCar.displayType();                 // This is a vehicle.  (inherited)
    myCar.displayModel();                // This is a car.      (own)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Base class and derived class ->
│      class Derived : accessSpecifier Base { ... };
│
│  ✔ Base class    : the class whose properties are inherited
│  ✔ Derived class : the class that inherits them
│  ✔ A Dog object has BOTH eat() (from Animal) and bark() (its own)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Animal {                           // base class
public:
    void eat() { cout << "This animal eats food." << endl; }
};

class Dog : public Animal {              // derived class
public:
    void bark() { cout << "The dog barks." << endl; }
};

int main() {

    Dog myDog;
    myDog.eat();                         // This animal eats food.
    myDog.bark();                        // The dog barks.

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  IS-A vs HAS-A
│  ✔ IS-A  → use INHERITANCE      Car IS-A Vehicle
│  ✔ HAS-A → use a MEMBER object  Car HAS-A Engine   (composition)
│  ⚠ Don't inherit just to reuse code. "class Car : public Engine" is
│    wrong — a car is not an engine. Then car.injectFuel() would be
│    public on Car, which makes no sense.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Engine {
public:
    void start() { cout << "Engine running" << endl; }
};

class Vehicle {
public:
    void honk() { cout << "Honk!" << endl; }
};

class Car : public Vehicle {             // IS-A  → inherit
private:
    Engine engine;                       // HAS-A → member

public:
    void drive() {
        engine.start();
        cout << "Car moving" << endl;
    }
};

int main() {

    Car c;
    c.honk();                            // Honk!          (IS-A Vehicle)
    c.drive();
    // Engine running                    (HAS-A Engine)
    // Car moving

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  public | protected | private inheritance ->
│      class D1 : public Base { };       // public  → stays public
│      class D2 : protected Base { };    // public  → becomes protected
│      class D3 : private Base { };      // public  → becomes private
│
│  ✔ public    : public and protected of Base stay public and protected
│  ✔ protected : public and protected of Base become protected
│  ✔ private   : public and protected of Base become private
│  ✔ Private of Base is NEVER accessible in any child
│  ✔ 99% of the time you want PUBLIC inheritance (true IS-A)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base {
public:
    int publicVar = 1;
protected:
    int protectedVar = 2;
private:
    int privateVar = 3;
};

class PublicDerived : public Base {
public:
    void show() {
        cout << publicVar << " " << protectedVar << endl;    // both OK
        // cout << privateVar;           // ERROR: private of Base
    }
};

class ProtectedDerived : protected Base {
public:
    void show() { cout << publicVar << endl; }   // OK inside the child
};

class PrivateDerived : private Base {
public:
    void show() { cout << publicVar << endl; }   // OK inside the child
};

int main() {

    PublicDerived pub;
    pub.show();                          // 1 2
    cout << pub.publicVar << endl;       // 1   (still public)

    ProtectedDerived prot;
    prot.show();                         // 1
    // prot.publicVar;                   // ERROR: now protected

    PrivateDerived priv;
    priv.show();                         // 1
    // priv.publicVar;                   // ERROR: now private

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  protected members — for the family only
│  ✔ protected = private for the OUTSIDE world, but CHILD classes can use
│    it directly
│  ✔ Use it for data the children really need; keep the rest private
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
    double balance = 0;                  // children can use

private:
    string pin = "1234";                 // nobody else, not even children

public:
    void deposit(double a) { balance += a; }
};

class SavingsAccount : public Account {
public:
    void addInterest() {
        balance += balance * 0.04;       // OK: protected
        // pin = "0000";                 // ERROR: private of Account
    }

    double getBalance() const { return balance; }
};

int main() {

    SavingsAccount s;
    s.deposit(1000);
    s.addInterest();
    cout << s.getBalance() << endl;      // 1040

    // s.balance = 5;                    // ERROR: protected from outside

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Single inheritance ->
│      class B : public A { };
│
│  ✔ Definition : A derived class inherits from ONE base class.
│                 The simplest form.            A ──► B
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Parent {
public:
    void showMessage() { cout << "This is the Parent class." << endl; }
};

class Child : public Parent {
public:
    void showChildMessage() { cout << "This is the Child class." << endl; }
};

int main() {

    Child myChild;
    myChild.showMessage();               // This is the Parent class.
    myChild.showChildMessage();          // This is the Child class.

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Multiple inheritance ->
│      class C : public A, public B { };
│
│  ✔ Definition : A derived class inherits from MORE THAN ONE base class.
│                 Combines features of many classes.
│  ✔ Real life: a SmartWatch IS-A Watch and IS-A FitnessTracker
│  ⚠ Can cause ambiguity if two bases have the same member (see later)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Watch {
public:
    void showTime() { cout << "10:30 AM" << endl; }
};

class FitnessTracker {
public:
    void countSteps() { cout << "Steps: 8500" << endl; }
};

class SmartWatch : public Watch, public FitnessTracker {
public:
    void showNotification() { cout << "1 new message" << endl; }
};

int main() {

    SmartWatch sw;
    sw.showTime();                       // 10:30 AM        (from Watch)
    sw.countSteps();                     // Steps: 8500     (from Tracker)
    sw.showNotification();               // 1 new message   (own)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Multilevel inheritance ->
│      class B : public A { };    class C : public B { };
│
│  ✔ Definition : A class inherits from a class that ITSELF inherits
│                 from another class. Forms a CHAIN.
│                 Grandparent ──► Parent ──► Child
│  ✔ Child gets the members of BOTH Parent and Grandparent
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Grandparent {
public:
    void showGrandparent() { cout << "This is the Grandparent." << endl; }
};

class Parent : public Grandparent {
public:
    void showParent() { cout << "This is the Parent." << endl; }
};

class Child : public Parent {
public:
    void showChild() { cout << "This is the Child." << endl; }
};

int main() {

    Child myChild;
    myChild.showGrandparent();           // This is the Grandparent.
    myChild.showParent();                // This is the Parent.
    myChild.showChild();                 // This is the Child.

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Hierarchical inheritance ->
│      class B : public A { };    class C : public A { };
│
│  ✔ Definition : MANY derived classes inherit from ONE base class.
│                 Common code is reused by all related classes.
│                         A
│                       /   \
│                      B     C
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Parent {
public:
    void showMessage() { cout << "This is the Parent class." << endl; }
};

class Child1 : public Parent {
public:
    void showChild1() { cout << "This is Child Class 1." << endl; }
};

class Child2 : public Parent {
public:
    void showChild2() { cout << "This is Child Class 2." << endl; }
};

int main() {

    Child1 child1;
    Child2 child2;

    child1.showMessage();                // This is the Parent class.
    child1.showChild1();                 // This is Child Class 1.

    child2.showMessage();                // This is the Parent class.
    child2.showChild2();                 // This is Child Class 2.

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Hybrid inheritance
│  ✔ Definition : A MIX of two or more types of inheritance.
│                 Here: hierarchical (B, C from A) + multiple (D from B, C)
│                         A
│                       /   \
│                      B     C
│                       \   /
│                         D
│  ⚠ This exact shape is the DIAMOND — D gets TWO copies of A, so
│    obj.showBase() is ambiguous. Fix → virtual base class (see below).
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class BaseClass {
public:
    void showBase() { cout << "This is the Base class." << endl; }
};

class Derived1 : public BaseClass {
public:
    void showDerived1() { cout << "This is Derived Class 1." << endl; }
};

class Derived2 : public BaseClass {
public:
    void showDerived2() { cout << "This is Derived Class 2." << endl; }
};

class Hybrid : public Derived1, public Derived2 {
public:
    void showHybrid() { cout << "This is the Hybrid class." << endl; }
};

int main() {

    Hybrid obj;
    // obj.showBase();                   // ERROR: ambiguous (2 copies)
    obj.Derived1::showBase();            // This is the Base class.
    obj.showDerived1();                  // This is Derived Class 1.
    obj.showDerived2();                  // This is Derived Class 2.
    obj.showHybrid();                    // This is the Hybrid class.

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Constructor / destructor in inheritance — order of execution
│  ✔ Base class constructor runs BEFORE the derived class constructor
│    (the base part must be ready first)
│  ✔ Destructors run in REVERSE: derived first, then base
│  ✔ Multilevel: Grandparent → Parent → Child, then back
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor" << endl; }
    ~Base() { cout << "Base destructor" << endl; }
};

class Derived : public Base {
public:
    Derived() { cout << "Derived constructor" << endl; }
    ~Derived() { cout << "Derived destructor" << endl; }
};

class MoreDerived : public Derived {
public:
    MoreDerived() { cout << "MoreDerived constructor" << endl; }
    ~MoreDerived() { cout << "MoreDerived destructor" << endl; }
};

int main() {

    {
        Derived obj;
        // Base constructor
        // Derived constructor
    }
    // Derived destructor
    // Base destructor

    cout << "---" << endl;            // ---

    MoreDerived m;
    // Base constructor
    // Derived constructor
    // MoreDerived constructor

    return 0;
    // MoreDerived destructor
    // Derived destructor
    // Base destructor
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Calling the base constructor with arguments ->
│      Derived(params) : Base(base_params), member(value) { ... }
│
│  ✔ Definition : The derived constructor can't set the base's private
│                 members in its body. So it calls the BASE CONSTRUCTOR
│                 in its initialization list and passes the values.
│  ✔ The base constructor ALWAYS runs first — if you don't call one,
│    the base's default constructor is called automatically
│  ⚠ If the base has NO default constructor and you don't call one
│    → compile error (the compiler can't guess the values)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string brand;
    int wheels;

public:
    Vehicle(string b, int w) {
        brand = b;
        wheels = w;
        cout << "Vehicle ctor: " << brand << ", " << wheels << " wheels"
             << endl;
    }

    void showVehicleInfo() {
        cout << "Brand: " << brand << ", Wheels: " << wheels << endl;
    }
};

class Car : public Vehicle {
private:
    string model;
    int doors;

public:
    Car(string b, int w, string m, int d) : Vehicle(b, w), model(m), doors(d) {
        cout << "Car ctor: " << model << ", " << doors << " doors" << endl;
    }

    void showCarInfo() {
        showVehicleInfo();               // base class function
        cout << "Model: " << model << ", Doors: " << doors << endl;
    }
};

int main() {

    Car myCar("Toyota", 4, "Fortuner", 4);
    // Vehicle ctor: Toyota, 4 wheels
    // Car ctor: Fortuner, 4 doors

    myCar.showCarInfo();
    // Brand: Toyota, Wheels: 4
    // Model: Fortuner, Doors: 4

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Inheriting constructors (C++11) ->
│      class Derived : public Base { using Base::Base; };
│
│  ✔ Definition : Normally constructors are NOT inherited. With
│                 using Base::Base;  the child gets all the base
│                 constructors, so you don't rewrite them.
│  ✔ Good when the child adds only functions, not new data
│  ⚠ New members of the child are NOT set by these → give them
│    in-class default values
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Message {
protected:
    string text;
    string from;

public:
    Message(string t) : text(t), from("system") {}
    Message(string t, string f) : text(t), from(f) {}
};

class UrgentMessage : public Message {
    int priority = 1;                    // default value for the new member

public:
    using Message::Message;              // reuse BOTH constructors

    void show() {
        cout << "[URGENT " << priority << "] " << from << ": " << text
             << endl;
    }
};

int main() {

    UrgentMessage a("Server down");
    UrgentMessage b("Pay bill", "Bank");

    a.show();                            // [URGENT 1] system: Server down
    b.show();                            // [URGENT 1] Bank: Pay bill

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Function overriding ->
│      class Base    { public: void display(); };
│      class Derived : public Base { public: void display(); };  // same
│
│  ✔ Definition : The derived class gives its OWN version of a function
│                 that already exists in the base, with the SAME
│                 signature (name + parameters).
│  ✔ An object of the derived class calls the derived version
│  ⚠ Without virtual, a BASE POINTER still calls the base version.
│    For true runtime overriding → virtual (see 07_Polymorphism.cpp)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base {
public:
    void display() { cout << "Display from Base class." << endl; }
};

class Derived : public Base {
public:
    void display() { cout << "Display from Derived class." << endl; }
};

int main() {

    Derived obj;
    obj.display();                       // Display from Derived class.

    Base b;
    b.display();                         // Display from Base class.

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Calling the base version of an overridden function ->
│      Base::functionName();
│
│  ✔ Definition : Inside the child, Base::f() runs the PARENT's version.
│                 Very common: do the parent's work, then add extra.
│  ✔ From outside:  obj.Base::f();
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Employee {
public:
    void showDetails() { cout << "Name: Neha, ID: 101" << endl; }
};

class Manager : public Employee {
public:
    void showDetails() {
        Employee::showDetails();         // parent's part first
        cout << "Team size: 8" << endl;  // then the extra part
    }
};

int main() {

    Manager m;
    m.showDetails();
    // Name: Neha, ID: 101
    // Team size: 8

    m.Employee::showDetails();           // Name: Neha, ID: 101

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Name hiding + using Base::func ->
│      class Derived : public Base { public: using Base::print; ... };
│
│  ✔ Definition : If the child writes a function with the same NAME as
│                 the base (even with different parameters), it HIDES
│                 ALL base functions of that name.
│  ✔ Fix: write  using Base::name;  in the child to bring them back
│  ⚠ Surprise bug: d.print(5) fails although Base has print(int)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Printer {
public:
    void print(int n) { cout << "int: " << n << endl; }
    void print(double d) { cout << "double: " << d << endl; }
};

class HidingPrinter : public Printer {
public:
    void print(string s) { cout << "string: " << s << endl; }
};

class GoodPrinter : public Printer {
public:
    using Printer::print;                // bring base versions back
    void print(string s) { cout << "string: " << s << endl; }
};

int main() {

    HidingPrinter h;
    h.print("hi");                       // string: hi
    // h.print(5);                       // ERROR: print(int) is hidden

    GoodPrinter g;
    g.print("hi");                       // string: hi
    g.print(5);                          // int: 5
    g.print(2.5);                        // double: 2.5

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Ambiguity in multiple inheritance — fix with ::
│  ✔ When two base classes have a function with the SAME name, a call
│    through the child doesn't know which one you mean → error
│  ✔ Fix 1: say which one   →  obj.Base1::show()
│  ✔ Fix 2: write show() in the child and decide inside it
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base1 {
public:
    void show() { cout << "Show from Base1" << endl; }
};

class Base2 {
public:
    void show() { cout << "Show from Base2" << endl; }
};

class Derived : public Base1, public Base2 {
public:
    void display() {
        Base1::show();                   // say which one
        Base2::show();
    }
};

int main() {

    Derived obj;
    // obj.show();                       // ERROR: ambiguous

    obj.display();
    // Show from Base1
    // Show from Base2

    obj.Base2::show();                   // Show from Base2

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Diamond problem — the PROBLEM
│  ✔ Teacher and Student both inherit Person. TA inherits both.
│  ✔ Without virtual, TA holds TWO separate Person parts:
│        • Person's constructor runs TWICE
│        • ta.name is ambiguous (which copy?)
│        • the two copies can even hold different values
│
│                 Person            Person
│                   │                 │
│                Teacher           Student
│                    \               /
│                     \_____ TA ____/        ← 2 copies of Person
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name = "unknown";
    Person() { cout << "Person ctor" << endl; }
};

class Teacher : public Person {};
class Student : public Person {};

class TA : public Teacher, public Student {};

int main() {

    TA ta;
    // Person ctor
    // Person ctor                       (twice!)

    // ta.name = "Ravi";                 // ERROR: ambiguous
    ta.Teacher::name = "Ravi";
    cout << ta.Teacher::name << endl;    // Ravi
    cout << ta.Student::name << endl;    // unknown   (other copy!)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Virtual base class — the FIX for the diamond ->
│      class Teacher : virtual public Person { };
│      class Student : virtual public Person { };
│
│  ✔ Definition : Inheriting with "virtual" means: share ONE copy of the
│                 base class among all paths.
│  ✔ Now the constructor runs once, and ta.name is not ambiguous
│  ✔ The MOST-DERIVED class (TA) calls the virtual base's constructor
│    directly — calls from Teacher / Student to Person are skipped
│
│                     Person      ← only ONE copy
│                    /      \
│              Teacher      Student
│                    \      /
│                       TA
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name;
    Person(string n = "unknown") : name(n) {
        cout << "Person ctor: " << name << endl;
    }
};

class Teacher : virtual public Person {
public:
    Teacher() : Person("from Teacher") {}        // skipped for TA
};

class Student : virtual public Person {
public:
    Student() : Person("from Student") {}        // skipped for TA
};

class TA : public Teacher, public Student {
public:
    TA(string n) : Person(n) {}                  // TA builds Person
};

int main() {

    TA ta("Ravi");                       // Person ctor: Ravi   (only once)

    cout << ta.name << endl;             // Ravi   (no ambiguity)
    ta.name = "Ravi Kumar";
    cout << ta.Teacher::name << " | " << ta.Student::name << endl;
    // Ravi Kumar | Ravi Kumar           (same single copy)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  final (C++11) ->
│      class Leaf final { ... };                   // nobody can inherit
│      void f() override final;                    // nobody can override
│
│  ✔ Definition : final on a CLASS stops any class from inheriting it.
│                 final on a virtual FUNCTION stops children from
│                 overriding it again.
│  ✔ Use it to protect a design (e.g. a security check must not change)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Payment {
public:
    virtual void validate() { cout << "basic check" << endl; }
    virtual void pay() { cout << "paying" << endl; }
    virtual ~Payment() {}
};

class SecurePayment : public Payment {
public:
    void validate() override final {             // can't be changed later
        cout << "OTP + PIN check" << endl;
    }
};

class CardPayment final : public SecurePayment {
public:
    // void validate() override {}               // ERROR: validate is final
    void pay() override { cout << "card paid" << endl; }
};

// class Fake : public CardPayment {};           // ERROR: CardPayment is final

int main() {

    CardPayment c;
    c.validate();                        // OTP + PIN check
    c.pay();                             // card paid

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Upcasting and downcasting
│  ✔ Upcasting   : child → base pointer / reference. Always SAFE and
│                  automatic, because a Dog IS-A Animal.
│  ✔ Downcasting : base → child pointer. NOT automatic and can be WRONG
│                  (the Animal may be a Cat!). Use dynamic_cast — it
│                  gives nullptr if the object is not really that type.
│  ⚠ dynamic_cast needs at least one virtual function in the base
│  ✔ More on casts → 12_TypeCasting.cpp
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Animal {
public:
    virtual ~Animal() {}
    void eat() { cout << "eating" << endl; }
};

class Dog : public Animal {
public:
    void fetch() { cout << "fetching ball" << endl; }
};

class Cat : public Animal {};

int main() {

    Dog d;
    Animal* a = &d;                      // upcast: automatic, safe
    a->eat();                            // eating
    // a->fetch();                       // ERROR: Animal has no fetch()

    Dog* back = dynamic_cast<Dog*>(a);   // downcast: checked
    if (back) back->fetch();             // fetching ball

    Cat c;
    Animal* a2 = &c;
    Dog* wrong = dynamic_cast<Dog*>(a2); // a Cat is not a Dog
    cout << (wrong == nullptr ? "not a dog" : "dog") << endl;   // not a dog

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Object slicing
│  ✔ Definition : When a CHILD object is copied into a BASE object (by
│                 value), only the base part is copied. The child's extra
│                 data and its overridden behaviour are "sliced off".
│  ✔ Happens with:  Base b = child;   and   void f(Base b)  (by value)
│  ✔ Fix: use a reference or pointer → Base& / Base*
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Notification {
public:
    string text = "You have a message";
    virtual void send() const { cout << "Notify: " << text << endl; }
    virtual ~Notification() {}
};

class EmailNotification : public Notification {
public:
    string email = "amit@mail.com";
    void send() const override {
        cout << "Email to " << email << ": " << text << endl;
    }
};

void sendByValue(Notification n) { n.send(); }       // ⚠ slices
void sendByRef(const Notification& n) { n.send(); }  // ✔ no slicing

int main() {

    EmailNotification e;

    sendByValue(e);                      // Notify: You have a message
    sendByRef(e);
    // Email to amit@mail.com: You have a message

    Notification copy = e;               // sliced: email part is gone
    copy.send();                         // Notify: You have a message

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  What is NOT inherited
│  ✔ Constructors      → not inherited (but  using Base::Base;  can bring
│                         them, see above)
│  ✔ Destructor        → not inherited; the child gets its own, which
│                         calls the base destructor automatically
│  ✔ operator=         → the child's own (compiler-made) operator= hides
│                         the base one; it calls the base's internally
│  ✔ Friend functions  → friendship is NOT inherited
│  ✔ Private members   → ARE inside the object, but NOT accessible
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Base {
    int secret = 42;
    friend void peek(const Base& b);

public:
    Base() { cout << "Base ctor" << endl; }
    Base(int) { cout << "Base(int) ctor" << endl; }
    ~Base() { cout << "Base dtor" << endl; }
};

void peek(const Base& b) { cout << "secret = " << b.secret << endl; }

class Derived : public Base {
    int mine = 7;
    // friend peek can NOT see 'mine' — friendship isn't inherited
};

int main() {

    Derived d;                           // Base ctor   (default one used)
    // Derived d2(5);                    // ERROR: Base(int) not inherited

    peek(d);                             // secret = 42  (Base part only)

    cout << sizeof(d) << endl;           // 8  (secret + mine: both inside)

    return 0;                            // Base dtor
}
