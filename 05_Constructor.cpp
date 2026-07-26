/*==============================================================================
   🧩 Constructors and Destructors
    ├─→ Introduction
    ├─→ Characteristics of Constructors
    ├─→ Types of Constructors
    │     ├─→ Default Constructor
    │     ├─→ Parameterized Constructor
    │     ├─→ Copy Constructor
    │     ├─→ Constructor with Default Arguments
    │     └─→ Constructor Overloading
    ├─→ Constructor Initialization List
    ├─→ Dynamic Constructor (using new)
    ├─→ Destructor
    ├─→ Order of Constructor / Destructor Calls
    ├─→ Shallow Copy vs Deep Copy
    ├─→ Implicit Copy Constructor
    └─→ Explicit Constructor Keyword
    │
==============================================================================*/

/*==============================================================================
    🧩 Introduction of Constructor
    --------------------------------------------------------------------------
    🔹 A constructor is a special member function that is automatically called when an object is created.
    🔹 It is used to initialize objects.
    🔹 The constructor has the same name as the class and does not have a return type.
    🔹 It can be defined inside or outside the class.
    🔹 It must be placed in the public section of the class.
    🔹 Constructors can also take parameters to allow for different initialization values.
==============================================================================*/

#include <iostream>
using namespace std;
class Sample{
public:
    // Constructor
    Sample(){
        cout << "Constructor called!" << endl;
    }
};
int main(){
    Sample obj; // Constructor is called here
    return 0;
}

/*==============================================================================
    🧩 Characteristics of Constructors
    --------------------------------------------------------------------------
    🔹 Name: Same as the class name.
    🔹 No Return Type: Constructors do not have a return type, not even void.
    🔹 Automatic Invocation: Called automatically when an object is created.
    🔹 Initialization: Primarily used to initialize member variables of the class.
    🔹 Access Specifier: Usually placed in the public section of the class.
    🔹 Overloading: Can be overloaded to provide different ways of initializing objects.
    🔹 No Explicit Call: Cannot be called explicitly like regular member functions.
==============================================================================*/

#include <iostream>
using namespace std;
class Demo{
private:
    int data;

public:
    // Constructor to initialize data
    Demo(int value){
        data = value;
        cout << "Constructor called! Data initialized to " << data << endl;
    }
};
int main()
{
    Demo obj(42); // Constructor is called here with parameter
    return 0;
}

/*==============================================================================
    🧩 Default Constructor
    --------------------------------------------------------------------------
    🔹 A constructor that takes no parameters.
    🔹 If no constructor is defined, the compiler provides a default constructor.
    🔹 Used to initialize objects with default values.
    🔹 Syntax:
        ClassName() {
            // constructor body
        }
==============================================================================*/

#include <iostream>
using namespace std;

class Employee{
public:
    // default constructor
    Employee(){
        cout << "Default Constructor Invoked" << endl;
    }
};

int main(void){
    Employee e1; // creating an object of Employee
    Employee e2;

    return 0;
}

/*==============================================================================
    🧩 Parameterized Constructor
    --------------------------------------------------------------------------
    🔹 A constructor that takes parameters to initialize an object with specific values.
    🔹 Allows different objects to be initialized with different values.
    🔹 It is used to provide different values to distinct objects.
    🔹 Syntax:
        ClassName(parameter_list) {
            // constructor body
        }
==============================================================================*/

#include <iostream>
using namespace std;
class Point{
private:
    int x, y;

public:
    // Parameterized constructor
    Point(int xCoord, int yCoord){
        x = xCoord;
        y = yCoord;
    }
    void display(){
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
};
int main(){
    Point p1(10, 20); // Creating object with specific values
    Point p2(30, 40);

    p1.display(); // Output: Point(10, 20)
    p2.display(); // Output: Point(30, 40)

    return 0;
}

/*==============================================================================
    🧩 Copy Constructor
    --------------------------------------------------------------------------
    🔹 The copy constructor in C++ is used to copy data of one object to another.
    🔹 Copy constructor takes a reference to an object of the same class as an argument.
    🔹 A constructor that creates a new object as a copy of an existing object.
    🔹 It takes a reference to an object of the same class as a parameter.
    🔹 Used for copying objects, especially when passing objects by value.
    🔹 Syntax:
        ClassName(const ClassName &obj) {
            // copy constructor body
        }
==============================================================================*/

#include <iostream>
using namespace std;
class Point{
private:
    int x, y;

public:
    // Parameterized constructor
    Point(int xCoord, int yCoord){
        x = xCoord;
        y = yCoord;
    }
    // Copy constructor
    Point(const Point &p){
        x = p.x;
        y = p.y;
    }
    void display(){
        cout << "Point(" << x << ", " << y << ")" << endl;
    }
    void translate(int dx, int dy){
        x += dx;
        y += dy;
    }
};
void movePoint(Point p, int dx, int dy){
    p.translate(dx, dy);
    p.display();
}
int main(){
    Point p1(10, 20); // Creating object with specific values
    Point p2 = p1;    // Copy constructor is called here

    p1.display(); // Output: Point(10, 20)
    p2.display(); // Output: Point(10, 20)

    return 0;
}

/*==============================================================================
    🧩 Copy Constructor Example
==============================================================================*/

#include <iostream>
using namespace std;
class Wall{
private:
    double length;
    double height;

public:
    // parameterized constructor
    Wall(double len, double hgt){
        length = len;
        height = hgt;
    }
    // copy constructor
    Wall(Wall &obj){
        length = obj.length;
        height = obj.height;
    }
    double calculateArea(){
        return length * height;
    }
};
int main(){
    // create an object of Wall class
    Wall wall1(10.5, 8.6);
    // copy contents of wall1 to wall2
    Wall wall2 = wall1;
    // print areas of wall1 and wall2
    cout << "Area of Wall 1: " << wall1.calculateArea() << endl;
    cout << "Area of Wall 2: " << wall2.calculateArea();
    return 0;
}

/*==============================================================================
    🧩 Defining Constructor Outside the Class
    --------------------------------------------------------------------------
    🔹 Constructors can be defined outside the class using the scope resolution operator (::).
    🔹 This helps in separating the class declaration from the implementation.
    🔹 Syntax:
        ClassName::ConstructorName(parameter_list) {
            // constructor body
        }
==============================================================================*/

#include <iostream>
#include <cstring>
using namespace std;
class Student{
private:
    int rno;
    char name[50];
    double fee;

public:
    Student(); // Constructor declaration
    void display();
};
// Constructor definition outside the class
Student::Student(){
    rno = 0;
    strcpy(name, "Unknown");
    fee = 0.0;
}
void Student::display(){
    cout << "Roll No: " << rno << ", Name: " << name << ", Fee: " << fee << endl;
}
int main(){
    Student s; // Constructor is called here
    s.display();
    return 0;
}


/*==============================================================================
    🧩 Constractor with default Argument
    --------------------------------------------------------------------------
    🔹 A constructor can have default arguments.
    🔹 This allows the constructor to be called with fewer arguments than it is defined to accept.
    🔹 If an argument is not provided, the default value is used.
    🔹 Syntax:
        ClassName(parameter_list_with_default_values) {
            // constructor body
        }
==============================================================================*/
#include <iostream>
using namespace std;
class Circle{
private:
    double radius;
public:
    Circle(){}
    // Constructor with default argument
    Circle(double r = 1.0){
        radius = r;
    }
    double area(){
        return 3.14159 * radius * radius;
    }
};
int main()
{
    Circle c1(105);  // Calls constructor with default radius 1.0
    Circle c2(5.0);  // Calls constructor with radius 5.0

    cout << "Area of Circle c1 (default radius): " << c1.area() << endl;
    cout << "Area of Circle c2 (radius 5.0): " << c2.area() << endl;

    return 0;
}


/*==============================================================================
    🧩 Constructor Overloading
    --------------------------------------------------------------------------
    🔹 C++ allows multiple constructors in a class with different parameter lists.
    🔹 This is known as constructor overloading.
    🔹 It enables the creation of objects in different ways.
    🔹 Constructors can be overloaded in a similar way as function overloading.
    🔹 Overloaded constructors have the same name (name of the class)
    🔹 But the different number  and types of arguments.
    🔹 Depending upon the number and type of arguments passed,the corresponding constructor is called.

    🔹 Syntax:
        ClassName() {
            // default constructor
        }
        ClassName(parameter_list) {
            // parameterized constructor
        }
==============================================================================*/

#include <iostream>
using namespace std;
class Box{
private:
    double length;
    double breadth;
public:
    // Default constructor
    Box(){
        length = 1.0;
        breadth = 1.0;
    }
    // Parameterized constructor
    Box(double l, double b){
        length = l;
        breadth = b;
    }
    void display(){
        cout << "Length: " << length << ", Breadth: " << breadth << endl;
    }
};
int main(){
    Box box1;           // Calls default constructor
    Box box2(5.0, 3.0); // Calls parameterized constructor

    box1.display(); // Output: Length: 1, Breadth: 1
    box2.display(); // Output: Length: 5, Breadth: 3

    return 0;
}


//************************************/

#include <iostream>
using namespace std;

class Room{
private:
   double length;
   double breadth;

public:
    // 1. Constructor with no arguments
    Room(){
       length = 6.9;
       breadth = 4.2;
    }
 
    // 2. Constructor with two arguments
    Room(double l, double b){
       length = l;
       breadth = b;
    }
    // 3. Constructor with one argument
    Room(double len){
       length = len;
       breadth = 7.2;
    }
 
    double calculateArea(){
       return length * breadth;
    }
};

int main(){
   Room room1, room2(8.2, 6.6), room3(8.2);

   cout << "When no argument is passed: " << endl;
   cout << "Area of room = " << room1.calculateArea() << endl;

   cout << "\nWhen (8.2, 6.6) is passed." << endl;
   cout << "Area of room = " << room2.calculateArea() << endl;

   cout << "\nWhen breadth is fixed to 7.2 and (8.2) is passed:" << endl;
   cout << "Area of room = " << room3.calculateArea() << endl;

   return 0;
}


/*==============================================================================
    🧩 Constructor Initialization List
    --------------------------------------------------------------------------
    🔹 A constructor initialization list allows you to initialize member variables 
       before the constructor body executes.
    🔹 It is more efficient than assigning values inside the constructor body.
    🔹 Syntax:
        ClassName(parameter_list) : member1(value1), member2(value2) {
            // constructor body
        }
==============================================================================*/

#include <iostream>
using namespace std;
class Rectangle{
private:
    double length;
    double width;
public:
    // Constructor with initialization list
    Rectangle(double len, double wid) : length(len), width(wid){
        // constructor body (if needed)
    }
    double area(){
        return length * width;
    }
};
int main(){
    Rectangle rect(10.0, 5.0);
    cout << "Area of Rectangle: " << rect.area() << endl;
    return 0;
}


/*==============================================================================
    🧩 Dynamic Constructor (using new)
    --------------------------------------------------------------------------
    🔹 You can create objects dynamically using the new keyword.
    🔹 This allows for runtime allocation of objects.
    🔹 Syntax:
        ClassName *obj = new ClassName(parameter_list);
    🔹 Remember to delete the dynamically allocated object using delete to free memory.
==============================================================================*/

#include <iostream>
using namespace std;
class Circle{
private:
    double radius;
public:
    // Parameterized constructor
    Circle(double r){
        radius = r;
    }
    double area(){
        return 3.14159 * radius * radius;
    }
};
int main()
{
    // Dynamically creating an object of Circle
    Circle *circ = new Circle(5.0);

    cout << "Area of Circle: " << circ->area() << endl;

    // Freeing the allocated memory
    delete circ;

    return 0;
}



/*==============================================================================
    🧩 Destructor in c++
    --------------------------------------------------------------------------        
    🔹 A destructor is called automatically when the object goes out of scope.
    🔹 It is used to release resources that were allocated to the object during its lifetime.
    🔹 If you do not define a destructor, the compiler provides a default destructor.
    🔹 Destructors cannot be overloaded and cannot be inherited.
    🔹 In C++,a destructor name is the same as the Class Name preceded by a tilde (~).
    🔹 And it does not have a return type and it does not take any parameters.
    🔹 Destructors are called in the reverse order of the constructors.

    🔹 Destructors cannot be declared const, volatile, const volatile or static.
    🔹 A destructor can be declared virtual or pure virtual.
    🔹 It must be placed in the public section of the class.

    🔹 A destructor can be declared inside the class or outside the class using scope resolution operator(::).

    🔹 Syntax:
        class <class-name> {
            public:
            <class-name>();       // Constructor for class
            --------------
            ~ <class-name>();    // Destructor for class
        };
        OR
        <class-name>: : ~ <class-name>()   <-- Outside the class

==============================================================================*/

#include <iostream>
using namespace std;
class Test
{
public:
    Test(){
        cout << "\n Constructor executed";
    }
    ~Test(){
        cout << "\n Destructor executed";
    }
};
int main(){
    Test t;   // Constructor is called here
    return 0; // Destructor is called here when t goes out of scope
}

/*==============================================================================
    🧩 Destructor Definition Outside the Class
    --------------------------------------------------------------------------
    🔹 Destructors can be defined outside the class using the scope resolution operator (::).
    🔹 This helps in separating the class declaration
        from the implementation.
    🔹 Syntax:
        ClassName::~ClassName() {
            // destructor body
        }
==============================================================================*/

#include <iostream>
using namespace std;
class Test{
public:
    Test(){
        cout << "\n Constructor executed";
    }
    ~Test(); // Destructor declaration
};
// Destructor definition outside the class
Test::~Test(){
    cout << "\n Destructor executed";
}
int main(){
    Test t;   // Constructor is called here
    return 0; // Destructor is called here when t goes out of scope
}

/*==============================================================================
    🧩 Destructor Example with Copy Constructor
==============================================================================*/

#include <iostream>
using namespace std;
class Wall{
private:
    double length;
    double height;

public:
    // parameterized constructor
    Wall(double len, double hgt){
        length = len;
        height = hgt;
    }
    // copy constructor
    Wall(Wall &obj){
        length = obj.length;
        height = obj.height;
    }
    double calculateArea(){
        return length * height;
    }
    // destructor
    ~Wall(){
        cout << "\nDestructor called for Wall object with area: " << calculateArea() << endl;
    }
};
int main(){
    // create an object of Wall class
    Wall wall1(10.5, 8.6);
    // copy contents of wall1 to wall2
    Wall wall2 = wall1;
    // print areas of wall1 and wall2
    cout << "Area of Wall 1: " << wall1.calculateArea() << endl;
    cout << "Area of Wall 2: " << wall2.calculateArea();
    return 0;
}


/*==============================================================================
    🧩 Order of Constructor / Destructor Calls
    --------------------------------------------------------------------------
    🔹 When multiple objects are created, constructors are called in the order of their creation.
    🔹 Destructors are called in the reverse order of the constructors.
    🔹 For dynamically allocated objects, destructors are called when delete is used.

    🔹 This ensures proper resource management and cleanup.
==============================================================================*/

#include <iostream>
using namespace std;
class Sample{
public:
    Sample(){
        cout << "Constructor called!" << endl;
    }
    ~Sample(){
        cout << "Destructor called!" << endl;
    }
};
int main(){
    cout << "Creating first object:" << endl;
    Sample obj1; // Constructor called

    {
        cout << "Creating second object inside block:" << endl;
        Sample obj2; // Constructor called
        cout << "Exiting block:" << endl;
    } // Destructor called for obj2 here

    cout << "Back to main function:" << endl;
    return 0; // Destructor called for obj1 here
}


/*==============================================================================
    🧩 Shallow Copy vs Deep Copy
    --------------------------------------------------------------------------
    🔹 Shallow Copy:
        → Copies all member values as they are.
        → If the object contains pointers, only the pointer addresses are copied.
        → Both objects point to the same memory location for dynamic data.
        → Changes made through one object affect the other.
    🔹 Deep Copy:
        → Creates a new copy of all member values.
        → If the object contains pointers, new memory is allocated and the data is copied.
        → Both objects have their own separate copies of dynamic data.
        → Changes made through one object do not affect the other.
    🔹 Deep copy is essential when dealing with dynamic memory allocation to avoid issues like double deletion.
    
==============================================================================*/

#include <iostream>
#include <cstring>
using namespace std;
class Shallow{
private:
    char *data;
public:
    // Constructor
    Shallow(const char *str){
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    // Copy Constructor (Shallow Copy)
    Shallow(const Shallow &obj){
        data = obj.data; // Copying pointer address (shallow copy)
    }
    void display(){
        cout << "Data: " << data << endl;
    }
    ~Shallow(){
        delete[] data; // Destructor
    }
};
int main(){
    Shallow obj1("Hello, World!");
    Shallow obj2 = obj1; // Shallow copy

    obj1.display();
    obj2.display();

    return 0;
}

//************************/


#include <iostream>
#include <cstring>
using namespace std;
class Deep{
private:
    char *data;
public:
    // Constructor
    Deep(const char *str){
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    // Copy Constructor (Deep Copy)
    Deep(const Deep &obj){
        data = new char[strlen(obj.data) + 1]; // Allocating new memory
        strcpy(data, obj.data);                 // Copying data (deep copy)
    }
    void display(){
        cout << "Data: " << data << endl;
    }
    ~Deep(){
        delete[] data; // Destructor
    }
};
int main(){
    Deep obj1("Hello, World!");
    Deep obj2 = obj1; // Deep copy

    obj1.display();
    obj2.display();

    return 0;
}


/*==============================================================================
    🧩 Implicit Copy Constructor
    --------------------------------------------------------------------------
    🔹 If no copy constructor is defined, the compiler provides an implicit copy constructor.
    🔹 The implicit copy constructor performs a shallow copy of the object's members.
    🔹 It copies all member values as they are, including pointer addresses.
    🔹 This can lead to issues like double deletion if the object contains dynamic memory.
    🔹 It is advisable to define a custom copy constructor for classes that manage dynamic memory.
==============================================================================*/

#include <iostream>
#include <cstring>
using namespace std;
class ImplicitCopy{
private:
    char *data;
public:
    // Constructor
    ImplicitCopy(const char *str){
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    void display(){
        cout << "Data: " << data << endl;
    }
    ~ImplicitCopy(){
        delete[] data; // Destructor
    }
};
int main(){
    ImplicitCopy obj1("Hello, World!");
    ImplicitCopy obj2 = obj1; // Implicit copy constructor (shallow copy)

    obj1.display();
    obj2.display();

    return 0;
}


/*==============================================================================
    🧩 Explicit Constructor Keyword
    --------------------------------------------------------------------------
    🔹 The explicit keyword is used to prevent implicit conversions and copy-initialization.
    🔹 It is applied to constructors that can be called with a single argument.
    🔹 When a constructor is declared explicit, it cannot be used for implicit conversions.
    🔹 This helps to avoid unintended conversions that may lead to errors.
    🔹 Syntax:
        explicit ClassName(parameter_list) {
            // constructor body
        }
==============================================================================*/

#include <iostream>
using namespace std;
class ExplicitExample{
private:
    int value;
public:

    // Explicit constructor
    explicit ExplicitExample(int val){
        value = val;
    }
    void display(){
        cout << "Value: " << value << endl;
    }
};
int main(){
    ExplicitExample obj1(42); // Direct initialization (allowed)
    obj1.display();

    // ExplicitExample obj2 = 42; // Copy initialization (not allowed, would cause a compile-time error)

    return 0;
}


/*==============================================================================
    🧩 Explanation:
    --------------------------------------------------------------------------
    🔹 In this example, the constructor of ExplicitExample is declared with the explicit keyword.
    🔹 This prevents the compiler from using it for implicit conversions.
    🔹 The line that attempts to create obj2 using copy initialization is commented out,
       as it would cause a compile-time error.
    🔹 This ensures that objects of ExplicitExample can only be created through direct initialization,
       reducing the risk of unintended conversions.
==============================================================================*/



