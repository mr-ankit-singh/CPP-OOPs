<div align="center">

# 🧠 C++ OOPs — Detailed Notes & Code Examples

### A complete, structured, and deeply-commented guide to Object-Oriented Programming in C++

![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)
![Level](https://img.shields.io/badge/Level-Beginner%20to%20Advanced-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

</div>

---

## 📖 About This Repository

This repository is a **topic-wise, deeply-commented collection of C++ Object-Oriented Programming concepts**, built while learning OOPs from scratch to advanced level. Every file focuses on **one core concept**, explained with:

- 📘 Clear definitions
- 💡 Real-life analogies
- ⚙️ Clean, runnable code examples
- 🎯 Interview-focused key points

Whether you're **starting out with OOPs** or **revising before an interview**, these notes are designed to give you both **conceptual clarity** and **practical code** in one place.

---

## 🗂️ Repository Structure

One file = one roadmap section. Every topic is its own runnable block (select it → `Ctrl + Alt + N`).

```
📦 Object Oriented Programming
 ┣ 📜 00_Roadmap.cpp                 → Full OOP roadmap (topic tree + file map)
 ┣ 📜 01_Introduction.cpp            → What is OOP, POP vs OOP, features, multi-paradigm
 ┣ 📜 02_ClassObject.cpp             → Class, object, access, member fns, this, const, mutable
 ┣ 📜 03_Constructors.cpp            → All constructors, destructor, deep copy, move, Rule of 0/3/5, RAII
 ┣ 📜 04_Encapsulation.cpp           → Data hiding, getters/setters, validation, const-correctness
 ┣ 📜 05_Abstraction.cpp             → Abstract classes, pure virtual, interfaces, vs encapsulation
 ┣ 📜 06_Inheritance.cpp             → Types, access table, diamond problem, final, slicing
 ┣ 📜 07_Polymorphism.cpp            → Compile-time & runtime, override, CRTP, variant/visit
 ┣ 📜 08_FriendFunction.cpp          → Friend function / member / class, friendship rules
 ┣ 📜 09_OperatorOverloading.cpp     → Unary, binary, =, <<, [], (), ->, <=>, conversion, new/delete
 ┣ 📜 10_VirtualFunction.cpp         → vtable/vptr, rules, pure virtual, virtual destructor, traps
 ┣ 📜 11_StaticMembers.cpp           → Static data & functions, inline static, object counting
 ┣ 📜 12_TypeCasting.cpp             → static/dynamic/const/reinterpret_cast, RTTI, typeid
 ┣ 📜 13_ClassRelationships.cpp      → Association, aggregation, composition, dependency
 ┣ 📜 14_ExceptionsWithClasses.cpp   → Custom exceptions, hierarchy, noexcept, stack unwinding
 ┣ 📜 15_ObjectLifetimeMemory.cpp    → Stack vs heap, smart pointers, memory layout, dangling
 ┣ 📜 16_ClassTemplates.cpp          → Class templates, specialization, CRTP, templates vs virtual
 ┣ 📜 17_DesignPrinciples.cpp        → SOLID, DRY, KISS, YAGNI, Law of Demeter
 ┣ 📜 18_DesignPatterns.cpp          → Singleton, Factory, Builder, Observer, Strategy ... + idioms
 ┣ 📜 19_MiniProjects.cpp            → Student, Bank, Employee, Shapes, Library, Parking Lot
 ┗ 📜 README.md                      → You are here 📍
```

---

## 📌 Topics Covered

<table>
<tr>
<td>

### 🏗️ Fundamentals
- ✅ Classes & Objects, class vs struct
- ✅ Access Specifiers
- ✅ `this` Pointer & method chaining
- ✅ const / mutable members
- ✅ Constructors & Destructors (all types)
- ✅ Copy / Move, Rule of 0/3/5, RAII
- ✅ Static Members

</td>
<td>

### 🎭 Core OOP Pillars
- ✅ Encapsulation
- ✅ Abstraction & Interfaces
- ✅ Inheritance (all types, diamond problem)
- ✅ Polymorphism (Compile-time & Runtime)

</td>
</tr>
<tr>
<td>

### ⚡ Advanced Concepts
- ✅ Virtual Functions, vtable & vptr
- ✅ Abstract Classes, Virtual Destructors
- ✅ Type Casting & RTTI
- ✅ Exceptions with Classes
- ✅ Smart Pointers & Object Lifetime
- ✅ Class Templates & CRTP

</td>
<td>

### 🔧 Design
- ✅ Friend Function & Friend Class
- ✅ Operator Overloading (all operators)
- ✅ Class Relationships (UML)
- ✅ SOLID & Design Principles
- ✅ Design Patterns & C++ Idioms
- ✅ 6 Mini Projects (incl. Parking Lot LLD)

</td>
</tr>
</table>

---

## 🎯 Why This Repository?

| Feature | Description |
|---|---|
| 📘 **Concept-first** | Every file starts with a clear definition before diving into code |
| 🧩 **Real examples** | Bank Account, Student, Shape, Car, TV — real-world analogies used throughout |
| 🗣️ **Interview-ready** | Key interview questions & tricky points highlighted in every topic |
| 🧱 **Structured** | Numbered files (00 → 19) follow the roadmap order |
| 💻 **Runnable code** | All examples compile and run directly — no missing pieces |

---

## 🚀 How to Use

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/<repo-name>.git
   cd <repo-name>
   ```

2. **Run one block** — every file has many small programs (each with its own `main()`).
   Select one block in VS Code and press `Ctrl + Alt + N` (Code Runner), or copy it to a file:
   ```bash
   g++ -std=c++20 block.cpp -o output
   ./output
   ```

3. **Follow the numbering** (00 → 19) for a structured learning path, or jump directly to the topic you want to revise.

---

## 🧭 Recommended Learning Path

```
00_Roadmap → 01_Introduction → 02_ClassObject → 03_Constructors
     ↓
04_Encapsulation → 05_Abstraction → 06_Inheritance → 07_Polymorphism
     ↓
08_FriendFunction → 09_OperatorOverloading → 10_VirtualFunction → 11_StaticMembers
     ↓
12_TypeCasting → 13_ClassRelationships → 14_ExceptionsWithClasses → 15_ObjectLifetimeMemory
     ↓
16_ClassTemplates → 17_DesignPrinciples → 18_DesignPatterns → 19_MiniProjects
```

---

## 🏷️ Tech Stack

![C++](https://img.shields.io/badge/-C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![GCC](https://img.shields.io/badge/-GCC%2FG%2B%2B-4EAA25?style=flat-square&logo=gnu&logoColor=white)
![VS Code](https://img.shields.io/badge/-VS%20Code-007ACC?style=flat-square&logo=visualstudiocode&logoColor=white)

---

## 🤝 Contributing

Found a typo, mistake, or want to add a missing OOPs concept? Feel free to open an **Issue** or submit a **Pull Request** — contributions are always welcome!

---

## ⭐ Support

If these notes helped you understand C++ OOPs better, consider giving this repo a **⭐ star** — it motivates further improvements and helps others discover it too.

---

<div align="center">

### 📚 Made with dedication while mastering C++ OOPs from the ground up.

**Happy Learning! 🚀**

</div>