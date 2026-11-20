/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                     DESIGN PATTERNS AND C++ IDIOMS                        ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is a design pattern?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ A design pattern is a PROVEN, reusable solution to a problem that
 *    keeps coming up in software design
 *  ✔ It's not ready-made code — it's a "recipe" you adapt to your classes
 *  ✔ Gives everyone a common language: "use a Factory here", "make it an
 *    Observer" — and the whole team understands
 *  ✔ Made famous by the "Gang of Four" (GoF) book — 23 patterns in 3
 *    groups. The most used ones are covered here.
 *
 *  The 3 groups
 *  ────────────────────────────────────────────────────────────────────────────
 *   GROUP        PROBLEM IT SOLVES              PATTERNS HERE
 *   ───────────  ─────────────────────────────  ───────────────────────────
 *   Creational   HOW objects are created        Singleton, Factory,
 *                                               Builder, Prototype
 *   Structural   HOW classes are combined       Adapter, Decorator, Facade
 *   Behavioral   HOW objects talk / share work  Observer, Strategy, Command
 *
 *  C++ idioms (C++-specific techniques)
 *  ────────────────────────────────────────────────────────────────────────────
 *   RAII            ─► resource tied to object life
 *   PIMPL           ─► hide private details behind a pointer
 *   Copy-and-swap   ─► safe, simple operator=
 *   NVI             ─► public non-virtual, private virtual
 *
 *  ⚠ Don't force patterns everywhere — use one when you actually have
 *    the problem it solves (remember KISS / YAGNI)
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   CREATIONAL
 *   ──────────
 *   Singleton  ⭐                ─► exactly ONE object (config, logger)
 *   Factory  ⭐                  ─► create objects without naming the class
 *   Builder                      ─► build complex objects step by step
 *   Prototype                    ─► copy an object via virtual clone()
 *
 *   STRUCTURAL
 *   ──────────
 *   Adapter                      ─► make an incompatible class fit
 *   Decorator                    ─► add features by wrapping
 *   Facade                       ─► one simple front for a complex system
 *
 *   BEHAVIORAL
 *   ──────────
 *   Observer  ⭐                 ─► notify many listeners of a change
 *   Strategy  ⭐                 ─► swap algorithms at run time
 *   Command                      ─► wrap a request as an object (undo)
 *
 *   C++ IDIOMS
 *   ──────────
 *   RAII, PIMPL, Copy-and-swap, NVI
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Singleton  (creational)
│  ✔ Problem : some things must exist ONLY ONCE in the program — app
│              settings, a logger, a connection pool
│  ✔ Idea    : private constructor + a static function that returns the
│              ONE instance. Copying is deleted.
│  ✔ "Meyers singleton": a static local object — created on first use,
│    thread-safe since C++11, destroyed at program end
│  ⚠ It's a global in disguise — overuse makes testing hard. Prefer
│    passing objects (dependency injection) when you can.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class AppConfig {
    string theme = "light";

    AppConfig() { cout << "config loaded (once)" << endl; }  // private

public:
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    static AppConfig& instance() {
        static AppConfig only;           // created on first call only
        return only;
    }

    string getTheme() const { return theme; }
    void setTheme(const string& t) { theme = t; }
};

int main() {

    AppConfig::instance().setTheme("dark");      // config loaded (once)

    AppConfig& a = AppConfig::instance();        // same object
    AppConfig& b = AppConfig::instance();
    cout << a.getTheme() << endl;                // dark
    cout << boolalpha << (&a == &b) << endl;     // true

    // AppConfig c;                      // ERROR: constructor is private
    // AppConfig d = a;                  // ERROR: copy deleted

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Factory  (creational)
│  ✔ Problem : the code that USES objects shouldn't need to know every
│              concrete class (and "new" them itself). Adding a new type
│              would mean editing many places.
│  ✔ Idea    : ONE function / class decides which concrete object to
│              create and returns it as the BASE type (unique_ptr<Base>)
│  ✔ The rest of the program only knows the interface
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Transport {
public:
    virtual void deliver(const string& item) const = 0;
    virtual ~Transport() {}
};

class Bike : public Transport {
public:
    void deliver(const string& i) const override {
        cout << "Bike delivers " << i << " (30 min)" << endl;
    }
};

class Truck : public Transport {
public:
    void deliver(const string& i) const override {
        cout << "Truck delivers " << i << " (2 days)" << endl;
    }
};

class Drone : public Transport {
public:
    void deliver(const string& i) const override {
        cout << "Drone delivers " << i << " (10 min)" << endl;
    }
};

unique_ptr<Transport> makeTransport(double weightKg, bool urgent) {
    if (urgent && weightKg < 2) return make_unique<Drone>();
    if (weightKg < 20) return make_unique<Bike>();
    return make_unique<Truck>();
}

int main() {

    makeTransport(0.5, true)->deliver("medicine");
    // Drone delivers medicine (10 min)
    makeTransport(5, false)->deliver("groceries");
    // Bike delivers groceries (30 min)
    makeTransport(300, false)->deliver("sofa");
    // Truck delivers sofa (2 days)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Builder  (creational)
│  ✔ Problem : an object with MANY optional parts → a constructor with
│              10 parameters  Pizza("L", true, false, true, 2, ...)
│              is impossible to read and easy to get wrong
│  ✔ Idea    : a Builder sets each part with a NAMED method (chaining
│              with return *this), then build() makes the final object
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HttpRequest {
public:
    string method = "GET", url;
    vector<string> headers;
    string body;
    int timeout = 30;

    void send() const {
        cout << method << " " << url << " (timeout " << timeout << "s)"
             << endl;
        for (const string& h : headers) cout << "  " << h << endl;
        if (!body.empty()) cout << "  body: " << body << endl;
    }
};

class RequestBuilder {
    HttpRequest req;

public:
    RequestBuilder& url(const string& u) { req.url = u; return *this; }
    RequestBuilder& post() { req.method = "POST"; return *this; }
    RequestBuilder& header(const string& h) {
        req.headers.push_back(h);
        return *this;
    }
    RequestBuilder& body(const string& b) { req.body = b; return *this; }
    RequestBuilder& timeout(int s) { req.timeout = s; return *this; }
    HttpRequest build() const { return req; }
};

int main() {

    HttpRequest r = RequestBuilder()
                        .url("api.shop.com/orders")
                        .post()
                        .header("Auth: token123")
                        .body("{\"item\": 7}")
                        .timeout(5)
                        .build();
    r.send();
    // POST api.shop.com/orders (timeout 5s)
    //   Auth: token123
    //   body: {"item": 7}

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Prototype  (creational)
│  ✔ Problem : you have an object through a BASE pointer and need a COPY
│              of it — but you don't know its real class, so you can't
│              write  new RealClass(*p)
│  ✔ Idea    : every class gives a virtual clone() that copies itself.
│              p->clone() makes the right type automatically.
│  ✔ Real use: copy-paste of shapes in a drawing app, game enemies
│    spawned from a template
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Shape {
public:
    virtual unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    int r;

public:
    Circle(int x) : r(x) {}
    unique_ptr<Shape> clone() const override {
        return make_unique<Circle>(*this);
    }
    void draw() const override { cout << "Circle r=" << r << endl; }
};

class Rect : public Shape {
    int w, h;

public:
    Rect(int a, int b) : w(a), h(b) {}
    unique_ptr<Shape> clone() const override {
        return make_unique<Rect>(*this);
    }
    void draw() const override { cout << "Rect " << w << "x" << h << endl; }
};

int main() {

    vector<unique_ptr<Shape>> canvas;
    canvas.push_back(make_unique<Circle>(5));
    canvas.push_back(make_unique<Rect>(3, 4));

    // "copy-paste" everything without knowing the real types
    size_t n = canvas.size();
    for (size_t i = 0; i < n; i++) canvas.push_back(canvas[i]->clone());

    for (const auto& s : canvas) s->draw();
    // Circle r=5
    // Rect 3x4
    // Circle r=5
    // Rect 3x4

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Adapter  (structural)
│  ✔ Problem : you have a class with the WRONG interface for your code —
│              e.g. an old / third-party payment library you can't edit
│  ✔ Idea    : write a small ADAPTER class that has YOUR interface and,
│              inside, calls the old class — like a travel plug adapter
│
│      your code ──► IPayment ──► PaytmAdapter ──► OldPaytmSDK
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class IPayment {                         // what our app expects
public:
    virtual bool pay(double rupees) = 0;
    virtual ~IPayment() = default;
};

class OldPaytmSDK {                      // can't change this
public:
    int makeTransaction(long paise, const string& currency) {
        cout << "SDK: " << paise << " " << currency << endl;
        return 200;                      // 200 = success
    }
};

class PaytmAdapter : public IPayment {
    OldPaytmSDK sdk;

public:
    bool pay(double rupees) override {
        long paise = (long)(rupees * 100);           // convert
        return sdk.makeTransaction(paise, "INR") == 200;
    }
};

void checkout(IPayment& p, double amt) {
    cout << (p.pay(amt) ? "Payment OK" : "Payment failed") << endl;
}

int main() {

    PaytmAdapter paytm;
    checkout(paytm, 499.50);
    // SDK: 49950 INR
    // Payment OK

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Decorator  (structural)
│  ✔ Problem : add extra features (milk, sugar, cream ...) in ANY mix,
│              without a subclass for every combination
│  ✔ Idea    : a decorator HAS the object AND IS the same type. It adds
│              its bit, then calls the wrapped object. Wrap many times.
│
│      Cream( Sugar( Milk( Coffee ) ) )
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Beverage {
public:
    virtual string name() const = 0;
    virtual double cost() const = 0;
    virtual ~Beverage() {}
};

class Coffee : public Beverage {
public:
    string name() const override { return "Coffee"; }
    double cost() const override { return 100; }
};

class AddOn : public Beverage {          // base decorator
protected:
    unique_ptr<Beverage> inner;

public:
    AddOn(unique_ptr<Beverage> b) : inner(move(b)) {}
};

class Milk : public AddOn {
public:
    using AddOn::AddOn;
    string name() const override { return inner->name() + " + Milk"; }
    double cost() const override { return inner->cost() + 20; }
};

class Caramel : public AddOn {
public:
    using AddOn::AddOn;
    string name() const override { return inner->name() + " + Caramel"; }
    double cost() const override { return inner->cost() + 35; }
};

int main() {

    unique_ptr<Beverage> order = make_unique<Coffee>();
    order = make_unique<Milk>(move(order));
    order = make_unique<Caramel>(move(order));
    order = make_unique<Milk>(move(order));          // double milk

    cout << order->name() << endl;   // Coffee + Milk + Caramel + Milk
    cout << order->cost() << endl;   // 175

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Facade  (structural)
│  ✔ Problem : a task needs MANY subsystems in the right order (check
│              stock, take payment, create shipment, send email). Every
│              caller would have to know all of them.
│  ✔ Idea    : one FACADE class with a simple method (placeOrder) that
│              talks to all the subsystems inside
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Inventory {
public:
    bool reserve(const string& item) {
        cout << "  stock reserved: " << item << endl;
        return true;
    }
};

class PaymentGateway {
public:
    bool charge(double amt) {
        cout << "  charged Rs." << amt << endl;
        return true;
    }
};

class Shipping {
public:
    void ship(const string& item) { cout << "  shipped: " << item << endl; }
};

class Mailer {
public:
    void send(const string& m) { cout << "  email: " << m << endl; }
};

class ShopFacade {                       // the simple front door
    Inventory inv;
    PaymentGateway pay;
    Shipping ship;
    Mailer mail;

public:
    void placeOrder(const string& item, double price) {
        cout << "Order " << item << ":" << endl;
        if (!inv.reserve(item) || !pay.charge(price)) return;
        ship.ship(item);
        mail.send("Your " + item + " is on the way");
    }
};

int main() {

    ShopFacade shop;
    shop.placeOrder("Headphones", 1999);
    // Order Headphones:
    //   stock reserved: Headphones
    //   charged Rs.1999
    //   shipped: Headphones
    //   email: Your Headphones is on the way

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Observer  (behavioral)
│  ✔ Problem : when one object changes (stock price, new video, order
│              status), MANY others must know — without the object
│              knowing their concrete classes
│  ✔ Idea    : the SUBJECT keeps a list of OBSERVERS (interface). On a
│              change it calls notify() on all of them. Observers can
│              subscribe / unsubscribe at any time.
│  ✔ Real use: YouTube subscriptions, UI events, stock tickers
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Observer {
public:
    virtual void update(const string& video) = 0;
    virtual ~Observer() {}
};

class Channel {                          // subject
    string name;
    vector<Observer*> subscribers;

public:
    Channel(string n) : name(n) {}
    void subscribe(Observer* o) { subscribers.push_back(o); }
    void unsubscribe(Observer* o) {
        subscribers.erase(remove(subscribers.begin(), subscribers.end(), o),
                          subscribers.end());
    }
    void upload(const string& video) {
        cout << name << " uploaded: " << video << endl;
        for (Observer* o : subscribers) o->update(video);
    }
};

class User : public Observer {
    string name;

public:
    User(string n) : name(n) {}
    void update(const string& v) override {
        cout << "  " << name << " got notification: " << v << endl;
    }
};

int main() {

    Channel ch("CodeWithAmit");
    User a("Neha"), b("Ravi");

    ch.subscribe(&a);
    ch.subscribe(&b);
    ch.upload("C++ OOP in 1 hour");
    // CodeWithAmit uploaded: C++ OOP in 1 hour
    //   Neha got notification: C++ OOP in 1 hour
    //   Ravi got notification: C++ OOP in 1 hour

    ch.unsubscribe(&b);
    ch.upload("Design Patterns");
    // CodeWithAmit uploaded: Design Patterns
    //   Neha got notification: Design Patterns

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Strategy  (behavioral)
│  ✔ Problem : one task, many ways to do it (route by car / bike / walk;
│              sort by price / rating) — and the choice changes at run
│              time. A big if-else grows forever.
│  ✔ Idea    : put each way in its own class behind an interface. The
│              context HAS a strategy and can swap it.
│  ✔ In modern C++ a std::function / lambda can also be a strategy
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class RouteStrategy {
public:
    virtual int minutes(int km) const = 0;
    virtual string name() const = 0;
    virtual ~RouteStrategy() {}
};

class ByCar : public RouteStrategy {
public:
    int minutes(int km) const override { return km * 2; }
    string name() const override { return "car"; }
};

class ByBike : public RouteStrategy {
public:
    int minutes(int km) const override { return km * 4; }
    string name() const override { return "bike"; }
};

class Walking : public RouteStrategy {
public:
    int minutes(int km) const override { return km * 12; }
    string name() const override { return "walk"; }
};

class Navigator {
    unique_ptr<RouteStrategy> strategy;

public:
    void setStrategy(unique_ptr<RouteStrategy> s) { strategy = move(s); }
    void route(int km) const {
        cout << km << " km by " << strategy->name() << ": "
             << strategy->minutes(km) << " min" << endl;
    }
};

int main() {

    Navigator maps;

    maps.setStrategy(make_unique<ByCar>());
    maps.route(10);                      // 10 km by car: 20 min

    maps.setStrategy(make_unique<ByBike>());
    maps.route(10);                      // 10 km by bike: 40 min

    maps.setStrategy(make_unique<Walking>());
    maps.route(2);                       // 2 km by walk: 24 min

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Command  (behavioral)
│  ✔ Problem : you want to UNDO actions, queue them, log them, or assign
│              them to buttons / shortcuts
│  ✔ Idea    : wrap each action in a Command object with execute() and
│              undo(). Keep executed commands in a stack → undo = pop and
│              call undo().
│  ✔ Real use: Ctrl+Z in editors, remote-control buttons, task queues
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <stack>
#include <string>
using namespace std;

class TextEditor {
public:
    string text;
};

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

class TypeCommand : public Command {
    TextEditor& ed;
    string added;

public:
    TypeCommand(TextEditor& e, string s) : ed(e), added(s) {}
    void execute() override { ed.text += added; }
    void undo() override { ed.text.erase(ed.text.size() - added.size()); }
};

class History {
    stack<unique_ptr<Command>> done;

public:
    void run(unique_ptr<Command> c) {
        c->execute();
        done.push(move(c));
    }
    void undo() {
        if (done.empty()) return;
        done.top()->undo();
        done.pop();
    }
};

int main() {

    TextEditor ed;
    History h;

    h.run(make_unique<TypeCommand>(ed, "Hello"));
    h.run(make_unique<TypeCommand>(ed, " World"));
    cout << ed.text << endl;             // Hello World

    h.undo();                            // Ctrl+Z
    cout << ed.text << endl;             // Hello

    h.undo();
    cout << "[" << ed.text << "]" << endl;   // []

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  RAII idiom  (Resource Acquisition Is Initialization)
│  ✔ Take the resource in the CONSTRUCTOR, release it in the DESTRUCTOR
│  ✔ Cleanup is then automatic — on normal exit, early return OR
│    exception. No "forgot to close / unlock / delete" bugs.
│  ✔ Standard RAII types: unique_ptr, shared_ptr, vector, string,
│    fstream, lock_guard, scoped_lock
│  ✔ More → 03_Constructors.cpp and 14_ExceptionsWithClasses.cpp
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <mutex>
using namespace std;

mutex bankLock;
int balance = 1000;

bool withdraw(int amt) {
    lock_guard<mutex> guard(bankLock);   // lock in constructor
    if (amt > balance) return false;     // early return → still unlocked
    balance -= amt;
    return true;
}                                        // unlock in destructor

int main() {

    cout << boolalpha;
    cout << withdraw(300) << endl;       // true
    cout << withdraw(5000) << endl;      // false
    cout << balance << endl;             // 700

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  PIMPL idiom  (Pointer to IMPLementation)
│  ✔ Problem : private members live in the header (.h). Change one
│              private member → EVERY file that includes the header must
│              recompile, and users see your internal details.
│  ✔ Idea    : the class keeps only a pointer to a hidden "Impl" struct
│              defined in the .cpp. The header stays tiny and stable.
│
│      // Widget.h  (users see only this)
│      class Widget {
│          struct Impl;                    // declared, not defined
│          unique_ptr<Impl> pImpl;
│      public:
│          Widget();  ~Widget();  void draw();
│      };
│
│  ✔ The destructor must be defined in the .cpp (where Impl is complete)
│  ✔ Below, all parts are in one file so it runs with Ctrl+Alt+N
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

// ───── Widget.h ─────
class Widget {
    struct Impl;
    unique_ptr<Impl> pImpl;

public:
    Widget(string title);
    ~Widget();
    void draw() const;
};

// ───── Widget.cpp ─────
struct Widget::Impl {                    // all private details here
    string title;
    int width = 300, height = 200;
    string color = "blue";
};

Widget::Widget(string title) : pImpl(make_unique<Impl>()) {
    pImpl->title = title;
}

Widget::~Widget() = default;             // here, Impl is complete

void Widget::draw() const {
    cout << pImpl->title << " [" << pImpl->width << "x" << pImpl->height
         << ", " << pImpl->color << "]" << endl;
}

// ───── main.cpp ─────
int main() {

    Widget w("Login Button");
    w.draw();                            // Login Button [300x200, blue]

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Copy-and-swap idiom
│  ✔ Write operator= by taking the parameter BY VALUE (the copy is made
│    there) and swapping its contents into *this
│  ✔ Safe on self-assignment, strong exception safety, and one operator=
│    works for both copy and move
│  ✔ Full explanation → 09_OperatorOverloading.cpp
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

class IntBuffer {
    int* data;
    size_t n;

public:
    IntBuffer(size_t size) : data(new int[size]()), n(size) {}
    IntBuffer(const IntBuffer& o) : data(new int[o.n]), n(o.n) {
        copy(o.data, o.data + n, data);
    }
    ~IntBuffer() { delete[] data; }

    friend void swap(IntBuffer& a, IntBuffer& b) noexcept {
        std::swap(a.data, b.data);
        std::swap(a.n, b.n);
    }

    IntBuffer& operator=(IntBuffer other) {      // copy made here
        swap(*this, other);                      // take it
        return *this;                            // old data dies in other
    }

    size_t size() const { return n; }
};

int main() {

    IntBuffer a(3), b(10);
    a = b;
    cout << a.size() << endl;            // 10
    a = a;                               // safe
    cout << a.size() << endl;            // 10

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  NVI idiom  (Non-Virtual Interface)
│  ✔ Idea : the PUBLIC function is NOT virtual. It does the fixed steps
│           (checks, logging, timing) and calls a PRIVATE virtual
│           function that children override.
│  ✔ Benefit: the base class controls the order of steps — children can
│    change only the part they are allowed to change
│  ✔ Same idea as the "Template Method" pattern
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class ReportGenerator {
public:
    void generate() {                    // public, NOT virtual
        cout << "[start] checking permissions" << endl;
        writeBody();                     // the only custom step
        cout << "[end] report saved" << endl;
    }
    virtual ~ReportGenerator() {}

private:
    virtual void writeBody() = 0;        // private virtual
};

class SalesReport : public ReportGenerator {
    void writeBody() override { cout << "  sales: Rs.12,40,000" << endl; }
};

class HRReport : public ReportGenerator {
    void writeBody() override { cout << "  employees: 48" << endl; }
};

int main() {

    SalesReport s;
    s.generate();
    // [start] checking permissions
    //   sales: Rs.12,40,000
    // [end] report saved

    HRReport h;
    h.generate();
    // [start] checking permissions
    //   employees: 48
    // [end] report saved

    return 0;
}
