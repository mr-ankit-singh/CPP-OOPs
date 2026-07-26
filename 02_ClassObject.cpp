/*==============================================================================
    2️⃣ Class and Object
    ├─→ Defining a Class
    ├─→ Creating Objects
    ├─→ Access Specifiers
    │     ├─→ public
    │     ├─→ private
    │     └─→ protected
    ├─→ Defining Member Functions
    │     ├─→ Inside Class
    │     └─→ Outside Class (Scope Resolution)
    ├─→ Inline Member Functions
    ├─→ Nesting of Member Functions
    ├─→ Array of Objects
    ├─→ Object as Function Argument
    │     ├─→ Pass by Value
    │     ├─→ Pass by Reference
    │     └─→ Return Object from Function
    ├─→ Static Members
    │     ├─→ Static Data Members
    │     └─→ Static Member Functions
    ├─→ const Objects and Functions
    └─→ this Pointer

==============================================================================*/

/*==============================================================================
    🧩 Class & Object – Basic Concept
    --------------------------------------------------------------------------
    🔹 Class: User-defined data type containing data members & member functions.
    🔹 Object: Instance of a class that stores data and can call functions.
    🔹 Everything in c++ associated with classess and objects along with its attribute and methods.
    🔹 Attributes and methods are basically variables and functions that belongs to the calss.
    🔹 These are often refered as class members
    🔹 Syntax:
            class ClassName {
                AccessSpecifier:
                    data_members;
                    member_functions();
            };
            ClassName object_name;
==============================================================================*/
#include <iostream>
using namespace std;
class Car
{
public:
    string brand;
    string model;
    int year;

    void honk()
    {
        cout << "Beep Beep!" << endl;
    }
};
int main()
{
    // Create an object of Car
    Car carObj1;

    // Access attributes and set values
    carObj1.brand = "BMW";
    carObj1.model = "X5";
    carObj1.year = 1999;

    // Print attribute values
    cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << endl;

    // Call the honk method
    carObj1.honk();

    return 0;
}

/*==============================================================================
    🧩 Defining Member Functions (Inside / Outside)
    --------------------------------------------------------------------------
    🔹 Inside class → Automatically inline.
    🔹 Outside class → Use Scope Resolution (::) to link with class.
==============================================================================*/

#include <iostream>
using namespace std;
class Rectangle
{
private:
    double length;
    double width;

public:
    void setDimensions(double len, double wid);
    double area();
};
void Rectangle::setDimensions(double len, double wid)
{
    length = len;
    width = wid;
}
double Rectangle::area()
{
    return length * width;
}
int main()
{
    Rectangle rect;
    rect.setDimensions(10.0, 5.0);
    cout << "Area of Rectangle: " << rect.area() << endl;
    return 0;
}

/*==============================================================================
    🧩 Inline Member Functions
    --------------------------------------------------------------------------
    🔹 Inline functions are defined inside the class definition.
    🔹 The compiler attempts to expand inline fn at the point of call to reduce fn call overhead
    🔹 Reduces function call overhead (used for small functions).
==============================================================================*/

#include <iostream>
using namespace std;
class Circle{
private:
    double radius;

public:
    void setRadius(double r){
        radius = r;
    }
    double area(){
        return 3.14159 * radius * radius;
    }
};
int main(){
    Circle circ;
    circ.setRadius(5.0);
    cout << "Area of Circle: " << circ.area() << endl;
    return 0;
}

/*==============================================================================
    🧩 Nesting of Member Functions
    --------------------------------------------------------------------------
    🔹 When one member function calls another member function of same class.
    🔹 This is known as nesting of member functions.
==============================================================================*/

#include <iostream>
using namespace std;
class Square{
private:
    double side;

public:
    void setSide(double s) { side = s; }
    double area(){ return side * side; }
    double perimeter(){ return 4 * side; }

    void display(){
        cout << "Area: " << area() << endl;           // Calling area() function
        cout << "Perimeter: " << perimeter() << endl; // Calling perimeter() function
    }
};
int main(){
    Square sq;
    sq.setSide(4.0);
    sq.display();
    return 0;
}

/*==============================================================================
    🧩 Array of Objects
    --------------------------------------------------------------------------
    🔹 Used to store multiple objects of same class.
    🔹 You can create an array of objects to manage multiple instances of a class.
    🔹 Each object in the array can be accessed using its index.
==============================================================================*/

#include <iostream>
using namespace std;
class Student{
public:
    string name;
    int age;
    void display(){
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
int main(){
    const int size = 3;
    Student students[size];

    // Setting values for each student object
    students[0].name = "Alice";
    students[0].age = 20;

    students[1].name = "Bob";
    students[1].age = 22;

    students[2].name = "Charlie";
    students[2].age = 21;

    // Displaying student information
    for (int i = 0; i < size; i++){
        students[i].display();
    }

    return 0;
}

/*==============================================================================
    🧩 Object as Function Argument
    --------------------------------------------------------------------------
    🍁 Object can be passed:

    🔹 Pass by Value:
        → Function gets a copy of the object.
        → Modifications are local (original object unchanged).
    🔹 Pass by Reference:
        → Function gets the original object.
        → Modifications affect the actual object.
    🔹 Returning Object:
        → Function creates a temporary object and returns it.
        → The returned object can be assigned or used further.
==============================================================================*/

// 1️⃣ Pass by Value Example

#include <iostream>
using namespace std;
class Point{
    public:
        int x, y;
        void display(){
            cout << "Point(" << x << ", " << y << ")" << endl;
        }
};
void movePoint(Point p){ // Pass by Value
    p.x += 10;
    p.y += 10;
    cout << "Inside movePoint (by value): ";
    p.display();
}
int main(){
    Point pt;
    pt.x = 5;
    pt.y = 10;

    cout << "Before movePoint: ";
    pt.display();

    movePoint(pt); // Original object remains unchanged

    cout << "After movePoint: ";
    pt.display();

    return 0;
}

// 2️⃣ Pass by Reference Example

#include <iostream>
using namespace std;
class PointRef{
public:
    int x, y;
    void display(){
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
};
void movePointRef(PointRef &p) // Pass by Reference
{
    p.x += 10;
    p.y += 10;
    cout << "Inside movePointRef (by reference): ";
    p.display();
}
int main()
{
    PointRef pt;
    pt.x = 5;
    pt.y = 10;

    cout << "Before movePointRef: ";
    pt.display();

    movePointRef(pt); // Original object is modified

    cout << "After movePointRef: ";
    pt.display();

    return 0;
}

// 3️⃣ Return Object from Function

#include <iostream>
using namespace std;
class PointReturn{
public:
    int x, y;
    void display(){
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
};
PointReturn createPoint(int x, int y){ // Return Object

    PointReturn p;
    p.x = x;
    p.y = y;
    return p; // Returning object
}
int main()
{
    PointReturn pt = createPoint(15, 25); // Receiving returned object
    cout << "Created Point: ";
    pt.display();
    return 0;
}

/*==============================================================================
    🧩 const Objects & const Member Functions
    --------------------------------------------------------------------------
    🔹 const member functions → cannot modify data members.
    🔹 const objects → can only call const member functions.
==============================================================================*/

#include <iostream>
using namespace std;
class Immutable
{
private:
    int value;

public:
    Immutable(int val) : value(val) {}
    int getValue() const // const member function
    {
        return value;
    }
};
int main()
{
    const Immutable obj(42);                     // const object
    cout << "Value: " << obj.getValue() << endl; // Calling const member function
    return 0;
}

/*==============================================================================
    🧩 this Pointer
    --------------------------------------------------------------------------
    🔹 Points to current object of class.
    🔹 Used to resolve ambiguity between member variable and parameter.
    🔹 Can be used to return current object from member function.
    🔹 The this pointer is an implicit pointer available in all non-static member functions.
    🔹 It points to the object for which the member function is called.
==============================================================================*/

#include <iostream>
using namespace std;
class Fruits
{
private:
    string name;

public:
    void setName(string name)
    {
        this->name = name; // Using this pointer to distinguish between member and parameter
    }
    void display()
    {
        cout << "Fruit Name: " << this->name << endl; // Using this pointer
    }
};
int main()
{
    Fruits fruit;
    fruit.setName("Apple");
    fruit.display();
    return 0;
}
