/*
#__ Roadmap Object Oriented Programming __#

    OOPs in C++
    │
    ├── 1️⃣ Introduction to Object-Oriented Programming
    │   ├─→ What is OOP
    │   ├─→ Need / Advantages of OOP
    │   ├─→ Difference: POP vs OOP
    │   ├─→ Key Features of OOP
    │   │     ├─→ Class
    │   │     ├─→ Object
    │   │     ├─→ Abstraction
    │   │     ├─→ Encapsulation
    │   │     ├─→ Inheritance
    │   │     ├─→ Polymorphism
    │   │     ├─→ Message Passing
    │   │     └─→ Dynamic Binding
    │   ├─→ Object & Class Relationship
    │   └─→ Terminologies: Data Members, Member Functions, Methods, Messages
    │
    ├── 2️⃣ Class and Object
    │   ├─→ Defining a Class
    │   ├─→ Creating Objects
    │   ├─→ Access Specifiers
    │   │     ├─→ public
    │   │     ├─→ private
    │   │     └─→ protected
    │   ├─→ Defining Member Functions
    │   │     ├─→ Inside Class
    │   │     └─→ Outside Class (Scope Resolution)
    │   ├─→ Inline Member Functions
    │   ├─→ Nesting of Member Functions
    │   ├─→ Array of Objects
    │   ├─→ Object as Function Argument
    │   │     ├─→ Pass by Value
    │   │     ├─→ Pass by Reference
    │   │     └─→ Return Object from Function
    │   ├─→ Static Members
    │   │     ├─→ Static Data Members
    │   │     └─→ Static Member Functions
    │   ├─→ const Objects and Functions
    │   └─→ this Pointer
    │
    ├── 3️⃣ Constructors and Destructors
    │   ├─→ Introduction
    │   ├─→ Characteristics of Constructors
    │   ├─→ Types of Constructors
    │   │     ├─→ Default Constructor
    │   │     ├─→ Parameterized Constructor
    │   │     ├─→ Copy Constructor
    │   │     ├─→ Constructor with Default Arguments
    │   │     └─→ Constructor Overloading
    │   ├─→ Constructor Initialization List
    │   ├─→ Dynamic Constructor (using new)
    │   ├─→ Destructor
    │   ├─→ Order of Constructor / Destructor Calls
    │   ├─→ Shallow Copy vs Deep Copy
    │   ├─→ Implicit Copy Constructor
    │   └─→ Explicit Constructor Keyword
    │
    ├── 4️⃣ Encapsulation
    │   ├─→ Concept of Data Binding (Data + Function)
    │   ├─→ Data Hiding using Access Modifiers
    │   ├─→ Interfaces for Safe Access
    │   ├─→ Real-Life Examples (Bank Account, Student Info)
    │   └─→ Benefits of Encapsulation (Security, Maintainability)
    │
    ├── 5️⃣ Abstraction
    │   ├─→ Concept of Abstraction
    │   ├─→ Hiding Implementation Details
    │   ├─→ Showing Only Essential Features
    │   ├─→ Abstract Classes
    │   ├─→ Pure Virtual Functions
    │   └─→ Difference Between Abstraction & Encapsulation
    │
    ├── 6️⃣ Inheritance
    │   ├─→ Concept of Reusability
    │   ├─→ Base Class and Derived Class
    │   ├─→ Syntax and Access Control
    │   │     ├─→ public Inheritance
    │   │     ├─→ private Inheritance
    │   │     └─→ protected Inheritance
    │   ├─→ Types of Inheritance
    │   │     ├─→ Single Inheritance
    │   │     ├─→ Multiple Inheritance
    │   │     ├─→ Multilevel Inheritance
    │   │     ├─→ Hierarchical Inheritance
    │   │     └─→ Hybrid Inheritance
    │   ├─→ Constructor and Destructor in Inheritance
    │   ├─→ Function Overriding
    │   ├─→ Ambiguity in Multiple Inheritance
    │   │     ├─→ Scope Resolution Operator (::)
    │   │     └─→ Virtual Base Class
    │   ├─→ Order of Execution (Base → Derived)
    │   ├─→ Virtual Base Class
    │   └─→ Diamond Problem
    │
    ├── 7️⃣ Polymorphism
    │   ├─→ Meaning of Polymorphism ("Many Forms")
    │   ├─→ Types of Polymorphism
    │   │     ├─→ Compile-Time Polymorphism
    │   │     │     ├─→ Function Overloading
    │   │     │     ├─→ Operator Overloading
    │   │     │     └─→ Constructor Overloading
    │   │     └─→ Runtime Polymorphism
    │   │           ├─→ Virtual Functions
    │   │           ├─→ Function Overriding
    │   │           ├─→ Abstract Classes (Pure Virtual Functions)
    │   │           ├─→ Virtual Destructors
    │   │           └─→ Dynamic Binding (Late Binding)
    │   ├─→ vtable and vptr Concept
    │   ├─→ Rules for Virtual Functions
    │   └─→ Static vs Dynamic Binding
    │
    ├── 8️⃣ Friend Concept
    │   ├─→ Friend Function
    │   │     ├─→ Declaration and Syntax
    │   │     ├─→ Access to Private/Protected Members
    │   │     └─→ Use Cases (Operator Overloading, Two-Class Communication)
    │   ├─→ Friend Class
    │   │     ├─→ Relationship Between Classes
    │   │     └─→ Advantages and Risks
    │   └─→ Friend vs Member Function
    │
    ├── 9️⃣ Operator Overloading
    │   ├─→ Need for Operator Overloading
    │   ├─→ Rules & Limitations
    │   ├─→ Types of Operator Overloading
    │   │     ├─→ Unary Operators
    │   │     │     ├─→ ++, --, -, !
    │   │     └─→ Binary Operators
    │   │           ├─→ +, -, *, /, ==, !=, etc.
    │   ├─→ Overloading Using
    │   │     ├─→ Member Function
    │   │     └─→ Non-Member (Friend) Function
    │   ├─→ Assignment Operator Overloading (=)
    │   ├─→ Stream Operator Overloading (<<, >>)
    │   ├─→ Relational Operator Overloading
    │   ├─→ Function Call Operator Overloading (operator())
    │   └─→ Rules for Return Type and Arguments
    │
    ├── 🔟 Virtual Functions and Abstract Classes
    │   ├─→ Virtual Function Basics
    │   ├─→ Late Binding
    │   ├─→ Virtual Function Table (vtable)
    │   ├─→ Pure Virtual Functions
    │   ├─→ Abstract Classes
    │   ├─→ Rules for Abstract Classes
    │   ├─→ Virtual Destructors
    │   ├─→ Overriding and Hiding
    │   └─→ Example Hierarchies (Shape → Circle/Rectangle)
    │
    ├── 1️⃣1️⃣ Static Members
    │   ├─→ Static Data Members
    │   ├─→ Static Member Functions
    │   ├─→ Lifetime and Scope of Static Members
    │   ├─→ Initialization of Static Data
    │   └─→ Difference Between Static and Non-Static Members
    │
    ├── 1️⃣2️⃣ Type Casting in OOP
    │   ├─→ static_cast
    │   ├─→ dynamic_cast
    │   ├─→ const_cast
    │   └─→ reinterpret_cast
    │
    ├── 1️⃣3️⃣ Relationships Between Classes
    │   ├─→ Association
    │   ├─→ Aggregation
    │   ├─→ Composition
    │   ├─→ Dependency
    │   └─→ Real-Life Implementation Examples
    │
    └── 1️⃣4️⃣ Practical Implementation / Design
        ├─→ Applying All Four OOP Pillars Together
        ├─→ UML Class Diagrams (Basic Understanding)
        ├─→ Modular OOP Design
        ├─→ Example Mini Projects
        │     ├─→ Student Management System
        │     ├─→ Banking System
        │     ├─→ Employee Record System
        │     └─→ Shape/Geometry Hierarchy
        └─→ Best OOP Practices in C++
 
*/