/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                       OBJECT LIFETIME AND MEMORY                          ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Where can an object live?
 *  ────────────────────────────────────────────────────────────────────────────
 *
 *   PLACE      HOW YOU MAKE IT           WHEN IT DIES               WHO FREES
 *   ─────────  ────────────────────────  ─────────────────────────  ─────────
 *   Stack      Car c;  (local)           at the closing }           automatic
 *   Heap       new Car  /  make_unique   when you delete / owner    you / RAII
 *                                        smart pointer dies
 *   Static     global, static local,     when the program ends      automatic
 *              static member
 *
 *        ┌──────────────────────────┐
 *        │  STACK   (fast, small)   │  local objects, function calls
 *        ├──────────────────────────┤
 *        │            ↓ ↑           │
 *        ├──────────────────────────┤
 *        │  HEAP    (big, manual)   │  new / make_unique / make_shared
 *        ├──────────────────────────┤
 *        │  STATIC / GLOBAL DATA    │  globals, statics
 *        ├──────────────────────────┤
 *        │  CODE                    │  your functions (one copy)
 *        └──────────────────────────┘
 *
 *  Modern rule
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Prefer STACK objects
 *  ✔ Need the heap? Use SMART POINTERS, not raw new / delete
 *        unique_ptr → one owner        (default choice)
 *        shared_ptr → many owners      (shared data)
 *        weak_ptr   → watch without owning (break cycles)
 *  ✔ Header: <memory>
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Stack vs heap objects        ─► automatic vs manual lifetime
 *   new / delete with objects    ─► ctor runs on new, dtor on delete
 *   new[] / delete[]             ─► array of objects on the heap
 *   Placement new                ─► build an object in memory you have
 *   unique_ptr                   ─► single owner, auto delete
 *   shared_ptr                   ─► reference counting
 *   weak_ptr                     ─► break a shared_ptr cycle
 *   unique_ptr<Base> ⭐          ─► polymorphism without leaks
 *   Object memory layout         ─► members, padding, vptr, base part
 *   Temporary object lifetime    ─► dies at ; (const& can extend it)
 *   ⚠ Dangling pointers / refs   ─► the classic memory bugs
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Objects on the stack vs the heap
│  ✔ Stack object : made by a normal declaration, destroyed AUTOMATICALLY
│                   at the end of its { } block
│  ✔ Heap object  : made with new, lives until YOU delete it — even after
│                   the function that made it returns
│  ✔ Stack is faster; heap is for big data, or data that must outlive
│    the function, or when the size / type is known only at run time
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Car {
    string name;

public:
    Car(string n) : name(n) { cout << "  make " << name << endl; }
    ~Car() { cout << "  scrap " << name << endl; }
};

Car* buildOnHeap() {
    Car local("StackCar");               // dies when this function ends
    return new Car("HeapCar");           // survives the function
}

int main() {

    cout << "calling buildOnHeap" << endl;     // calling buildOnHeap
    Car* p = buildOnHeap();
    //   make StackCar
    //   make HeapCar
    //   scrap StackCar             (end of function)

    cout << "back in main, HeapCar still alive" << endl;
    // back in main, HeapCar still alive
    delete p;                            //   scrap HeapCar

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  new / delete with objects ->
│      ClassName* p = new ClassName(args);     // memory + constructor
│      delete p;                               // destructor + free memory
│
│  ✔ Definition : new does TWO things: gets heap memory AND runs the
│                 constructor. delete runs the destructor AND frees it.
│  ⚠ Forget delete → memory LEAK
│  ⚠ delete twice  → crash / undefined behaviour
│  ⚠ Use p after delete → undefined behaviour (set p = nullptr)
│  ✔ delete nullptr is safe (does nothing)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Order {
    int id;

public:
    Order(int i) : id(i) { cout << "Order " << id << " created" << endl; }
    ~Order() { cout << "Order " << id << " closed" << endl; }
    void show() const { cout << "Order #" << id << endl; }
};

int main() {

    Order* o = new Order(101);           // Order 101 created
    o->show();                           // Order #101
    delete o;                            // Order 101 closed
    o = nullptr;                         // good habit

    delete o;                            // safe: deleting nullptr

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  new[] / delete[] for an array of objects ->
│      ClassName* arr = new ClassName[n];      delete[] arr;
│
│  ✔ Definition : new[] makes n objects (default constructor for EACH).
│                 delete[] runs the destructor for EACH, in reverse.
│  ⚠ new[] must be paired with delete[]. Using plain delete on an array
│    → only one destructor may run → undefined behaviour
│  ✔ Easier: vector<ClassName> does all of this for you
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
using namespace std;

class Seat {
    static inline int next = 1;
    int number;

public:
    Seat() : number(next++) { cout << "seat " << number << " "; }
    ~Seat() { cout << "~" << number << " "; }
};

int main() {

    int n = 3;
    Seat* row = new Seat[n];             // seat 1 seat 2 seat 3
    cout << endl;
    delete[] row;                        // ~3 ~2 ~1
    cout << endl;

    vector<Seat> row2(2);                // seat 4 seat 5
    cout << endl;

    return 0;                            // ~4 ~5   (vector cleans up)
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Placement new ->
│      void* mem = ...;                        // memory you already have
│      ClassName* p = new (mem) ClassName(args);
│      p->~ClassName();                        // call destructor yourself
│
│  ✔ Definition : Build an object in memory you ALREADY own, without
│                 asking for new memory. Header: <new>
│  ✔ Used inside vector, optional, memory pools, embedded systems
│  ⚠ Never delete it — call the destructor by hand, and free the memory
│    the way it was obtained
│  ✔ The buffer must be big enough and correctly aligned (alignas)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <new>
#include <string>
using namespace std;

class Sensor {
    string id;

public:
    Sensor(string i) : id(i) { cout << "Sensor " << id << " on" << endl; }
    ~Sensor() { cout << "Sensor " << id << " off" << endl; }
    void read() const { cout << id << " = 23.5 C" << endl; }
};

int main() {

    alignas(Sensor) unsigned char buffer[sizeof(Sensor)];   // raw memory

    Sensor* s = new (buffer) Sensor("T1");   // Sensor T1 on
    s->read();                               // T1 = 23.5 C
    s->~Sensor();                            // Sensor T1 off
    // no delete — buffer is a local array

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  unique_ptr — single owner ->
│      unique_ptr<T> p = make_unique<T>(args);
│      p->member;   *p;   p.get();   p.reset();   move(p);
│
│  ✔ Definition : A smart pointer that OWNS one heap object. When the
│                 unique_ptr dies, it deletes the object automatically.
│  ✔ Only ONE owner: it can't be copied, only MOVED (ownership transfer)
│  ✔ Same size and speed as a raw pointer → the DEFAULT choice
│  ✔ Prefer make_unique<T>(...) over new
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Document {
    string title;

public:
    Document(string t) : title(t) { cout << "open " << title << endl; }
    ~Document() { cout << "close " << title << endl; }
    void edit() const { cout << "editing " << title << endl; }
};

unique_ptr<Document> createDoc(string t) {   // factory: gives ownership
    return make_unique<Document>(t);
}

int main() {

    unique_ptr<Document> a = createDoc("notes.txt");   // open notes.txt
    a->edit();                                         // editing notes.txt

    // unique_ptr<Document> b = a;       // ERROR: can't copy
    unique_ptr<Document> b = move(a);    // ownership moves to b
    cout << boolalpha << (a == nullptr) << endl;       // true

    b.reset(new Document("todo.txt"));
    // open todo.txt
    // close notes.txt                   (old object deleted by reset)

    return 0;                            // close todo.txt
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  shared_ptr — many owners ->
│      shared_ptr<T> p = make_shared<T>(args);
│      shared_ptr<T> q = p;                    // copy → count goes up
│      p.use_count();                          // how many owners
│
│  ✔ Definition : Many shared_ptrs can own the SAME object. It keeps a
│                 REFERENCE COUNT; the object is deleted when the LAST
│                 owner goes away.
│  ✔ Use when ownership is truly shared (cache, graph nodes, shared
│    settings)
│  ⚠ A bit slower than unique_ptr (counter updates). Don't use it "by
│    default" — start with unique_ptr.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Image {
    string file;

public:
    Image(string f) : file(f) { cout << "load " << file << endl; }
    ~Image() { cout << "free " << file << endl; }
};

struct Post {
    shared_ptr<Image> photo;             // many posts can share one image
};

int main() {

    auto img = make_shared<Image>("sunset.jpg");   // load sunset.jpg
    cout << img.use_count() << endl;               // 1

    Post p1{img};
    {
        Post p2{img};
        cout << img.use_count() << endl;           // 3
    }
    cout << img.use_count() << endl;               // 2

    img.reset();                                   // main lets go
    cout << p1.photo.use_count() << endl;          // 1

    return 0;                                      // free sunset.jpg
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  weak_ptr — watch without owning (break cycles) ->
│      weak_ptr<T> w = someShared;
│      if (auto s = w.lock()) { ... }          // get a shared_ptr if alive
│
│  ✔ Problem: A owns B and B owns A with shared_ptr → counts never reach
│    0 → NEITHER is ever deleted (memory leak)
│  ✔ Fix: make one side a weak_ptr. It points to the object but does
│    NOT increase the count.
│  ✔ lock() gives a shared_ptr if the object still exists, else empty
│
│     Parent ──shared──► Child           Parent ──shared──► Child
│        ▲                 │                ▲                 │
│        └─────shared──────┘                └──────weak───────┘
│          LEAK (cycle)                       OK
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

struct Employee;

struct Team {
    string name;
    shared_ptr<Employee> lead;
    Team(string n) : name(n) {}
    ~Team() { cout << "Team " << name << " deleted" << endl; }
};

struct Employee {
    string name;
    weak_ptr<Team> team;                 // weak → no cycle
    Employee(string n) : name(n) {}
    ~Employee() { cout << "Employee " << name << " deleted" << endl; }
};

int main() {

    {
        auto t = make_shared<Team>("Backend");
        auto e = make_shared<Employee>("Neha");
        t->lead = e;
        e->team = t;

        if (auto team = e->team.lock())
            cout << e->name << " leads " << team->name << endl;
        // Neha leads Backend
    }
    // Team Backend deleted
    // Employee Neha deleted          (with shared both ways: NOTHING here)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  unique_ptr<Base> for polymorphism  ⭐
│  ✔ Store DIFFERENT child objects in one container through
│    unique_ptr<Base> — no manual delete, no leaks
│  ✔ Needs a VIRTUAL destructor in Base, so deleting through Base*
│    runs the child's destructor too
│  ✔ The modern way to write factories:  unique_ptr<Shape> make(...)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class Notification {
public:
    virtual void send() const = 0;
    virtual ~Notification() { cout << "~Notification" << endl; }
};

class Sms : public Notification {
public:
    void send() const override { cout << "SMS sent" << endl; }
    ~Sms() { cout << "~Sms" << endl; }
};

class Email : public Notification {
public:
    void send() const override { cout << "Email sent" << endl; }
    ~Email() { cout << "~Email" << endl; }
};

unique_ptr<Notification> make(const string& type) {     // factory
    if (type == "sms") return make_unique<Sms>();
    return make_unique<Email>();
}

int main() {

    vector<unique_ptr<Notification>> queue;
    queue.push_back(make("sms"));
    queue.push_back(make("email"));

    for (const auto& n : queue) n->send();
    // SMS sent
    // Email sent

    return 0;
    // ~Sms
    // ~Notification
    // ~Email
    // ~Notification
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Object memory layout
│  ✔ An object holds ONLY its data members (+ padding + maybe a vptr).
│    Functions are stored once, in the code area.
│  ✔ Members are laid out in DECLARATION order; padding is added so each
│    member sits at an address that suits its size (alignment)
│  ✔ A class with virtual functions gets a hidden vptr (8 bytes, 64-bit)
│  ✔ A derived object = base part FIRST, then its own members
│
│      struct Bad { char a; int b; char c; }   → a . . . b b b b c . . .
│                                                 (12 bytes, 6 wasted)
│      struct Good { int b; char a; char c; }  → b b b b a c . .
│                                                 (8 bytes)
│  ✔ Numbers below are for g++ on 64-bit
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <cstddef>
using namespace std;

struct Bad { char a; int b; char c; };
struct Good { int b; char a; char c; };

struct Base { int x; };
struct Derived : Base { int y; };        // base part + y

struct WithVirtual {
    int x;
    virtual void f() {}
    virtual ~WithVirtual() {}
};

int main() {

    cout << sizeof(Bad) << endl;             // 12
    cout << sizeof(Good) << endl;            // 8
    cout << offsetof(Bad, b) << endl;        // 4   (3 padding bytes before)

    cout << sizeof(Base) << endl;            // 4
    cout << sizeof(Derived) << endl;         // 8   (x then y)

    cout << sizeof(WithVirtual) << endl;     // 16  (vptr 8 + int 4 + pad 4)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Lifetime of temporary objects
│  ✔ A temporary (unnamed object, e.g. a function's return value) dies
│    at the END of the full statement — the ;
│  ✔ Binding it to a  const T&  (or  T&&) EXTENDS its life to the life of
│    that reference
│  ⚠ This does NOT work through a function that returns a reference to
│    its argument — that reference dangles after the ;
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Temp {
    string name;

public:
    Temp(string n) : name(n) { cout << "make " << name << endl; }
    ~Temp() { cout << "kill " << name << endl; }
    void hello() const { cout << "hello from " << name << endl; }
};

Temp makeTemp(string n) { return Temp(n); }

int main() {

    makeTemp("A").hello();
    // make A
    // hello from A
    // kill A                      (end of this statement)

    const Temp& keep = makeTemp("B");    // make B
    cout << "B still alive" << endl;     // B still alive
    keep.hello();                        // hello from B

    return 0;                            // kill B   (reference ends)
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  ⚠ Dangling pointers and references to objects
│  ✔ A DANGLING pointer / reference points to an object that is already
│    DEAD. Using it is undefined behaviour — it may print garbage, crash,
│    or seem to "work" and fail later.
│  ✔ The classic ways to create one (shown in comments, NOT run):
│        1. return a reference / pointer to a LOCAL variable
│        2. use a pointer after delete
│        3. keep a pointer into a vector, then push_back (vector moves
│           its elements to new memory)
│        4. a raw pointer to an object owned by a unique_ptr that died
│  ✔ Fixes: return by value, smart pointers, set to nullptr after
│    delete, use indexes instead of pointers into vectors
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

struct User { string name; };

// 1. ✘  User& bad() { User u{"temp"}; return u; }   // u dies here
User good() { return User{"temp"}; }                 // ✔ return by value

int main() {

    // 2. ✘  User* p = new User{"x"}; delete p; cout << p->name;
    User* p = new User{"x"};
    delete p;
    p = nullptr;                                     // ✔
    if (!p) cout << "pointer cleared" << endl;       // pointer cleared

    // 3. ✘  User* first = &users[0]; users.push_back(...); first->name;
    vector<User> users = {{"Amit"}};
    size_t firstIndex = 0;                           // ✔ keep an index
    users.push_back({"Neha"});
    users.push_back({"Ravi"});
    cout << users[firstIndex].name << endl;          // Amit

    // 4. ✔ shared_ptr + weak_ptr tells you if the object is gone
    weak_ptr<User> watcher;
    {
        auto owner = make_shared<User>(User{"Sara"});
        watcher = owner;
    }
    cout << boolalpha << watcher.expired() << endl;  // true

    cout << good().name << endl;                     // temp

    return 0;
}
