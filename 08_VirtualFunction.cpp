/*==============================================================================
    🧩 VIRTUAL FUNCTIONS — Complete Guide
    ==============================================================================

    📘 Definition (English):
     A virtual function is a member function declared in a base class using the 
     keyword "virtual", which is redefined (overridden) in a derived class. 
     It enables Runtime Polymorphism (Dynamic Binding) through a base class 
     pointer or reference.

    --------------------------------------------------------------------------
    🔹 Kaise kaam karta hai (Hinglish):
     - Normally jab function call hota hai, compiler decide karta hai (compile 
       time pe) ki kaunsa function call hoga — ise "Static Binding" kehte hain.
     - Lekin agar function "virtual" hai, toh decision RUN TIME pe hota hai — 
       ise "Dynamic Binding" kehte hain.
     - Ye check hota hai ki actual object kaunsa hai (base ya derived), na ki 
       pointer/reference kaunse type ka hai.

    🔹 Kyun zaroori hai:
     - Base class pointer se agar derived class ka object point karo, aur function 
       call karo — bina virtual ke HAMESHA base class ka function call hoga, 
       chahe object derived class ka ho. Ye galat behavior hai.
     - Virtual function isko fix karta hai — sahi (derived class ka) function 
       call hota hai.
==============================================================================*/

#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() {   // virtual function
        cout << "Base class show()" << endl;
    }
};

class Derived : public Base {
public:
    void show() override {  // overriding the virtual function
        cout << "Derived class show()" << endl;
    }
};

int main() {
    Base* basePtr;
    Derived derivedObj;

    basePtr = &derivedObj;

    basePtr->show();  
    // Bina virtual: "Base class show()" print hota
    // Virtual ke saath: "Derived class show()" print hoga (Runtime Polymorphism)

    return 0;
}


/*==============================================================================
    🧩 PURE VIRTUAL FUNCTIONS
    ==============================================================================

    📘 Definition (English):
    A pure virtual function is a virtual function that has no implementation 
    in the base class and is declared by assigning it the value 0. Any class 
    containing at least one pure virtual function automatically becomes an 
    Abstract Class.

    Syntax: virtual returnType functionName() = 0;

    --------------------------------------------------------------------------
    🔹 Key Points (Hinglish):
    - "= 0" likhne ka matlab hai ye function ka koi body/definition nahi hai 
      base class mein — sirf ek declaration hai jo force karta hai ki 
      derived class isko zaroor implement kare.
    - Agar derived class isko override nahi karti, toh derived class bhi 
      automatically abstract ban jaati hai (usko bhi instantiate nahi kar 
      sakte).
    - Pure virtual function ek "contract" jaisa kaam karta hai — "jo bhi 
      derived class banegi, usko yeh function definitely define karna 
      padega."
==============================================================================*/

class Shape {
public:
    virtual double area() = 0;   // Pure Virtual Function
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() override {
        return 3.14159 * radius * radius;
    }
};

// Agar Circle class 'area()' ko override na karti, toh Circle bhi 
// abstract ban jaati aur "Circle circ(7.0);" likhna compile error deta.


/*==============================================================================
    🧩 ABSTRACT CLASSES
    ==============================================================================

    📘 Definition (English):
    An Abstract Class is a class that contains at least one pure virtual 
    function. It cannot be instantiated directly and is meant to serve as a 
    base/blueprint for derived classes, which must implement all pure 
    virtual functions to become concrete (instantiable) classes.

    --------------------------------------------------------------------------
    🔹 Key Points (Hinglish):
    - Abstract class ka object seedha nahi bana sakte:
        Animal a;  // ❌ Error: cannot declare object of abstract type
    - Lekin abstract class ka POINTER ya REFERENCE bana sakte hain, 
      jo derived class object ko point kare:
        Animal* a = new Dog();  // ✅ Allowed
    - Abstract class mein normal (non-pure) functions bhi ho sakte hain — 
      sirf ek pure virtual function hona kaafi hai usse abstract banane ke 
      liye.
    - Abstract class ka use "Interface" jaisa hota hai C++ mein — ek common 
      structure/blueprint define karne ke liye jo saare derived classes 
      follow karengi.
==============================================================================*/

class Animal {
public:
    virtual void sound() = 0;      // Pure virtual → makes class abstract
    void eat() {                    // Normal function — abstract class mein bhi allowed
        cout << "Animal is eating..." << endl;
    }
};

class Dog : public Animal {
public:
    void sound() override {
        cout << "Woof Woof!" << endl;
    }
};

// Animal a;        // ❌ Error — abstract class ka object nahi bana sakte
// Animal* ptr = new Animal();  // ❌ Error


/*==============================================================================
    🧩 VIRTUAL vs PURE VIRTUAL vs ABSTRACT CLASS — Quick Comparison
    ==============================================================================

    | Feature              | Virtual Function          | Pure Virtual Function     |
    |----------------------|---------------------------|----------------------------|
    | Definition in base   | Hoti hai (optional override)| Nahi hoti (= 0)          |
    | Override zaroori?    | Optional                 | Mandatory (derived mein)   |
    | Class abstract banti?| Nahi                     | Haan                        |
    | Instantiation        | Class ka object ban sakta| Class (agar sirf isi wajah 
                             hai                        se) abstract ban jaati hai |
*/


/*==============================================================================
    🧩 IMPORTANT INTERVIEW POINTS
    ==============================================================================

    1️⃣ Abstract class ka object kyun nahi ban sakta?
        → Kyunki usme kam se kam ek function ka implementation missing hota 
          hai (pure virtual). Agar object banane diya jaye toh us function 
          ko call karne pe kya hoga — ye undefined ho jayega. Isliye 
          compiler explicitly rok deta hai.

    2️⃣ Abstract class ka pointer/reference kyun allowed hai?
        → Kyunki pointer/reference sirf memory address store karta hai, 
          object nahi banata. Runtime pe wo kisi derived (concrete) class 
          ke object ko point karega — jiska implementation complete hai.

    3️⃣ Virtual destructor kyun zaroori hota hai Abstract class mein?
        → Agar base class pointer se derived object delete karo bina 
          virtual destructor ke, toh sirf base class ka destructor call 
          hoga — derived class ka destructor skip ho jayega. Isse MEMORY 
          LEAK ho sakta hai. Isliye base class ka destructor virtual 
          rakhna best practice hai:
              virtual ~Animal() {}

    4️⃣ Pure virtual function ka body ho sakta hai kya?
        → Haan! C++ mein pure virtual function ka body define kar sakte ho 
          (rare use case), lekin phir bhi class abstract rahegi aur 
          derived class ko override karna hi padega. Body sirf "default/
          common implementation" provide karne ke liye hota hai jo derived 
          class chahe toh call kar sake (Base::functionName()).

    5️⃣ Runtime Polymorphism kaise achieve hota hai?
        → Virtual functions + Base class pointer/reference ke through. 
          Ye vtable (virtual table) mechanism use karta hai internally — 
          har object ke andar ek hidden pointer (vptr) hota hai jo uske 
          class ke vtable ko point karta hai, jisme actual function 
          addresses store hote hain.

    6️⃣ Function overriding vs Function overloading?
        → Overriding: Same function signature, base aur derived class mein, 
          runtime pe decide hota hai (virtual keyword zaroori).
        → Overloading: Same function name, different parameters, same 
          class mein, compile time pe decide hota hai.

    7️⃣ Multiple pure virtual functions ho sakte hain ek class mein?
        → Haan, ek class mein multiple pure virtual functions ho sakte hain 
          — jaise ek proper "Interface" (C++ mein isko "Pure Abstract 
          Class" kehte hain agar SAARE functions pure virtual hon).

    8️⃣ Real-world use case:
        → Design patterns (Factory, Strategy), Framework/Library design 
          jahan tumhe ek common interface define karna ho jise multiple 
          teams/classes apne hisaab se implement karein — e.g. Shape → 
          Circle, Rectangle, Triangle sab apna "area()" define karenge, 
          lekin sab "Shape" interface follow karenge.
==============================================================================*/


/*==============================================================================
    🧩 Full Working Example — Combining Everything
==============================================================================*/

#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() = 0;          // Pure virtual function
    virtual ~Shape() {}                  // Virtual destructor — best practice
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() override {
        return width * height;
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() override {
        return 3.14159 * radius * radius;
    }
};

int main() {
    Shape* shapes[2];
    shapes[0] = new Rectangle(10.0, 5.0);
    shapes[1] = new Circle(7.0);

    for (int i = 0; i < 2; i++) {
        cout << "Area: " << shapes[i]->area() << endl;
        delete shapes[i];   // virtual destructor ensures proper cleanup
    }

    return 0;
}


/*==============================================================================
    🧠 Key Takeaways:

    • Virtual function       → Runtime polymorphism enable karta hai
    • Pure virtual function  → "= 0" se declare hota hai, body optional hai
    • Abstract class         → Kam se kam ek pure virtual function hoti hai
    • Abstract class object  → Nahi ban sakta, sirf pointer/reference
    • Virtual destructor     → Base class mein hamesha rakho agar 
                                polymorphic delete karna ho
    • Real use               → Interfaces/blueprints design karne ke liye
==============================================================================*/