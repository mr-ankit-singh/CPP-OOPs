/*==============================================================================
  🧩 Abstraction
   ├─→ Concept of Abstraction
   ├─→ Hiding Implementation Details
   ├─→ Showing Only Essential Features
   ├─→ Abstract Classes
   ├─→ Pure Virtual Functions
   └─→ Difference Between Abstraction & Encapsulation

==============================================================================*/

/*==============================================================================
    🧩 Introduction of Abstraction
    --------------------------------------------------------------------------
    🔹 Abstraction means SHOWING ONLY the ESSENTIAL, RELEVANT features of
       something to the USER, while HIDING all the COMPLEX, INTERNAL
       implementation details that the user doesn't NEED to know about.
    🔸 Simple words: The user knows WHAT something does — NOT HOW it does
       it internally.

    ⚙️ Real-Life Analogy: Jab tum CAR chalate ho, tumhe sirf ITNA pata
       hona chahiye — STEERING ghumao, ACCELERATOR dabao, BRAKE lagao.
       Tumhe ye JAANNE ki ZAROORAT NAHI hai ki ENGINE ke ANDAR, FUEL
       INJECTION, COMBUSTION, PISTONS — SAB EXACTLY KAISE kaam kar rahe
       hain. Wo COMPLEXITY, CAR ke "INTERFACE" (steering, pedals) ke
       PEECHE, HIDDEN hai.
    🔹 In C++, Abstraction usually achieve hota hai:
         - CLASSES ke through — sirf PUBLIC members (interface) EXPOSE
           karke, PRIVATE members (implementation) ko HIDE karke
         - ABSTRACT CLASSES ke through — pure virtual functions se, ek
           "WHAT to do" define karna, bina "HOW" bataye (ye advanced
           topic, ALAG SE cover hoga)

==============================================================================*/


/*------------------------------------------------------------------------
    Simple Example — Abstraction via a Class
    --------------------------------------------------------------------
    🔹 User ko sirf "startCar()" function ka pata hai — CALL karne se,
       CAR start ho jaati hai.
    🔸 User ko ye JAANNE ki ZAROORAT NAHI ki, ANDAR, kaunsa "IGNITION
       SEQUENCE", "FUEL PUMP ACTIVATION" waghera CHAL raha hai — WO
       SAARI COMPLEXITY, PRIVATE section mein, HIDDEN hai.
------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

class Car1 {
private:
    // Complex, INTERNAL details — user ko in FUNCTIONS ka DIRECTLY
    // ACCESS NAHI milta (HIDDEN implementation)
    void igniteFuel() {
        cout << "Fuel ignited..." << endl;
    }
    void engageIgnition() {
        cout << "Ignition engaged..." << endl;
    }
 
public:
    // SIMPLE, ESSENTIAL interface — user ko SIRF YE dikhta/pata hai
    void startCar() {
        engageIgnition();
        igniteFuel();
        cout << "Car started! Ready to drive." << endl;
    }
};
 
int main() {
    Car1 myCar;
 
    // User, SIRF "startCar()" CALL karta hai — internal STEPS
    // (igniteFuel, engageIgnition) ke baare mein SOCHTA hi NAHI
    myCar.startCar();
 
    return 0;
}

/*==============================================================================
    ⚡ Why Abstraction Matters
    --------------------------------------------------------------------------
    🔹 Reduces COMPLEXITY for the user — sirf ZAROORI cheez dikhti hai,
       BAAKI sab, BACKGROUND mein, MANAGE ho jaata hai.
    🔸 Changes, INTERNAL implementation mein, AASANI se ki ja sakti hain
       — bina USER-FACING interface ko TOUCH kiye (jaise, "igniteFuel()"
       ke ANDAR ka logic BADAL bhi do, "startCar()" CALL karne wale ko
       KUCH FARAK nahi padega).
    🔹 CODE, SAAF aur MAINTAINABLE rehta hai — kyunki "WHAT" aur "HOW",
       CLEARLY SEPARATE rehte hain.
==============================================================================*/




#include <iostream>
using namespace std;
class TV
{
public:
    void turnOn(){
        cout << "TV is now ON." << endl;
    }
    void turnOff(){
        cout << "TV is now OFF." << endl;
    }
    void changeChannel(int channel){
        cout << "Changing to channel " << channel << "." << endl;
    }
};
int main()
{
    TV myTV;
    myTV.turnOn();
    myTV.changeChannel(5);
    myTV.turnOff();
    return 0;
}

/*==============================================================================
    🧩 Hiding Implementation Details
    --------------------------------------------------------------------------
    🔹 Users interact with high-level interfaces.
    🔹 Internal workings are hidden to reduce complexity.
    🔹 Example: Using a TV remote without knowing its circuitry.
==============================================================================*/

#include <iostream>
using namespace std;
class Car
{
public:
    void startEngine(){
        cout << "Engine started." << endl;
    }
    void stopEngine(){
        cout << "Engine stopped." << endl;
    }
    void accelerate(int speed){
        cout << "Accelerating to " << speed << " km/h." << endl;
    }
};
int main()
{
    Car myCar;
    myCar.startEngine();
    myCar.accelerate(60);
    myCar.stopEngine();
    return 0;
}


/*==============================================================================
    🧩 Showing Only Essential Features
    --------------------------------------------------------------------------
    🔹 Provide simple interfaces for complex systems.
    🔹 Users can perform tasks without understanding internal complexity.
    🔹 Example: Using a smartphone without knowing its hardware details.
==============================================================================*/

#include <iostream>
using namespace std;
class Smartphone
{
public:
    void makeCall(string number){
        cout << "Calling " << number << "..." << endl;
    }
    void sendMessage(string number, string message){
        cout << "Sending message to " << number << ": " << message << endl;
    }
    void browseInternet(string url){
        cout << "Browsing to " << url << "..." << endl;
    }
};
int main()
{
    Smartphone myPhone;
    myPhone.makeCall("123-456-7890");
    myPhone.sendMessage("123-456-7890", "Hello!");
    myPhone.browseInternet("www.example.com");
    return 0;
}


/*==============================================================================
    🧩 Abstract Classes
    --------------------------------------------------------------------------
    🔹 An Abstract Class is a class that cannot be instantiated and contains at least 
        one pure virtual function, which must be implemented by its derived classes.
    🔹 Cannot be instantiated directly.
    🔹 Serve as blueprints for derived classes.
    🔹 Contain at least one pure virtual function.
==============================================================================*/

#include <iostream>
using namespace std;
class Animal
{
public:
    virtual void sound() = 0; // Pure virtual function
};
class Dog : public Animal
{
public:
    void sound() override {
        cout << "Woof Woof!" << endl;
    }
};
class Cat : public Animal
{
public:
    void sound() override {
        cout << "Meow Meow!" << endl;
    }
};
int main() {
    Dog dog;
    Cat cat;

    dog.sound();
    cat.sound();

    return 0;
}


/*==============================================================================
    🧩 Pure Virtual Functions
    --------------------------------------------------------------------------
    🔹 Declared by assigning 0 in declaration.
    🔹 Must be overridden in derived classes.
    🔹 Makes a class abstract.
    
==============================================================================*/

#include <iostream>
using namespace std;
class Shape{
    public:
        virtual double area() = 0; // Pure virtual function
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
        double area() override{
            return 3.14159 * radius * radius;
        }
};

int main(){
    Rectangle rect(10.0, 5.0);
    Circle circ(7.0);

    cout << "Area of Rectangle: " << rect.area() << endl;
    cout << "Area of Circle: " << circ.area() << endl;

    return 0;
}


/*==============================================================================
    🧩 Difference Between Abstraction & Encapsulation
    --------------------------------------------------------------------------
    🔹 Abstraction: Hides complexity by exposing only essential features.
    🔹 Encapsulation: Bundles data and methods, restricting direct access.
    🔹 Abstraction focuses on "what" an object does, while encapsulation focuses on "how" it does it.
==============================================================================*/

#include <iostream>
using namespace std;
class Product{
private:
    string productName;
    double price;
public:
    // Setter methods
    void setProductName(string name){
        productName = name;
    }
    void setPrice(double p){
        price = p;
    }
    // Other methods can be added here
};
int main(){
    Product prod;
    prod.setProductName("Laptop");
    prod.setPrice(1200.50);
    return 0;
}

