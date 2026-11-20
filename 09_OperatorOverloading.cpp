/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                           OPERATOR OVERLOADING                            ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is Operator Overloading?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ It lets EXISTING C++ operators (+, -, ==, <<, [] ...) work with your
 *    own classes — with a meaning that makes sense for THAT class
 *  ✔ Without it, joining two objects needs awkward calls:
 *        Complex c3 = c1.add(c2);           // without
 *        Complex c3 = c1 + c2;              // with — reads like maths
 *  ✔ Under the hood "a + b" is just a FUNCTION CALL that the compiler
 *    writes for you:
 *        a + b   →   a.operator+(b)         (member function)
 *        a + b   →   operator+(a, b)        (non-member / friend)
 *
 *  Syntax
 *  ────────────────────────────────────────────────────────────────────────────
 *        ReturnType operator<symbol>(parameters) { ... }
 *
 *  Rules & limitations  ⭐
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ 1. You can't make NEW operators (no ** for power)
 *  ✔ 2. You can't change PRECEDENCE or ASSOCIATIVITY (* still beats +)
 *  ✔ 3. You can't change the NUMBER of operands (unary stays unary)
 *  ✔ 4. At least ONE operand must be your own type — you can't redefine
 *       int + int
 *  ✔ 5. These can NOT be overloaded:
 *          ::   .   .*   ?:   sizeof   typeid   alignof
 *  ✔ 6. These MUST be member functions:   =   [ ]   ( )   ->
 *  ✔ 7. Keep the natural meaning — don't make + subtract
 *
 *  Which operators can be overloaded?
 *  ────────────────────────────────────────────────────────────────────────────
 *   Arithmetic     + - * / %          Compound    += -= *= /= %=
 *   Unary          - + ! ~ ++ --      Relational  == != < > <= >= <=>
 *   Logical        && ||              Bitwise     & | ^ << >>
 *   Special        = [] () -> * ,     Memory      new delete new[] delete[]
 *   Conversion     operator int(), operator bool() ...
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   UNARY
 *   ─────
 *   - and !                       ─► -c,  !c
 *   Prefix vs postfix ++ / --     ─► ++c  vs  c++  (dummy int)
 *
 *   BINARY
 *   ──────
 *   + - * /                       ─► Complex maths
 *   Member vs friend              ─► same operator, two ways
 *   Compound assignment += -=     ─► change *this, return *this
 *   Assignment =                  ─► deep copy + self-assignment check
 *   Copy-and-swap idiom           ─► the safe, short way to write =
 *
 *   COMPARISON
 *   ──────────
 *   Relational == != < >          ─► Fraction
 *   Spaceship <=> (C++20)         ─► all 6 comparisons from one
 *
 *   SPECIAL
 *   ───────
 *   Stream << and >>              ─► cout << p,  cin >> p
 *   Subscript [ ]                 ─► safe array: arr[i]
 *   Function call ( ) → functor   ─► obj(5)
 *   Arrow -> and *                ─► smart-pointer style
 *   Conversion operator           ─► operator double(), explicit bool
 *   new / delete                  ─► custom memory for a class
 *
 *   SUMMARY
 *   ───────
 *   Rules for return type and arguments
 *   Interview questions
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Unary operators: - and ! ->
│      ClassName operator-() const;        // -obj
│      bool operator!() const;             // !obj
│
│  ✔ Definition : A unary operator works on ONE operand — the object
│                 itself. As a member function it takes NO parameter.
│  ✔ -obj should return a NEW object (don't change the original)
│  ✔ !obj usually means "is it empty / zero / invalid?"
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Counter {
private:
    int count;

public:
    Counter(int c = 0) : count(c) {}
    int getCount() const { return count; }

    Counter operator-() const { return Counter(-count); }    // -obj
    bool operator!() const { return count == 0; }            // !obj
};

int main() {

    Counter c1(5), zero;

    cout << (-c1).getCount() << endl;        // -5
    cout << c1.getCount() << endl;           // 5   (original unchanged)

    cout << boolalpha;
    cout << !c1 << endl;                     // false
    cout << !zero << endl;                   // true

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Prefix vs postfix ++ / -- ->
│      ClassName& operator++();        // PREFIX  ++obj
│      ClassName  operator++(int);     // POSTFIX obj++  (int = dummy)
│
│  ✔ Definition : Both are named operator++. The compiler tells them
│                 apart by a DUMMY int parameter that is never used.
│  ✔ Prefix  ++obj : increase FIRST, return the NEW object by REFERENCE
│  ✔ Postfix obj++ : save a copy, increase, return the OLD copy by VALUE
│  ✔ Prefix is a little faster (no copy) → prefer ++it in loops
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Counter {
private:
    int count;

public:
    Counter(int c = 0) : count(c) {}
    int getCount() const { return count; }

    Counter& operator++() {                  // prefix
        count++;
        return *this;
    }

    Counter operator++(int) {                // postfix
        Counter temp = *this;                // save the current state
        count++;                             // then increase
        return temp;                         // give back the OLD state
    }

    Counter& operator--() { count--; return *this; }
    Counter operator--(int) { Counter t = *this; count--; return t; }
};

int main() {

    Counter c2(10);
    Counter pre = ++c2;
    cout << c2.getCount() << " " << pre.getCount() << endl;    // 11 11

    Counter c3(10);
    Counter post = c3++;
    cout << c3.getCount() << " " << post.getCount() << endl;   // 11 10

    Counter c4(5);
    c4--;
    --c4;
    cout << c4.getCount() << endl;                             // 3

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Binary operators: + - * / ->
│      ClassName operator+(const ClassName& other) const;
│
│  ✔ Definition : A binary operator works on TWO operands. As a member,
│                 "this" is the LEFT operand and the parameter is the
│                 RIGHT operand.
│  ✔ Return a NEW object by value; mark it const (it changes nothing)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex& o) const {
        return Complex(real + o.real, imag + o.imag);
    }

    Complex operator-(const Complex& o) const {
        return Complex(real - o.real, imag - o.imag);
    }

    Complex operator*(const Complex& o) const {
        // (a+bi)(c+di) = (ac - bd) + (ad + bc)i
        return Complex(real * o.real - imag * o.imag,
                       real * o.imag + imag * o.real);
    }

    Complex operator/(const Complex& o) const {
        double d = o.real * o.real + o.imag * o.imag;
        return Complex((real * o.real + imag * o.imag) / d,
                       (imag * o.real - real * o.imag) / d);
    }

    void display() const { cout << real << " + " << imag << "i" << endl; }
};

int main() {

    Complex a(2, 3), b(4, 5);

    (a + b).display();                       // 6 + 8i
    (a - b).display();                       // -2 + -2i
    (a * b).display();                       // -7 + 22i
    (a / b).display();                       // 0.560976 + 0.0487805i

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Member function vs non-member (friend) function
│
│   POINT               MEMBER FUNCTION           FRIEND / NON-MEMBER
│   ──────────────────  ────────────────────────  ────────────────────────
│   Left operand        MUST be this class        ANY type (5 + obj)
│   Private access      automatic (this)          needs "friend"
│   Parameters          one FEWER (left = this)   ALL operands passed
│   Must be used for    =  [ ]  ( )  ->           <<  >>  (left is stream)
│
│  ✔ Below: the same kind of operator written both ways
│  ✔ Common style: += as member, + as non-member built from +=
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Vector2D {
    double x, y;

public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // A — member:  v1 + v2  →  v1.operator+(v2)
    Vector2D operator+(const Vector2D& o) const {
        return Vector2D(x + o.x, y + o.y);
    }

    // B — friend:  v1 - v2  →  operator-(v1, v2)
    friend Vector2D operator-(const Vector2D& a, const Vector2D& b);

    // friend lets the LEFT side be a number:  2 * v
    friend Vector2D operator*(double k, const Vector2D& v);

    void display() const { cout << "(" << x << ", " << y << ")" << endl; }
};

Vector2D operator-(const Vector2D& a, const Vector2D& b) {
    return Vector2D(a.x - b.x, a.y - b.y);
}

Vector2D operator*(double k, const Vector2D& v) {
    return Vector2D(k * v.x, k * v.y);
}

int main() {

    Vector2D v1(1, 2), v2(3, 4);

    (v1 + v2).display();                     // (4, 6)    member
    (v1 - v2).display();                     // (-2, -2)  friend
    (2 * v2).display();                      // (6, 8)    number on left

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Compound assignment: += -= *= ->
│      ClassName& operator+=(const ClassName& other);
│
│  ✔ Definition : Changes the LEFT object itself and returns *this by
│                 reference (so  a += b += c  works).
│  ✔ Smart trick: write += once, then make + from it → no repeated logic
│        T operator+(T a, const T& b) { a += b; return a; }
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Money {
    long long paise;

public:
    Money(long long rupees = 0) : paise(rupees * 100) {}

    Money& operator+=(const Money& o) {      // changes this object
        paise += o.paise;
        return *this;
    }

    Money& operator-=(const Money& o) {
        paise -= o.paise;
        return *this;
    }

    double rupees() const { return paise / 100.0; }
};

Money operator+(Money a, const Money& b) {   // + built from +=
    a += b;
    return a;
}

int main() {

    Money wallet(500);
    wallet += Money(250);
    wallet -= Money(100);
    cout << wallet.rupees() << endl;         // 650

    Money total = Money(10) + Money(20);
    cout << total.rupees() << endl;          // 30

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Assignment operator = ->
│      ClassName& operator=(const ClassName& other) {
│          if (this == &other) return *this;     // 1. self check
│          delete[] data;                        // 2. free old
│          data = new ...; copy;                 // 3. deep copy
│          return *this;                         // 4. allow a = b = c
│      }
│
│  ✔ Definition : Runs for  a = b;  when a ALREADY exists. MUST be a
│                 member function.
│  ✔ Needed when the class owns DYNAMIC memory (char*, int*). The
│    compiler's default = does a SHALLOW copy (only the pointer) → both
│    objects share memory → both destructors delete it → crash
│  ⚠ Without the self check,  s = s;  deletes its own data first
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* data;

public:
    MyString(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    MyString(const MyString& o) {            // copy ctor (Rule of 3)
        data = new char[strlen(o.data) + 1];
        strcpy(data, o.data);
    }

    MyString& operator=(const MyString& other) {
        if (this == &other) return *this;            // s1 = s1 guard
        delete[] data;                               // free old memory
        data = new char[strlen(other.data) + 1];     // new memory
        strcpy(data, other.data);                    // copy characters
        return *this;
    }

    void display() const { cout << data << endl; }
    ~MyString() { delete[] data; }
};

int main() {

    MyString s1("Hello"), s2, s3;

    s2 = s1;                                 // deep copy
    s3 = s2 = s1;                            // chaining works
    s1 = s1;                                 // self-assignment: safe

    s1.display();                            // Hello
    s2.display();                            // Hello
    s3.display();                            // Hello

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Copy-and-swap idiom — the safe, short way to write operator=
│  ✔ Take the parameter BY VALUE (that makes the copy for you), then
│    SWAP its insides with this object. The old data leaves with the
│    temporary and is freed by its destructor.
│  ✔ Benefits:
│        • self-assignment is safe automatically
│        • if the copy throws, *this is untouched (strong guarantee)
│        • one operator= handles both copy AND move
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstring>
#include <utility>
using namespace std;

class Text {
    char* data;

public:
    Text(const char* s = "") {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    Text(const Text& o) {
        data = new char[strlen(o.data) + 1];
        strcpy(data, o.data);
    }

    Text(Text&& o) noexcept : data(o.data) { o.data = nullptr; }

    friend void swap(Text& a, Text& b) noexcept {
        std::swap(a.data, b.data);           // swap just the pointers
    }

    Text& operator=(Text other) {            // copy (or move) happens here
        swap(*this, other);                  // take its data
        return *this;                        // old data dies with other
    }

    ~Text() { delete[] data; }

    void show() const { cout << data << endl; }
};

int main() {

    Text a("Monday"), b("Friday");

    a = b;                                   // copy-assign
    a.show();                                // Friday

    a = Text("Sunday");                      // move-assign, same operator
    a.show();                                // Sunday

    a = a;                                   // self: safe
    a.show();                                // Sunday

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Relational operators: == != < > <= >= ->
│      bool operator==(const ClassName& other) const;
│
│  ✔ Definition : Tell the compiler what "equal" or "smaller" means for
│                 your class. They return bool.
│  ✔ Write == and <, then build the others from them — no repeated logic
│  ✔ operator< lets your objects work with sort(), set, map
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Fraction {
private:
    int numerator, denominator;

public:
    Fraction(int n, int d) : numerator(n), denominator(d) {}

    double value() const { return (double)numerator / denominator; }

    bool operator==(const Fraction& o) const {
        return numerator * o.denominator == o.numerator * denominator;
    }
    bool operator!=(const Fraction& o) const { return !(*this == o); }
    bool operator<(const Fraction& o) const { return value() < o.value(); }
    bool operator>(const Fraction& o) const { return o < *this; }

    void show() const { cout << numerator << "/" << denominator << " "; }
};

int main() {

    Fraction f1(1, 2), f2(2, 4), f3(3, 4);

    cout << boolalpha;
    cout << (f1 == f2) << endl;              // true
    cout << (f1 != f3) << endl;              // true
    cout << (f1 < f3) << endl;               // true
    cout << (f3 > f1) << endl;               // true

    vector<Fraction> v = {f3, f1, Fraction(1, 3)};
    sort(v.begin(), v.end());                // uses operator<
    for (auto& f : v) f.show();              // 1/3 1/2 3/4
    cout << endl;

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Spaceship operator <=> (C++20) ->
│      auto operator<=>(const ClassName&) const = default;
│      bool operator==(const ClassName&) const = default;
│
│  ✔ Definition : One three-way comparison gives you <, >, <=, >= for
│                 free. "= default" compares the members in order of
│                 declaration (first member, then the next ...).
│  ✔ = default == gives == and != too
│  ✔ Header: <compare>
│  ✔ Write your own <=> when the order should be different
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <compare>
#include <string>
using namespace std;

struct Version {
    int major, minor, patch;

    auto operator<=>(const Version&) const = default;    // < > <= >=
    bool operator==(const Version&) const = default;     // == !=
};

struct Student {
    string name;
    int marks;

    auto operator<=>(const Student& o) const {           // custom: by marks
        return marks <=> o.marks;
    }
};

int main() {

    Version a{1, 4, 2}, b{1, 10, 0};

    cout << boolalpha;
    cout << (a < b) << endl;                 // true   (4 < 10)
    cout << (a >= b) << endl;                // false
    cout << (a == Version{1, 4, 2}) << endl; // true
    cout << (a != b) << endl;                // true

    Student s1{"Amit", 80}, s2{"Neha", 92};
    cout << (s1 < s2) << endl;               // true

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Stream operators << and >> ->
│      friend ostream& operator<<(ostream& out, const ClassName& obj);
│      friend istream& operator>>(istream& in, ClassName& obj);
│
│  ✔ Definition : Print with  cout << obj  and read with  cin >> obj.
│  ✔ MUST be non-member (friend) — the LEFT operand is cout / cin, not
│    your class
│  ✔ Return the stream by reference → chaining:  cout << p1 << p2
│  ✔ >> takes the object by NON-const reference (it fills it)
│  ✔ Below, istringstream stands in for cin so it runs without typing
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <sstream>
using namespace std;

class Point {
    double x, y;

public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    friend ostream& operator<<(ostream& out, const Point& p);
    friend istream& operator>>(istream& in, Point& p);
};

ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

int main() {

    Point p1(3.5, 7.2), p2(1, 1);
    cout << p1 << " and " << p2 << endl;     // (3.5, 7.2) and (1, 1)

    istringstream input("10 20");            // pretend the user typed this
    Point p3;
    input >> p3;                             // same as  cin >> p3;
    cout << p3 << endl;                      // (10, 20)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Subscript operator [ ] ->
│      T& operator[](size_t i);                // read AND write
│      const T& operator[](size_t i) const;    // read only (const objects)
│
│  ✔ Definition : Lets your object be used like an array:  obj[i]
│  ✔ MUST be a member function
│  ✔ Return a REFERENCE so  obj[i] = value;  can change the element
│  ✔ Write both versions so const objects can read too
│  ✔ You can add a bounds check (normal arrays don't have one)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class SafeArray {
    int data[5] = {0};

public:
    int& operator[](int i) {
        if (i < 0 || i >= 5) throw out_of_range("bad index");
        return data[i];
    }

    const int& operator[](int i) const {
        if (i < 0 || i >= 5) throw out_of_range("bad index");
        return data[i];
    }
};

int main() {

    SafeArray marks;
    marks[0] = 90;                           // write (returns int&)
    marks[1] = 75;
    cout << marks[0] + marks[1] << endl;     // 165

    const SafeArray& view = marks;
    cout << view[1] << endl;                 // 75   (const version)

    try {
        marks[10] = 1;
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;   // Error: bad index
    }

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Function call operator ( ) → functor ->
│      ReturnType operator()(parameters);
│
│  ✔ Definition : Overloading ( ) lets an OBJECT be called like a
│                 FUNCTION:  obj(5). Such an object is a FUNCTOR
│                 (function object).
│  ✔ MUST be a member. Can take ANY number of parameters.
│  ✔ Unlike a plain function, a functor can REMEMBER data (its members)
│  ✔ Used with STL algorithms: sort, count_if, transform ...
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Multiplier {
private:
    int factor;

public:
    Multiplier(int f) : factor(f) {}
    int operator()(int value) const { return value * factor; }
};

class AboveLimit {
    int limit;

public:
    AboveLimit(int l) : limit(l) {}
    bool operator()(int x) const { return x > limit; }
};

int main() {

    Multiplier triple(3);
    cout << triple(7) << endl;               // 21   (looks like a function)

    vector<int> prices = {120, 450, 80, 999};
    int costly = count_if(prices.begin(), prices.end(), AboveLimit(400));
    cout << costly << endl;                  // 2

    transform(prices.begin(), prices.end(), prices.begin(), Multiplier(2));
    cout << prices[0] << endl;               // 240

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Arrow -> and dereference * ->
│      T* operator->();          T& operator*();
│
│  ✔ Definition : Make your object act like a POINTER. This is exactly
│                 how smart pointers (unique_ptr, shared_ptr) and
│                 iterators work.
│  ✔ operator-> returns a raw pointer; C++ then applies -> again on it
│  ✔ MUST be a member function
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

struct User {
    string name;
    void greet() const { cout << "Hi, " << name << endl; }
};

class SmartPtr {                             // tiny unique_ptr
    User* ptr;

public:
    SmartPtr(User* p) : ptr(p) {}
    ~SmartPtr() { delete ptr; cout << "memory freed" << endl; }

    SmartPtr(const SmartPtr&) = delete;
    SmartPtr& operator=(const SmartPtr&) = delete;

    User* operator->() const { return ptr; }
    User& operator*() const { return *ptr; }
};

int main() {

    SmartPtr p(new User{"Amit"});
    p->greet();                              // Hi, Amit
    (*p).name = "Amit Kumar";
    cout << p->name << endl;                 // Amit Kumar

    return 0;                                // memory freed
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Conversion operator ->
│      operator double() const;              // obj → double silently
│      explicit operator bool() const;       // only in if / while / !
│
│  ✔ Definition : Converts YOUR object INTO another type. No return type
│                 is written — the type name IS the return type.
│  ✔ explicit stops surprise conversions; explicit operator bool still
│    works in  if (obj)  — that's how  if (file)  and  if (ptr)  work
│  ⚠ Too many silent conversions cause confusing bugs → prefer explicit
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Temperature {
    double celsius;

public:
    Temperature(double c) : celsius(c) {}
    operator double() const { return celsius; }      // → double
};

class Connection {
    bool connected;

public:
    Connection(bool c) : connected(c) {}
    explicit operator bool() const { return connected; }
};

int main() {

    Temperature t(36.6);
    double d = t;                            // silent conversion
    cout << d + 1 << endl;                   // 37.6

    Connection good(true), bad(false);
    if (good) cout << "online" << endl;      // online
    if (!bad) cout << "offline" << endl;     // offline
    // int x = good;                         // ERROR: explicit

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  new / delete overloading ->
│      static void* operator new(size_t size);
│      static void operator delete(void* p);
│
│  ✔ Definition : Give a class its OWN way to get and free memory. Every
│                 "new ClassName" then calls your function.
│  ✔ Used for: memory pools (games, servers), counting / tracking
│    allocations, debugging leaks
│  ✔ They are static automatically (no object exists yet during new)
│  ✔ Use ::operator new / ::operator delete to call the normal ones
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstdlib>
using namespace std;

class Bullet {
    int x = 0, y = 0;

public:
    static int alive;

    static void* operator new(size_t size) {
        alive++;
        cout << "new Bullet (" << size << " bytes)" << endl;
        return ::operator new(size);
    }

    static void operator delete(void* p) {
        alive--;
        cout << "delete Bullet" << endl;
        ::operator delete(p);
    }
};

int Bullet::alive = 0;

int main() {

    Bullet* b1 = new Bullet;                 // new Bullet (8 bytes)
    Bullet* b2 = new Bullet;                 // new Bullet (8 bytes)
    cout << Bullet::alive << endl;           // 2

    delete b1;                               // delete Bullet
    cout << Bullet::alive << endl;           // 1
    delete b2;                               // delete Bullet

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Rules for return type and arguments (summary)
│
│   OPERATOR              RETURN                MEMBER?     NOTE
│   ────────────────────  ────────────────────  ──────────  ────────────────
│   + - * /               new object (value)    either      const operands
│   += -= *= /=           *this (reference)     member      changes left
│   == != < > <=>         bool / ordering       either      mark const
│   =                     *this (reference)     MUST        self check
│   ++x / --x             *this (reference)     usually     prefix
│   x++ / x--             old copy (value)      usually     dummy int
│   << >>                 stream (reference)    MUST NOT    friend
│   [ ]                   element reference     MUST        + const version
│   ( )                   anything              MUST        any parameters
│   ->                    raw pointer           MUST
│
│  ✔ Take operands you only READ as  const T&  (no copy)
│  ✔ Mark operators that don't change *this as const
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Score {
    int value;

public:
    Score(int v = 0) : value(v) {}

    Score operator+(const Score& o) const { return Score(value + o.value); }
    Score& operator+=(const Score& o) { value += o.value; return *this; }
    bool operator==(const Score& o) const { return value == o.value; }
    Score& operator++() { ++value; return *this; }

    friend ostream& operator<<(ostream& out, const Score& s) {
        return out << s.value;
    }
};

int main() {

    Score a(10), b(5);
    Score c = a + b;
    c += Score(1);
    ++c;

    cout << c << endl;                       // 17
    cout << boolalpha << (c == Score(17)) << endl;     // true

    return 0;
}


/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   🎯 INTERVIEW QUESTIONS                                                  ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Q1  What is operator overloading and why is it needed?
 *      → Making existing operators (+, -, == ...) work with your own
 *        classes. It gives natural, maths-like syntax (c1 + c2) instead
 *        of awkward calls (c1.add(c2)).
 *
 *  Q2  Which operators can NOT be overloaded?
 *      → ::  .  .*  ?:  sizeof  typeid  alignof
 *
 *  Q3  How does the compiler tell prefix ++obj from postfix obj++?
 *      → Postfix takes an extra DUMMY int parameter: operator++(int).
 *        The int is never used; it only separates the two overloads.
 *
 *  Q4  Why can't operator= be a friend function?
 *      → The standard requires =, [ ], ( ) and -> to be members. This
 *        makes sure the left operand is always an object of the class,
 *        and every class has its own assignment.
 *
 *  Q5  Shallow vs deep copy — how does operator= fix the problem?
 *      → The default = copies only the pointer (shallow) → both objects
 *        share memory → double delete crash. A custom = allocates new
 *        memory and copies the real data (deep copy).
 *
 *  Q6  Why can't << and >> be member functions?
 *      → In  cout << obj  the left operand is cout (an ostream), not
 *        your class. A member always has your class on the left, so <<
 *        and >> must be non-member (friend) functions.
 *
 *  Q7  What is operator() and what does it create?
 *      → It lets an object be called like a function: obj(5). Such a
 *        class is a FUNCTOR. Used a lot with STL algorithms.
 *
 *  Q8  Member vs friend for a binary operator like +?
 *      → Member: the left side must be your class, so 5 + obj fails.
 *        Friend: both sides are parameters, so 5 + obj works (if a
 *        constructor can turn 5 into the class).
 *
 *  Q9  Why should operator= check for self-assignment?
 *      → In  a = a;  it would delete its own data first and then copy
 *        from the freed memory. The check (or copy-and-swap) avoids it.
 *
 *  Q10 What does <=> = default give you in C++20?
 *      → <, >, <=, >= comparing members in order. With
 *        operator== = default you also get == and !=.
 */
