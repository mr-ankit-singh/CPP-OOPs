/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                             CLASS AND OBJECT                              ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is a Class?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ A class is a USER-DEFINED data type
 *  ✔ It groups data members (variables) and member functions together
 *  ✔ In C++, almost everything in OOP is built from classes and objects
 *  ✔ Attributes (variables) and methods (functions) that belong to a class
 *    are called CLASS MEMBERS
 *
 *  What is an Object?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ An object is an INSTANCE of a class
 *  ✔ It stores real data and can call the class's functions
 *  ✔ Memory for data members is given only when an object is created
 *
 *  Syntax
 *  ────────────────────────────────────────────────────────────────────────────
 *        class ClassName {
 *        AccessSpecifier:              // public / private / protected
 *            data_members;             // variables
 *            member_functions();       // functions
 *        };                            // ⚠ semicolon is required
 *
 *        ClassName objectName;         // create an object
 *        objectName.member;            // use a member with dot (.)
 *
 *  Memory picture
 *  ────────────────────────────────────────────────────────────────────────────
 *        Car c1;  c1.brand = "BMW";  c1.year = 2020;
 *        Car c2;  c2.brand = "Audi"; c2.year = 2023;
 *
 *          c1                       c2
 *        ┌──────────────────┐     ┌──────────────────┐
 *        │ brand : "BMW"    │     │ brand : "Audi"   │   ← each object has
 *        │ year  : 2020     │     │ year  : 2023     │     its OWN data
 *        └──────────────────┘     └──────────────────┘
 *                  │                       │
 *                  └───────────┬───────────┘
 *                              ▼
 *                    honk()  (ONE copy of the code, shared by all)
 *
 *  ✔ Data is per object. Member functions are stored once for the class.
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   BASICS
 *   ──────
 *   Defining a class           ─► class Car { ... };
 *   Creating objects           ─► Car c;  Car* p = new Car;
 *   class vs struct            ─► only the default access is different
 *   Access specifiers          ─► public / private / protected
 *
 *   MEMBER FUNCTIONS
 *   ────────────────
 *   Inside the class           ─► body written inside { }
 *   Outside the class          ─► void Car::start() { ... }
 *   Inline member functions    ─► small functions, call replaced by code
 *   Nesting of member functions ─► one member function calls another
 *
 *   OBJECTS IN USE
 *   ──────────────
 *   Array of objects           ─► Student s[3];
 *   Dynamic array of objects   ─► Student* p = new Student[n];
 *   Pass by value             ─► function gets a COPY
 *   Pass by reference          ─► function gets the ORIGINAL
 *   Pass by const reference    ─► original, but read-only (no copy)
 *   Return an object           ─► Point make() { return p; }
 *   Object to member function  ─► w3.sum(w1, w2);
 *
 *   CONST, MUTABLE, THIS
 *   ────────────────────
 *   const objects / functions  ─► promise not to change data
 *   mutable data members       ─► can change even inside const functions
 *   this pointer               ─► address of the current object
 *   return *this               ─► method chaining  a.f().g().h()
 *   Getters and setters        ─► safe read / write of private data
 *
 *   MORE
 *   ────
 *   Size of an object          ─► sizeof, empty class = 1 byte
 *   Anonymous / temp objects   ─► Car().honk();
 *   Nested class               ─► class inside a class
 *   Local class                ─► class inside a function
 *   Forward declaration        ─► class B;  (use before full definition)
 *   Header + source files      ─► Car.h / Car.cpp / main.cpp
 *
 *  ✔ Static members → see 11_StaticMembers.cpp
 *  ✔ protected + inheritance in depth → see 06_Inheritance.cpp
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Defining a class | Creating an object ->
│      class Car { public: string brand; void honk(); };
│      Car c;     c.brand = "BMW";     c.honk();
│
│  ✔ Definition : A class is the design. An object is made from it.
│                 Use dot (.) to reach a member of the object.
│  ✔ Each object keeps its own copy of the data members
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string brand;                        // attributes
    string model;
    int year;

    void honk() {                        // method
        cout << "Beep Beep!" << endl;
    }
};

int main() {

    Car carObj1;                         // create an object of Car

    carObj1.brand = "BMW";               // set attribute values
    carObj1.model = "X5";
    carObj1.year = 1999;

    cout << carObj1.brand << " " << carObj1.model << " "
         << carObj1.year << endl;        // BMW X5 1999

    carObj1.honk();                      // Beep Beep!

    Car carObj2;                         // second object, own data
    carObj2.brand = "Ford";
    cout << carObj2.brand << endl;       // Ford
    cout << carObj1.brand << endl;       // BMW  (not changed)

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Ways to create objects ->
│      Car a;                    // normal object (on stack)
│      Car b{"BMW", 2020};       // brace init (all members public)
│      Car* p = new Car;         // on heap → use -> , then delete
│
│  ✔ Definition : Objects can live on the STACK (auto removed at end of
│                 scope) or on the HEAP (made with new, you must delete).
│  ✔ obj.member  → for an object      ptr->member → for a pointer
│  ⚠ Forgetting delete = memory leak
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    string brand;
    int year;

    void show() { cout << brand << " (" << year << ")" << endl; }
};

int main() {

    Car a;                               // stack object
    a.brand = "Tata";
    a.year = 2018;
    a.show();                            // Tata (2018)

    Car b{"BMW", 2020};                  // brace initialization
    b.show();                            // BMW (2020)

    Car* p = new Car;                    // heap object
    p->brand = "Audi";                   // -> because p is a pointer
    p->year = 2023;
    p->show();                           // Audi (2023)
    (*p).show();                         // Audi (2023)  same thing
    delete p;                            // free heap memory

    Car garage[2] = {{"Kia", 2021}, {"MG", 2022}};
    garage[1].show();                    // MG (2022)

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  class vs struct ->
│      struct Point { int x; };      // members are PUBLIC by default
│      class  Point { int x; };      // members are PRIVATE by default
│
│  ✔ Definition : In C++, class and struct are almost the SAME. Both can
│                 have functions, constructors, inheritance ...
│                 The only difference is the DEFAULT access.
│  ✔ Common habit: struct → simple data holder,  class → object with rules
│  ⚠ Default inheritance is also different: struct → public, class → private
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

struct PointS {                          // public by default
    int x, y;
    void show() { cout << x << "," << y << endl; }
};

class PointC {                           // private by default
    int x, y;
public:
    void set(int a, int b) { x = a; y = b; }
    void show() { cout << x << "," << y << endl; }
};

int main() {

    PointS s;
    s.x = 3;                             // OK, public
    s.y = 4;
    s.show();                            // 3,4

    PointC c;
    // c.x = 3;                          // ERROR: x is private
    c.set(5, 6);
    c.show();                            // 5,6

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Access specifiers ->
│      public:     → anyone can use
│      private:    → only this class can use       (default in class)
│      protected:  → this class + child classes
│
│  ✔ Definition : They decide WHO can see a member. Usually data is
│                 private and functions are public.
│  ✔ One label applies to everything below it, until the next label
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    double salary = 50000;               // hidden from outside

protected:
    string department = "IT";            // for child classes

public:
    string name = "Neha";                // open to all

    void showSalary() {                  // public function can read private
        cout << name << " earns " << salary << endl;
    }
};

int main() {

    Employee e;
    cout << e.name << endl;              // Neha
    e.showSalary();                      // Neha earns 50000

    // cout << e.salary;                 // ERROR: private
    // cout << e.department;             // ERROR: protected

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Access specifiers — who can see what
│  ✔ Definition : Access specifiers set the scope and visibility of class
│                 members.
│
│      MEMBER       SAME CLASS    CHILD CLASS    OUTSIDE (main)
│      ──────────   ───────────   ───────────    ──────────────
│      public       ✔ yes         ✔ yes          ✔ yes
│      protected    ✔ yes         ✔ yes          ✘ no
│      private      ✔ yes         ✘ no           ✘ no
│
│  ✔ Default access in a class = private (if you write nothing)
│  ✔ Private / protected data is reached from outside through public
│    functions (setWidth, getWidth ...)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Box {
public:
    double length;                       // public member

private:
    double width;                        // private member

protected:
    double height;                       // protected member

public:
    void setWidth(double wid) { width = wid; }   // private, inside class
    double getWidth() { return width; }

    void setHeight(double hgt) { height = hgt; } // protected, inside class
    double getHeight() { return height; }
};

class PrivateByDefault {
    int x;                               // private (nothing written)
    int y;                               // private
};

int main() {

    Box box;

    box.length = 10.0;                   // public → direct access
    cout << "Length: " << box.length << endl;        // Length: 10

    box.setWidth(5.0);                   // private → through function
    cout << "Width: " << box.getWidth() << endl;     // Width: 5

    box.setHeight(7.0);                  // protected → through function
    cout << "Height: " << box.getHeight() << endl;   // Height: 7

    // box.width = 1;                    // ERROR: private
    // box.height = 1;                   // ERROR: protected

    PrivateByDefault p;
    // p.x = 5;                          // ERROR: private by default
    (void)p;

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Member function inside the class ->
│      class A { public: void f() { ... } };
│
│  ✔ Definition : The full body is written inside the class.
│                 Such functions are automatically treated as inline.
│  ✔ Good for short functions (1–3 lines)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Light {
    bool on = false;

public:
    void toggle() { on = !on; }                      // inside class
    void status() { cout << (on ? "ON" : "OFF") << endl; }
};

int main() {

    Light l;
    l.status();                          // OFF
    l.toggle();
    l.status();                          // ON
    l.toggle();
    l.status();                          // OFF

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Member function outside the class ->
│      class A { public: void f(); };            // only declare inside
│      void A::f() { ... }                // define outside with ::
│
│  ✔ Definition : Declare the function in the class, write the body
│                 outside using the scope resolution operator (::).
│                 A::f means "f that belongs to class A".
│  ✔ Keeps the class short and easy to read → good for big functions
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Rectangle {
private:
    double length;
    double width;

public:
    void setDimensions(double len, double wid);      // declaration
    double area();
    double perimeter();
};

void Rectangle::setDimensions(double len, double wid) {
    length = len;
    width = wid;
}

double Rectangle::area() {
    return length * width;
}

double Rectangle::perimeter() {
    return 2 * (length + width);
}

int main() {

    Rectangle rect;
    rect.setDimensions(10.0, 5.0);
    cout << "Area: " << rect.area() << endl;             // Area: 50
    cout << "Perimeter: " << rect.perimeter() << endl;   // Perimeter: 30

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Inline member functions ->
│      class A { void f() { ... } };             // inside → inline
│      inline void A::g() { ... }                // outside → add inline
│
│  ✔ Definition : For an inline function, the compiler may put the
│                 function's code directly at the place of the call.
│                 This saves the cost of a function call.
│  ✔ Use for SMALL functions only
│  ⚠ inline is only a request — the compiler can ignore it
│  ⚠ Big inline functions make the program bigger, not faster
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Circle {
private:
    double radius;

public:
    void setRadius(double r) { radius = r; }     // inline (inside class)
    double area();
    double diameter();
};

inline double Circle::area() {                   // inline (outside class)
    return 3.14159 * radius * radius;
}

inline double Circle::diameter() {
    return 2 * radius;
}

int main() {

    Circle circ;
    circ.setRadius(5.0);
    cout << "Area: " << circ.area() << endl;         // Area: 78.5397
    cout << "Diameter: " << circ.diameter() << endl; // Diameter: 10

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Nesting of member functions
│  ✔ Definition : When one member function calls another member function
│                 of the SAME class, by name only (no object, no dot).
│  ✔ Avoids repeating code — display() reuses area() and perimeter()
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Square {
private:
    double side;

public:
    void setSide(double s) { side = s; }
    double area() { return side * side; }
    double perimeter() { return 4 * side; }

    void display() {
        cout << "Area: " << area() << endl;            // calls area()
        cout << "Perimeter: " << perimeter() << endl;  // calls perimeter()
    }
};

int main() {

    Square sq;
    sq.setSide(4.0);
    sq.display();
    // Area: 16
    // Perimeter: 16

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Array of objects ->
│      ClassName arr[size];        arr[i].member;
│
│  ✔ Definition : An array whose elements are objects of a class.
│                 Reach each object by its index.
│  ✔ When a class is defined, NO memory is given for data. Memory comes
│    only when objects are created — an array creates many at once.
│  ✔ Advantages:
│        • many objects under ONE name
│        • random access by index → arr[i]
│        • easy to loop over all of them
│  ⚠ Each object is made with the DEFAULT constructor
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int age;

    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {

    const int size = 3;
    Student students[size];

    students[0].name = "Alice";    students[0].age = 20;
    students[1].name = "Bob";      students[1].age = 22;
    students[2].name = "Charlie";  students[2].age = 21;

    for (int i = 0; i < size; i++)
        students[i].display();
    // Name: Alice, Age: 20
    // Name: Bob, Age: 22
    // Name: Charlie, Age: 21

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Array of objects — student records with private data
│  ✔ Data is private, so each object is filled through member functions
│  ✔ Functions are defined outside the class with ::
│  ✔ The input version (with cin) is in the comment inside main()
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Student {
    int roll_no;                         // private by default
    string name;

public:
    void get_record(int r, string n);
    void show_record();
};

void Student::get_record(int r, string n) {
    roll_no = r;
    name = n;
}

void Student::show_record() {
    cout << "Roll no: " << roll_no << ", Name: " << name << endl;
}

int main() {

    Student obj[2];                      // 2 students

    obj[0].get_record(1, "Amit");
    obj[1].get_record(2, "Neha");

    // To take input from the user instead:
    //     int r; string n;
    //     cin >> r;  getline(cin >> ws, n);
    //     obj[i].get_record(r, n);

    for (int i = 0; i < 2; i++)
        obj[i].show_record();
    // Roll no: 1, Name: Amit
    // Roll no: 2, Name: Neha

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Dynamic array of objects ->
│      ClassName* p = new ClassName[n];      p[i].member;
│      delete[] p;
│
│  ✔ Definition : Make an array of objects on the HEAP when the size is
│                 known only at run time.
│  ✔ new[] calls the default constructor for EVERY object,
│    delete[] calls the destructor for every object (in reverse order)
│  ✔ If memory can't be given, new throws bad_alloc (header <new>)
│  ⚠ Use delete[] (not delete) for arrays made with new[]
│  ✔ In modern C++, vector<ClassName> does all of this for you
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <new>
using namespace std;

class Rectangle {
    int width;
    int height;

public:
    Rectangle() {
        width = height = 0;
        cout << "Constructing " << width << " by " << height << endl;
    }

    ~Rectangle() {
        cout << "Destructing " << width << " by " << height << endl;
    }

    void set(int w, int h) { width = w; height = h; }
    int area() { return width * height; }
};

int main() {

    Rectangle* p;

    try {
        p = new Rectangle[3];
    } catch (const bad_alloc&) {
        cout << "Allocation Failure" << endl;
        return 1;
    }
    // Constructing 0 by 0
    // Constructing 0 by 0
    // Constructing 0 by 0

    p[0].set(3, 4);
    p[1].set(10, 8);
    p[2].set(5, 6);

    for (int i = 0; i < 3; i++)
        cout << "Area is " << p[i].area() << endl;
    // Area is 12
    // Area is 80
    // Area is 30

    delete[] p;
    // Destructing 5 by 6
    // Destructing 10 by 8
    // Destructing 3 by 4

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Object as argument — Pass by Value ->
│      void f(Point p);            f(obj);
│
│  ✔ Definition : The function gets a COPY of the object.
│                 Changes inside the function stay local — the original
│                 object does NOT change.
│  ⚠ Copying a big object is slow
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    void display() { cout << "Point(" << x << ", " << y << ")" << endl; }
};

void movePoint(Point p) {                // copy
    p.x += 10;
    p.y += 10;
    cout << "Inside: ";
    p.display();
}

int main() {

    Point pt;
    pt.x = 5;
    pt.y = 10;

    movePoint(pt);                       // Inside: Point(15, 20)

    cout << "After: ";
    pt.display();                        // After: Point(5, 10)  unchanged

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Object as argument — Pass by Reference ->
│      void f(Point& p);           f(obj);
│
│  ✔ Definition : The function gets the ORIGINAL object (no copy).
│                 Changes inside the function change the real object.
│  ✔ Faster for big objects
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    void display() { cout << "Point(" << x << ", " << y << ")" << endl; }
};

void movePointRef(Point& p) {            // reference
    p.x += 10;
    p.y += 10;
}

int main() {

    Point pt;
    pt.x = 5;
    pt.y = 10;

    movePointRef(pt);

    cout << "After: ";
    pt.display();                        // After: Point(15, 20)  changed

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Object as argument — Pass by const Reference ->
│      void f(const Point& p);     f(obj);
│
│  ✔ Definition : The function gets the original object (no copy) but
│                 it is READ-ONLY. Best of both: fast AND safe.
│  ✔ The normal choice for passing objects you only want to read
│  ⚠ Inside, you can call only const member functions on p
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    string name;
    double price;

    double priceWithGST() const { return price * 1.18; }
};

void printBill(const Product& p) {       // no copy, can't change p
    cout << p.name << " : " << p.priceWithGST() << endl;
    // p.price = 0;                      // ERROR: p is const
}

int main() {

    Product phone{"Phone", 10000};
    printBill(phone);                    // Phone : 11800

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Passing TWO objects — average marks of two students
│  ✔ Both objects are passed by const reference: no copy, no change
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Student {
public:
    int marks;
    Student(int m) { marks = m; }
};

void calculateAverage(const Student& s1, const Student& s2) {
    float average = (s1.marks + s2.marks) / 2.0;
    cout << "Average Marks = " << average << endl;
}

int main() {

    Student student1(89), student2(56);
    calculateAverage(student1, student2);    // Average Marks = 72.5

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Return an object from a function ->
│      Point create(int x, int y) { Point p; ...; return p; }
│      Point pt = create(1, 2);
│
│  ✔ Definition : A function can build an object and return it.
│                 The caller can store it or use it directly.
│  ✔ Modern compilers avoid the extra copy (RVO) → it's cheap
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Point {
public:
    int x, y;
    void display() { cout << "Point(" << x << ", " << y << ")" << endl; }
};

Point createPoint(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;                            // return the object
}

Point addPoints(Point a, Point b) {
    return createPoint(a.x + b.x, a.y + b.y);
}

int main() {

    Point pt = createPoint(15, 25);
    pt.display();                        // Point(15, 25)

    Point sum = addPoints(pt, createPoint(5, 5));
    sum.display();                       // Point(20, 30)

    createPoint(1, 2).display();         // Point(1, 2)  used directly

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Return object — assign it to an object that already exists
│  ✔ student1 is created first, then the returned object is COPIED
│    into it with =
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Student {
public:
    double marks1, marks2;
};

Student createStudent() {
    Student student;
    student.marks1 = 96.5;
    student.marks2 = 75.0;
    return student;
}

int main() {

    Student student1;
    student1 = createStudent();          // assign the returned object

    cout << "Marks 1 = " << student1.marks1 << endl;     // Marks 1 = 96.5
    cout << "Marks 2 = " << student1.marks2 << endl;     // Marks 2 = 75

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Object as argument to a MEMBER function ->
│      void sum(Weight a, Weight b);       w3.sum(w1, w2);
│
│  ✔ Definition : A member function can take objects of its own class.
│                 Inside it you can read their PRIVATE data too, because
│                 it is the same class.
│  ✔ Here w3 stores the total of w1 and w2
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Weight {
private:
    int kilogram;
    int gram;

public:
    void setData(int kg, int g) { kilogram = kg; gram = g; }

    void showData() {
        cout << kilogram << " kg " << gram << " g" << endl;
    }

    void sum_weight(Weight w1, Weight w2) {
        gram = w1.gram + w2.gram;        // private data of w1, w2: OK
        kilogram = gram / 1000;          // extra grams → kg
        gram = gram % 1000;
        kilogram += w1.kilogram + w2.kilogram;
    }
};

int main() {

    Weight w1, w2, w3;
    w1.setData(2, 700);
    w2.setData(1, 500);

    w3.sum_weight(w1, w2);

    cout << "Weight #1 = ";  w1.showData();      // Weight #1 = 2 kg 700 g
    cout << "Weight #2 = ";  w2.showData();      // Weight #2 = 1 kg 500 g
    cout << "Total     = ";  w3.showData();      // Total     = 4 kg 200 g

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  const objects | const member functions ->
│      int get() const { return v; }     // const member function
│      const ClassName obj(args);        // const object
│
│  ✔ Definition : A const member function promises NOT to change any
│                 data member. A const object can call ONLY const member
│                 functions.
│  ✔ Mark every function that only reads data as const
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Immutable {
private:
    int value;

public:
    Immutable(int val) : value(val) {}

    int getValue() const { return value; }       // const: only reads
    void setValue(int v) { value = v; }          // not const: changes

    // void bad() const { value = 5; }           // ERROR: const fn
};

int main() {

    const Immutable obj(42);                     // const object
    cout << "Value: " << obj.getValue() << endl; // Value: 42
    // obj.setValue(10);                         // ERROR: obj is const

    Immutable normal(7);
    normal.setValue(8);                          // OK
    cout << normal.getValue() << endl;           // 8

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  mutable data members ->
│      mutable int counter;
│
│  ✔ Definition : A mutable member can be changed EVEN inside a const
│                 function or a const object.
│  ✔ Use it for "behind the scenes" data that is not the object's real
│    state: counters, cache, logs
│  ⚠ Don't use mutable to cheat on real data — that breaks const
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Webpage {
private:
    string title;
    mutable int views = 0;               // can change in const functions

public:
    Webpage(string t) : title(t) {}

    string getTitle() const {
        views++;                         // OK because views is mutable
        return title;
    }

    int getViews() const { return views; }
};

int main() {

    const Webpage home("Home");          // const object

    cout << home.getTitle() << endl;     // Home
    cout << home.getTitle() << endl;     // Home
    cout << home.getViews() << endl;     // 2

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  this pointer ->
│      this->member        // member of the current object
│      *this               // the current object itself
│
│  ✔ Definition : this is a hidden pointer inside every non-static member
│                 function. It holds the address of the object that
│                 called the function.
│  ✔ Main use: when a parameter has the SAME name as a data member
│  ⚠ Static member functions do NOT have this
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Fruit {
private:
    string name;

public:
    void setName(string name) {
        this->name = name;               // left: member, right: parameter
    }

    void display() {
        cout << "Fruit: " << this->name << endl;
    }

    bool isSame(Fruit& other) { return this == &other; }
};

int main() {

    Fruit apple, mango;
    apple.setName("Apple");
    mango.setName("Mango");

    apple.display();                     // Fruit: Apple
    mango.display();                     // Fruit: Mango

    cout << boolalpha;
    cout << apple.isSame(apple) << endl; // true
    cout << apple.isSame(mango) << endl; // false

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  return *this → method chaining ->
│      ClassName& f() { ...; return *this; }
│      obj.f().g().h();
│
│  ✔ Definition : If a member function returns a reference to the current
│                 object (*this), the next function can be called right
│                 after it, in one line.
│  ✔ Used in builders, string builders, cout itself (cout << a << b)
│  ⚠ Return ClassName& (reference). Returning ClassName makes a copy
│    and the next calls change the copy, not the original.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Pizza {
private:
    string size = "Small";
    string toppings;

public:
    Pizza& setSize(string s) {
        size = s;
        return *this;
    }

    Pizza& addTopping(string t) {
        toppings += t + " ";
        return *this;
    }

    void show() const { cout << size << " pizza: " << toppings << endl; }
};

int main() {

    Pizza order;
    order.setSize("Large")
         .addTopping("Cheese")
         .addTopping("Onion")
         .addTopping("Corn");

    order.show();                        // Large pizza: Cheese Onion Corn

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Getters and setters ->
│      Type getX() const { return x; }           // read
│      void setX(Type v) { if (valid) x = v; }   // write with a check
│
│  ✔ Definition : Keep data private. Give public functions to read it
│                 (getter) and to change it (setter).
│  ✔ The setter can CHECK the value first, so the object never holds
│    wrong data (like negative age)
│  ✔ Don't add a setter if the value should never change (e.g. id)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    int id;
    string name;
    int age = 0;

public:
    Person(int i, string n) : id(i), name(n) {}

    int getId() const { return id; }             // no setter: id is fixed
    string getName() const { return name; }
    int getAge() const { return age; }

    void setAge(int a) {
        if (a < 0 || a > 150) {
            cout << "Invalid age: " << a << endl;
            return;
        }
        age = a;
    }
};

int main() {

    Person p(101, "Ravi");
    p.setAge(25);
    p.setAge(-5);                        // Invalid age: -5

    cout << p.getId() << " " << p.getName() << " "
         << p.getAge() << endl;          // 101 Ravi 25

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Size of an object ->
│      sizeof(ClassName)       sizeof(obj)
│
│  ✔ Definition : The size of an object = size of its data members
│                 (+ padding). Member functions take NO space inside
│                 the object.
│  ✔ Empty class → size is 1 byte, so two objects never share an address
│  ✔ Padding: the compiler adds empty bytes to line up data in memory.
│    Put bigger members first to waste less space.
│  ⚠ Exact numbers can change with compiler / 32-bit vs 64-bit.
│    Comments below are for g++ on 64-bit.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

class Empty {};

class OnlyFunctions {
public:
    void a() {}
    void b() {}
};

class TwoInts {
    int x, y;
};

class Padded {                           // char, int, char → wasted bytes
    char a;
    int b;
    char c;
};

class Packed {                           // int first → less waste
    int b;
    char a;
    char c;
};

int main() {

    cout << sizeof(Empty) << endl;           // 1
    cout << sizeof(OnlyFunctions) << endl;   // 1  (functions take no space)
    cout << sizeof(TwoInts) << endl;         // 8
    cout << sizeof(Padded) << endl;          // 12
    cout << sizeof(Packed) << endl;          // 8

    Empty e1, e2;
    cout << boolalpha << (&e1 != &e2) << endl;   // true

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Anonymous / temporary objects ->
│      ClassName();                ClassName(args).method();
│
│  ✔ Definition : An object made without a name. It lives only until the
│                 end of that line (statement), then it is destroyed.
│  ✔ Useful when you need an object just once: pass it to a function,
│    or call one method on it
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Message {
    string text;

public:
    Message(string t) : text(t) { cout << "made: " << text << endl; }
    ~Message() { cout << "gone: " << text << endl; }

    void send() const { cout << "send: " << text << endl; }
};

void deliver(const Message& m) { m.send(); }

int main() {

    Message("Hello").send();             // made, send, gone — same line
    // made: Hello
    // send: Hello
    // gone: Hello

    deliver(Message("OTP 4321"));
    // made: OTP 4321
    // send: OTP 4321
    // gone: OTP 4321

    cout << "end of main" << endl;       // end of main

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Nested class ->
│      class Outer { public: class Inner { ... }; };
│      Outer::Inner obj;
│
│  ✔ Definition : A class written INSIDE another class. Use it when the
│                 inner class only makes sense as a part of the outer one.
│  ✔ Its full name is Outer::Inner
│  ✔ Inner can use Outer's private members (it is a member of Outer)
│  ⚠ Outer can NOT use Inner's private members
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Library {
public:
    class Book {                         // nested class
    public:
        string title;
        string author;

        void show() const { cout << title << " by " << author << endl; }
    };

private:
    vector<Book> books;

public:
    void add(const Book& b) { books.push_back(b); }

    void showAll() const {
        for (const Book& b : books) b.show();
    }
};

int main() {

    Library lib;
    Library::Book b1{"Wings of Fire", "A.P.J. Abdul Kalam"};
    lib.add(b1);
    lib.add({"Godan", "Premchand"});

    lib.showAll();
    // Wings of Fire by A.P.J. Abdul Kalam
    // Godan by Premchand

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Local class ->
│      void f() { class Helper { ... }; Helper h; }
│
│  ✔ Definition : A class written INSIDE a function. It can be used only
│                 inside that function.
│  ✔ Good for a small helper that nobody else needs
│  ⚠ All member functions must be written inside the class
│  ⚠ It can't have static data members
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

void printReport(int marks[], int n) {

    class Stats {                        // local class
    public:
        int total = 0, best = 0;

        void add(int m) {
            total += m;
            if (m > best) best = m;
        }
    };

    Stats s;
    for (int i = 0; i < n; i++) s.add(marks[i]);

    cout << "Total: " << s.total << ", Best: " << s.best << endl;
}

int main() {

    int marks[] = {70, 95, 82};
    printReport(marks, 3);               // Total: 247, Best: 95

    // Stats x;                          // ERROR: Stats is not known here

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Forward declaration ->
│      class B;                    // "B exists, details come later"
│
│  ✔ Definition : Tell the compiler a class name BEFORE writing the full
│                 class. Needed when two classes refer to each other.
│  ✔ After a forward declaration you may use B* or B& (pointer/ref)
│  ⚠ You can't make a B object or call B's functions until B is fully
│    defined → write such function bodies AFTER class B
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <string>
using namespace std;

class Driver;                            // forward declaration

class Bus {
public:
    string number;
    Driver* driver = nullptr;            // OK: pointer to Driver

    void info();                         // body written later
};

class Driver {
public:
    string name;
    Bus* bus = nullptr;
};

void Bus::info() {                       // now Driver is complete
    cout << "Bus " << number << " driven by " << driver->name << endl;
}

int main() {

    Bus b;
    Driver d;
    b.number = "MH12-4455";
    d.name = "Suresh";

    b.driver = &d;
    d.bus = &b;

    b.info();                            // Bus MH12-4455 driven by Suresh
    cout << d.bus->number << endl;       // MH12-4455

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Class in header (.h) + source (.cpp) files
│  ✔ In real projects a class is split into 2 files:
│        Counter.h   → class declaration (what it has)
│        Counter.cpp → function bodies   (how it works)
│        main.cpp    → uses the class:  #include "Counter.h"
│  ✔ Other files only need the .h — they don't see the body
│  ✔ Build:  g++ main.cpp Counter.cpp -o app
│  ⚠ Use include guards (#pragma once) so the .h is not included twice
│
│      // ───── Counter.h ─────
│      #pragma once
│      class Counter {
│          int count = 0;
│      public:
│          void increment();
│          int get() const;
│      };
│
│      // ───── Counter.cpp ─────
│      #include "Counter.h"
│      void Counter::increment() { count++; }
│      int Counter::get() const { return count; }
│
│  ✔ The program below puts all 3 parts in one file so it runs with
│    Ctrl+Alt+N
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
using namespace std;

// ───── Counter.h ─────
class Counter {
    int count = 0;

public:
    void increment();
    int get() const;
};

// ───── Counter.cpp ─────
void Counter::increment() { count++; }
int Counter::get() const { return count; }

// ───── main.cpp ─────
int main() {

    Counter visitors;
    visitors.increment();
    visitors.increment();
    visitors.increment();

    cout << "Visitors: " << visitors.get() << endl;   // Visitors: 3

    return 0;
}
