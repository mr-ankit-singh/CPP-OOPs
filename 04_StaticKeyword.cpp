
/*==============================================================================
    🧩 Static Keyword in c++
    --------------------------------------------------------------------------

    🔹 In C++, static is a keyword or modifier that belongs to the type not instance. 
    🔹 So instance is not required to access the static members. 
    🔹 In C++, static can be field, method, constructor, class, properties, operator and event.

    🔹 We can define class member static using static keyword
    🔹 When we declare a member of class as static it means no matter how many object of class are created
    🔹 A static member is shared by all objects of the class.
    🔹 Exists even if no object is created.
    🔹 Static member functions can access only static data members.
    🔹 There is only one copy of the static member

    🧩 Static Data Members & Static Member Functions
    --------------------------------------------------------------------------
    🔹 Static Data Members
        → Shared among all objects of the class.
        → Only one copy exists, regardless of number of objects.
        → Initialized outside the class using scope resolution operator (::).
    🔹 Static Member Functions
        → Can access only static data members.
        → Called using ClassName::functionName().

==============================================================================*/

#include <iostream>
using namespace std;
class Counter {
private:
    static int count; // Static data member declaration
public:
    Counter() {
        count++; // Increment count whenever an object is created
    }
    static int getCount() { // Static member function
        return count; // Accessing static data member
    }
};
int Counter::count = 0; // Static data member definition and initialization
int main() {
    Counter c1;
    Counter c2;
    Counter c3;

    cout << "Number of Counter objects created: " << Counter::getCount() << endl;

    return 0;
}

/*==============================================================================
    🧩 Explanation:
    --------------------------------------------------------------------------
    🔹 In this example, we have a class Counter with a static data member count.
    🔹 Each time a Counter object is created, the constructor increments the count.
    🔹 The static member function getCount() returns the current value of count.
    🔹 Since count is static, it is shared among all instances of Counter, and there is only one copy of it.
    🔹 We define and initialize the static data member outside the class using the scope resolution operator (::).
==============================================================================*/