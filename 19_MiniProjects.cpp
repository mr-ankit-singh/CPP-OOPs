/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                  PRACTICAL IMPLEMENTATION / DESIGN                        ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Goal of this file
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Put EVERYTHING together: classes, the 4 pillars, relationships,
 *    smart pointers, exceptions and design principles
 *  ✔ Learn to go from a PROBLEM STATEMENT to CLASSES
 *
 *  How to design classes from a problem (step by step)
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ 1. Read the problem, underline the NOUNS     → candidate classes
 *        "A library has books. Members borrow books."
 *        → Library, Book, Member
 *  ✔ 2. Underline the VERBS                       → member functions
 *        borrow(), returnBook(), search()
 *  ✔ 3. Find the DATA each class owns             → private members
 *  ✔ 4. Find relationships: IS-A? HAS-A? USES-A?  → inheritance /
 *        composition / dependency
 *  ✔ 5. Find what VARIES                          → interface + virtual
 *  ✔ 6. Keep each class to ONE job (SRP), hide data (encapsulation)
 *
 *  UML class diagram — basic understanding
 *  ────────────────────────────────────────────────────────────────────────────
 *        ┌──────────────────────────┐
 *        │       BankAccount        │   ← class name
 *        ├──────────────────────────┤
 *        │ - accountNo : string     │   ← attributes
 *        │ - balance   : double     │
 *        ├──────────────────────────┤
 *        │ + deposit(amt) : void    │   ← methods
 *        │ + getBalance() : double  │
 *        │ # applyFee()   : void    │
 *        └──────────────────────────┘
 *
 *        +  public      -  private      #  protected
 *        italic / {abstract} → abstract class or pure virtual method
 *
 *        Arrows:  ──▷ inheritance   ◆── composition   ◇── aggregation
 *                 ──> association   - -> dependency
 *
 *  Modular OOP design
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ One class per pair of files:  Account.h  +  Account.cpp
 *  ✔ Group related classes in folders / namespaces (bank::Account)
 *  ✔ Classes talk through small PUBLIC interfaces
 *  ✔ main.cpp only wires objects together
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   All 4 pillars together       ─► smart home devices
 *   Project 1: Student Management System
 *   Project 2: Banking System
 *   Project 3: Employee Record System
 *   Project 4: Shape / Geometry Hierarchy
 *   Project 5: Library Management System
 *   Project 6: Parking Lot  (LLD interview favourite)
 *   Common OOP mistakes          ─► what NOT to do
 *   Best OOP practices in C++    ─► checklist
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Applying all four OOP pillars together — smart home
│  ✔ Abstraction    → Device says WHAT every device can do
│  ✔ Encapsulation  → each device hides its own state (on, brightness)
│  ✔ Inheritance    → Light, AC, Fan are Devices
│  ✔ Polymorphism   → Home turns everything off with ONE loop
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class Device {                                       // abstraction
protected:
    string room;
    bool on = false;                                 // encapsulation

public:
    Device(string r) : room(r) {}
    virtual void turnOn() { on = true; }
    virtual void turnOff() { on = false; }
    virtual string status() const = 0;
    virtual ~Device() {}
};

class Light : public Device {                        // inheritance
    int brightness = 70;

public:
    using Device::Device;
    string status() const override {
        return room + " light " + (on ? to_string(brightness) + "%" : "off");
    }
};

class AC : public Device {
    int temp = 24;

public:
    using Device::Device;
    void setTemp(int t) { if (t >= 16 && t <= 30) temp = t; }
    string status() const override {
        return room + " AC " + (on ? to_string(temp) + "C" : "off");
    }
};

class Home {
    vector<unique_ptr<Device>> devices;

public:
    void add(unique_ptr<Device> d) { devices.push_back(move(d)); }
    void allOn() { for (auto& d : devices) d->turnOn(); }
    void allOff() { for (auto& d : devices) d->turnOff(); }   // polymorphism
    void report() const {
        for (const auto& d : devices) cout << "  " << d->status() << endl;
    }
};

int main() {

    Home home;
    home.add(make_unique<Light>("Hall"));
    auto ac = make_unique<AC>("Bedroom");
    ac->setTemp(22);
    home.add(move(ac));

    home.allOn();
    home.report();
    //   Hall light 70%
    //   Bedroom AC 22C

    home.allOff();
    home.report();
    //   Hall light off
    //   Bedroom AC off

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Project 1: Student Management System
│  ✔ Features : add student, add marks, find by roll no, topper,
│               class average, remove student
│  ✔ Design   : Student (data + grade logic)  ◇──  StudentManager
│               (stores and searches)
│  ✔ Uses     : encapsulation, const getters, vector, find_if, optional
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <optional>
using namespace std;

class Student {
    int roll;
    string name;
    vector<int> marks;

public:
    Student(int r, string n) : roll(r), name(n) {}

    void addMark(int m) { if (m >= 0 && m <= 100) marks.push_back(m); }

    double average() const {
        if (marks.empty()) return 0;
        int sum = 0;
        for (int m : marks) sum += m;
        return (double)sum / marks.size();
    }

    char grade() const {
        double a = average();
        return a >= 90 ? 'A' : a >= 75 ? 'B' : a >= 50 ? 'C' : 'F';
    }

    int getRoll() const { return roll; }
    string getName() const { return name; }
};

class StudentManager {
    vector<Student> students;

public:
    Student& add(int roll, string name) {
        students.emplace_back(roll, name);
        return students.back();
    }

    optional<Student> find(int roll) const {
        auto same = [roll](const Student& s) { return s.getRoll() == roll; };
        auto it = find_if(students.begin(), students.end(), same);
        if (it == students.end()) return nullopt;
        return *it;
    }

    bool remove(int roll) {
        auto same = [roll](const Student& s) { return s.getRoll() == roll; };
        auto it = remove_if(students.begin(), students.end(), same);
        if (it == students.end()) return false;
        students.erase(it, students.end());
        return true;
    }

    void report() const {
        for (const Student& s : students)
            cout << s.getRoll() << " " << s.getName() << " avg "
                 << s.average() << " grade " << s.grade() << endl;
    }

    void topper() const {
        auto best = max_element(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.average() < b.average();
            });
        if (best != students.end())
            cout << "Topper: " << best->getName() << endl;
    }
};

int main() {

    StudentManager sm;

    Student& a = sm.add(1, "Amit");
    a.addMark(80); a.addMark(90);
    Student& n = sm.add(2, "Neha");
    n.addMark(95); n.addMark(98);
    Student& r = sm.add(3, "Ravi");
    r.addMark(40); r.addMark(55);

    sm.report();
    // 1 Amit avg 85 grade B
    // 2 Neha avg 96.5 grade A
    // 3 Ravi avg 47.5 grade F

    sm.topper();                                 // Topper: Neha

    if (auto s = sm.find(3)) cout << "Found " << s->getName() << endl;
    // Found Ravi

    sm.remove(3);
    cout << boolalpha << sm.find(3).has_value() << endl;    // false

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Project 2: Banking System
│  ✔ Features : savings / current accounts, deposit, withdraw, transfer,
│               monthly interest, transaction history, errors
│  ✔ Design   : Account (abstract) ──▷ Savings, Current
│               Bank ◆── accounts (unique_ptr)
│               InsufficientFunds exception
│  ✔ Rules    : Savings keeps min balance 1000 and earns 4%;
│               Current allows an overdraft of 5000
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class InsufficientFunds : public runtime_error {
public:
    using runtime_error::runtime_error;
};

class Account {
protected:
    string number, owner;
    double balance = 0;
    vector<string> history;

    virtual double withdrawLimit() const = 0;        // what varies

public:
    Account(string no, string ow) : number(no), owner(ow) {}

    void deposit(double amt) {
        if (amt <= 0) throw invalid_argument("Deposit must be > 0");
        balance += amt;
        history.push_back("+" + to_string((int)amt));
    }

    void withdraw(double amt) {
        if (amt > withdrawLimit())
            throw InsufficientFunds(owner + ": can withdraw at most " +
                                    to_string((int)withdrawLimit()));
        balance -= amt;
        history.push_back("-" + to_string((int)amt));
    }

    virtual void monthEnd() {}
    double getBalance() const { return balance; }

    void statement() const {
        cout << owner << " (" << number << "): ";
        for (const string& h : history) cout << h << " ";
        cout << "= " << balance << endl;
    }

    virtual ~Account() {}
};

class Savings : public Account {
    double withdrawLimit() const override { return balance - 1000; }

public:
    using Account::Account;
    void monthEnd() override {
        double interest = balance * 0.04 / 12;
        balance += interest;
        history.push_back("+int" + to_string((int)interest));
    }
};

class Current : public Account {
    double withdrawLimit() const override { return balance + 5000; }

public:
    using Account::Account;
};

class Bank {
    map<string, unique_ptr<Account>> accounts;

public:
    Account& open(unique_ptr<Account> acc, const string& no) {
        Account& ref = *acc;
        accounts[no] = move(acc);
        return ref;
    }

    void transfer(const string& from, const string& to, double amt) {
        accounts.at(from)->withdraw(amt);            // may throw
        accounts.at(to)->deposit(amt);
    }

    void monthEnd() { for (auto& [no, a] : accounts) a->monthEnd(); }
    void statements() const {
        for (const auto& [no, a] : accounts) a->statement();
    }
};

int main() {

    Bank bank;
    Account& amit = bank.open(make_unique<Savings>("S1", "Amit"), "S1");
    Account& shop = bank.open(make_unique<Current>("C1", "Shop"), "C1");

    amit.deposit(12000);
    shop.deposit(2000);
    bank.transfer("S1", "C1", 3000);

    try {
        amit.withdraw(9000);                         // would go below 1000
    } catch (const InsufficientFunds& e) {
        cout << e.what() << endl;    // Amit: can withdraw at most 8000
    }

    shop.withdraw(8000);                             // overdraft allowed
    bank.monthEnd();
    bank.statements();
    // Shop (C1): +2000 +3000 -8000 = -3000
    // Amit (S1): +12000 -3000 +int30 = 9030

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Project 3: Employee Record System
│  ✔ Features : different employee types with their own pay rules,
│               payroll, search by department, raise salaries
│  ✔ Design   : Employee (abstract, salary() pure virtual)
│               ──▷ FullTime, Intern, Contractor
│               static counter for auto employee IDs
│  ✔ Uses     : constructors, static members, virtual, unique_ptr
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Employee {
    inline static int nextId = 1;

protected:
    int id;
    string name, dept;

public:
    Employee(string n, string d) : id(nextId++), name(n), dept(d) {}

    virtual double salary() const = 0;
    virtual string type() const = 0;
    virtual void raise(double pct) = 0;

    string getDept() const { return dept; }

    void print() const {
        cout << "#" << id << " " << name << " [" << type() << ", " << dept
             << "] Rs." << salary() << endl;
    }

    virtual ~Employee() {}
};

class FullTime : public Employee {
    double monthly;

public:
    FullTime(string n, string d, double m) : Employee(n, d), monthly(m) {}
    double salary() const override { return monthly; }
    string type() const override { return "Full-time"; }
    void raise(double pct) override { monthly *= 1 + pct / 100; }
};

class Intern : public Employee {
    double stipend;

public:
    Intern(string n, string d, double s) : Employee(n, d), stipend(s) {}
    double salary() const override { return stipend; }
    string type() const override { return "Intern"; }
    void raise(double) override {}               // fixed stipend
};

class Contractor : public Employee {
    double rate;
    int hours;

public:
    Contractor(string n, string d, double r, int h)
        : Employee(n, d), rate(r), hours(h) {}
    double salary() const override { return rate * hours; }
    string type() const override { return "Contractor"; }
    void raise(double pct) override { rate *= 1 + pct / 100; }
};

int main() {

    vector<unique_ptr<Employee>> staff;
    staff.push_back(make_unique<FullTime>("Neha", "IT", 80000));
    staff.push_back(make_unique<Intern>("Ravi", "IT", 15000));
    staff.push_back(make_unique<Contractor>("Sara", "Design", 600, 100));

    double payroll = 0;
    for (const auto& e : staff) { e->print(); payroll += e->salary(); }
    // #1 Neha [Full-time, IT] Rs.80000
    // #2 Ravi [Intern, IT] Rs.15000
    // #3 Sara [Contractor, Design] Rs.60000
    cout << "Payroll: " << payroll << endl;          // Payroll: 155000

    for (auto& e : staff)
        if (e->getDept() == "IT") e->raise(10);      // raise for IT only
    staff[0]->print();               // #1 Neha [Full-time, IT] Rs.88000
    staff[1]->print();               // #2 Ravi [Intern, IT] Rs.15000

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Project 4: Shape / Geometry Hierarchy
│  ✔ Features : many shapes, area + perimeter, sort by area, total area,
│               print with <<, find the largest
│  ✔ Design   : Shape (abstract) ──▷ Circle, Rectangle ──▷ Square,
│               Triangle
│  ✔ Uses     : pure virtual, override, operator<<, sort with a lambda,
│               constructor validation with exceptions
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual string name() const = 0;
    virtual ~Shape() {}

    friend ostream& operator<<(ostream& out, const Shape& s) {
        return out << s.name() << " area=" << s.area()
                   << " perimeter=" << s.perimeter();
    }
};

class Circle : public Shape {
    double r;

public:
    Circle(double radius) : r(radius) {
        if (r <= 0) throw invalid_argument("radius must be > 0");
    }
    double area() const override { return 3.14 * r * r; }
    double perimeter() const override { return 2 * 3.14 * r; }
    string name() const override { return "Circle"; }
};

class Rectangle : public Shape {
protected:
    double w, h;

public:
    Rectangle(double a, double b) : w(a), h(b) {}
    double area() const override { return w * h; }
    double perimeter() const override { return 2 * (w + h); }
    string name() const override { return "Rectangle"; }
};

class Square : public Rectangle {
public:
    Square(double s) : Rectangle(s, s) {}
    string name() const override { return "Square"; }
};

class Triangle : public Shape {
    double a, b, c;

public:
    Triangle(double x, double y, double z) : a(x), b(y), c(z) {
        if (a + b <= c || a + c <= b || b + c <= a)
            throw invalid_argument("not a valid triangle");
    }
    double perimeter() const override { return a + b + c; }
    double area() const override {
        double s = perimeter() / 2;                  // Heron's formula
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    string name() const override { return "Triangle"; }
};

int main() {

    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Rectangle>(4, 5));
    shapes.push_back(make_unique<Circle>(1));
    shapes.push_back(make_unique<Square>(3));
    shapes.push_back(make_unique<Triangle>(3, 4, 5));

    sort(shapes.begin(), shapes.end(),
         [](const auto& x, const auto& y) { return x->area() < y->area(); });

    for (const auto& s : shapes) cout << *s << endl;
    // Circle area=3.14 perimeter=6.28
    // Triangle area=6 perimeter=12
    // Square area=9 perimeter=12
    // Rectangle area=20 perimeter=18

    try {
        Triangle bad(1, 2, 10);
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;   // Error: not a valid triangle
    }

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Project 5: Library Management System
│  ✔ Features : add books, register members, issue / return, max 2 books
│               per member, fine for late return, search by author
│  ✔ Design   : Book, Member (associations by ISBN / id)
│               Library ◆── books, members (owns them)
│               LibraryError exception
│  ✔ Uses     : map, encapsulation, exceptions, const-correctness
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stdexcept>
using namespace std;

class LibraryError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

struct Book {
    string isbn, title, author;
    bool issued = false;
};

class Member {
    int id;
    string name;
    set<string> borrowed;

public:
    static const int MAX_BOOKS = 2;

    Member(int i = 0, string n = "") : id(i), name(n) {}
    bool canBorrow() const { return (int)borrowed.size() < MAX_BOOKS; }
    void take(const string& isbn) { borrowed.insert(isbn); }
    bool give(const string& isbn) { return borrowed.erase(isbn) > 0; }
    string getName() const { return name; }
};

class Library {
    map<string, Book> books;
    map<int, Member> members;
    static constexpr int FINE_PER_DAY = 5;
    static constexpr int FREE_DAYS = 14;

public:
    void addBook(Book b) { books[b.isbn] = b; }
    void addMember(int id, string name) { members[id] = Member(id, name); }

    void issue(int memberId, const string& isbn) {
        Member& m = members.at(memberId);
        Book& b = books.at(isbn);
        if (b.issued) throw LibraryError(b.title + " is already issued");
        if (!m.canBorrow()) throw LibraryError(m.getName() + " has 2 books");
        b.issued = true;
        m.take(isbn);
        cout << m.getName() << " took " << b.title << endl;
    }

    int giveBack(int memberId, const string& isbn, int daysKept) {
        Member& m = members.at(memberId);
        if (!m.give(isbn)) throw LibraryError("book not with this member");
        books.at(isbn).issued = false;
        int fine = max(0, daysKept - FREE_DAYS) * FINE_PER_DAY;
        cout << m.getName() << " returned " << books.at(isbn).title
             << ", fine Rs." << fine << endl;
        return fine;
    }

    void byAuthor(const string& author) const {
        for (const auto& [isbn, b] : books)
            if (b.author == author)
                cout << "  " << b.title << (b.issued ? " (issued)" : "")
                     << endl;
    }
};

int main() {

    Library lib;
    lib.addBook({"111", "Godan", "Premchand"});
    lib.addBook({"222", "Nirmala", "Premchand"});
    lib.addBook({"333", "Gitanjali", "Tagore"});
    lib.addMember(1, "Amit");
    lib.addMember(2, "Neha");

    lib.issue(1, "111");                         // Amit took Godan
    lib.issue(1, "333");                         // Amit took Gitanjali

    try { lib.issue(1, "222"); }
    catch (const LibraryError& e) { cout << e.what() << endl; }
    // Amit has 2 books

    try { lib.issue(2, "111"); }
    catch (const LibraryError& e) { cout << e.what() << endl; }
    // Godan is already issued

    lib.giveBack(1, "111", 20);          // Amit returned Godan, fine Rs.30

    lib.byAuthor("Premchand");
    //   Godan
    //   Nirmala

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Project 6: Parking Lot  (Low-Level Design interview favourite)
│  ✔ Requirements:
│        • spots of 3 sizes: Bike, Car, Large
│        • a vehicle parks in the smallest spot that fits it
│        • a ticket is given at entry; fee at exit by hours and vehicle
│        • show free spots
│  ✔ Design:
│        Vehicle (abstract) ──▷ Bike, Car, Truck     (size + rate)
│        ParkingSpot        (id, size, who is parked)
│        Ticket             (spot, vehicle, entry hour)
│        ParkingLot ◆── spots, issues tickets  (Singleton in real apps)
│  ✔ Uses: enum class, abstract class, composition, optional,
│          unique_ptr, map, exceptions
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

enum class Size { Bike = 0, Car = 1, Large = 2 };

class Vehicle {
    string plate;

public:
    Vehicle(string p) : plate(p) {}
    virtual Size size() const = 0;
    virtual int ratePerHour() const = 0;
    string getPlate() const { return plate; }
    virtual ~Vehicle() {}
};

class Bike : public Vehicle {
public:
    using Vehicle::Vehicle;
    Size size() const override { return Size::Bike; }
    int ratePerHour() const override { return 10; }
};

class Car : public Vehicle {
public:
    using Vehicle::Vehicle;
    Size size() const override { return Size::Car; }
    int ratePerHour() const override { return 30; }
};

class Truck : public Vehicle {
public:
    using Vehicle::Vehicle;
    Size size() const override { return Size::Large; }
    int ratePerHour() const override { return 80; }
};

struct ParkingSpot {
    int id;
    Size size;
    unique_ptr<Vehicle> vehicle;         // the spot holds the parked car
    bool isFree() const { return vehicle == nullptr; }
};

struct Ticket {
    int number, spotId, entryHour;
};

class ParkingLot {
    vector<ParkingSpot> spots;
    map<int, Ticket> active;
    int nextTicket = 1;

    void addSpot(int id, Size s) { spots.push_back({id, s, nullptr}); }

    optional<size_t> findSpot(Size need) const {
        for (size_t i = 0; i < spots.size(); i++)        // smallest first
            if (spots[i].isFree() && spots[i].size >= need) return i;
        return nullopt;
    }

public:
    ParkingLot(int bikes, int cars, int large) {
        int id = 1;
        for (int i = 0; i < bikes; i++) addSpot(id++, Size::Bike);
        for (int i = 0; i < cars; i++) addSpot(id++, Size::Car);
        for (int i = 0; i < large; i++) addSpot(id++, Size::Large);
    }

    Ticket park(unique_ptr<Vehicle> v, int hour) {
        auto idx = findSpot(v->size());
        if (!idx) throw runtime_error("No spot for " + v->getPlate());
        ParkingSpot& s = spots[*idx];
        cout << v->getPlate() << " parked at spot " << s.id << endl;
        s.vehicle = move(v);
        Ticket t{nextTicket++, s.id, hour};
        active[t.number] = t;
        return t;
    }

    int leave(int ticketNo, int hour) {
        Ticket t = active.at(ticketNo);
        ParkingSpot& s = spots[t.spotId - 1];
        int hours = max(1, hour - t.entryHour);
        int fee = hours * s.vehicle->ratePerHour();
        cout << s.vehicle->getPlate() << " left after " << hours
             << "h, fee Rs." << fee << endl;
        s.vehicle.reset();
        active.erase(ticketNo);
        return fee;
    }

    void freeSpots() const {
        int count[3] = {0, 0, 0};
        for (const auto& s : spots)
            if (s.isFree()) count[(int)s.size]++;
        cout << "Free -> bike:" << count[0] << " car:" << count[1]
             << " large:" << count[2] << endl;
    }
};

int main() {

    ParkingLot lot(1, 2, 1);
    lot.freeSpots();                             // Free -> bike:1 car:2 large:1

    Ticket t1 = lot.park(make_unique<Car>("MH12-1111"), 9);
    // MH12-1111 parked at spot 2
    Ticket t2 = lot.park(make_unique<Bike>("MH12-2222"), 9);
    // MH12-2222 parked at spot 1
    lot.park(make_unique<Bike>("MH12-3333"), 10);
    // MH12-3333 parked at spot 3       (bike spot full → car spot)
    lot.park(make_unique<Truck>("GJ01-9999"), 10);
    // GJ01-9999 parked at spot 4

    try {
        lot.park(make_unique<Car>("DL01-5555"), 11);
    } catch (const exception& e) {
        cout << e.what() << endl;                // No spot for DL01-5555
    }

    lot.leave(t1.number, 12);            // MH12-1111 left after 3h, fee Rs.90
    lot.leave(t2.number, 9);             // MH12-2222 left after 1h, fee Rs.10
    lot.freeSpots();                             // Free -> bike:1 car:1 large:0

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Common OOP mistakes  (and the fix)
│
│   MISTAKE                                  FIX
│   ───────────────────────────────────────  ──────────────────────────────
│   public data everywhere                   private data + methods
│   getter + setter for EVERY field          give meaningful methods only
│   no virtual destructor in a base class    virtual ~Base() {}
│   forgetting "override"                    always write override
│   inheriting just to reuse code (no IS-A)  composition (HAS-A)
│   deep inheritance chains (5+ levels)      flatter design + interfaces
│   "God class" doing everything             split by responsibility (SRP)
│   raw new / delete                         unique_ptr / containers
│   passing objects by value (slicing)       const T& / pointers
│   virtual call in constructor              call after construction
│   Rule of 3/5 broken (raw pointer member)  Rule of 0 with smart ptrs
│   if-else on type names                    virtual functions (OCP)
│
│  ✔ The program below shows 3 of these bugs fixed side by side
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Animal {
public:
    virtual string sound() const { return "..."; }
    virtual ~Animal() = default;                 // ✔ virtual destructor
};

class Dog : public Animal {
public:
    string sound() const override { return "Woof"; }   // ✔ override
};

void speakCopy(Animal a) { cout << a.sound() << endl; }        // ✘ slices
void speakRef(const Animal& a) { cout << a.sound() << endl; }  // ✔

int main() {

    Dog d;
    speakCopy(d);                        // ...    (sliced — bug)
    speakRef(d);                         // Woof   (correct)

    unique_ptr<Animal> pet = make_unique<Dog>();   // ✔ no raw new/delete
    cout << pet->sound() << endl;        // Woof

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Best OOP practices in C++  (checklist)
│  ✔ Classes
│        • one job per class; small public interface
│        • data private; functions const when they don't change data
│        • initialize every member (in-class initializers / init list)
│        • mark one-argument constructors explicit
│  ✔ Inheritance & polymorphism
│        • public inheritance only for a true IS-A
│        • base classes: virtual destructor, use override / final
│        • prefer composition for reuse; interfaces for flexibility
│  ✔ Resources
│        • RAII everywhere; Rule of 0 (smart pointers, containers)
│        • unique_ptr by default, shared_ptr only for real sharing
│  ✔ Errors
│        • throw exceptions from constructors when the object is invalid
│        • catch by const reference; never throw from destructors
│  ✔ Design
│        • follow SOLID, DRY, KISS, YAGNI
│        • use a design pattern only for the problem it solves
│
│  ✔ Below: a small class that follows ALL of the class-level rules
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Temperature final {                // not meant to be a base
    double celsius = 0;                  // private, initialized

public:
    explicit Temperature(double c) : celsius(c) {        // explicit
        if (c < -273.15) throw invalid_argument("below absolute zero");
    }

    double inCelsius() const { return celsius; }         // const getters
    double inFahrenheit() const { return celsius * 9 / 5 + 32; }

    void warmBy(double d) {              // meaningful method, not setX()
        if (d < 0) throw invalid_argument("use coolBy()");
        celsius += d;
    }
};                                       // Rule of 0: nothing else needed

int main() {

    Temperature t(25);
    t.warmBy(5);
    cout << t.inCelsius() << " C = " << t.inFahrenheit() << " F" << endl;
    // 30 C = 86 F

    try {
        Temperature bad(-300);
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;   // Error: below absolute zero
    }

    return 0;
}
