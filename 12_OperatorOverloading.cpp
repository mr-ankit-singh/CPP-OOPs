/*==============================================================================
    🧩 Operator Overloading
    --------------------------------------------------------------------------
    🔹 Operator Overloading lets EXISTING C++ operators (+, -, ==, <<, etc.)
       work with USER-DEFINED types (classes) — giving them a MEANING that
       makes sense for THAT class.
    🔸 Without it, combining two objects (like two Vectors, or two Complex
       numbers) would need AWKWARD function calls (like v1.add(v2)) instead
       of NATURAL syntax (v1 + v2).
    ⚙️ Under the hood, "a + b" (for objects) is just SYNTACTIC SUGAR for a
       FUNCTION CALL — "a.operator+(b)" or "operator+(a, b)" — the compiler
       rewrites it automatically.
==============================================================================*/

#include <iostream>
#include <cstring>
using namespace std;


/*==============================================================================
    PART 1 : Need for Operator Overloading
    ------------------------------------------------------------------------
    🔹 WITHOUT overloading — awkward, function-call-heavy syntax:
           Complex c3 = c1.add(c2);
    🔸 WITH overloading — natural, intuitive, math-like syntax:
           Complex c3 = c1 + c2;
    ⚙️ It makes code involving USER-DEFINED types read as NATURALLY as
       code involving BUILT-IN types (int, double, etc.) — improving
       readability WITHOUT changing what's actually happening internally.
==============================================================================*/


/*==============================================================================
    PART 2 : Rules & Limitations
    ------------------------------------------------------------------------
    🔹 1. You CANNOT create NEW operators (e.g. no "**" for power) — only
          EXISTING C++ operators can be overloaded.
    🔸 2. You CANNOT change an operator's PRECEDENCE or ASSOCIATIVITY
          (e.g. "*" will ALWAYS bind tighter than "+", even if overloaded).
    🔹 3. You CANNOT change the NUMBER OF OPERANDS an operator takes
          (a unary operator stays unary, a binary operator stays binary).
    🔸 4. At LEAST ONE operand MUST be a user-defined type (class/struct) —
          you CANNOT overload operators for ONLY built-in types (like
          "int + int") — that would be meaningless/impossible to redefine.
    🔹 5. Some operators CANNOT be overloaded at all:
          "::"  (scope resolution)
          "."   (member access)
          ".*"  (pointer-to-member access)
          "?:"  (ternary/conditional operator)
          "sizeof"
    🔸 6. Certain operators (=, [], (), ->) MUST be overloaded as MEMBER
          functions — they CANNOT be friend/non-member functions.
==============================================================================*/


/*==============================================================================
    PART 3 : Unary Operators (++, --, -, !)
    ------------------------------------------------------------------------
    🔹 Unary operators act on a SINGLE operand (the object itself).
    🔸 IMPORTANT: "++"/"--" have TWO forms — PREFIX (++obj) and POSTFIX
       (obj++) — they are told apart using a DUMMY "int" parameter:
           operator++()     -> PREFIX  (++obj)
           operator++(int)  -> POSTFIX (obj++)  <- the "int" here is a
                                                     dummy, UNUSED marker
==============================================================================*/
class Counter {
private:
    int count;
public:
    Counter(int c = 0) : count(c) {}

    int getCount() { return count; }

    // Unary "-"  -> negates the count (returns a NEW Counter)
    Counter operator-() {
        return Counter(-count);
    }

    // Unary "!"  -> returns TRUE if count is ZERO (like "is this empty?")
    bool operator!() {
        return count == 0;
    }

    // PREFIX "++obj"  -> increments FIRST, then returns the NEW value
    Counter& operator++() {
        count++;
        return *this;
    }

    // POSTFIX "obj++" -> returns the OLD value, THEN increments
    // (the "int" parameter is a dummy, just to distinguish this overload)
    Counter operator++(int) {
        Counter temp = *this;   // save the CURRENT state
        count++;                 // now increment
        return temp;              // return the OLD (saved) state
    }
};


/*==============================================================================
    PART 4 : Binary Operators (+, -, *, /, ==, !=)
    ------------------------------------------------------------------------
    🔹 Binary operators act on TWO operands — usually, "this" object is
       the LEFT operand, and the parameter is the RIGHT operand.
==============================================================================*/
class Complex {
public:
    double real, imag;
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }
    Complex operator-(const Complex& other) {
        return Complex(real - other.real, imag - other.imag);
    }
    Complex operator*(const Complex& other) {
        // (a+bi) * (c+di) = (ac - bd) + (ad + bc)i
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }
    Complex operator/(const Complex& other) {
        double denom = other.real * other.real + other.imag * other.imag;
        return Complex(
            (real * other.real + imag * other.imag) / denom,
            (imag * other.real - real * other.imag) / denom
        );
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};


/*==============================================================================
    PART 5 : Overloading Using — Member Function vs Non-Member (Friend)
    ------------------------------------------------------------------------
    ┌──────────────────┬───────────────────────┬───────────────────────┐
    │ Aspect              │ Member Function            │ Friend/Non-Member Fn      │
    ├──────────────────┼───────────────────────┼───────────────────────┤
    │ Left operand           │ MUST be an object of         │ Can be ANY type (even       │
    │                       │ this class ("this")            │ built-in, like "5 + obj")     │
    │ Access to privates        │ Automatic (via "this")           │ Needs "friend" declaration     │
    │ Parameters needed           │ ONE FEWER (left side is           │ ALL operands passed              │
    │                       │ implicit "this")                    │ explicitly                          │
    │ Required for                │ =, [], (), ->                        │ <<, >> (stream operators)             │
    └──────────────────┴───────────────────────┴───────────────────────┘

    🔹 Below: the SAME "+" operator, shown BOTH ways, for comparison.
==============================================================================*/
class Vector2D {
public:
    double x, y;
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // Version A — MEMBER function: "v1 + v2" becomes "v1.operator+(v2)"
    Vector2D operator+(const Vector2D& other) {
        return Vector2D(x + other.x, y + other.y);
    }

    void display() {
        cout << "(" << x << ", " << y << ")" << endl;
    }

    // Needed so the FRIEND version below can access private-like data
    // (here x, y are public for simplicity, but friend would be REQUIRED
    // if they were private)
    friend Vector2D operator-(const Vector2D& a, const Vector2D& b);
};

// Version B — FRIEND function: "v1 - v2" becomes "operator-(v1, v2)"
// Both operands are EXPLICIT parameters — NEITHER is an implicit "this"
Vector2D operator-(const Vector2D& a, const Vector2D& b) {
    return Vector2D(a.x - b.x, a.y - b.y);
}


/*==============================================================================
    PART 6 : Assignment Operator Overloading (=)
    ------------------------------------------------------------------------
    🔹 MUST be a MEMBER function (cannot be a friend/non-member function).
    🔸 CRITICAL use case: classes that manage DYNAMIC MEMORY (like a
       custom string class holding "char*"). WITHOUT a custom "operator=",
       the COMPILER'S DEFAULT version does a "SHALLOW COPY" — it just
       copies the POINTER, not the actual data — causing BOTH objects to
       point to the SAME memory (a "double free" crash waiting to happen
       when both destructors run).
==============================================================================*/
class MyString {
private:
    char* data;
public:
    MyString(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // Custom assignment operator — performs a "DEEP COPY"
    MyString& operator=(const MyString& other) {
        if (this == &other) return *this;   // guard against "s1 = s1"

        delete[] data;                       // free OLD memory first
        data = new char[strlen(other.data) + 1];   // allocate NEW memory
        strcpy(data, other.data);                   // COPY the actual characters

        return *this;   // enables chaining: a = b = c
    }

    void display() {
        cout << data << endl;
    }

    ~MyString() {
        delete[] data;
    }
};


/*==============================================================================
    PART 7 : Stream Operator Overloading (<<, >>)
    ------------------------------------------------------------------------
    🔹 MUST be overloaded as FRIEND/NON-MEMBER functions — because the
       LEFT operand is "cout"/"cin" (an ostream/istream object), NOT an
       object of OUR class — so a MEMBER function (which needs "this" to
       be the left operand) simply cannot work here.
    🔸 "<<" (insertion, for printing)  -> takes "ostream&", returns "ostream&"
       ">>" (extraction, for input)     -> takes "istream&", returns "istream&"
==============================================================================*/
class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // friend needed to access private-like data AND to allow
    // "cout << point" (cout must be the LEFT operand)
    friend ostream& operator<<(ostream& out, const Point& p);
    friend istream& operator>>(istream& in, Point& p);
};

ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;   // returning ostream& allows CHAINING: cout << p1 << p2
}

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}


/*==============================================================================
    PART 8 : Relational Operator Overloading (==, !=, <, >, <=, >=)
    ------------------------------------------------------------------------
    🔹 Used to define what "EQUALITY" or "ORDERING" means for a class —
       the compiler has NO idea how to compare two custom objects
       otherwise.
    🔸 Returns a "bool" — TRUE or FALSE.
==============================================================================*/
class Fraction {
private:
    int numerator, denominator;
public:
    Fraction(int n, int d) : numerator(n), denominator(d) {}

    double value() const {
        return (double)numerator / denominator;
    }

    bool operator==(const Fraction& other) {
        return value() == other.value();
    }
    bool operator!=(const Fraction& other) {
        return !(*this == other);   // reusing "==" avoids duplicating logic
    }
    bool operator<(const Fraction& other) {
        return value() < other.value();
    }
    bool operator>(const Fraction& other) {
        return value() > other.value();
    }
};


/*==============================================================================
    PART 9 : Function Call Operator Overloading — operator()
    ------------------------------------------------------------------------
    🔹 Overloading "()" lets an OBJECT be "called" like a FUNCTION — this
       creates what's called a "FUNCTOR" (function object).
    🔸 MUST be a MEMBER function. Can take ANY number of parameters
       (unlike other operators, which have a fixed operand count).
    ⚙️ Real Usage: Functors are heavily used with STL algorithms (like
       sort(), for_each()) as CUSTOM, STATEFUL "comparison" or
       "transformation" logic.
==============================================================================*/
class Multiplier {
private:
    int factor;
public:
    Multiplier(int f) : factor(f) {}

    // Now, "obj(5)" works just like calling a function
    int operator()(int value) {
        return value * factor;
    }
};


/*==============================================================================
    PART 10 : Rules for Return Type and Arguments (Summary)
    ------------------------------------------------------------------------
    🔹 Arithmetic operators (+, -, *, /) -> usually RETURN a NEW object
       (BY VALUE) — they should NOT modify either original operand.
    🔸 Compound assignment (+=, -=, etc.) -> should MODIFY "*this" AND
       return "*this" BY REFERENCE (for chaining: a += b += c).
    🔹 Relational operators (==, <, etc.) -> should RETURN "bool".
    🔸 Assignment (=) -> should return "*this" BY REFERENCE (for
       chaining: a = b = c), and MUST be a member function.
    🔹 Stream operators (<<, >>) -> should return the stream BY
       REFERENCE ("ostream&"/"istream&"), and MUST be non-member
       (friend) functions.
    🔸 Prefer "const" reference parameters (const T&) for operands that
       are only READ, not modified — avoids UNNECESSARY COPYING.
==============================================================================*/


/*==============================================================================
    MAIN — Testing every example above
==============================================================================*/
int main() {

    cout << "===== Part 3: Unary Operators =====" << endl;
    Counter c1(5);
    cout << "-c1 = " << (-c1).getCount() << endl;
    cout << "!c1 (is zero?) = " << (!c1 ? "true" : "false") << endl;

    Counter c2(10);
    Counter preResult = ++c2;               // prefix: increments FIRST
    cout << "After ++c2, c2 = " << c2.getCount()
         << ", returned = " << preResult.getCount() << endl;

    Counter c3(10);
    Counter postResult = c3++;              // postfix: returns OLD value
    cout << "After c3++, c3 = " << c3.getCount()
         << ", returned = " << postResult.getCount() << endl;

    cout << "\n===== Part 4: Binary Operators =====" << endl;
    Complex a(2, 3), b(4, 5);
    cout << "a + b = "; (a + b).display();
    cout << "a - b = "; (a - b).display();
    cout << "a * b = "; (a * b).display();
    cout << "a / b = "; (a / b).display();

    cout << "\n===== Part 5: Member vs Friend Function =====" << endl;
    Vector2D v1(1, 2), v2(3, 4);
    cout << "v1 + v2 (member function)  = "; (v1 + v2).display();
    cout << "v1 - v2 (friend function)  = "; (v1 - v2).display();

    cout << "\n===== Part 6: Assignment Operator (Deep Copy) =====" << endl;
    MyString s1("Hello");
    MyString s2;
    s2 = s1;              // uses our custom operator= (deep copy)
    cout << "s1 = "; s1.display();
    cout << "s2 = "; s2.display();
    // s1 and s2 now have SEPARATE memory — safe, no double-free risk

    cout << "\n===== Part 7: Stream Operator Overloading =====" << endl;
    Point p1(3.5, 7.2);
    cout << "p1 = " << p1 << endl;   // uses our operator<<

    cout << "\n===== Part 8: Relational Operator Overloading =====" << endl;
    Fraction f1(1, 2), f2(2, 4), f3(3, 4);
    cout << "1/2 == 2/4 ? " << (f1 == f2 ? "true" : "false") << endl;
    cout << "1/2 < 3/4 ?  " << (f1 < f3 ? "true" : "false") << endl;

    cout << "\n===== Part 9: Function Call Operator (Functor) =====" << endl;
    Multiplier triple(3);
    cout << "triple(7) = " << triple(7) << endl;   // looks like a function call!

    return 0;
}

/*==============================================================================
    🎯 Frequently Asked Interview Questions
    --------------------------------------------------------------------------
    Q1  Operator Overloading kya hai, aur ye ZAROORI kyun hai?
        -> Existing operators (+, -, ==, etc.) ko, USER-DEFINED classes ke
           saath kaam karne LAYAK banana. Isse OBJECTS ke saath, NATURAL,
           MATH-JAISI syntax use ho paati hai (jaise "c1 + c2"), instead of
           AWKWARD function calls (jaise "c1.add(c2)").

    Q2  Kaunse operators, C++ mein OVERLOAD NAHI kiye ja sakte?
        -> "::" (scope resolution), "." (member access), ".*"
           (pointer-to-member), "?:" (ternary), aur "sizeof" -- inhe
           OVERLOAD karna ALLOWED nahi hai.

    Q3  Prefix (++obj) aur Postfix (obj++) increment operators ko, COMPILER
        KAISE ALAG PEHCHANTA hai, jab DONO ka naam "operator++" hi hai?
        -> POSTFIX version, EK EXTRA, DUMMY "int" parameter leta hai
           (operator++(int)) -- ye "int", ACTUALLY kabhi use NAHI hota,
           SIRF COMPILER ko DONO OVERLOADS mein DIFFERENTIATE karne ke liye
           hota hai.

    Q4  Assignment Operator (=) ko, FRIEND function ki tarah KYUN NAHI
        overload kiya ja sakta?
        -> C++ STANDARD ye REQUIRE karta hai ki "=", "[]", "()", aur "->"
           jaise operators, HAMESHA MEMBER FUNCTIONS hi hon -- isse ENSURE
           hota hai ki HAR class, apna OWN, DEFAULT assignment behavior
           rakh sake, aur LEFT operand, HAMESHA "this" class ka object hi
           ho.

    Q5  "Shallow Copy" aur "Deep Copy" mein kya farak hai, aur Assignment
        Operator Overloading, YE PROBLEM KAISE SOLVE karta hai?
        -> Shallow Copy: Compiler ka DEFAULT "=", sirf POINTER VALUE copy
           karta hai -- DONO objects, SAME memory ko POINT karte hain
           (DANGEROUS, kyunki DONO ke destructor, SAME memory ko "delete"
           karne ki koshish karenge -- crash). Deep Copy: NAYI memory
           ALLOCATE karke, ACTUAL DATA copy kiya jaata hai -- DONO objects,
           SEPARATE, INDEPENDENT memory rakhte hain. Custom "operator="
           likhkar, hum DEEP COPY implement karte hain.

    Q6  Stream Operators (<<, >>) ko, MEMBER function ki tarah OVERLOAD
        KYUN NAHI kiya ja sakta?
        -> Kyunki "cout << obj" mein, LEFT operand "cout" hai (jo
           "ostream" TYPE ka object hai, HAMARI class ka NAHI). MEMBER
           function mein, "this" (LEFT operand) HAMESHA HAMARI OWN CLASS
           ka object HONA CHAHIYE -- isliye "<<" aur ">>" ko, MAJBOORAN,
           FRIEND/NON-MEMBER function ki tarah likhna padta hai.

    Q7  operator() kya hota hai, aur ise use karke kya BANTA hai?
        -> "operator()" ko overload karke, EK OBJECT ko, FUNCTION ki
           tarah "CALL" kiya ja sakta hai (jaise "obj(5)"). Aisi class,
           jiska ye operator overload hota hai, use "FUNCTOR" (Function
           Object) kehte hain -- STL algorithms (jaise sort, for_each)
           mein, CUSTOM logic pass karne ke liye BAHUT use hota hai.

    Q8  Binary operator (jaise "+") ko, MEMBER function VS FRIEND function
        ki tarah overload karne mein, KYA FARAK padta hai?
        -> Member function mein, LEFT operand HAMESHA "this" class ka
           object HONA CHAHIYE (isliye "5 + obj" jaisa expression, agar
           "5" ek built-in int hai, MEMBER function se HANDLE nahi ho
           sakta). Friend function mein, DONO operands EXPLICIT parameters
           hote hain -- isliye YE ZYADA FLEXIBLE hai, aur "5 + obj" jaisi
           cases bhi handle kar sakta hai (agar CONSTRUCTOR, int se Object
           BANA sake).
==============================================================================*/