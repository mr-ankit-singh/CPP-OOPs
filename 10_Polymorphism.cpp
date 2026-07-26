/*==============================================================================
    🧩 Polymorphism
    --------------------------------------------------------------------------
    🔹 Polymorphism means "Many Forms" — the SAME function/operator/entity
       behaves DIFFERENTLY depending on the CONTEXT (arguments, or the
       ACTUAL object type it's working with).
    🔸 2 Main Types:
         1. Compile-Time Polymorphism (Static Binding)  → Resolved at
            COMPILE time — Function Overloading, Operator Overloading,
            Constructor Overloading.
         2. Runtime Polymorphism (Dynamic Binding)       → Resolved at
            RUN time — Virtual Functions, Function Overriding.
    ⚙️ Compile-Time = FASTER (decided before program runs)
    ⚙️ Runtime      = FLEXIBLE (decided while program is running)
==============================================================================*/

#include <iostream>
using namespace std;


/*==============================================================================
    PART 1 : Compile-Time Polymorphism (Static Binding)
==============================================================================*/

/*------------------------------------------------------------------------
    1.1 Function Overloading
    --------------------------------------------------------------------
    🔹 SAME function name, but DIFFERENT parameters (number/type).
    🔸 Compiler decides, AT COMPILE TIME, WHICH version to call —
       based on the ARGUMENTS you pass.
------------------------------------------------------------------------*/
class Calculator {
public:
    // Same name "add", DIFFERENT parameter lists
    int add(int a, int b) {
        return a + b;
    }
    double add(double a, double b) {
        return a + b;
    }
    int add(int a, int b, int c) {
        return a + b + c;
    }
};


/*------------------------------------------------------------------------
    1.2 Operator Overloading
    --------------------------------------------------------------------
    🔹 Giving EXISTING operators (+, -, ==, etc.) a NEW meaning, for
       USER-DEFINED types (classes).
    🔸 Compiler decides, AT COMPILE TIME, which "+" to use — based on
       the TYPE of operands.
------------------------------------------------------------------------*/
class Complex {
public:
    double real, imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Overloading "+" operator for Complex numbers
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};


/*------------------------------------------------------------------------
    1.3 Constructor Overloading
    --------------------------------------------------------------------
    🔹 SAME class, MULTIPLE constructors — DIFFERENT parameter lists.
    🔸 Compiler decides, AT COMPILE TIME, WHICH constructor to call —
       based on HOW MANY/WHAT TYPE of arguments you pass while creating
       the object.
------------------------------------------------------------------------*/
class Rectangle {
public:
    double length, width;

    // Default constructor
    Rectangle() {
        length = 1.0;
        width = 1.0;
    }
    // Parameterized constructor (Square-like — one value)
    Rectangle(double side) {
        length = side;
        width = side;
    }
    // Parameterized constructor (two values)
    Rectangle(double l, double w) {
        length = l;
        width = w;
    }

    double area() {
        return length * width;
    }
};


/*==============================================================================
    PART 2 : Runtime Polymorphism (Dynamic Binding)
==============================================================================*/

/*------------------------------------------------------------------------
    2.1 Virtual Functions & 2.2 Function Overriding
    --------------------------------------------------------------------
    🔹 Virtual Function: A BASE CLASS function, marked with "virtual",
       that a DERIVED CLASS is EXPECTED to REDEFINE (override).
    🔸 Function Overriding: DERIVED class provides its OWN
       implementation of a function ALREADY defined in the BASE class
       (SAME name, SAME parameters).
    ⚙️ WITHOUT "virtual", C++ uses STATIC BINDING (decides at compile
       time, based on POINTER TYPE, NOT actual object) — this is the
       #1 mistake beginners make.
------------------------------------------------------------------------*/
class Animal {
public:
    // "virtual" keyword — tells compiler: "decide the ACTUAL function
    // to call, at RUNTIME, based on the REAL object, not the pointer type"
    virtual void makeSound() {
        cout << "Some generic animal sound" << endl;
    }
};

class Dog : public Animal {
public:
    // "override" keyword (C++11+) — OPTIONAL, but BEST PRACTICE —
    // compiler will ERROR if this doesn't actually match a virtual
    // function in the base class (catches typos)
    void makeSound() override {
        cout << "Woof! Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "Meow!" << endl;
    }
};


/*------------------------------------------------------------------------
    2.3 Abstract Classes (Pure Virtual Functions)
    --------------------------------------------------------------------
    🔹 Pure Virtual Function: A virtual function with "= 0" — it has
       NO implementation in the base class, FORCING derived classes to
       provide their OWN implementation.
    🔸 Abstract Class: A class with AT LEAST ONE pure virtual function
       — it CANNOT be instantiated directly (you cannot do
       "Shape s;" — only derived, CONCRETE classes can be created).
------------------------------------------------------------------------*/
class Shape {
public:
    // Pure virtual function — makes Shape an ABSTRACT class
    virtual double area() = 0;

    virtual void describe() {
        cout << "This shape has an area of " << area() << endl;
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}

    // MUST override area(), otherwise Circle would ALSO become abstract
    double area() override {
        return 3.14159 * radius * radius;
    }
};

class Square : public Shape {
    double side;
public:
    Square(double s) : side(s) {}

    double area() override {
        return side * side;
    }
};


/*------------------------------------------------------------------------
    2.4 Virtual Destructors
    --------------------------------------------------------------------
    🔹 If a BASE class pointer is used to "delete" a DERIVED class
       object, and the BASE destructor is NOT virtual, ONLY the base
       class destructor runs — the DERIVED class destructor is SKIPPED
       (memory leak risk!).
    🔸 RULE: If a class has ANY virtual function (or is meant to be a
       base class for polymorphism), its DESTRUCTOR should ALSO be
       virtual.
------------------------------------------------------------------------*/
class Base {
public:
    // virtual destructor — ensures derived destructor ALSO runs
    virtual ~Base() {
        cout << "Base destructor called" << endl;
    }
};

class Derived : public Base {
    int* data;
public:
    Derived() {
        data = new int[10];   // allocates some memory
        cout << "Derived constructor called" << endl;
    }
    ~Derived() {
        delete[] data;         // this MUST run, to avoid a memory leak
        cout << "Derived destructor called" << endl;
    }
};


/*------------------------------------------------------------------------
    2.5 Dynamic Binding (Late Binding) — Demonstrated via a function
    --------------------------------------------------------------------
    🔹 The ACTUAL function called is decided at RUNTIME, based on the
       REAL object the pointer/reference points to — NOT the pointer's
       declared type. This is what makes Runtime Polymorphism POWERFUL.
------------------------------------------------------------------------*/
void printAnimalSound(Animal* animal) {
    // Even though the parameter type is "Animal*", the CORRECT
    // overridden version runs, based on what it ACTUALLY points to
    animal->makeSound();
}


/*==============================================================================
    PART 3 : vtable and vptr Concept (How Virtual Functions Work Internally)
    ------------------------------------------------------------------------
    🔹 vtable (Virtual Table): A HIDDEN, STATIC array, created by the
       COMPILER, ONE PER CLASS that has virtual functions — it stores
       POINTERS to the ACTUAL virtual function implementations.
    🔸 vptr (Virtual Pointer): A HIDDEN pointer, added to EVERY OBJECT
       of such a class, that POINTS to its class's vtable.
    ⚙️ How a virtual call works:
         object->function()
           → Compiler follows the object's vptr → finds its vtable
           → looks up the CORRECT function address in that vtable
           → calls THAT function (this lookup happens at RUNTIME)
    ⚙️ This is WHY runtime polymorphism has a (tiny) performance cost
       compared to normal function calls — there's ONE EXTRA "hop"
       through the vtable.
==============================================================================*/


/*==============================================================================
    PART 4 : Rules for Virtual Functions
    ------------------------------------------------------------------------
    🔹 1. A function becomes virtual ONLY if declared "virtual" in the
          BASE class — derived classes don't need to repeat the
          keyword (but "override" is recommended for safety).
    🔸 2. Virtual functions are resolved using a BASE CLASS
          POINTER/REFERENCE pointing to a DERIVED object — NOT with
          normal (non-pointer/non-reference) objects.
    🔹 3. Constructors CANNOT be virtual (object isn't fully created
          yet when constructor runs) — but DESTRUCTORS SHOULD be
          virtual in a polymorphic base class.
    🔸 4. Static member functions CANNOT be virtual (they don't belong
          to any specific object).
    🔹 5. A pure virtual function (= 0) makes its class ABSTRACT —
          cannot be instantiated directly.
==============================================================================*/


/*==============================================================================
    PART 5 : Static vs Dynamic Binding
    ------------------------------------------------------------------------
    🔹 Static Binding (Early Binding): Function call is resolved AT
          COMPILE TIME. Used for: normal functions, overloaded
          functions, non-virtual functions.
    🔸 Dynamic Binding (Late Binding): Function call is resolved AT
          RUNTIME, based on the ACTUAL object type. Used for: virtual
          functions, called through a base class pointer/reference.
==============================================================================*/
class Parent {
public:
    void staticBindDemo() {         // NOT virtual → Static Binding
        cout << "Parent's staticBindDemo()" << endl;
    }
    virtual void dynamicBindDemo() { // virtual → Dynamic Binding
        cout << "Parent's dynamicBindDemo()" << endl;
    }
};

class Child : public Parent {
public:
    void staticBindDemo() {
        cout << "Child's staticBindDemo()" << endl;
    }
    void dynamicBindDemo() override {
        cout << "Child's dynamicBindDemo()" << endl;
    }
};


/*==============================================================================
    MAIN — Testing everything above
==============================================================================*/
int main() {

    cout << "===== 1.1 Function Overloading =====" << endl;
    Calculator calc;
    cout << "add(2,3) = " << calc.add(2, 3) << endl;
    cout << "add(2.5,3.5) = " << calc.add(2.5, 3.5) << endl;
    cout << "add(1,2,3) = " << calc.add(1, 2, 3) << endl;

    cout << "\n===== 1.2 Operator Overloading =====" << endl;
    Complex c1(2, 3), c2(4, 5);
    Complex c3 = c1 + c2;   // uses our overloaded "+"
    cout << "c1 + c2 = ";
    c3.display();

    cout << "\n===== 1.3 Constructor Overloading =====" << endl;
    Rectangle r1;             // default constructor
    Rectangle r2(5);          // single-arg constructor
    Rectangle r3(4, 6);       // two-arg constructor
    cout << "r1 area = " << r1.area() << endl;
    cout << "r2 area = " << r2.area() << endl;
    cout << "r3 area = " << r3.area() << endl;

    cout << "\n===== 2.1/2.2 Virtual Functions & Overriding =====" << endl;
    Dog dog;
    Cat cat;
    Animal* animalPtr;

    animalPtr = &dog;
    animalPtr->makeSound();   // Runtime decides: calls Dog's version

    animalPtr = &cat;
    animalPtr->makeSound();   // Runtime decides: calls Cat's version

    cout << "\n===== 2.3 Abstract Classes (Pure Virtual) =====" << endl;
    // Shape s;               // ERROR — cannot instantiate abstract class
    Circle circle(5);
    Square square(4);
    circle.describe();
    square.describe();

    cout << "\n===== 2.4 Virtual Destructors =====" << endl;
    Base* basePtr = new Derived();
    delete basePtr;   // BOTH destructors run, because ~Base() is virtual

    cout << "\n===== 2.5 Dynamic Binding via Function Parameter =====" << endl;
    printAnimalSound(&dog);
    printAnimalSound(&cat);

    cout << "\n===== Part 5: Static vs Dynamic Binding =====" << endl;
    Child childObj;
    Parent* parentPtr = &childObj;

    parentPtr->staticBindDemo();    // STATIC binding -> Parent's version
                                     // (decided by POINTER TYPE, not object)
    parentPtr->dynamicBindDemo();   // DYNAMIC binding -> Child's version
                                     // (decided by ACTUAL object type)

    return 0;
}