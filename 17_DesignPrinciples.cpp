/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                            DESIGN PRINCIPLES                              ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Why design principles?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Knowing classes, inheritance and virtual is not enough — you also
 *    need to know HOW to split a program into good classes
 *  ✔ Design principles are proven rules that make code:
 *        • easy to CHANGE (new features without breaking old ones)
 *        • easy to TEST and REUSE
 *        • easy to UNDERSTAND for the next person
 *  ✔ Bad design smells: one class does everything, changing one thing
 *    breaks five others, lots of copy-paste, long if-else on types
 *
 *  SOLID  ⭐  (5 principles for OOP design)
 *  ────────────────────────────────────────────────────────────────────────────
 *   S  Single Responsibility  ─► a class should have ONE reason to change
 *   O  Open / Closed          ─► open to EXTEND, closed to MODIFY
 *   L  Liskov Substitution    ─► a child must work wherever the parent works
 *   I  Interface Segregation  ─► many small interfaces > one fat interface
 *   D  Dependency Inversion   ─► depend on ABSTRACTIONS, not concrete classes
 *
 *  Other common principles
 *  ────────────────────────────────────────────────────────────────────────────
 *   DRY      ─► Don't Repeat Yourself — one place for each piece of logic
 *   KISS     ─► Keep It Simple, Stupid — simplest solution that works
 *   YAGNI    ─► You Aren't Gonna Need It — don't build features "for later"
 *   Composition over inheritance ─► prefer HAS-A over IS-A for reuse
 *   Law of Demeter ─► talk only to your close friends, not strangers
 *
 *  ✔ Each block below shows the BAD way (✘) and the GOOD way (✔)
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   S → Single Responsibility    ─► split Invoice / Printer / Repository
 *   O → Open / Closed            ─► new discount = new class, no edits
 *   L → Liskov Substitution      ─► Square is NOT a Rectangle
 *   I → Interface Segregation    ─► Printer doesn't need fax()
 *   D → Dependency Inversion     ─► OrderService depends on INotifier
 *   DRY                          ─► one function instead of copy-paste
 *   KISS                         ─► simple code beats clever code
 *   YAGNI                        ─► build only what is needed now
 *   Composition over inheritance ─► behaviours as parts, not parents
 *   Law of Demeter               ─► no a.getB().getC().doThing()
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  S → Single Responsibility Principle (SRP)
│  ✔ Definition : A class should have ONLY ONE reason to change — it
│                 should do ONE job.
│  ✘ Bad : Invoice calculates the total, prints it AND saves it to a
│          database. A change in printing format, tax rules OR database
│          forces you to edit the same class.
│  ✔ Good: Invoice → math only,  InvoicePrinter → output only,
│          InvoiceRepository → saving only
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ✘ class Invoice { total(); print(); saveToDB(); };   // 3 jobs

struct Item { string name; double price; int qty; };

class Invoice {                          // job 1: business logic
public:
    vector<Item> items;
    double total() const {
        double t = 0;
        for (const Item& i : items) t += i.price * i.qty;
        return t * 1.18;                 // with 18% GST
    }
};

class InvoicePrinter {                   // job 2: presentation
public:
    void print(const Invoice& inv) const {
        for (const Item& i : inv.items)
            cout << i.name << " x" << i.qty << endl;
        cout << "Total: " << inv.total() << endl;
    }
};

class InvoiceRepository {                // job 3: storage
public:
    void save(const Invoice&) const { cout << "saved to database" << endl; }
};

int main() {

    Invoice inv;
    inv.items = {{"Pen", 10, 5}, {"Notebook", 50, 2}};

    InvoicePrinter().print(inv);
    // Pen x5
    // Notebook x2
    // Total: 177

    InvoiceRepository().save(inv);       // saved to database

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  O → Open / Closed Principle (OCP)
│  ✔ Definition : Code should be OPEN for extension but CLOSED for
│                 modification — add new behaviour by ADDING code, not
│                 by EDITING code that already works.
│  ✘ Bad : a switch / if-else on a "type" string. Every new discount
│          means editing that function again (and maybe breaking it).
│  ✔ Good: a Discount interface. A new discount = a NEW class.
│          Checkout never changes.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// ✘ double apply(string type, double p) {
//       if (type == "flat") ... else if (type == "percent") ...
//       // new type? edit here again!
//   }

class Discount {
public:
    virtual double apply(double price) const = 0;
    virtual ~Discount() {}
};

class FlatOff : public Discount {
    double amount;

public:
    FlatOff(double a) : amount(a) {}
    double apply(double p) const override { return p - amount; }
};

class PercentOff : public Discount {
    double pct;

public:
    PercentOff(double x) : pct(x) {}
    double apply(double p) const override { return p * (1 - pct / 100); }
};

class FestivalOff : public Discount {    // NEW — nothing else edited
public:
    double apply(double p) const override { return p > 2000 ? p - 500 : p; }
};

double checkout(double price, const Discount& d) {   // closed for edits
    return d.apply(price);
}

int main() {

    cout << checkout(3000, FlatOff(200)) << endl;    // 2800
    cout << checkout(3000, PercentOff(10)) << endl;  // 2700
    cout << checkout(3000, FestivalOff()) << endl;   // 2500

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  L → Liskov Substitution Principle (LSP)
│  ✔ Definition : If S is a child of T, you must be able to use an S
│                 ANYWHERE a T is expected, and the program still behaves
│                 correctly. A child must keep the parent's promises.
│  ✘ Bad : Square inherits Rectangle. setWidth() on a Square also
│          changes height → code that expects a Rectangle gets a wrong
│          area. Same for Penguin : Bird with fly() that throws.
│  ✔ Good: don't force the IS-A. Make both children of a common Shape
│          with area(), and give flying only to birds that fly.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

// ✘ The broken version
class Rectangle {
protected:
    int w = 0, h = 0;

public:
    virtual void setWidth(int x) { w = x; }
    virtual void setHeight(int x) { h = x; }
    int area() const { return w * h; }
    virtual ~Rectangle() {}
};

class Square : public Rectangle {        // "a square IS-A rectangle"?
public:
    void setWidth(int x) override { w = h = x; }
    void setHeight(int x) override { w = h = x; }
};

void resize(Rectangle& r) {              // expects normal rectangle rules
    r.setWidth(5);
    r.setHeight(4);
    cout << "expected 20, got " << r.area() << endl;
}

// ✔ The fixed version
class Shape {
public:
    virtual int area() const = 0;
    virtual ~Shape() {}
};

class Rect : public Shape {
    int w, h;

public:
    Rect(int a, int b) : w(a), h(b) {}
    int area() const override { return w * h; }
};

class Sq : public Shape {
    int s;

public:
    Sq(int a) : s(a) {}
    int area() const override { return s * s; }
};

int main() {

    Rectangle r;
    Square s;
    resize(r);                           // expected 20, got 20
    resize(s);                           // expected 20, got 16   ✘ LSP broken

    Rect good1(5, 4);
    Sq good2(4);
    cout << good1.area() << " " << good2.area() << endl;   // 20 16  ✔

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  I → Interface Segregation Principle (ISP)
│  ✔ Definition : No class should be forced to depend on methods it does
│                 NOT use. Prefer many SMALL interfaces over one big one.
│  ✘ Bad : one IMachine with print(), scan(), fax(). A simple printer
│          must still write fax() — usually as "throw not supported".
│  ✔ Good: IPrinter, IScanner, IFax. Each machine implements only what
│          it really can do.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

// ✘ class IMachine { virtual void print()=0; virtual void scan()=0;
//                    virtual void fax()=0; };   // too fat

class IPrinter {
public:
    virtual void print(const string& doc) = 0;
    virtual ~IPrinter() = default;
};

class IScanner {
public:
    virtual string scan() = 0;
    virtual ~IScanner() = default;
};

class BasicPrinter : public IPrinter {             // only printing
public:
    void print(const string& d) override { cout << "print: " << d << endl; }
};

class OfficeMachine : public IPrinter, public IScanner {    // both
public:
    void print(const string& d) override { cout << "print: " << d << endl; }
    string scan() override { return "scanned-page"; }
};

void printReport(IPrinter& p) { p.print("report.pdf"); }

int main() {

    BasicPrinter home;
    OfficeMachine office;

    printReport(home);                   // print: report.pdf
    printReport(office);                 // print: report.pdf
    cout << office.scan() << endl;       // scanned-page

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  D → Dependency Inversion Principle (DIP)
│  ✔ Definition : High-level code (business rules) should NOT depend on
│                 low-level details (email, SMS, database). BOTH should
│                 depend on an ABSTRACTION (an interface).
│  ✘ Bad : OrderService creates an EmailSender inside itself. To switch
│          to SMS, or to test without sending real emails, you must edit
│          OrderService.
│  ✔ Good: OrderService receives an INotifier from outside
│          ("dependency injection"). Swap Email / SMS / a fake for tests
│          without touching OrderService.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

// ✘ class OrderService { EmailSender email; ... email.send(...); };

class INotifier {                        // the abstraction
public:
    virtual void notify(const string& msg) = 0;
    virtual ~INotifier() = default;
};

class EmailNotifier : public INotifier {
public:
    void notify(const string& m) override { cout << "Email: " << m << endl; }
};

class SmsNotifier : public INotifier {
public:
    void notify(const string& m) override { cout << "SMS: " << m << endl; }
};

class FakeNotifier : public INotifier {  // for testing
public:
    int calls = 0;
    void notify(const string&) override { calls++; }
};

class OrderService {                     // high-level logic
    INotifier& notifier;

public:
    OrderService(INotifier& n) : notifier(n) {}      // injected
    void placeOrder(int id) {
        notifier.notify("Order #" + to_string(id) + " placed");
    }
};

int main() {

    EmailNotifier email;
    SmsNotifier sms;
    FakeNotifier fake;

    OrderService(email).placeOrder(101);     // Email: Order #101 placed
    OrderService(sms).placeOrder(102);       // SMS: Order #102 placed

    OrderService(fake).placeOrder(103);      // nothing sent
    cout << "fake calls: " << fake.calls << endl;    // fake calls: 1

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  DRY — Don't Repeat Yourself
│  ✔ Definition : Every piece of knowledge / logic should live in ONE
│                 place. Copy-paste means a bug must be fixed in many
│                 places — and one is always forgotten.
│  ✘ Bad : the same GST formula written in 3 functions
│  ✔ Good: one function / constant, used everywhere
│  ⚠ Don't overdo it: two things that only LOOK alike but change for
│    different reasons can stay separate
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

// ✘ double bookPrice(double p)  { return p + p * 0.18; }
//   double phonePrice(double p) { return p + p * 0.18; }
//   double shoePrice(double p)  { return p + p * 0.18; }

constexpr double GST_RATE = 0.18;        // one place

double withGST(double price) {           // one place
    return price * (1 + GST_RATE);
}

int main() {

    cout << withGST(100) << endl;        // 118
    cout << withGST(25000) << endl;      // 29500
    cout << withGST(2500) << endl;       // 2950

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  KISS — Keep It Simple, Stupid
│  ✔ Definition : Choose the SIMPLEST solution that does the job. Code is
│                 read far more often than it is written.
│  ✘ Bad : a "clever" one-liner nobody understands, or 5 classes and a
│          factory to check if a number is even
│  ✔ Good: clear names, small functions, standard library tools
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ✘ bool isEven(int n) { return !(n & 1) ? !!1 : !!0; }   // why?!
bool isEven(int n) { return n % 2 == 0; }                  // ✔ obvious

int main() {

    vector<int> marks = {72, 95, 60, 88};

    // ✘ manual loops with index tricks to find the top mark
    // ✔ simple and clear:
    int best = *max_element(marks.begin(), marks.end());

    cout << best << endl;                // 95
    cout << boolalpha << isEven(best) << endl;   // false

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  YAGNI — You Aren't Gonna Need It
│  ✔ Definition : Don't build features, options or layers "because we
│                 might need them later". Build what is needed NOW;
│                 add more when there's a real need.
│  ✘ Bad : a UserManager with plugins, XML config, 6 export formats ...
│          for an app that only needs to add and list users
│  ✔ Good: the small class below. Easy to extend later — because it is
│          small and clean.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class UserList {                         // just what is needed today
    vector<string> users;

public:
    void add(const string& name) { users.push_back(name); }
    void list() const {
        for (const string& u : users) cout << "- " << u << endl;
    }
};

int main() {

    UserList ul;
    ul.add("Amit");
    ul.add("Neha");
    ul.list();
    // - Amit
    // - Neha

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Composition over inheritance
│  ✔ Definition : To REUSE behaviour, prefer putting it in a separate
│                 object the class HAS, instead of inheriting it.
│  ✘ Bad : FlyingDuck, SwimmingDuck, FlyingSwimmingDuck, RubberDuck ...
│          one subclass for every mix of abilities (class explosion)
│  ✔ Good: Duck HAS a FlyBehaviour. Mix and change at run time.
│  ✔ More detail → 13_ClassRelationships.cpp
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class FlyBehaviour {
public:
    virtual string fly() const = 0;
    virtual ~FlyBehaviour() {}
};

class Wings : public FlyBehaviour {
public:
    string fly() const override { return "flies with wings"; }
};

class CantFly : public FlyBehaviour {
public:
    string fly() const override { return "can't fly"; }
};

class Duck {
    string name;
    unique_ptr<FlyBehaviour> flying;     // HAS-A behaviour

public:
    Duck(string n, unique_ptr<FlyBehaviour> f) : name(n), flying(move(f)) {}
    void show() const { cout << name << " " << flying->fly() << endl; }
    void setFly(unique_ptr<FlyBehaviour> f) { flying = move(f); }
};

int main() {

    Duck mallard("Mallard", make_unique<Wings>());
    Duck rubber("Rubber duck", make_unique<CantFly>());

    mallard.show();                      // Mallard flies with wings
    rubber.show();                       // Rubber duck can't fly

    mallard.setFly(make_unique<CantFly>());   // injured wing
    mallard.show();                      // Mallard can't fly

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Law of Demeter — "talk only to your close friends"
│  ✔ Definition : A method should call methods only on:
│        • its own object (this)        • its own members
│        • its parameters               • objects it creates
│    NOT on objects returned by THEM (strangers).
│  ✘ Bad : order.getCustomer().getWallet().deduct(500);
│          Order now knows the inside of Customer AND Wallet. Change
│          Wallet → Order breaks. ("train wreck" of dots)
│  ✔ Good: order.getCustomer().pay(500)  →  better: customer.pay(500).
│          Each class talks only to its direct neighbour.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Wallet {
    double money = 1000;

public:
    bool deduct(double amt) {
        if (amt > money) return false;
        money -= amt;
        return true;
    }
    double balance() const { return money; }
};

class Customer {
    Wallet wallet;

public:
    bool pay(double amt) { return wallet.deduct(amt); }   // hides Wallet
    double balance() const { return wallet.balance(); }
};

class Order {
    double amount;

public:
    Order(double a) : amount(a) {}

    void checkout(Customer& c) {         // talks only to Customer
        // ✘ c.getWallet().deduct(amount);
        if (c.pay(amount)) cout << "Paid " << amount << endl;
        else cout << "Payment failed" << endl;
    }
};

int main() {

    Customer amit;
    Order(400).checkout(amit);           // Paid 400
    Order(900).checkout(amit);           // Payment failed
    cout << amit.balance() << endl;      // 600

    return 0;
}
