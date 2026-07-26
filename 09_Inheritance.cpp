/*==============================================================================
    🧩 Inheritance

    - Inheritance is one of the key features of Object-oriented programming in C++.
    - The capability of a class to inherit the properties of some other class is known as Inheritance. 
    - The class whose properties are inherited is called the base class 
    - While the class which inherits the properties is known as the derived class.
    - It helps in the reusability of code that saves lots of time.

    Two types of classes in inheritance:
        Parent Class or Base Class   : It is a class whose property is inherited by a subclass. 
        Child Class or Derived Class : It is a class that inherits the property of another class. 

     ---------------------------------------------------------------------------------
      Base class member  |                   Type of Inheritence                     |
      access specifier   | Public	       |     Protected	      |     Private      |
      -------------------------------------|----------------------|------------------|
      Public	         | Public	       |     Protected        |	  Private        |
      Protected	         | Protected	   |     Protected	      |     Private      |
      Private	         | Not accessible  |	Not accessible    |	Not accessible   |   
     ---------------------------------------------------------------------------------       

    Note :  Use inheritance whene there is IS-A relationship.

    🧩 Inheritance
    ├─→ Concept of Reusability
    ├─→ Base Class and Derived Class
    ├─→ Syntax and Access Control
    │     ├─→ public Inheritance
    │     ├─→ private Inheritance
    │     └─→ protected Inheritance
    ├─→ Types of Inheritance
    │     ├─→ Single Inheritance
    │     ├─→ Multiple Inheritance
    │     ├─→ Multilevel Inheritance
    │     ├─→ Hierarchical Inheritance
    │     └─→ Hybrid Inheritance
    ├─→ Constructor and Destructor in Inheritance
    ├─→ Function Overriding
    ├─→ Ambiguity in Multiple Inheritance
    │     ├─→ Scope Resolution Operator (::)
    │     └─→ Virtual Base Class
    ├─→ Order of Execution (Base → Derived)
    ├─→ Virtual Base Class
    └─→ Diamond Problem

==============================================================================*/

/*==============================================================================
    🧩 Concept of Reusability
    --------------------------------------------------------------------------
    🔹 Inheritance allows a new class to reuse code from an existing class.
    🔹 Promotes code reusability and reduces redundancy.
    🔹 Example: A 'Car' class can inherit
              properties from a 'Vehicle' class.
==============================================================================*/
#include <iostream>
using namespace std;

class Vehicle{
public:
    void displayType(){
        cout << "This is a vehicle." << endl;
    }
};
class Car : public Vehicle {
public:
    void displayModel(){
        cout << "This is a car." << endl;
    }
};
int main(){
    Car myCar;
    myCar.displayType();  // Inherited from Vehicle
    myCar.displayModel(); // Defined in Car
    return 0;
}

/*==============================================================================
    🧩 Base Class and Derived Class
    --------------------------------------------------------------------------
    🔹 Base Class: The class whose properties are inherited.
    🔹 Derived Class: The class that inherits properties from the base class.
    🔹 Syntax: class DerivedClass : accessSpecifier BaseClass { ... };
==============================================================================*/
#include <iostream>
using namespace std;

class Animal{ // Base Class

public:
    void eat(){
        cout << "This animal eats food." << endl;
    }
};
class Dog : public Animal {// Derived Class
public:
    void bark(){
        cout << "The dog barks." << endl;
    }
};
int main(){
    Dog myDog;
    myDog.eat(); // Inherited from Animal
    myDog.bark(); // Defined in Dog
    return 0;
}


/*==============================================================================
    🧩 Syntax and Access Control
    --------------------------------------------------------------------------
    🔹 public Inheritance: Public and protected members of base class remain public and protected in derived class.
    🔹 private Inheritance: Public and protected members of base class become private in derived class.
    🔹 protected Inheritance: Public and protected members of base class become protected in derived class.
==============================================================================*/
#include <iostream>
using namespace std;
class Base{
public:
    int publicVar;
protected:

    int protectedVar;
private:
    int privateVar;
};
class PublicDerived : public Base{
    // publicVar is public
    // protectedVar is protected
    // privateVar is not accessible
};
class PrivateDerived : private Base{
    // publicVar is private
    // protectedVar is private
    // privateVar is not accessible
};
class ProtectedDerived : protected Base{
    // publicVar is protected
    // protectedVar is protected
    // privateVar is not accessible
};
int main(){
    PublicDerived pubDeriv;
    // pubDeriv.publicVar = 10; // Accessible

    PrivateDerived privDeriv;
    // privDeriv.publicVar = 20; // Not Accessible

    ProtectedDerived protDeriv;
    // protDeriv.publicVar = 30; // Not Accessible

    return 0;
}

/*==============================================================================
    🧩 Single Inheritance
    --------------------------------------------------------------------------
    🔹 A derived class inherits from a single base class.
    🔹 Simple and straightforward form of inheritance.
==============================================================================*/
#include <iostream>
using namespace std;

class Parent {
public:
    void showMessage() {
        cout << "This is the Parent class." << endl;
    }
};

class ChildSingle : public Parent {
public:
    void showChildMessage() {
        cout << "This is the Child class." << endl;
    }
};

int main() {
    ChildSingle myChild;
    myChild.showMessage();       // Inherited from Parent
    myChild.showChildMessage();  // Defined in ChildSingle
    return 0;
}


/*==============================================================================
    🧩 Multiple Inheritance
    --------------------------------------------------------------------------
    🔹 A derived class inherits from more than one base class.
    🔹 Allows combining features from multiple classes.
==============================================================================*/
#include <iostream>
using namespace std;
class BaseClass11
{
public:
    void displayBase11()
    {
        cout << "This is Base Class 1." << endl;
    }
};
class BaseClass2
{
public:
    void displayBase2()
    {
        cout << "This is Base Class 2." << endl;
    }
};
class DerivedClass : public BaseClass11, public BaseClass2
{
public:
    void displayDerived()
    {
        cout << "This is the Derived Class." << endl;
    }
};
int main()
{
    DerivedClass obj;
    obj.displayBase11();   // From Base1
    obj.displayBase2();   // From Base2
    obj.displayDerived(); // From Derived
    return 0;
}


/*==============================================================================
    🧩 Multilevel Inheritance
    --------------------------------------------------------------------------
    🔹 A derived class inherits from a base class, which itself is derived from another base class.
    🔹 Forms a chain of inheritance.
==============================================================================*/
#include <iostream>
using namespace std;
class GrandparentClass
{
public:
    void showGrandparent()
    {
        cout << "This is the Grandparent class." << endl;
    }
};
class ParentClass : public GrandparentClass
{
public:
    void showParent()
    {
        cout << "This is the Parent class." << endl;
    }
};
class Child : public ParentClass
{
public:
    void showChild()
    {
        cout << "This is the Child class." << endl;
    }
};
int main()
{
    Child myChild;
    myChild.showGrandparent(); // Inherited from Grandparent
    myChild.showParent();      // Inherited from Parent
    myChild.showChild();       // Defined in Child
    return 0;
}

/*==============================================================================
    🧩 Hierarchical Inheritance
    --------------------------------------------------------------------------
    🔹 Multiple derived classes inherit from a single base class.
    🔹 Promotes code reuse across related classes.
==============================================================================*/
#include <iostream>
using namespace std;
class Parent
{
public:
    void showMessage()
    {
        cout << "This is the Parent class." << endl;
    }
};
class Child1 : public Parent
{
public:
    void showChild1()
    {
        cout << "This is Child Class 1." << endl;
    }
};
class Child2 : public Parent
{
public:
    void showChild2()
    {
        cout << "This is Child Class 2." << endl;
    }
};
int main()
{
    Child1 child1;
    Child2 child2;

    child1.showMessage(); // Inherited from Parent
    child1.showChild1();  // Defined in Child1

    child2.showMessage(); // Inherited from Parent
    child2.showChild2();  // Defined in Child2

    return 0;
}

/*==============================================================================
    🧩 Hybrid Inheritance
    --------------------------------------------------------------------------
    🔹 Combination of two or more types of inheritance.
    🔹 Provides flexibility in designing class hierarchies.
==============================================================================*/
#include <iostream>
using namespace std;
class BaseClass1
{
public:
    void showBase()
    {
        cout << "This is the Base class." << endl;
    }
};
class DerivedClass1 : public BaseClass1
{
public:
    void showDerived1()
    {
        cout << "This is Derived Class 1." << endl;
    }
};
class DerivedClass2 : public BaseClass1
{
public:
    void showDerived2()
    {
        cout << "This is Derived Class 2." << endl;
    }
};
class HybridClass : public DerivedClass1, public DerivedClass2
{
public:
    void showHybrid()
    {
        cout << "This is the Hybrid class." << endl;
    }
};
int main()
{
    HybridClass obj;
    // obj.showBase();      // Ambiguity arises here
    obj.showDerived1();
    obj.showDerived2();
    obj.showHybrid();
    return 0;
}

/*==============================================================================
    🧩 Constructor and Destructor in Inheritance
    --------------------------------------------------------------------------
    🔹 Base class constructor is called before derived class constructor.
    🔹 Base class destructor is called after derived class destructor.
==============================================================================*/
#include <iostream>
using namespace std;
class Base{
public:
    Base(){
        cout << "Base class constructor called." << endl;
    }
    ~Base(){
        cout << "Base class destructor called." << endl;
    }
};
class Derived : public Base{
public:
    Derived(){
        cout << "Derived class constructor called." << endl;
    }
    ~Derived(){
        cout << "Derived class destructor called." << endl;
    }
};
int main(){
    Derived obj;
    return 0;
}


/*==============================================================================
    🧩 Function Overriding
    --------------------------------------------------------------------------
    🔹 A derived class provides a specific implementation of a function already defined in its base class.
    🔹 Achieved using the same function signature in both base and derived classes.
==============================================================================*/

#include <iostream>
using namespace std;
class Base{
public:
    void display(){
        cout << "Display from Base class." << endl;
    }
};
class DerivedOverride : public Base{
public:
    void display() // Overriding the base class function
    {
        cout << "Display from Derived class." << endl;
    }
};
int main()
{
    DerivedOverride obj;
    obj.display(); // Calls DerivedOverride class display
    return 0;
}

/*==============================================================================
    🧩 Ambiguity in Multiple Inheritance
    --------------------------------------------------------------------------
    🔹 Occurs when two base classes have a function with the same name.
    🔹 Resolved using Scope Resolution Operator (::) or Virtual Base Class.
==============================================================================*/

#include <iostream>
using namespace std;
class Base1{
public:
    void show(){
        cout << "Show from Base1" << endl;
    }
};
class Base2{
public:
    void show(){
        cout << "Show from Base2" << endl;
    }
};
class Derived : public Base1, public Base2{
public:
    void display(){
        Base1::show(); // Resolving ambiguity using Scope Resolution Operator
        Base2::show();
    }
};
int main()
{
    Derived obj;
    // obj.display();
    return 0;
}


/*==============================================================================
    🧩 Order of Execution (Base → Derived)
    --------------------------------------------------------------------------
    🔹 In constructor calls, base class constructors are executed before derived class constructors.
    🔹 In destructor calls, derived class destructors are executed before base class destructors.
==============================================================================*/
#include <iostream>
using namespace std;
class Base{
public:
    Base(){
        cout << "Base class constructor called." << endl;
    }
    ~Base(){
        cout << "Base class destructor called." << endl;
    }
};
class Derived : public Base{
public:
    Derived(){
        cout << "Derived class constructor called." << endl;
    }
    ~Derived(){
        cout << "Derived class destructor called." << endl;
    }
};
int main(){
    Derived obj;
    return 0;
}


/*==============================================================================
    🧩 Virtual Base Class
    --------------------------------------------------------------------------
    🔹 Used to prevent multiple "instances" of a base class when using multiple inheritance.
    🔹 Ensures that only one instance of the base class is shared among derived classes.
==============================================================================*/

#include <iostream>
using namespace std;
class Base{
public:
    void show(){
        cout << "Show from Base class." << endl;
    }
};
class Derived1 : virtual public Base{};
class Derived2 : virtual public Base{};
class Hybrid : public Derived1, public Derived2{};
int main(){
    Hybrid obj;
    obj.show(); // No ambiguity, single instance of Base
    return 0;
}


/*==============================================================================
    🧩 Diamond Problem
    --------------------------------------------------------------------------
    🔹 Occurs in multiple inheritance when two derived classes inherit from the same base class.
    🔹 Can lead to ambiguity if the derived class tries to access members of the base class.
    🔹 Resolved using Virtual Inheritance.
==============================================================================*/

#include <iostream>
using namespace std;
class Base
{
public:
    void show()
    {
        cout << "Show from Base class." << endl;
    }
};
class Derived1 : virtual public Base{};
class Derived2 : virtual public Base{};
class Hybrid : public Derived1, public Derived2{};
int main(){
    Hybrid obj;
    obj.show(); // No ambiguity, single instance of Base
    return 0;
}

