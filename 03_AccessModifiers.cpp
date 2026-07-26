/*==============================================================================
    🧩 Access Specifiers
    --------------------------------------------------------------------------
    🔹 Access specifiers define the scope and visibility of class members.
    🔸 public    → Accessible from anywhere.
    🔸 private   → Accessible only within the class.
    🔸 protected → Accessible within the class & derived classes.
    ⚙️ Default access specifier = private (if not mentioned)
==============================================================================*/

#include <iostream>
using namespace std;
class Box{
public:
    double length; // Public member
private:
    double width; // Private member
protected:
    double height; // Protected member
public:
    void setWidth(double wid) {
        width = wid; // Accessing private member within the class
    }
    double getWidth() {
        return width; // Accessing private member within the class
    }
    void setHeight(double hgt) {
        height = hgt; // Accessing protected member within the class
    }
    double getHeight() {
        return height; // Accessing protected member within the class
    }
};
int main()
{
    Box box;

    // Accessing public member
    box.length = 10.0;
    cout << "Length: " << box.length << endl;

    // Accessing private member through public methods
    box.setWidth(5.0);
    cout << "Width: " << box.getWidth() << endl;

    // Accessing protected member through public methods
    box.setHeight(7.0);
    cout << "Height: " << box.getHeight() << endl;

    return 0;
}

/********/

class MyClass {
  public:    // Public access specifier
    int x;   // Public attribute
  private:   // Private access specifier
    int y;   // Private attribute
};


class ProtectedAccess { 
    protected:        // protected access modifier
    int x;            // Data Member Declaration 
    void display();   // Member Function decaration
};

// Note: By default, all members of a class are private if you don't specify an access specifier.

class PrivateAccess {
    int x;   // Private attribute
    int y;   // Private attribute
};
