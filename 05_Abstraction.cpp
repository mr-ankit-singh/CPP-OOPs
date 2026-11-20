/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                                ABSTRACTION                                ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is Abstraction?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Abstraction = SHOW only the essential, useful features to the user,
 *    and HIDE all the complex inside details the user doesn't need
 *  ✔ Simple words: the user knows WHAT something does — not HOW it does
 *    it inside
 *
 *  ✔ Real life: when you drive a CAR you only need to know — turn the
 *    steering, press the accelerator, press the brake. Engine ke andar
 *    fuel injection, combustion, pistons kaise kaam karte hain — yeh
 *    jaanne ki zaroorat nahi. That complexity is hidden behind the car's
 *    "interface" (steering, pedals).
 *
 *              USER sees                  HIDDEN inside
 *          ┌──────────────────┐       ┌──────────────────────────┐
 *          │  startCar()      │ ────► │ engageIgnition()         │
 *          │  brake()         │       │ igniteFuel()             │
 *          │                  │       │ checkBattery() ...       │
 *          └──────────────────┘       └──────────────────────────┘
 *               WHAT                            HOW
 *
 *  How do we get abstraction in C++?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ 1. Classes      → make only the needed members public (interface),
 *                      keep the implementation private
 *  ✔ 2. Abstract classes → pure virtual functions say "WHAT to do"
 *                      without saying "HOW"; child classes give the HOW
 *  ✔ 3. Header files → users see only the .h (declarations), not the
 *                      .cpp (bodies)
 *
 *  Why abstraction matters
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Less complexity for the user — only the needed things are visible
 *  ✔ Inside code can change easily without touching the user-facing part
 *    (change igniteFuel()'s logic → people calling startCar() see no
 *    difference)
 *  ✔ Code stays clean and maintainable because WHAT and HOW are separate
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Abstraction via a class        ─► public startCar(), private steps
 *   Hiding implementation details  ─► TV, Car — use without the circuit
 *   Showing only essential features ─► Smartphone
 *   Abstract classes               ─► at least one pure virtual function
 *   Pure virtual functions         ─► virtual void f() = 0;
 *   Rules of abstract classes      ─► ctor, data, pointer, must override
 *   Interface                      ─► class with ONLY pure virtual fns
 *   Abstraction via header files   ─► .h shows WHAT, .cpp hides HOW
 *   Abstraction vs Encapsulation   ─► table + example
 *
 *  ✔ vtable, virtual destructors in depth → see 10_VirtualFunction.cpp
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Abstraction via a class
│  ✔ The user only knows startCar() — call it and the car starts
│  ✔ igniteFuel() and engageIgnition() are PRIVATE: the user can't call
│    them and doesn't even need to know they exist
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Car {
private:
    void engageIgnition() { cout << "Ignition engaged..." << endl; }
    void igniteFuel() { cout << "Fuel ignited..." << endl; }

public:
    void startCar() {                    // simple, essential interface
        engageIgnition();
        igniteFuel();
        cout << "Car started! Ready to drive." << endl;
    }
};

int main() {

    Car myCar;
    myCar.startCar();
    // Ignition engaged...
    // Fuel ignited...
    // Car started! Ready to drive.

    // myCar.igniteFuel();               // ERROR: hidden detail

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Hiding implementation details
│  ✔ Users work with a high-level interface; the inside is hidden to
│    reduce complexity
│  ✔ Like using a TV remote without knowing its circuit
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class TV {
private:
    int current = 1;
    void tuneFrequency(int ch) { current = ch; }     // hidden

public:
    void turnOn() { cout << "TV is now ON." << endl; }
    void turnOff() { cout << "TV is now OFF." << endl; }

    void changeChannel(int channel) {
        tuneFrequency(channel);
        cout << "Changing to channel " << current << "." << endl;
    }
};

class Engine {
public:
    void startEngine() { cout << "Engine started." << endl; }
    void stopEngine() { cout << "Engine stopped." << endl; }
    void accelerate(int speed) {
        cout << "Accelerating to " << speed << " km/h." << endl;
    }
};

int main() {

    TV myTV;
    myTV.turnOn();                       // TV is now ON.
    myTV.changeChannel(5);               // Changing to channel 5.
    myTV.turnOff();                      // TV is now OFF.

    Engine e;
    e.startEngine();                     // Engine started.
    e.accelerate(60);                    // Accelerating to 60 km/h.
    e.stopEngine();                      // Engine stopped.

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Showing only essential features
│  ✔ Give a simple interface for a complex system
│  ✔ You use a smartphone without knowing the network, antenna or
│    hardware details
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Smartphone {
private:
    bool connectToTower() { return true; }           // hidden
    string encrypt(string s) { return "[" + s + "]"; }

public:
    void makeCall(string number) {
        if (connectToTower()) cout << "Calling " << number << "..." << endl;
    }

    void sendMessage(string number, string message) {
        cout << "To " << number << ": " << encrypt(message) << endl;
    }

    void browseInternet(string url) {
        cout << "Browsing to " << url << "..." << endl;
    }
};

int main() {

    Smartphone myPhone;
    myPhone.makeCall("98765-43210");             // Calling 98765-43210...
    myPhone.sendMessage("98765-43210", "Hello!");
    // To 98765-43210: [Hello!]
    myPhone.browseInternet("example.com");   // Browsing to example.com...

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Abstract class ->
│      class Animal { public: virtual void sound() = 0; };
│      class Dog : public Animal { public: void sound() override {...} };
│
│  ✔ Definition : An abstract class has AT LEAST ONE pure virtual
│                 function. You can NOT create its object. It is a
│                 blueprint that child classes must complete.
│  ✔ It says "every Animal can make a sound", but not WHICH sound
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void sound() = 0;            // pure virtual function
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void sound() override { cout << "Woof Woof!" << endl; }
};

class Cat : public Animal {
public:
    void sound() override { cout << "Meow Meow!" << endl; }
};

int main() {

    // Animal a;                         // ERROR: Animal is abstract

    Dog dog;
    Cat cat;
    dog.sound();                         // Woof Woof!
    cat.sound();                         // Meow Meow!

    Animal* pets[] = {&dog, &cat};       // pointer to abstract class: OK
    for (Animal* p : pets) p->sound();
    // Woof Woof!
    // Meow Meow!

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Pure virtual function ->
│      virtual ReturnType name(params) = 0;
│
│  ✔ Definition : A virtual function with "= 0" and (usually) no body.
│                 It MUST be overridden in the child class. Having even
│                 one of them makes the class abstract.
│  ✔ Shape says "every shape has area()" — Rectangle and Circle say how
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() = 0;           // pure virtual
    virtual ~Shape() {}
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() override { return width * height; }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    double area() override { return 3.14159 * radius * radius; }
};

int main() {

    Rectangle rect(10.0, 5.0);
    Circle circ(7.0);

    cout << "Rectangle: " << rect.area() << endl;    // Rectangle: 50
    cout << "Circle: " << circ.area() << endl;       // Circle: 153.938

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Rules of abstract classes
│  ✔ 1. No objects of it — but POINTERS and REFERENCES to it are fine
│  ✔ 2. It CAN have data members, normal functions and a constructor
│       (the constructor runs when a child object is made)
│  ✔ 3. A child that does NOT override every pure virtual function is
│       ALSO abstract
│  ✔ 4. Give it a virtual destructor (so delete via base pointer works)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Employee {                                 // abstract
protected:
    string name;                                 // data member: OK

public:
    Employee(string n) : name(n) {               // constructor: OK
        cout << "Employee ctor for " << name << endl;
    }

    virtual double salary() = 0;                 // pure virtual
    virtual string role() = 0;

    void payslip() {                             // normal function: OK
        cout << name << " (" << role() << "): " << salary() << endl;
    }

    virtual ~Employee() {}
};

class Manager : public Employee {
public:
    Manager(string n) : Employee(n) {}
    double salary() override { return 90000; }
    string role() override { return "Manager"; }
};

class Intern : public Employee {                 // overrides only ONE
public:
    Intern(string n) : Employee(n) {}
    double salary() override { return 15000; }
    // role() missing → Intern is still abstract
};

int main() {

    Manager m("Neha");                   // Employee ctor for Neha
    m.payslip();                         // Neha (Manager): 90000

    Employee& ref = m;                   // reference to abstract: OK
    cout << ref.role() << endl;          // Manager

    // Intern i("Ravi");                 // ERROR: Intern is abstract

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Interface (class with ONLY pure virtual functions) ->
│      class IPayment {
│      public:
│          virtual bool pay(double amt) = 0;
│          virtual ~IPayment() = default;
│      };
│
│  ✔ Definition : C++ has no "interface" keyword. A class with ONLY pure
│                 virtual functions (and no data) works as an interface:
│                 a contract that says what a class MUST be able to do.
│  ✔ Many people start interface names with I (IPayment, IPrintable)
│  ✔ A class can implement MANY interfaces (multiple inheritance)
│  ✔ Code that uses IPayment works with ANY payment type — even ones
│    written later
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class IPayment {                                 // interface
public:
    virtual bool pay(double amount) = 0;
    virtual string name() = 0;
    virtual ~IPayment() = default;
};

class INotifier {                                // another interface
public:
    virtual void notify(string msg) = 0;
    virtual ~INotifier() = default;
};

class UPI : public IPayment {
public:
    bool pay(double a) override {
        cout << "UPI paid " << a << endl;
        return true;
    }
    string name() override { return "UPI"; }
};

class Card : public IPayment, public INotifier { // two interfaces
public:
    bool pay(double a) override {
        cout << "Card paid " << a << endl;
        return true;
    }
    string name() override { return "Card"; }
    void notify(string msg) override { cout << "SMS: " << msg << endl; }
};

void checkout(IPayment& method, double amount) { // knows only the contract
    if (method.pay(amount))
        cout << "Order done via " << method.name() << endl;
}

int main() {

    UPI upi;
    Card card;

    checkout(upi, 499);
    // UPI paid 499
    // Order done via UPI

    checkout(card, 1299);
    // Card paid 1299
    // Order done via Card

    card.notify("Rs.1299 debited");      // SMS: Rs.1299 debited

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Abstraction using header files
│  ✔ The .h file shows only WHAT the class offers (declarations)
│  ✔ The .cpp file has HOW it works (bodies). Users of a library often
│    get only the .h and a compiled file — they never see the code.
│  ✔ Example: you use  sqrt()  from <cmath>  without seeing its code
│
│      // ───── Weather.h ─────      (users see this)
│      class Weather {
│      public:
│          double getTemperature(const string& city);
│      };
│
│      // ───── Weather.cpp ─────    (hidden: API call, caching ...)
│
│  ✔ Below, all parts are in one file so it runs with Ctrl+Alt+N
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

// ───── Weather.h ─────
class Weather {
public:
    double getTemperature(const string& city);

private:
    double fetchFromServer(const string& city);
};

// ───── Weather.cpp ─────
double Weather::fetchFromServer(const string& city) {
    return city == "Delhi" ? 41.5 : 29.0;        // pretend API call
}

double Weather::getTemperature(const string& city) {
    return fetchFromServer(city);
}

// ───── main.cpp ─────
int main() {

    Weather w;
    cout << w.getTemperature("Delhi") << endl;   // 41.5
    cout << w.getTemperature("Pune") << endl;    // 29

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Abstraction vs Encapsulation
│
│   POINT           ABSTRACTION                 ENCAPSULATION
│   ──────────────  ──────────────────────────  ──────────────────────────
│   Idea            hide COMPLEXITY             hide DATA
│   Focus           WHAT the object does        HOW data is kept safe
│   Level           design level                implementation level
│   Achieved by     abstract class, interface,  private / protected +
│                   public methods              getters / setters
│   Question        "what should user see?"     "who can touch the data?"
│   Example         car pedals hide the engine  balance is private
│
│  ✔ They work TOGETHER: encapsulation is one of the tools used to get
│    abstraction
│  ✔ Below: the user sees only buy() (abstraction), and price / stock
│    are private with checks (encapsulation)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string productName;                  // encapsulation: hidden data
    double price;
    int stock;

    double applyDiscount() const {       // abstraction: hidden logic
        return price > 1000 ? price * 0.9 : price;
    }

public:
    Product(string n, double p, int s) : productName(n), price(p), stock(s) {}

    void buy() {                         // the only thing users see
        if (stock == 0) { cout << "Out of stock" << endl; return; }
        stock--;
        cout << productName << " bought for " << applyDiscount() << endl;
    }
};

int main() {

    Product prod("Laptop", 50000, 1);
    prod.buy();                          // Laptop bought for 45000
    prod.buy();                          // Out of stock

    return 0;
}
