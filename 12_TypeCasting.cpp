/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                           TYPE CASTING IN OOP                             ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is type casting?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Type casting = converting a value from one type to another
 *  ✔ Implicit → done by the compiler automatically   (int → double)
 *  ✔ Explicit → you ask for it with a cast
 *  ✔ In OOP we often convert between a BASE and a DERIVED class pointer
 *
 *  Old C-style cast vs C++ casts
 *  ────────────────────────────────────────────────────────────────────────────
 *        (Dog*)animalPtr;                  // C-style — does ANYTHING,
 *                                          // no checks, hard to find
 *        static_cast<Dog*>(animalPtr);     // C++ — clear purpose, easy
 *                                          // to search, safer
 *
 *  ✔ C++ has 4 named casts, each for ONE job:
 *
 *   CAST               JOB                                 CHECKED WHEN
 *   ─────────────────  ──────────────────────────────────  ──────────────
 *   static_cast        normal, "sensible" conversions      compile time
 *   dynamic_cast       SAFE down-cast in a hierarchy       run time
 *   const_cast         add / remove const                  compile time
 *   reinterpret_cast   treat bits as another type (raw)    NOT checked
 *
 *  Upcasting vs downcasting
 *  ────────────────────────────────────────────────────────────────────────────
 *
 *               Animal          ▲  UPCAST  (Dog* → Animal*)
 *                 │             │  always safe, automatic
 *                Dog            ▼  DOWNCAST (Animal* → Dog*)
 *                                  may be WRONG — check with dynamic_cast
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   static_cast                  ─► numbers, upcast, unchecked downcast
 *   dynamic_cast (pointer)       ─► nullptr if the type is wrong
 *   dynamic_cast (reference)     ─► throws bad_cast if wrong
 *   const_cast                   ─► remove const (only if not really const)
 *   reinterpret_cast             ─► raw bits / addresses
 *   RTTI: typeid and type_info   ─► find the real type at run time
 *   User-defined conversions     ─► constructor + conversion operator
 *   Which cast when?             ─► summary table
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  static_cast ->
│      static_cast<NewType>(value)
│
│  ✔ Definition : For normal, sensible conversions the compiler can
│                 check at COMPILE time:
│                   • number types   double → int,  int → char
│                   • upcast         Dog* → Animal*  (also automatic)
│                   • downcast       Animal* → Dog*  (NOT checked!)
│                   • void* → T*
│  ⚠ static_cast downcast trusts YOU. If the object isn't really a Dog
│    → undefined behaviour. Use it only when you are 100% sure.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Animal {
public:
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void bark() { cout << "Woof" << endl; }
};

int main() {

    double price = 99.99;
    int rupees = static_cast<int>(price);        // number conversion
    cout << rupees << endl;                      // 99

    int total = 7, count = 2;
    cout << static_cast<double>(total) / count << endl;    // 3.5

    Dog d;
    Animal* a = static_cast<Animal*>(&d);        // upcast (safe)

    Dog* back = static_cast<Dog*>(a);            // downcast: we KNOW it's a Dog
    back->bark();                                // Woof

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  dynamic_cast with pointers ->
│      Derived* p = dynamic_cast<Derived*>(basePtr);
│      if (p) { ... }                  // nullptr if the type is wrong
│
│  ✔ Definition : A SAFE downcast. At RUN time it checks the real type of
│                 the object. Right type → valid pointer, wrong type →
│                 nullptr.
│  ⚠ Works only for POLYMORPHIC classes (base has at least one virtual
│    function — usually the virtual destructor)
│  ✔ Small run-time cost; frequent use can mean the design needs a
│    virtual function instead
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
using namespace std;

class Employee {
public:
    virtual ~Employee() {}
};

class Manager : public Employee {
public:
    void approveLeave() { cout << "Leave approved" << endl; }
};

class Developer : public Employee {
public:
    void writeCode() { cout << "Writing code" << endl; }
};

int main() {

    vector<Employee*> staff = {new Developer, new Manager, new Developer};

    for (Employee* e : staff) {
        if (Manager* m = dynamic_cast<Manager*>(e))
            m->approveLeave();
        else if (Developer* d = dynamic_cast<Developer*>(e))
            d->writeCode();
    }
    // Writing code
    // Leave approved
    // Writing code

    for (Employee* e : staff) delete e;

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  dynamic_cast with references ->
│      Derived& r = dynamic_cast<Derived&>(baseRef);   // may throw
│
│  ✔ Definition : A reference can't be "null", so when the type is wrong
│                 dynamic_cast THROWS std::bad_cast instead.
│  ✔ Header: <typeinfo>
│  ✔ Pointer version → check for nullptr,  reference version → try/catch
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <typeinfo>
using namespace std;

class Payment {
public:
    virtual ~Payment() {}
};

class CardPayment : public Payment {
public:
    string last4 = "4242";
};

class CashPayment : public Payment {};

void printCard(Payment& p) {
    try {
        CardPayment& card = dynamic_cast<CardPayment&>(p);
        cout << "Card ending " << card.last4 << endl;
    } catch (const bad_cast&) {
        cout << "Not a card payment" << endl;
    }
}

int main() {

    CardPayment card;
    CashPayment cash;

    printCard(card);                     // Card ending 4242
    printCard(cash);                     // Not a card payment

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  const_cast ->
│      const_cast<T*>(constPtr)        const_cast<T&>(constRef)
│
│  ✔ Definition : The ONLY cast that can add or remove const.
│  ✔ Real use: calling an OLD function that takes  char*  but doesn't
│    actually change the data, when you only have a  const char*
│  ⚠ Changing an object that was CREATED const through const_cast is
│    undefined behaviour. Only remove const if the original object
│    was NOT const.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstring>
using namespace std;

int oldLibraryLength(char* s) {          // old API, forgot "const"
    return strlen(s);                    // (doesn't change s)
}

class Counter {
    int hits = 0;

public:
    void touch() { hits++; }
    int get() const { return hits; }
};

int main() {

    const char* name = "Neha";
    // oldLibraryLength(name);           // ERROR: const char* → char*
    cout << oldLibraryLength(const_cast<char*>(name)) << endl;   // 4

    Counter c;                           // NOT const originally
    const Counter& view = c;
    const_cast<Counter&>(view).touch();  // OK: real object isn't const
    cout << c.get() << endl;             // 1

    // const Counter fixed;
    // const_cast<Counter&>(fixed).touch();   // ⚠ undefined behaviour

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  reinterpret_cast ->
│      reinterpret_cast<NewType*>(ptr)
│
│  ✔ Definition : Treat the same BITS as a completely different type.
│                 No checks, no conversion of the value. The most
│                 DANGEROUS cast.
│  ✔ Real use: low-level work — reading raw bytes of an object, hardware
│    addresses, network / file buffers, pointer ↔ integer
│  ⚠ Avoid in normal OOP code. If you need it, you are working with raw
│    memory.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstdint>
using namespace std;

struct Pixel {
    unsigned char r, g, b, a;
};

int main() {

    Pixel px{255, 128, 0, 255};

    // look at the same 4 bytes as raw unsigned chars
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&px);
    for (int i = 0; i < 4; i++) cout << (int)bytes[i] << " ";
    cout << endl;                        // 255 128 0 255

    // pointer → integer (e.g. to print or hash an address)
    uintptr_t addr = reinterpret_cast<uintptr_t>(&px);
    cout << (addr != 0) << endl;         // 1

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  RTTI: typeid and type_info ->
│      typeid(expression).name()        typeid(a) == typeid(b)
│
│  ✔ Definition : RTTI (Run-Time Type Information) lets you ask "what is
│                 the REAL type of this object?" while the program runs.
│  ✔ typeid(*ptr) gives the real (dynamic) type — only if the class is
│    polymorphic (has a virtual function)
│  ✔ Compare types with ==. Header: <typeinfo>
│  ⚠ name() text depends on the compiler (g++ prints "3Dog")
│  ✔ dynamic_cast also uses RTTI
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <typeinfo>
using namespace std;

class Animal {
public:
    virtual ~Animal() {}
};

class Dog : public Animal {};
class Cat : public Animal {};

class Plain {};                          // no virtual
class PlainChild : public Plain {};

int main() {

    Dog d;
    Animal* a = &d;

    cout << boolalpha;
    cout << (typeid(*a) == typeid(Dog)) << endl;     // true   (real type)
    cout << (typeid(*a) == typeid(Cat)) << endl;     // false
    cout << (typeid(a) == typeid(Animal*)) << endl;  // true   (pointer type)

    PlainChild pc;
    Plain* p = &pc;
    cout << (typeid(*p) == typeid(Plain)) << endl;   // true  ⚠ no virtual →
                                                     // only static type
    cout << typeid(int).name() << endl;              // i  (g++)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  User-defined conversions — constructor + conversion operator
│  ✔ INTO your class   → a one-argument constructor     (int → Meters)
│  ✔ OUT of your class → a conversion operator          (Meters → double)
│  ✔ Mark them explicit to stop SILENT conversions, then convert with
│    static_cast — clear and safe
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Meters {
    double value;

public:
    explicit Meters(double v) : value(v) {}              // double → Meters
    explicit operator double() const { return value; }   // Meters → double
};

class Feet {
    double value;

public:
    Feet(double v) : value(v) {}                         // NOT explicit
    operator Meters() const { return Meters(value * 0.3048); }
};

void printMeters(Meters m) {
    cout << static_cast<double>(m) << " m" << endl;
}

int main() {

    Meters m(100);
    // Meters bad = 100;                 // ERROR: explicit constructor
    // double d = m;                     // ERROR: explicit operator

    double d = static_cast<double>(m);   // clear, intended
    cout << d << endl;                   // 100

    Feet f(10);
    printMeters(f);                      // 3.048 m   (Feet → Meters)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Which cast when?
│
│   I WANT TO ...                                    USE
│   ───────────────────────────────────────────────  ────────────────────
│   convert numbers (double → int)                   static_cast
│   go child → base                                  nothing (automatic)
│   go base → child, and I'm SURE of the type        static_cast
│   go base → child, and I must CHECK                dynamic_cast
│   remove const for an old API                      const_cast
│   look at raw bytes / addresses                    reinterpret_cast
│   anything else                                    rethink the design
│
│  ✔ Never use C-style (T)x in C++ code — it silently picks the most
│    dangerous cast that compiles
│  ✔ Many dynamic_casts → usually a virtual function would be better
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;     // ✔ virtual instead of casting
    virtual ~Shape() {}
};

class Square : public Shape {
    double s;

public:
    Square(double x) : s(x) {}
    double area() const override { return s * s; }
};

class Circle : public Shape {
    double r;

public:
    Circle(double x) : r(x) {}
    double area() const override { return 3.14 * r * r; }
};

int main() {

    Shape* shapes[] = {new Square(2), new Circle(1)};

    // ✘ bad design: if (dynamic_cast<Square*>(s)) ... else if (Circle) ...
    // ✔ good design: just call the virtual function
    for (Shape* s : shapes) cout << s->area() << endl;
    // 4
    // 3.14

    for (Shape* s : shapes) delete s;

    return 0;
}
