/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                      RELATIONSHIPS BETWEEN CLASSES                        ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Why learn relationships?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Real programs have many classes that WORK TOGETHER
 *  ✔ The question is always: HOW are two classes connected, and who
 *    controls whose LIFE (creation / destruction)?
 *
 *  The 5 relationships  (weakest → strongest)
 *  ────────────────────────────────────────────────────────────────────────────
 *
 *   NAME          MEANING      LIFETIME                   REAL EXAMPLE
 *   ────────────  ───────────  ─────────────────────────  ───────────────────
 *   Dependency    USES-A       only during a function     Printer uses Doc
 *   Association   KNOWS-A      both live independently    Teacher ↔ Student
 *   Aggregation   HAS-A weak   part can live without      Department has
 *                              the whole                  Professors
 *   Composition   HAS-A strong part dies WITH the whole   House has Rooms
 *   Inheritance   IS-A         child is a kind of parent  Car is a Vehicle
 *
 *  UML symbols (for class diagrams)
 *  ────────────────────────────────────────────────────────────────────────────
 *        A - - - - -> B      Dependency    (dashed arrow)
 *        A ─────────> B      Association   (plain line / arrow)
 *        A ◇───────── B      Aggregation   (empty diamond on the whole)
 *        A ◆───────── B      Composition   (filled diamond on the whole)
 *        A ────────▷ B       Inheritance   (empty triangle on the parent)
 *
 *  How it looks in C++ code
 *  ────────────────────────────────────────────────────────────────────────────
 *   Dependency    ─► object is a function PARAMETER or local variable
 *   Association   ─► a POINTER / REFERENCE member to an object you don't own
 *   Aggregation   ─► pointer / reference (or shared_ptr) to a part that is
 *                    created OUTSIDE and passed in
 *   Composition   ─► a plain MEMBER object (or unique_ptr) created INSIDE
 *   Inheritance   ─► class Child : public Parent
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Association                  ─► Doctor ↔ Patient
 *   Aggregation                  ─► Department ◇ Professor
 *   Composition                  ─► House ◆ Room
 *   Aggregation vs Composition   ─► the lifetime test
 *   Dependency                   ─► Printer - - > Document
 *   Multiplicity                 ─► 1-1, 1-many, many-many
 *   Composition over inheritance ─► swap behaviour at run time
 *   Real-life example            ─► small library system
 */


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Association — "knows a"
│  ✔ Definition : Two classes are connected and can talk to each other,
│                 but NEITHER owns the other. Both are created and
│                 destroyed independently.
│  ✔ Can be one-way (A knows B) or two-way (both know each other)
│  ✔ Code: pointer members, NO delete in the destructor
│  ✔ Real life: a Doctor treats many Patients, a Patient visits many
│    Doctors — none of them "owns" the other
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Patient;

class Doctor {
public:
    string name;
    vector<Patient*> patients;           // knows patients, doesn't own

    Doctor(string n) : name(n) {}
    void addPatient(Patient* p);
    void showPatients() const;
};

class Patient {
public:
    string name;
    vector<Doctor*> doctors;             // knows doctors, doesn't own

    Patient(string n) : name(n) {}
};

void Doctor::addPatient(Patient* p) {
    patients.push_back(p);
    p->doctors.push_back(this);          // two-way link
}

void Doctor::showPatients() const {
    cout << "Dr. " << name << ": ";
    for (Patient* p : patients) cout << p->name << " ";
    cout << endl;
}

int main() {

    Doctor d1("Mehta"), d2("Rao");
    Patient p1("Amit"), p2("Neha");

    d1.addPatient(&p1);
    d1.addPatient(&p2);
    d2.addPatient(&p1);

    d1.showPatients();                   // Dr. Mehta: Amit Neha
    d2.showPatients();                   // Dr. Rao: Amit
    cout << p1.name << " sees " << p1.doctors.size() << " doctors" << endl;
    // Amit sees 2 doctors

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Aggregation — weak "has a"
│  ✔ Definition : A whole HAS parts, but the parts are created OUTSIDE and
│                 can live WITHOUT the whole. Destroying the whole does
│                 NOT destroy the parts.
│  ✔ Code: the whole stores pointers / references to parts passed in;
│    its destructor does NOT delete them
│  ✔ Real life: a Department has Professors. Close the department — the
│    professors still exist and can join another one.
│
│        Department ◇──────── Professor
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Professor {
public:
    string name;
    Professor(string n) : name(n) {}
    ~Professor() { cout << "Professor " << name << " gone" << endl; }
};

class Department {
    string title;
    vector<Professor*> staff;            // not owned

public:
    Department(string t) : title(t) {}
    void hire(Professor* p) { staff.push_back(p); }
    void show() const {
        cout << title << ": ";
        for (Professor* p : staff) cout << p->name << " ";
        cout << endl;
    }
    ~Department() { cout << "Department " << title << " closed" << endl; }
};

int main() {

    Professor a("Sharma"), b("Iyer");    // created outside

    {
        Department cs("CS");
        cs.hire(&a);
        cs.hire(&b);
        cs.show();                       // CS: Sharma Iyer
    }                                    // Department CS closed

    cout << a.name << " still here" << endl;   // Sharma still here

    return 0;
    // Professor Iyer gone
    // Professor Sharma gone
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Composition — strong "has a"
│  ✔ Definition : A whole is MADE OF parts it creates and OWNS. The parts
│                 can NOT exist without the whole — when the whole dies,
│                 its parts die with it.
│  ✔ Code: plain member objects (or unique_ptr). They are built when the
│    whole is built and destroyed automatically with it.
│  ✔ Real life: a House has Rooms. Demolish the house → the rooms are
│    gone too. A Car has an Engine built into it.
│
│        House ◆──────── Room
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Room {
    string name;

public:
    Room(string n) : name(n) { cout << "  Room " << name << " built" << endl; }
    ~Room() { cout << "  Room " << name << " destroyed" << endl; }
};

class House {
    string owner;
    vector<Room> rooms;                  // owned parts

public:
    House(string o) : owner(o) {
        cout << "House of " << owner << ":" << endl;
        rooms.reserve(2);
        rooms.emplace_back("Kitchen");   // created INSIDE the house
        rooms.emplace_back("Bedroom");
    }

    ~House() { cout << "Demolishing house of " << owner << endl; }
};

int main() {

    {
        House h("Amit");
        // House of Amit:
        //   Room Kitchen built
        //   Room Bedroom built
    }
    // Demolishing house of Amit
    //   Room Kitchen destroyed
    //   Room Bedroom destroyed

    cout << "rooms can't outlive the house" << endl;
    // rooms can't outlive the house

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Aggregation vs Composition — the lifetime test
│  ✔ Ask: "If the WHOLE is destroyed, is the PART destroyed too?"
│        YES → Composition       NO → Aggregation
│
│   POINT            AGGREGATION                 COMPOSITION
│   ───────────────  ──────────────────────────  ──────────────────────────
│   Ownership        no                          yes
│   Part created     outside, passed in          inside the whole
│   Part shared?     can be shared               belongs to ONE whole
│   Whole dies       part survives               part dies too
│   C++ member       T* / T& / shared_ptr<T>     T  or  unique_ptr<T>
│   Example          Playlist ◇ Song             Song ◆ Lyrics
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

struct Song {
    string title;
    Song(string t) : title(t) {}
    ~Song() { cout << "Song " << title << " removed from library" << endl; }
};

class Playlist {                         // aggregation: shares songs
    string name;
    vector<shared_ptr<Song>> songs;

public:
    Playlist(string n) : name(n) {}
    void add(shared_ptr<Song> s) { songs.push_back(s); }
    ~Playlist() { cout << "Playlist " << name << " deleted" << endl; }
};

int main() {

    auto s1 = make_shared<Song>("Kesariya");
    auto s2 = make_shared<Song>("Tum Hi Ho");

    {
        Playlist gym("Gym"), chill("Chill");
        gym.add(s1);
        chill.add(s1);                   // same song in 2 playlists
        chill.add(s2);
    }
    // Playlist Chill deleted
    // Playlist Gym deleted            (songs are still alive)

    cout << s1->title << " still in library" << endl;
    // Kesariya still in library

    return 0;
    // Song Tum Hi Ho removed from library
    // Song Kesariya removed from library
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Dependency — "uses a"
│  ✔ Definition : The weakest link. One class USES another only inside a
│                 function (as a parameter or a local object). It doesn't
│                 store it as a member.
│  ✔ If Document changes, Printer may need changes — that's the
│    "dependency"
│  ✔ Real life: a Printer uses a Document only while printing it
│
│        Printer - - - - -> Document
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Document {
public:
    string title;
    int pages;
};

class Printer {
public:
    void print(const Document& doc) {    // used only here
        cout << "Printing '" << doc.title << "' (" << doc.pages
             << " pages)" << endl;
    }
};

int main() {

    Printer hp;
    Document resume{"Resume", 2}, report{"Report", 15};

    hp.print(resume);                    // Printing 'Resume' (2 pages)
    hp.print(report);                    // Printing 'Report' (15 pages)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Multiplicity — how MANY objects on each side
│
│   TYPE          EXAMPLE                     C++ MEMBER
│   ────────────  ──────────────────────────  ──────────────────────────
│   one-to-one    Person ── Passport          Passport passport;
│   one-to-many   Customer ── Orders          vector<Order> orders;
│   many-to-many  Students ── Courses         vector<Course*> in each,
│                                             or a separate Enrollment
│
│  ✔ In UML it's written on the line ends:  1, 0..1, *, 1..*
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Passport { string number; };

struct Person {                          // 1 person → 1 passport
    string name;
    Passport passport;
};

struct Order { int id; double amount; };

struct Customer {                        // 1 customer → many orders
    string name;
    vector<Order> orders;

    double totalSpent() const {
        double t = 0;
        for (const Order& o : orders) t += o.amount;
        return t;
    }
};

struct Course;
struct Student {                         // many students ↔ many courses
    string name;
    vector<Course*> courses;
};
struct Course {
    string title;
    vector<Student*> students;
};

void enroll(Student& s, Course& c) {
    s.courses.push_back(&c);
    c.students.push_back(&s);
}

int main() {

    Person p{"Amit", {"K1234567"}};
    cout << p.name << " -> " << p.passport.number << endl;
    // Amit -> K1234567

    Customer c{"Neha", {{1, 499}, {2, 1299}, {3, 250}}};
    cout << c.name << " spent " << c.totalSpent() << endl;
    // Neha spent 2048

    Student s1{"Ravi"}, s2{"Sara"};
    Course dsa{"DSA"}, os{"OS"};
    enroll(s1, dsa);
    enroll(s1, os);
    enroll(s2, dsa);
    cout << dsa.title << " has " << dsa.students.size() << " students, "
         << s1.name << " takes " << s1.courses.size() << " courses" << endl;
    // DSA has 2 students, Ravi takes 2 courses

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Composition over inheritance
│  ✔ Problem with inheritance for behaviour: ElectricCar, PetrolCar,
│    HybridCar, ElectricTruck, PetrolTruck ... → class explosion, and a
│    car can't CHANGE its engine at run time
│  ✔ Composition: a Car HAS an Engine (an interface). Plug in any
│    engine, even swap it later. Fewer classes, more flexible.
│  ✔ Rule of thumb: inherit for a true IS-A with shared interface;
│    otherwise compose ("prefer HAS-A over IS-A")
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Engine {                           // interface
public:
    virtual string start() const = 0;
    virtual ~Engine() {}
};

class PetrolEngine : public Engine {
public:
    string start() const override { return "Vroom (petrol)"; }
};

class ElectricEngine : public Engine {
public:
    string start() const override { return "Hmmm (electric)"; }
};

class Car {
    string model;
    unique_ptr<Engine> engine;           // HAS-A, owned

public:
    Car(string m, unique_ptr<Engine> e) : model(m), engine(move(e)) {}

    void drive() const { cout << model << ": " << engine->start() << endl; }

    void swapEngine(unique_ptr<Engine> e) { engine = move(e); }
};

int main() {

    Car nexon("Nexon", make_unique<PetrolEngine>());
    nexon.drive();                       // Nexon: Vroom (petrol)

    nexon.swapEngine(make_unique<ElectricEngine>());     // at run time!
    nexon.drive();                       // Nexon: Hmmm (electric)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Real-life example — a small library system using ALL relationships
│  ✔ Library ◆ Shelf       composition (shelves are part of the library)
│  ✔ Shelf   ◇ Book        aggregation (books exist on their own)
│  ✔ Member ── Book        association (member borrows a book)
│  ✔ Librarian - - > Member dependency (only used inside issue())
│  ✔ Librarian IS-A Person inheritance
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Book {
    string title;
    bool issued = false;
};

class Shelf {
    string label;
    vector<Book*> books;                 // aggregation

public:
    Shelf(string l) : label(l) {}
    void put(Book* b) { books.push_back(b); }
    void list() const {
        cout << "Shelf " << label << ": ";
        for (Book* b : books)
            cout << b->title << (b->issued ? "(out) " : " ");
        cout << endl;
    }
};

class Library {
    vector<Shelf> shelves;               // composition

public:
    Library() { shelves.emplace_back("A"); shelves.emplace_back("B"); }
    Shelf& shelf(int i) { return shelves[i]; }
};

class Person {
public:
    string name;
    Person(string n) : name(n) {}
};

class Member : public Person {
public:
    Book* borrowed = nullptr;            // association
    using Person::Person;
};

class Librarian : public Person {        // inheritance
public:
    using Person::Person;

    void issue(Member& m, Book& b) {     // dependency on Member
        if (b.issued) { cout << b.title << " already issued" << endl; return; }
        b.issued = true;
        m.borrowed = &b;
        cout << name << " issued " << b.title << " to " << m.name << endl;
    }
};

int main() {

    Book b1{"Godan"}, b2{"Gitanjali"};
    Library lib;
    lib.shelf(0).put(&b1);
    lib.shelf(1).put(&b2);

    Librarian lily("Lily");
    Member amit("Amit"), neha("Neha");

    lily.issue(amit, b1);                // Lily issued Godan to Amit
    lily.issue(neha, b1);                // Godan already issued

    lib.shelf(0).list();                 // Shelf A: Godan(out)
    lib.shelf(1).list();                 // Shelf B: Gitanjali

    return 0;
}
