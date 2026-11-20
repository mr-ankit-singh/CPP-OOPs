/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                 TEMPLATES WITH OOP (GENERIC CLASSES)                      ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is a class template?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ A class template is a BLUEPRINT for making classes. You write the
 *    class once with a placeholder type T; the compiler makes a real
 *    class for every type you use
 *        Box<int>,  Box<string>,  Box<Student>  → 3 classes, 1 template
 *  ✔ This is how vector<T>, map<K, V>, unique_ptr<T> are written
 *  ✔ Function templates basics → C++/37_Templates.cpp
 *    This file is about templates INSIDE OOP: generic classes, their
 *    members, specialization, inheritance and CRTP
 *
 *        template <typename T>            Box<int>    ─► class with int
 *        class Box { T value; };   ───►   Box<string> ─► class with string
 *                                         Box<double> ─► class with double
 *
 *  Words
 *  ────────────────────────────────────────────────────────────────────────────
 *   template parameter  ─► the placeholder:  T, K, V, N
 *   instantiation       ─► compiler making Box<int> from the template
 *   specialization      ─► a special version for one particular type
 *   non-type parameter  ─► a VALUE, not a type:  template <int N>
 *
 *  ⚠ Template code usually lives fully in the HEADER (.h) — the compiler
 *    needs the full body to make each version
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Class template                ─► template <typename T> class Box
 *   Member functions outside      ─► template <typename T> T Box<T>::get()
 *   Many parameters + defaults    ─► Pair<K, V = int>, Array<T, N>
 *   Member function template      ─► a template function inside a class
 *   Full specialization           ─► special Box<bool>
 *   Partial specialization        ─► special Box<T*> for all pointers
 *   Class template + inheritance  ─► generic base / generic child
 *   CRTP                          ─► base knows the child's type
 *   Templates vs virtual          ─► when to use which
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Class template ->
│      template <typename T>
│      class Box { T value; public: Box(T v); T get(); };
│      Box<int> a(5);       Box<string> b("hi");
│
│  ✔ Definition : One class written with a placeholder type T. The
│                 compiler creates a real class for every T you use.
│  ✔ "typename" and "class" mean the same here:
│        template <typename T>  ==  template <class T>
│  ✔ C++17 can often guess T:  Box c(3.5);  → Box<double>
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Box {
    T value;

public:
    Box(T v) : value(v) {}
    T get() const { return value; }
    void set(T v) { value = v; }
};

int main() {

    Box<int> marks(95);
    Box<string> name("Neha");
    Box price(499.5);                    // C++17: T guessed as double

    cout << marks.get() << endl;         // 95
    cout << name.get() << endl;          // Neha
    cout << price.get() << endl;         // 499.5

    marks.set(99);
    cout << marks.get() << endl;         // 99

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Member functions defined outside the class template ->
│      template <typename T>
│      ReturnType ClassName<T>::function(params) { ... }
│
│  ✔ Definition : Repeat the "template <typename T>" line, and write the
│                 class name WITH <T> before ::
│  ✔ Real example: a generic Stack that works for any type
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
    vector<T> items;

public:
    void push(const T& x);
    T pop();
    bool empty() const;
    size_t size() const { return items.size(); }
};

template <typename T>
void Stack<T>::push(const T& x) {
    items.push_back(x);
}

template <typename T>
T Stack<T>::pop() {
    if (items.empty()) throw out_of_range("stack is empty");
    T top = items.back();
    items.pop_back();
    return top;
}

template <typename T>
bool Stack<T>::empty() const {
    return items.empty();
}

int main() {

    Stack<int> undo;
    undo.push(1);
    undo.push(2);
    undo.push(3);
    cout << undo.pop() << endl;          // 3
    cout << undo.size() << endl;         // 2

    Stack<string> history;
    history.push("google.com");
    history.push("github.com");
    cout << history.pop() << endl;       // github.com

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Many parameters, default types, non-type parameters ->
│      template <typename K, typename V = int>   class Pair { ... };
│      template <typename T, size_t N>           class FixedArray { ... };
│
│  ✔ Many parameters  : Pair<string, double>
│  ✔ Default type     : Pair<string>  → V becomes int
│  ✔ Non-type param   : a compile-time VALUE (size, count, flag)
│                       FixedArray<int, 5>  — size known at compile time
│                       (that's how std::array<T, N> works)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

template <typename K, typename V = int>
class Pair {
public:
    K key;
    V value;
    Pair(K k, V v) : key(k), value(v) {}
    void show() const { cout << key << " = " << value << endl; }
};

template <typename T, size_t N>
class FixedArray {
    T data[N] = {};

public:
    T& operator[](size_t i) { return data[i]; }
    size_t size() const { return N; }
};

int main() {

    Pair<string, double> price("Pen", 9.5);
    Pair<string> stock("Pen", 120);      // V = int (default)
    price.show();                        // Pen = 9.5
    stock.show();                        // Pen = 120

    FixedArray<int, 5> week;
    week[0] = 7;
    cout << week.size() << " " << week[0] << endl;   // 5 7

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Member function template ->
│      class A { template <typename U> void f(U x); };
│
│  ✔ Definition : A template function INSIDE a class (normal class or a
│                 class template). It gets its OWN type parameter.
│  ✔ Useful to accept MANY types in one method, e.g. a logger that can
│    print anything, or converting Box<int> to Box<double>
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Logger {                           // normal class
public:
    template <typename T>
    void log(const string& label, const T& value) {
        cout << "[" << label << "] " << value << endl;
    }
};

template <typename T>
class Box {
public:
    T value;
    Box(T v) : value(v) {}

    template <typename U>                // own parameter U
    Box<U> convert() const { return Box<U>(static_cast<U>(value)); }
};

int main() {

    Logger log;
    log.log("user", string("Amit"));     // [user] Amit
    log.log("age", 25);                  // [age] 25
    log.log("rating", 4.7);              // [rating] 4.7

    Box<double> b(9.99);
    Box<int> i = b.convert<int>();
    cout << i.value << endl;             // 9

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Full template specialization ->
│      template <>
│      class Box<bool> { ... };               // special version for bool
│
│  ✔ Definition : Write a COMPLETELY different version of the class for
│                 ONE specific type. The general template is used for
│                 all other types.
│  ✔ Real use: vector<bool> is specialised to store bits; here a
│    Printer prints bool as "yes / no"
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Printer {                          // general version
public:
    void print(const T& x) { cout << "value: " << x << endl; }
};

template <>
class Printer<bool> {                    // special version for bool
public:
    void print(bool x) { cout << "value: " << (x ? "yes" : "no") << endl; }
};

template <>
class Printer<string> {                  // special version for string
public:
    void print(const string& s) { cout << "value: \"" << s << "\"" << endl; }
};

int main() {

    Printer<int>().print(42);            // value: 42
    Printer<bool>().print(true);         // value: yes
    Printer<string>().print("hi");       // value: "hi"

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Partial template specialization ->
│      template <typename T>
│      class Holder<T*> { ... };              // for ANY pointer type
│
│  ✔ Definition : A special version for a whole GROUP of types (all
│                 pointers, all pairs ...) — T is still a parameter.
│  ✔ Only CLASS templates can be partially specialised (not functions)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

template <typename T>
class Holder {                           // general
public:
    void describe() { cout << "holds a value" << endl; }
};

template <typename T>
class Holder<T*> {                       // every pointer type
public:
    void describe() { cout << "holds a pointer" << endl; }
};

template <typename A, typename B>
class Combo {
public:
    void describe() { cout << "two different types" << endl; }
};

template <typename A>
class Combo<A, A> {                      // both types the same
public:
    void describe() { cout << "same type twice" << endl; }
};

int main() {

    Holder<int>().describe();            // holds a value
    Holder<int*>().describe();           // holds a pointer
    Holder<double*>().describe();        // holds a pointer

    Combo<int, char>().describe();       // two different types
    Combo<int, int>().describe();        // same type twice

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Class template + inheritance
│  ✔ 3 combinations:
│        1. normal class   → inherits a template:  class A : Base<int>
│        2. template class → inherits a normal one
│        3. template class → inherits a template:  Child<T> : Base<T>
│  ⚠ In case 3, use  this->member  (or Base<T>::member) to reach base
│    members — the compiler doesn't look inside a dependent base by
│    itself
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class Repository {                       // generic storage
protected:
    vector<T> items;

public:
    void add(const T& x) { items.push_back(x); }
    size_t count() const { return items.size(); }
};

struct Product { string name; double price; };

class ProductRepo : public Repository<Product> {     // case 1
public:
    double totalValue() const {
        double t = 0;
        for (const Product& p : items) t += p.price;
        return t;
    }
};

template <typename T>
class LoggedRepo : public Repository<T> {            // case 3
public:
    void add(const T& x) {
        cout << "adding item #" << this->count() + 1 << endl;
        Repository<T>::add(x);
    }
};

int main() {

    ProductRepo shop;
    shop.add({"Pen", 10});
    shop.add({"Bag", 750});
    cout << shop.count() << " items, Rs." << shop.totalValue() << endl;
    // 2 items, Rs.760

    LoggedRepo<string> names;
    names.add("Amit");                   // adding item #1
    names.add("Neha");                   // adding item #2

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  CRTP (Curiously Recurring Template Pattern) ->
│      template <typename Derived> class Base { ... };
│      class Child : public Base<Child> { ... };
│
│  ✔ Definition : The child passes ITSELF to its template base. The base
│                 can then call child functions with
│                 static_cast<Derived*>(this) — no virtual needed.
│  ✔ Uses: add ready-made features to many classes (comparison
│    operators, counters, clone), static polymorphism
│  ✔ Below: a mixin that gives EVERY class an object counter
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

template <typename Derived>
class Counted {                          // reusable "feature"
    inline static int alive = 0;

protected:
    Counted() { alive++; }
    Counted(const Counted&) { alive++; }
    ~Counted() { alive--; }

public:
    static int count() { return alive; }
};

class User : public Counted<User> {};    // each class gets its OWN counter
class Order : public Counted<Order> {};

int main() {

    User u1, u2, u3;
    Order o1;

    cout << User::count() << endl;       // 3
    cout << Order::count() << endl;      // 1

    {
        User temp;
        cout << User::count() << endl;   // 4
    }
    cout << User::count() << endl;       // 3

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Templates vs virtual functions — when to use which
│
│   POINT                 TEMPLATES (static)        VIRTUAL (dynamic)
│   ────────────────────  ────────────────────────  ────────────────────────
│   Type decided          compile time              run time
│   Speed                 fastest (can inline)      one vtable jump
│   Mixed types in one    NO (Box<int> ≠ Box<str>)  YES (vector<Base*>)
│   container
│   New types later       recompile                 just add a child class
│   (plugins)
│   Code size             a copy per type           one copy
│   Error messages        long, hard                short
│
│  ✔ Same behaviour on DIFFERENT, unrelated types, known while compiling
│    → TEMPLATES (containers, algorithms, math)
│  ✔ Different behaviour for RELATED types, chosen while running
│    → VIRTUAL (shapes, payments, plugins)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// templates: one algorithm, many types
template <typename T>
T sumAll(const vector<T>& v) {
    T total{};
    for (const T& x : v) total += x;
    return total;
}

// virtual: many behaviours, one interface, mixed in one list
class Discount {
public:
    virtual double apply(double price) const = 0;
    virtual ~Discount() {}
};

class Flat100 : public Discount {
public:
    double apply(double p) const override { return p - 100; }
};

class TenPercent : public Discount {
public:
    double apply(double p) const override { return p * 0.9; }
};

int main() {

    cout << sumAll(vector<int>{1, 2, 3}) << endl;            // 6
    cout << sumAll(vector<double>{1.5, 2.5}) << endl;        // 4

    vector<unique_ptr<Discount>> offers;
    offers.push_back(make_unique<Flat100>());
    offers.push_back(make_unique<TenPercent>());
    for (const auto& d : offers) cout << d->apply(1000) << endl;
    // 900
    // 900

    return 0;
}
