/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                     C++ OOP (OBJECT ORIENTED PROGRAMMING)                 ║
 * ║                                  ROADMAP                                  ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  What is OOP?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ OOP = write a program as a group of OBJECTS
 *  ✔ Object = data (what it HAS) + functions (what it DOES)
 *        Car → data: color, speed      functions: start(), brake()
 *  ✔ Class = the blueprint, Object = the real thing made from it
 *  ✔ 4 pillars:
 *        a. Encapsulation → keep data + functions together, hide data
 *        b. Abstraction   → show only what is needed, hide the "how"
 *        c. Inheritance   → a new class reuses an old class
 *        d. Polymorphism  → same name, different behaviour
 *
 *        ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
 *        │    CLASS    │ ──► │   OBJECT    │ ──► │   MESSAGE   │
 *        │ (blueprint) │     │ (real thing)│     │ (fn call)   │
 *        └─────────────┘     └─────────────┘     └─────────────┘
 *
 *  How to read this roadmap
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ Go from top to bottom — each topic needs the ones above it
 *  ✔ (NEW) → topic that was missing in the old roadmap, now added
 *  ✔ ⭐    → very important for interviews
 *  ✔ Which file has which topic → see section 2
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   1)  FULL ROADMAP — TREE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   C++ OOP
 *   │
 *   ├── 1. INTRODUCTION TO OOP
 *   │   ├── What is OOP
 *   │   ├── Need / Advantages of OOP
 *   │   ├── POP vs OOP  ⭐
 *   │   ├── Key Features of OOP
 *   │   │   ├── Class
 *   │   │   ├── Object
 *   │   │   ├── Abstraction
 *   │   │   ├── Encapsulation
 *   │   │   ├── Inheritance
 *   │   │   ├── Polymorphism
 *   │   │   ├── Message Passing
 *   │   │   └── Dynamic Binding
 *   │   ├── Object & Class Relationship
 *   │   ├── Terms: Data Members, Member Functions, Methods, Messages
 *   │   └── C++ is multi-paradigm (procedural + OOP + generic)  (NEW)
 *   │
 *   ├── 2. CLASS AND OBJECT
 *   │   ├── Defining a Class
 *   │   ├── Creating Objects
 *   │   ├── class vs struct (default public / private)  ⭐  (NEW)
 *   │   ├── Access Specifiers
 *   │   │   ├── public
 *   │   │   ├── private
 *   │   │   └── protected
 *   │   ├── Defining Member Functions
 *   │   │   ├── Inside Class
 *   │   │   └── Outside Class (Scope Resolution ::)
 *   │   ├── Inline Member Functions
 *   │   ├── Nesting of Member Functions
 *   │   ├── Array of Objects
 *   │   ├── Object as Function Argument
 *   │   │   ├── Pass by Value
 *   │   │   ├── Pass by Reference
 *   │   │   ├── Pass by const Reference  (NEW)
 *   │   │   └── Return Object from Function
 *   │   ├── this Pointer  ⭐
 *   │   │   └── return *this → method chaining  (NEW)
 *   │   ├── const Objects and const Member Functions
 *   │   ├── mutable Data Members  (NEW)
 *   │   ├── Getters and Setters  (NEW)
 *   │   ├── Size of an Object (empty class = 1 byte)  ⭐  (NEW)
 *   │   ├── Anonymous / Temporary Objects  (NEW)
 *   │   ├── Nested Class  (NEW)
 *   │   ├── Local Class (class inside a function)  (NEW)
 *   │   ├── Forward Declaration of a Class  (NEW)
 *   │   └── Class in Header (.h) + Source (.cpp) files  (NEW)
 *   │
 *   ├── 3. CONSTRUCTORS AND DESTRUCTORS
 *   │   ├── Introduction
 *   │   ├── Characteristics of Constructors
 *   │   ├── Types of Constructors
 *   │   │   ├── Default Constructor
 *   │   │   ├── Parameterized Constructor
 *   │   │   ├── Copy Constructor  ⭐
 *   │   │   ├── Move Constructor (C++11)  ⭐  (NEW)
 *   │   │   ├── Conversion Constructor (one argument)  (NEW)
 *   │   │   ├── Constructor with Default Arguments
 *   │   │   └── Constructor Overloading
 *   │   ├── Constructor Initialization List  ⭐
 *   │   │   └── Init order = declaration order, not list order  (NEW)
 *   │   ├── In-class Member Initializers (C++11)  (NEW)
 *   │   ├── Delegating Constructor (C++11)  (NEW)
 *   │   ├── = default and = delete  (NEW)
 *   │   ├── explicit Constructor Keyword
 *   │   ├── Uniform / Brace Initialization { }  (NEW)
 *   │   ├── Dynamic Constructor (using new)
 *   │   ├── Destructor
 *   │   ├── Order of Constructor / Destructor Calls
 *   │   ├── Implicit (compiler-made) Copy Constructor
 *   │   ├── Shallow Copy vs Deep Copy  ⭐
 *   │   ├── Copy Assignment vs Move Assignment  (NEW)
 *   │   ├── Rule of 0 / Rule of 3 / Rule of 5  ⭐  (NEW)
 *   │   ├── Copy Elision / RVO (Return Value Optimization)  (NEW)
 *   │   ├── Private Constructor (stop object creation)  (NEW)
 *   │   └── RAII (constructor gets, destructor frees)  ⭐  (NEW)
 *   │
 *   ├── 4. ENCAPSULATION
 *   │   ├── Data Binding (Data + Function together)
 *   │   ├── Data Hiding using Access Modifiers
 *   │   ├── Interfaces for Safe Access
 *   │   ├── Setters with Validation (keep data always correct)  (NEW)
 *   │   ├── const-correctness  (NEW)
 *   │   ├── ⚠ Returning reference to private data breaks it  (NEW)
 *   │   ├── Real-Life Examples (Bank Account, Student Info)
 *   │   └── Benefits (Security, Maintainability)
 *   │
 *   ├── 5. ABSTRACTION
 *   │   ├── Concept of Abstraction
 *   │   ├── Hiding Implementation Details
 *   │   ├── Showing Only Essential Features
 *   │   ├── Abstract Classes
 *   │   ├── Pure Virtual Functions
 *   │   ├── Interface (class with ONLY pure virtual functions)  (NEW)
 *   │   ├── Abstraction using header files  (NEW)
 *   │   └── Abstraction vs Encapsulation  ⭐
 *   │
 *   ├── 6. INHERITANCE
 *   │   ├── Concept of Reusability
 *   │   ├── Base Class and Derived Class
 *   │   ├── IS-A vs HAS-A  ⭐  (NEW)
 *   │   ├── Syntax and Access Control
 *   │   │   ├── public Inheritance
 *   │   │   ├── private Inheritance
 *   │   │   ├── protected Inheritance
 *   │   │   └── Access table (what becomes what)  ⭐  (NEW)
 *   │   ├── Types of Inheritance
 *   │   │   ├── Single Inheritance
 *   │   │   ├── Multiple Inheritance
 *   │   │   ├── Multilevel Inheritance
 *   │   │   ├── Hierarchical Inheritance
 *   │   │   └── Hybrid Inheritance
 *   │   ├── Constructor and Destructor in Inheritance
 *   │   │   ├── Order of Execution (Base → Derived)
 *   │   │   ├── Calling Base Constructor with arguments  (NEW)
 *   │   │   └── Inheriting Constructors (using Base::Base)  (NEW)
 *   │   ├── Function Overriding
 *   │   │   └── Calling the Base version (Base::show())  (NEW)
 *   │   ├── Name Hiding + using Base::func  (NEW)
 *   │   ├── Ambiguity in Multiple Inheritance
 *   │   │   ├── Scope Resolution Operator (::)
 *   │   │   └── Virtual Base Class
 *   │   ├── Diamond Problem  ⭐
 *   │   ├── final class / final function (C++11)  (NEW)
 *   │   ├── Upcasting and Downcasting  (NEW)
 *   │   ├── Object Slicing  ⭐  (NEW)
 *   │   └── What is NOT inherited (ctor, dtor, friend, =)  (NEW)
 *   │
 *   ├── 7. POLYMORPHISM
 *   │   ├── Meaning ("Many Forms")
 *   │   ├── Compile-Time Polymorphism (Static Binding)
 *   │   │   ├── Function Overloading
 *   │   │   ├── Operator Overloading
 *   │   │   ├── Constructor Overloading
 *   │   │   └── Templates  (NEW)
 *   │   ├── Runtime Polymorphism (Dynamic Binding)
 *   │   │   ├── Virtual Functions
 *   │   │   ├── Function Overriding
 *   │   │   ├── override keyword (C++11)  ⭐  (NEW)
 *   │   │   ├── Abstract Classes (Pure Virtual Functions)
 *   │   │   ├── Virtual Destructors  ⭐
 *   │   │   └── Dynamic Binding (Late Binding)
 *   │   ├── Static vs Dynamic Binding  ⭐
 *   │   ├── Overloading vs Overriding vs Hiding  ⭐  (NEW)
 *   │   ├── Covariant Return Types  (NEW)
 *   │   ├── Static Polymorphism with CRTP  (NEW)
 *   │   └── std::variant + std::visit (no virtual)  (NEW)
 *   │
 *   ├── 8. FRIEND CONCEPT
 *   │   ├── Friend Function
 *   │   │   ├── Declaration and Syntax
 *   │   │   ├── Access to Private/Protected Members
 *   │   │   └── Use Cases (Operator Overloading, Two-Class Talk)
 *   │   ├── Friend Member Function of another class  (NEW)
 *   │   ├── Friend Class
 *   │   │   ├── Relationship Between Classes
 *   │   │   └── Advantages and Risks
 *   │   ├── Friendship is NOT inherited / mutual / transitive  (NEW)
 *   │   └── Friend vs Member Function
 *   │
 *   ├── 9. OPERATOR OVERLOADING
 *   │   ├── Need for Operator Overloading
 *   │   ├── Rules & Limitations
 *   │   ├── Operators that CANNOT be overloaded (:: . .* ?:)  ⭐  (NEW)
 *   │   ├── Unary Operators (++, --, -, !)
 *   │   │   └── Prefix ++a vs Postfix a++ (int dummy)  ⭐  (NEW)
 *   │   ├── Binary Operators (+, -, *, /, ==, !=, ...)
 *   │   ├── Overloading Using
 *   │   │   ├── Member Function
 *   │   │   └── Non-Member (Friend) Function
 *   │   ├── Assignment Operator (=)
 *   │   │   └── Self-assignment check + Copy-and-Swap  (NEW)
 *   │   ├── Compound Assignment (+=, -=, ...)  (NEW)
 *   │   ├── Stream Operators (<<, >>)
 *   │   ├── Relational Operators
 *   │   ├── Spaceship <=> and = default comparison (C++20)  (NEW)
 *   │   ├── Subscript Operator [ ]  (NEW)
 *   │   ├── Function Call Operator ( ) → Functor
 *   │   ├── Arrow -> and * (smart-pointer style)  (NEW)
 *   │   ├── Conversion Operator (operator int, operator bool)  (NEW)
 *   │   ├── new / delete Overloading  (NEW)
 *   │   └── Rules for Return Type and Arguments
 *   │
 *   ├── 10. VIRTUAL FUNCTIONS AND ABSTRACT CLASSES
 *   │   ├── Virtual Function Basics
 *   │   ├── Late Binding
 *   │   ├── vtable and vptr  ⭐
 *   │   ├── Rules for Virtual Functions
 *   │   ├── Pure Virtual Functions
 *   │   ├── Pure Virtual Function WITH a body  (NEW)
 *   │   ├── Abstract Classes
 *   │   ├── Rules for Abstract Classes
 *   │   ├── Virtual Destructors
 *   │   ├── Pure Virtual Destructor  (NEW)
 *   │   ├── Overriding and Hiding
 *   │   ├── ⚠ Virtual call inside constructor / destructor  (NEW)
 *   │   ├── ⚠ Default arguments in virtual functions  (NEW)
 *   │   ├── Cost of virtual (extra pointer, no inline)  (NEW)
 *   │   └── Example Hierarchy (Shape → Circle / Rectangle)
 *   │
 *   ├── 11. STATIC MEMBERS
 *   │   ├── Static Data Members
 *   │   ├── Static Member Functions
 *   │   ├── Lifetime and Scope of Static Members
 *   │   ├── Initialization of Static Data
 *   │   ├── static const and inline static (C++17)  (NEW)
 *   │   ├── Static local variable inside a member function  (NEW)
 *   │   ├── Counting objects with a static counter  (NEW)
 *   │   └── Static vs Non-Static Members
 *   │
 *   ├── 12. TYPE CASTING IN OOP
 *   │   ├── static_cast
 *   │   ├── dynamic_cast  ⭐
 *   │   │   └── nullptr (pointer) / bad_cast (reference)  (NEW)
 *   │   ├── const_cast
 *   │   ├── reinterpret_cast
 *   │   ├── RTTI: typeid and type_info  (NEW)
 *   │   └── User-defined Conversions (ctor + operator)  (NEW)
 *   │
 *   ├── 13. RELATIONSHIPS BETWEEN CLASSES
 *   │   ├── Association
 *   │   ├── Aggregation (weak HAS-A)
 *   │   ├── Composition (strong HAS-A)  ⭐
 *   │   ├── Dependency (USES-A)
 *   │   ├── Multiplicity (1-1, 1-many, many-many)  (NEW)
 *   │   ├── Composition over Inheritance  ⭐  (NEW)
 *   │   └── Real-Life Implementation Examples
 *   │
 *   ├── 14. EXCEPTION HANDLING WITH CLASSES  (NEW)
 *   │   ├── Custom Exception Class (derive from std::exception)
 *   │   ├── Override what()
 *   │   ├── Exception Hierarchy + catch order (child first)
 *   │   ├── Catch by const reference (avoid slicing)  ⭐
 *   │   ├── Exception thrown in a Constructor
 *   │   ├── ⚠ Never throw from a Destructor
 *   │   ├── noexcept (and why move ctor should be noexcept)
 *   │   └── Stack Unwinding + RAII
 *   │
 *   ├── 15. OBJECT LIFETIME AND MEMORY  (NEW)
 *   │   ├── Objects on Stack vs Heap
 *   │   ├── new / delete with Objects
 *   │   ├── new[] / delete[] for Array of Objects
 *   │   ├── Placement new
 *   │   ├── Smart Pointers with Classes
 *   │   │   ├── unique_ptr (single owner)
 *   │   │   ├── shared_ptr (many owners)
 *   │   │   ├── weak_ptr (break cyclic reference)
 *   │   │   └── unique_ptr<Base> for polymorphism  ⭐
 *   │   ├── Object Memory Layout (padding, vptr)
 *   │   ├── Lifetime of Temporary Objects
 *   │   └── ⚠ Dangling Pointers / References to objects
 *   │
 *   ├── 16. TEMPLATES WITH OOP (GENERIC CLASSES)  (NEW)
 *   │   ├── Class Template
 *   │   ├── Member Function Template
 *   │   ├── Template Specialization (full / partial)
 *   │   ├── Class Template + Inheritance
 *   │   ├── CRTP (Curiously Recurring Template Pattern)
 *   │   └── Templates vs Virtual Functions (when to use which)
 *   │
 *   ├── 17. DESIGN PRINCIPLES  (NEW)
 *   │   ├── SOLID  ⭐
 *   │   │   ├── S → Single Responsibility
 *   │   │   ├── O → Open / Closed
 *   │   │   ├── L → Liskov Substitution
 *   │   │   ├── I → Interface Segregation
 *   │   │   └── D → Dependency Inversion
 *   │   ├── DRY, KISS, YAGNI
 *   │   ├── Composition over Inheritance
 *   │   └── Law of Demeter (talk only to close friends)
 *   │
 *   ├── 18. DESIGN PATTERNS & IDIOMS (BASIC)  (NEW)
 *   │   ├── Creational
 *   │   │   ├── Singleton  ⭐
 *   │   │   ├── Factory  ⭐
 *   │   │   ├── Builder
 *   │   │   └── Prototype (virtual clone())
 *   │   ├── Structural
 *   │   │   ├── Adapter
 *   │   │   ├── Decorator
 *   │   │   └── Facade
 *   │   ├── Behavioral
 *   │   │   ├── Observer  ⭐
 *   │   │   ├── Strategy  ⭐
 *   │   │   └── Command
 *   │   └── C++ Idioms
 *   │       ├── RAII
 *   │       ├── PIMPL (pointer to implementation)
 *   │       ├── Copy-and-Swap
 *   │       └── NVI (Non-Virtual Interface)
 *   │
 *   └── 19. PRACTICAL IMPLEMENTATION / DESIGN
 *       ├── Applying All Four OOP Pillars Together
 *       ├── UML Class Diagrams (Basic Understanding)
 *       ├── Modular OOP Design
 *       ├── Example Mini Projects
 *       │   ├── Student Management System
 *       │   ├── Banking System
 *       │   ├── Employee Record System
 *       │   ├── Shape / Geometry Hierarchy
 *       │   ├── Library Management System  (NEW)
 *       │   └── Parking Lot (LLD interview favourite)  (NEW)
 *       ├── Common OOP Mistakes  (NEW)
 *       └── Best OOP Practices in C++
 *
 *  ✔ The old roadmap had some topics twice ("Virtual Base Class" in 6,
 *    "Static Members" in 2 and 11). They are now listed ONCE only.
 *  ✔ Old section 14 (Practical) moved to 19, so it stays at the end.
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   2)  FILES IN THIS FOLDER                                                ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  ✔ One file = one roadmap section, same number (file 06 = section 6)
 *  ✔ Every topic in the tree above has its own block in that file
 *  ✔ Each block = one complete program → select it, Ctrl + Alt + N
 *  ────────────────────────────────────────────────────────────────────────────
 *   01_Introduction.cpp              ─► 1.  Introduction to OOP
 *   02_ClassObject.cpp               ─► 2.  Class and Object
 *   03_Constructors.cpp              ─► 3.  Constructors and Destructors
 *   04_Encapsulation.cpp             ─► 4.  Encapsulation
 *   05_Abstraction.cpp               ─► 5.  Abstraction
 *   06_Inheritance.cpp               ─► 6.  Inheritance
 *   07_Polymorphism.cpp              ─► 7.  Polymorphism
 *   08_FriendFunction.cpp            ─► 8.  Friend Concept
 *   09_OperatorOverloading.cpp       ─► 9.  Operator Overloading
 *   10_VirtualFunction.cpp           ─► 10. Virtual Functions, Abstract
 *   11_StaticMembers.cpp             ─► 11. Static Members
 *   12_TypeCasting.cpp               ─► 12. Type Casting in OOP
 *   13_ClassRelationships.cpp        ─► 13. Relationships Between Classes
 *   14_ExceptionsWithClasses.cpp     ─► 14. Exception Handling with Classes
 *   15_ObjectLifetimeMemory.cpp      ─► 15. Object Lifetime and Memory
 *   16_ClassTemplates.cpp            ─► 16. Templates with OOP
 *   17_DesignPrinciples.cpp          ─► 17. Design Principles (SOLID)
 *   18_DesignPatterns.cpp            ─► 18. Design Patterns & Idioms
 *   19_MiniProjects.cpp              ─► 19. Practical Implementation
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   3)  🚨 MUST KNOW FOR INTERVIEWS  ⭐⭐⭐                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   4 pillars   class vs struct   this pointer   empty class size
 *   copy constructor   shallow vs deep copy   Rule of 3 / 5   RAII
 *   initialization list   explicit   virtual function   vtable / vptr
 *   virtual destructor   pure virtual   abstract class vs interface
 *   overloading vs overriding   static vs dynamic binding
 *   diamond problem   virtual base class   object slicing
 *   access table in inheritance   friend function   prefix vs postfix ++
 *   dynamic_cast   composition vs inheritance   SOLID   Singleton
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   4)  QUICK TABLES                                                        ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Access after inheritance
 *  ────────────────────────────────────────────────────────────────────────────
 *   BASE MEMBER     public INHERIT   protected INHERIT   private INHERIT
 *   ─────────────   ──────────────   ─────────────────   ───────────────
 *   public          public           protected           private
 *   protected       protected        protected           private
 *   private         NOT accessible   NOT accessible      NOT accessible
 *
 *  Special member functions (compiler can make these for you)
 *  ────────────────────────────────────────────────────────────────────────────
 *   Default constructor      A()
 *   Destructor               ~A()
 *   Copy constructor         A(const A&)
 *   Copy assignment          A& operator=(const A&)
 *   Move constructor         A(A&&) noexcept
 *   Move assignment          A& operator=(A&&) noexcept
 *
 *  ⚠ If you write ONE of destructor / copy / move yourself,
 *    you usually need to write ALL of them (Rule of 5).
 */
