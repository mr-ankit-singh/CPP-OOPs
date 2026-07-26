/*==============================================================================
    🧩 Encapsulation
    ├─→ Concept of Data Binding (Data + Function)
    ├─→ Data Hiding using Access Modifiers
    ├─→ Interfaces for Safe Access
    ├─→ Real-Life Examples (Bank Account, Student Info)
    └─→ Benefits of Encapsulation (Security, Maintainability)
==============================================================================*/

/*==============================================================================
    🧩 Introduction of Encapsulation
    --------------------------------------------------------------------------
    🔹 Encapsulation is the process of wrapping data and methods into a single 
        unit while restricting direct access to the data using access specifiers 
        like private.
    🔹 Encapsulation: Bundling data and methods within a class.
    🔹 Data Hiding: Restricting direct access to some of an object's components.
    🔹 Access Modifiers: public, private, protected.
    🔹 Interfaces: Public methods to safely access and modify private data.
    🔹 Benefits: Improved security, maintainability, and modularity.

    🧩 Advantage
    ⁜  Data security.
    ⁜  Data hiding.
    ⁜  Controlled access using getters/setters.
    ⁜  Validation laga sakte hain.
    ⁜  Code maintainable aur reusable hota hai.
    ⁜  Internal implementation change karne par external code par kam effect padta hai.
==============================================================================*/

#include <iostream>
using namespace std;
class BankAccount{
private:
    string accountNumber;
    double balance;

public:
    BankAccount(string accNum, double initialBalance){
        accountNumber = accNum;
        balance = initialBalance;
    }
    void deposit(double amount){
        if (amount > 0){
            balance += amount;
            cout << "Deposited: " << amount << endl;
        }
        else{
            cout << "Invalid deposit amount!" << endl;
        }
    }
    void withdraw(double amount){
        if (amount > 0 && amount <= balance){
            balance -= amount;
            cout << "Withdrew: " << amount << endl;
        }
        else{
            cout << "Invalid withdrawal amount!" << endl;
        }
    }
    double getBalance() const {
        return balance;
    }
    string getAccountNumber() const {
        return accountNumber;
    }
};

int main(){
    BankAccount myAccount("123456789", 1000.0);
    cout << "Account Number: " << myAccount.getAccountNumber() << endl;
    cout << "Initial Balance: " << myAccount.getBalance() << endl;

    myAccount.deposit(500.0);
    cout << "Balance after deposit: " << myAccount.getBalance() << endl;

    myAccount.withdraw(200.0);
    cout << "Balance after withdrawal: " << myAccount.getBalance() << endl;

    myAccount.withdraw(2000.0); // Invalid withdrawal

    return 0;
}

/*==============================================================================
    🧩 Concept of Data Binding (Data + Function)
    --------------------------------------------------------------------------
    🔹 Encapsulation binds data members and member functions together.
    🔹 Data members hold the state, member functions define behavior.
==============================================================================*/

#include <iostream>
using namespace std;
class Student{
private:
    string name;
    int age;

public:
    void setDetails(string studentName, int studentAge){
        name = studentName;
        age = studentAge;
    }
    void displayDetails(){
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
int main(){
    Student student1;
    student1.setDetails("Alice", 20);
    student1.displayDetails();
    return 0;
}

/*==============================================================================
    🧩 Data Hiding using Access Modifiers
    --------------------------------------------------------------------------
    🔹 Use private access modifier to hide data members.
    🔹 Public member functions provide controlled access to private data.
==============================================================================*/

#include <iostream>
using namespace std;
class Employee{
private:
    // Private data members
    string name;
    double salary;

public:
    // Public member functions to access private data
    void setName(string empName){
        name = empName;
    }
    void setSalary(double empSalary){
        if (empSalary >= 0){
            salary = empSalary;
        }
        else{
            cout << "Invalid salary!" << endl;
        }
    }
    void displayInfo(){
        cout << "Employee Name: " << name << ", Salary: " << salary << endl;
    }
};
int main(){
    Employee emp;
    emp.setName("Bob");
    emp.setSalary(50000);
    emp.displayInfo();
    return 0;
}

/*==============================================================================
    🧩 Interfaces for Safe Access
    --------------------------------------------------------------------------
    🔹 Public getter and setter methods to access private data.
    🔹 Validate data in setter methods before modifying private members.
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
    void setPrice(double productPrice){
        if (productPrice >= 0){
            price = productPrice;
        }
        else{
            cout << "Invalid price!" << endl;
        }
    }
    // Getter methods
    string getProductName() const{
        return productName;
    }
    double getPrice() const{
        return price;
    }
};
int main(){
    Product prod;
    prod.setProductName("Laptop");
    prod.setPrice(1200.50);

    cout << "Product: " << prod.getProductName() << ", Price: " << prod.getPrice() << endl;
    return 0;
}

/*==============================================================================
    🧩 Benefits of Encapsulation (Security, Maintainability)
    --------------------------------------------------------------------------
    🔹 Security: Protects data from unauthorized access.
    🔹 Maintainability: Easier to modify and maintain code.
    🔹 Modularity: Encapsulated classes can be reused across projects.
==============================================================================*/

#include <iostream>
using namespace std;
class Square{
private:
    double side;

public:
    // Setter method with validation
    void setSide(double s){
        if (s >= 0){
            side = s;
        }
        else{
            cout << "Invalid side length!" << endl;
        }
    }
    double area(){
        return side * side;
    }
};
int main(){
    Square sq;
    sq.setSide(5.0);
    cout << "Area of square: " << sq.area() << endl;
    return 0;
}
