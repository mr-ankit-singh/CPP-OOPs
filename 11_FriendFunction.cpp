
/*==============================================================================
    🧩 Friend Concept
    --------------------------------------------------------------------------
    🔹 By default, PRIVATE and PROTECTED members of a class can ONLY be
       accessed by the class's OWN member functions — NOT by outside
       functions or other classes.
    🔸 The "friend" keyword lets you EXPLICITLY BREAK this rule — for a
       SPECIFIC function, or a SPECIFIC other class — giving it FULL
       access to your class's private/protected members.
    ⚙️ Types:
         1. Friend Function → ONE specific function gets access
         2. Friend Class    → an ENTIRE other class gets access
    ⚙️ Why it exists: Sometimes TWO tightly-related classes/functions
       NEED to work closely together (e.g. operator overloading between
       two different classes) — "friend" allows this, WITHOUT making
       everything public (which would break encapsulation for everyone
       else).

    - A friend function of a class is defined outside that class scope but it has the 
      right to access all the private and protected member of class.
    - Even through the prototypes for friend function appear in the class definition.

==============================================================================*/

#include <iostream>
using namespace std;


/*==============================================================================
    PART 1 : Friend Function
==============================================================================*/

/*------------------------------------------------------------------------
    1.1 Declaration and Syntax
    --------------------------------------------------------------------
    🔹 A friend function is DECLARED inside the class (with the
       "friend" keyword), but DEFINED outside the class — and it is
       NOT a member of that class.
    🔸 Syntax:
           class ClassName {
               friend returnType functionName(parameters);
           };
    ⚙️ Key Points:
         - Friend functions CANNOT be called using the object
           (like "d1.addValue()") — they are called like a NORMAL
           function: "addValue(d1)".
         - You CAN declare a friend function in the public, private,
           OR protected section of a class — it makes NO DIFFERENCE,
           since it isn't a member in the first place (access
           specifiers only control MEMBER access).
         - The "friend" keyword goes ONLY in the class GRANTING
           access — NOT in the function's own definition outside the
           class.
------------------------------------------------------------------------*/
class Distance {
private:
    int meters;
public:
    Distance() {
        meters = 0;
    }
    void displayData() {
        cout << "Meter value: " << meters << endl;
    }

    // Declaration — "friend" keyword used HERE, inside the class
    friend void addValue(Distance& d);
};

// Definition — OUTSIDE the class, NO "friend" keyword needed here,
// and NOT written as "Distance::addValue" (it's NOT a member function)
void addValue(Distance& d) {
    d.meters = d.meters + 5;   // direct access to PRIVATE member
}


/*------------------------------------------------------------------------
    1.2 Access to Private/Protected Members
    --------------------------------------------------------------------
    🔹 A friend function can access BOTH private AND protected members
       DIRECTLY (no getter/setter needed) — exactly like a member
       function would.
------------------------------------------------------------------------*/
class Employee {
private:
    double salary;          // private
protected:
    string designation;      // protected
public:
    Employee(double s, string d) : salary(s), designation(d) {}

    // ONE friend function accessing BOTH a private AND a protected member
    friend void showConfidentialInfo(Employee& e);
};

void showConfidentialInfo(Employee& e) {
    cout << "Designation (protected): " << e.designation << endl;
    cout << "Salary (private): " << e.salary << endl;
}


/*------------------------------------------------------------------------
    1.3 Use Case — Operator Overloading (Very Common Real Use)
    --------------------------------------------------------------------
    🔹 Sometimes, an operator needs to access PRIVATE data of a class,
       but the LEFT-HAND side of the expression isn't naturally an
       object of that class (e.g. "5 + complexNumber" — here "5" is
       on the left, not the class). A MEMBER function operator
       overload can't handle this cleanly — a FRIEND function can.
------------------------------------------------------------------------*/
class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }

    // friend function can access BOTH objects' private data directly,
    // and supports being called as "c1 + c2" via operator overloading
    friend Complex operator+(const Complex& c1, const Complex& c2);
};

Complex operator+(const Complex& c1, const Complex& c2) {
    // Directly accessing PRIVATE "real"/"imag" of BOTH objects —
    // only possible because this function is a friend
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}


/*------------------------------------------------------------------------
    1.4 Use Case — Two-Class Communication
    --------------------------------------------------------------------
    🔹 A SINGLE friend function can be declared a friend of MULTIPLE
       DIFFERENT classes at once — letting it access PRIVATE members
       of BOTH, to compare/combine them (something neither class's
       OWN member functions could do alone, without exposing data
       publicly).
------------------------------------------------------------------------*/
class Fahrenheit;   // forward declaration needed, since Celsius refers to it below

class Celsius {
private:
    double temp;
public:
    Celsius(double t) : temp(t) {}
    // This function needs to be a friend of Fahrenheit TOO (declared below)
    friend bool isSameTemperature(Celsius& c, Fahrenheit& f);
};

class Fahrenheit {
private:
    double temp;
public:
    Fahrenheit(double t) : temp(t) {}
    friend bool isSameTemperature(Celsius& c, Fahrenheit& f);
};

// ONE function, friend of TWO classes — accesses BOTH private members directly
bool isSameTemperature(Celsius& c, Fahrenheit& f) {
    double converted = (c.temp * 9 / 5) + 32;   // Celsius -> Fahrenheit formula
    return converted == f.temp;
}


/*==============================================================================
    PART 2 : Friend Class
==============================================================================*/

/*------------------------------------------------------------------------
    2.1 Relationship Between Classes
    --------------------------------------------------------------------
    🔹 Instead of making just ONE function a friend, you can make an
       ENTIRE OTHER CLASS a friend — meaning EVERY member function of
       that OTHER class can access this class's private/protected
       members.
    🔸 Syntax:
           class A {
               friend class B;   // ALL of B's methods can access A's
                                  // private/protected members
           };
------------------------------------------------------------------------*/
class Engine {
private:
    int horsepower;
public:
    Engine(int hp) : horsepower(hp) {}

    // Declares the ENTIRE "Car" class as a friend
    friend class Car;
};

class Car {
public:
    void showEngineSpecs(Engine& e) {
        // Car can DIRECTLY access Engine's PRIVATE "horsepower",
        // because Car was declared a friend INSIDE Engine
        cout << "Engine horsepower: " << e.horsepower << " HP" << endl;
    }
};


/*------------------------------------------------------------------------
    2.2 Advantages and Risks
    --------------------------------------------------------------------
    ✓ Advantages:
        - Lets CLOSELY-RELATED classes/functions share data WITHOUT
          making everything public (encapsulation stays intact for
          everyone ELSE).
        - Useful for operator overloading, and for classes that
          NATURALLY need to work as a PAIR (e.g. an Iterator class
          needing access to its Container's internals).

    ✗ Risks:
        - BREAKS encapsulation, TO SOME DEGREE — the friend function/
          class can now change PRIVATE data in ways the original
          class didn't necessarily design for.
        - Overusing "friend" is a CODE SMELL — if MANY functions/
          classes need friendship, it often means the class's DESIGN
          (its public interface) should be RECONSIDERED instead.
        - Friendship is NOT INHERITED — if class A is a friend of B,
          and class C inherits from A, C does NOT automatically
          become a friend of B.
        - Friendship is NOT TRANSITIVE — if A is a friend of B, and B
          is a friend of C, A is NOT automatically a friend of C.
        - Friendship is NOT MUTUAL — A being a friend of B does NOT
          mean B is a friend of A (must be declared separately, in
          BOTH directions, if needed).
------------------------------------------------------------------------*/


/*==============================================================================
    PART 3 : Friend Function vs Member Function
    ------------------------------------------------------------------------
    ┌─────────────────────┬───────────────────────┬───────────────────────┐
    │ Aspect                 │ Friend Function          │ Member Function          │
    ├─────────────────────┼───────────────────────┼───────────────────────┤
    │ Belongs to the class?     │ NO                          │ YES                         │
    │ Called using object?        │ NO — called normally,        │ YES — called as               │
    │                            │ e.g. func(obj)                 │ obj.func()                       │
    │ Needs an object to access    │ YES — must be PASSED an           │ NO — has implicit access via     │
    │ class members?                 │ object as a parameter                │ "this" pointer                     │
    │ Can be inherited?                 │ NO                                       │ YES (with normal inheritance rules) │
    │ "this" pointer available?           │ NO                                          │ YES                                   │
    └─────────────────────┴───────────────────────┴───────────────────────┘
==============================================================================*/
class Box {
private:
    double width;
public:
    Box(double w) : width(w) {}

    // MEMBER function — has an IMPLICIT "this", called as: box.getWidthMember()
    double getWidthMember() {
        return width;   // really "this->width"
    }

    // FRIEND function — needs an EXPLICIT object parameter
    friend double getWidthFriend(Box& b);
};

double getWidthFriend(Box& b) {
    return b.width;   // must explicitly say WHICH object's width
}


/*==============================================================================
    MAIN — Testing every example above
==============================================================================*/
int main() {

    cout << "===== 1.1 Declaration and Syntax =====" << endl;
    Distance d1;
    d1.displayData();
    addValue(d1);          // called like a NORMAL function, not d1.addValue()
    d1.displayData();

    cout << "\n===== 1.2 Access to Private/Protected Members =====" << endl;
    Employee emp(75000, "Software Engineer");
    showConfidentialInfo(emp);

    cout << "\n===== 1.3 Operator Overloading via Friend Function =====" << endl;
    Complex c1(2, 3), c2(4, 5);
    Complex c3 = c1 + c2;   // internally calls: operator+(c1, c2)
    cout << "c1 + c2 = ";
    c3.display();

    cout << "\n===== 1.4 Two-Class Communication =====" << endl;
    Celsius boiling(100);
    Fahrenheit boilingF(212);
    cout << "Are 100C and 212F the same temperature? "
         << (isSameTemperature(boiling, boilingF) ? "Yes" : "No") << endl;

    cout << "\n===== 2.1 Friend Class =====" << endl;
    Engine engine(450);
    Car car;
    car.showEngineSpecs(engine);   // Car accesses Engine's PRIVATE member

    cout << "\n===== Part 3: Friend vs Member Function =====" << endl;
    Box box(12.5);
    cout << "Via member function: " << box.getWidthMember() << endl;
    cout << "Via friend function: " << getWidthFriend(box) << endl;

    return 0;
}

/*==============================================================================
    🎯 Frequently Asked Interview Questions
    --------------------------------------------------------------------------
    Q1  Friend function kya hai, aur ye member function se KAISE ALAG hai?
        -> Friend function, class ki PRIVATE/PROTECTED members ko ACCESS kar
           sakta hai, lekin ye class ka MEMBER NAHI hai. Isliye ise object ke
           through call NAHI kiya jaata (obj.func() nahi), balki NORMAL
           function ki tarah call hota hai (func(obj)) -- aur access ke liye,
           object ko EXPLICITLY parameter mein PASS karna padta hai.

    Q2  Kya Friend Function, OOP ke "Encapsulation" principle ko VIOLATE
        karta hai?
        -> THODA sa, HAAN -- kyunki ye, PRIVATE data ko, class ke BAHAR se
           bhi ACCESSIBLE bana deta hai. LEKIN, ye CONTROLLED tareeke se hota
           hai (sirf JIN functions/classes ko EXPLICITLY friend banaya gaya
           hai, unhi ko access milta hai) -- isliye pura encapsulation TOOTA
           nahi, balki SPECIFIC exceptions banaye jaate hain.

    Q3  Kya Friendship, INHERIT hoti hai? Example do.
        -> NAHI. Agar class A, class B ka FRIEND hai, aur class C, class A se
           INHERIT karti hai, to C, AUTOMATICALLY B ki FRIEND NAHI ban jaati.
           Friendship, HAR class ke liye, ALAG SE declare karni padti hai.

    Q4  Kya Friendship, TRANSITIVE hoti hai? Example do.
        -> NAHI. Agar A, B ka friend hai, aur B, C ka friend hai, to A,
           AUTOMATICALLY C ka friend NAHI ban jaata. Har FRIENDSHIP
           relationship, INDEPENDENT hota hai.

    Q5  Operator Overloading mein, MEMBER function ke bajaye, FRIEND function
        KAB use karni padti hai?
        -> Jab operator ke LEFT-HAND SIDE par, HAMARI class ka object NA ho
           (jaise "5 + complexObj", jahan "5" ek plain int hai, Complex object
           nahi) -- tab MEMBER function operator overload, kaam nahi karega,
           kyunki MEMBER function ko HAMESHA LEFT side ka object hi "this"
           milta hai. FRIEND function mein, DONO operands, EXPLICIT
           parameters ki tarah diye jaate hain, isliye ye PROBLEM nahi hoti.

    Q6  Friend Class kya hai, aur ye Friend Function se KAISE ALAG hai?
        -> Friend Function: SIRF EK SPECIFIC function ko access milta hai.
           Friend Class: EK POORI class ko friend banaya jaata hai -- matlab
           US class ke SAARE member functions, friend class ke PRIVATE/
           PROTECTED members access kar sakte hain.

    Q7  Friendship ko MISUSE/OVERUSE karne ke KYA RISKS hain?
        -> Agar BAHUT SAARE functions/classes ko friend banaya jaaye, to
           ENCAPSULATION effectively KHATAM ho jaata hai (koi bhi, class ke
           internal data ko change kar sakta hai) -- code MAINTAIN karna
           MUSHKIL ho jaata hai, aur ye usually ek SIGN hota hai ki class ka
           PUBLIC INTERFACE (design), DOBARA SOCHNA CHAHIYE.

    Q8  Kya "friend" keyword, FUNCTION ki DEFINITION mein (class ke BAHAR)
        bhi likhna padta hai?
        -> NAHI. "friend" keyword, SIRF us class ke ANDAR likha jaata hai,
           JO friendship GRANT kar rahi hai (declaration ke waqt). Function ki
           ACTUAL definition, class ke BAHAR, NORMAL function ki tarah likhi
           jaati hai -- bina "friend" keyword, aur bina "ClassName::" prefix
           ke (kyunki ye member function nahi hai).
==============================================================================*/