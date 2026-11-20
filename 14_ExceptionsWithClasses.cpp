/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                     EXCEPTION HANDLING WITH CLASSES                       ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *  Quick recap
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ An exception is a way to report an ERROR from deep inside the code
 *    to a place that can handle it
 *        throw   → report the error
 *        try     → run code that might fail
 *        catch   → handle the error
 *  ✔ Basics of try / throw / catch → C++/35_ExceptionHandling.cpp
 *  ✔ This file is about exceptions + OOP: exception CLASSES, hierarchies,
 *    and what happens to objects when an exception flies
 *
 *  Why throw OBJECTS (classes)?
 *  ────────────────────────────────────────────────────────────────────────────
 *  ✔ An object can carry DETAILS: message, error code, amount, file name
 *  ✔ A class HIERARCHY lets you catch a whole family of errors at once
 *        catch (const BankError&)  → catches InsufficientFunds,
 *                                    AccountLocked, ...
 *
 *  Standard exception hierarchy (part)
 *  ────────────────────────────────────────────────────────────────────────────
 *
 *                         std::exception        what()
 *                ┌──────────────┼──────────────────┐
 *          logic_error     runtime_error        bad_alloc, bad_cast ...
 *          ├ invalid_argument  ├ overflow_error
 *          ├ out_of_range      ├ range_error
 *          └ length_error      └ system_error
 *
 *  ✔ Header: <stdexcept> for logic_error / runtime_error family
 *
 *
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║   ALL TOPICS IN THIS FILE                                                 ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 *   Custom exception class        ─► derive from std::exception
 *   Override what()               ─► the error message
 *   Derive from runtime_error     ─► the easy way (message built in)
 *   Exception hierarchy           ─► catch order: CHILD first
 *   Catch by const reference ⭐   ─► avoid slicing and copies
 *   Exception in a constructor    ─► object is never created
 *   Never throw from a destructor ─► program terminates
 *   noexcept                      ─► promise "no exceptions"
 *   Stack unwinding + RAII        ─► local objects are cleaned up
 *   Rethrow                       ─► log, then pass the error up
 */


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Custom exception class — derive from std::exception ->
│      class MyError : public std::exception {
│      public:
│          const char* what() const noexcept override { return "..."; }
│      };
│      throw MyError();         catch (const MyError& e) { e.what(); }
│
│  ✔ Definition : Make your own error type by inheriting std::exception
│                 and overriding what() to return the message.
│  ✔ what() must be  const noexcept  (same as the base)
│  ✔ Now  catch (const std::exception&)  can catch your error too
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <exception>
using namespace std;

class DivideByZero : public exception {
public:
    const char* what() const noexcept override {
        return "Cannot divide by zero";
    }
};

double divide(double a, double b) {
    if (b == 0) throw DivideByZero();
    return a / b;
}

int main() {

    try {
        cout << divide(10, 2) << endl;   // 5
        cout << divide(1, 0) << endl;    // (not printed)
    } catch (const DivideByZero& e) {
        cout << "Error: " << e.what() << endl;   // Error: Cannot divide by zero
    }

    try {
        divide(5, 0);
    } catch (const exception& e) {       // base type also catches it
        cout << "Caught as exception: " << e.what() << endl;
        // Caught as exception: Cannot divide by zero
    }

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Exception that carries DETAILS — override what() with a built message
│  ✔ Store extra data (amount, balance) as members
│  ✔ Build the message ONCE in the constructor and keep it in a string
│    member. what() returns  msg.c_str()  — safe, because msg lives as
│    long as the exception object.
│  ⚠ Never return c_str() of a LOCAL string from what() — it dies at
│    the end of what() → dangling pointer
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <exception>
#include <string>
using namespace std;

class InsufficientFunds : public exception {
    double needed, available;
    string msg;

public:
    InsufficientFunds(double n, double a) : needed(n), available(a) {
        msg = "Need Rs." + to_string((int)needed) + ", have Rs." +
              to_string((int)available);
    }

    const char* what() const noexcept override { return msg.c_str(); }
    double shortBy() const { return needed - available; }
};

class Account {
    double balance = 1000;

public:
    void withdraw(double amt) {
        if (amt > balance) throw InsufficientFunds(amt, balance);
        balance -= amt;
    }
};

int main() {

    Account acc;
    try {
        acc.withdraw(300);
        acc.withdraw(5000);
    } catch (const InsufficientFunds& e) {
        cout << e.what() << endl;            // Need Rs.5000, have Rs.700
        cout << "Short by " << e.shortBy() << endl;   // Short by 4300
    }

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Derive from runtime_error / logic_error (the easy way) ->
│      class MyError : public std::runtime_error {
│      public:
│          using runtime_error::runtime_error;      // reuse constructor
│      };
│      throw MyError("message");
│
│  ✔ Definition : runtime_error already stores the message and gives
│                 what(). You only pick a NAME for your error type.
│  ✔ logic_error   → bugs in the program (bad argument, out of range)
│  ✔ runtime_error → problems only seen while running (file missing,
│                    network down)
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class FileNotFound : public runtime_error {
public:
    using runtime_error::runtime_error;
};

class InvalidAge : public invalid_argument {
public:
    InvalidAge(int age)
        : invalid_argument("Invalid age: " + to_string(age)) {}
};

void openFile(const string& name) {
    if (name != "data.txt") throw FileNotFound("No such file: " + name);
    cout << "opened " << name << endl;
}

void setAge(int a) {
    if (a < 0) throw InvalidAge(a);
}

int main() {

    try {
        openFile("data.txt");            // opened data.txt
        openFile("photo.png");
    } catch (const FileNotFound& e) {
        cout << e.what() << endl;        // No such file: photo.png
    }

    try {
        setAge(-4);
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;        // Invalid age: -4
    }

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Exception hierarchy + catch order
│  ✔ Build a family of errors: BankError → InsufficientFunds,
│    AccountLocked
│  ✔ catch blocks are checked TOP to BOTTOM; the FIRST match wins
│  ⚠ Put the most specific (CHILD) catch first, the general (BASE)
│    catch last. If the base is first, the child catch never runs.
│  ✔ catch (...) catches ANYTHING — use it as the very last safety net
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class BankError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

class InsufficientFunds : public BankError {
public:
    InsufficientFunds() : BankError("Insufficient funds") {}
};

class AccountLocked : public BankError {
public:
    AccountLocked() : BankError("Account locked") {}
};

void process(int code) {
    if (code == 1) throw InsufficientFunds();
    if (code == 2) throw AccountLocked();
    if (code == 3) throw out_of_range("Bad account index");
    if (code == 4) throw 42;
}

int main() {

    for (int code = 1; code <= 4; code++) {
        try {
            process(code);
        } catch (const InsufficientFunds& e) {       // most specific
            cout << "Add money: " << e.what() << endl;
        } catch (const BankError& e) {               // any other bank error
            cout << "Bank problem: " << e.what() << endl;
        } catch (const exception& e) {               // any std error
            cout << "General: " << e.what() << endl;
        } catch (...) {                              // anything else
            cout << "Unknown error" << endl;
        }
    }
    // Add money: Insufficient funds
    // Bank problem: Account locked
    // General: Bad account index
    // Unknown error

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Catch by const reference  ⭐
│  ✔ catch (BaseError e)        → BY VALUE: makes a copy AND slices it —
│                                 the child part is lost, what() of the
│                                 BASE runs
│  ✔ catch (const BaseError& e) → BY REFERENCE: no copy, no slicing, the
│                                 real child's what() runs
│  ✔ Rule: throw by VALUE, catch by CONST REFERENCE
│  ✔ g++ -Wall even warns: "catching polymorphic type by value"
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <exception>
using namespace std;

class AppError : public exception {
public:
    const char* what() const noexcept override { return "App error"; }
};

class NetworkError : public AppError {
public:
    const char* what() const noexcept override { return "Network down"; }
};

int main() {

    try {
        throw NetworkError();
    } catch (AppError e) {               // ⚠ by value → sliced
        cout << e.what() << endl;        // App error
    }

    try {
        throw NetworkError();
    } catch (const AppError& e) {        // ✔ by reference
        cout << e.what() << endl;        // Network down
    }

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Exception thrown in a constructor
│  ✔ A constructor has no return value, so throwing is THE way to say
│    "this object could not be created"
│  ✔ If the constructor throws, the object NEVER existed:
│        • its destructor does NOT run
│        • members that were ALREADY built ARE destroyed
│  ⚠ So raw "new" done before the throw would leak → use members that
│    clean themselves (string, vector, unique_ptr) = RAII
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
using namespace std;

class Part {
    string name;

public:
    Part(string n) : name(n) { cout << "  " << name << " built" << endl; }
    ~Part() { cout << "  " << name << " destroyed" << endl; }
};

class Email {
    Part header{"header"};               // built first
    unique_ptr<int> buffer;
    string address;

public:
    Email(string addr) : buffer(make_unique<int>(0)), address(addr) {
        if (address.find('@') == string::npos)
            throw invalid_argument("Bad email: " + address);
        cout << "  Email ready: " << address << endl;
    }

    ~Email() { cout << "  ~Email" << endl; }
};

int main() {

    try {
        Email ok("amit@mail.com");
        // header built
        // Email ready: amit@mail.com
        // ~Email
        // header destroyed
    } catch (...) {}

    cout << "---" << endl;           // ---

    try {
        Email bad("amit.mail.com");
        // header built
        // header destroyed          (~Email does NOT run)
    } catch (const exception& e) {
        cout << e.what() << endl;    // Bad email: amit.mail.com
    }

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  ⚠ Never throw from a destructor
│  ✔ Destructors are noexcept by default (C++11). If an exception
│    escapes one → std::terminate() → the program dies.
│  ✔ Worse: during stack unwinding (another exception already flying),
│    a second exception ALWAYS terminates.
│  ✔ Fix: catch inside the destructor, log it, and move on. If the error
│    matters, give a separate close() function that CAN throw.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class Connection {
    bool open = true;

    void sendGoodbye() { throw runtime_error("network lost"); }

public:
    void close() {                       // caller can handle errors
        if (!open) return;
        open = false;
        sendGoodbye();
    }

    ~Connection() {
        try {
            if (open) { open = false; sendGoodbye(); }
        } catch (const exception& e) {   // swallow + log, never rethrow
            cout << "dtor ignored: " << e.what() << endl;
        }
    }
};

int main() {

    {
        Connection c;
    }                                    // dtor ignored: network lost

    try {
        Connection c2;
        c2.close();
    } catch (const exception& e) {
        cout << "close failed: " << e.what() << endl;
        // close failed: network lost
    }

    cout << "program still alive" << endl;     // program still alive

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  noexcept ->
│      void f() noexcept;              // promise: never throws
│      noexcept(expr)                  // ask: can expr throw? → bool
│
│  ✔ Definition : noexcept PROMISES the function won't throw. If it does
│                 anyway → std::terminate().
│  ✔ Why it matters for classes: vector moves elements on resize ONLY if
│    the move constructor is noexcept. Otherwise it COPIES (slower) to
│    keep its safety guarantee.
│  ✔ Mark as noexcept: destructors (automatic), move ctor / move =,
│    swap, simple getters
│  ✔ is_nothrow_move_constructible_v<T> (<type_traits>) checks it
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
using namespace std;

class SafeMove {
    string data = "x";

public:
    SafeMove() = default;
    SafeMove(const SafeMove& o) : data(o.data) { cout << "copy "; }
    SafeMove(SafeMove&& o) noexcept : data(move(o.data)) { cout << "move "; }
};

class RiskyMove {
    string data = "x";

public:
    RiskyMove() = default;
    RiskyMove(const RiskyMove& o) : data(o.data) { cout << "copy "; }
    RiskyMove(RiskyMove&& o) : data(move(o.data)) { cout << "move "; }
};

int main() {

    vector<SafeMove> a(2);
    a.reserve(10);                       // resize → elements are MOVED
    cout << endl;                        // move move

    vector<RiskyMove> b(2);
    b.reserve(10);                       // resize → elements are COPIED
    cout << endl;                        // copy copy

    cout << boolalpha;
    cout << is_nothrow_move_constructible_v<SafeMove> << endl;   // true
    cout << is_nothrow_move_constructible_v<RiskyMove> << endl;  // false

    return 0;
}


/*
┌── Example ────────────────────────────────────────────────────────────────┐
│  Stack unwinding + RAII
│  ✔ When an exception is thrown, C++ leaves each function on the way to
│    the matching catch, and DESTROYS every local object in them (in
│    reverse order). This is "stack unwinding".
│  ✔ So RAII objects (lock_guard, unique_ptr, fstream, your own classes)
│    ALWAYS clean up — even when an error jumps over the normal code
│  ⚠ Raw new / manual delete is SKIPPED → leak. Use RAII.
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Guard {
    string name;

public:
    Guard(string n) : name(n) { cout << "acquire " << name << endl; }
    ~Guard() { cout << "release " << name << endl; }
};

void step3() {
    Guard g("file");
    throw runtime_error("disk full");
    cout << "never printed" << endl;
}

void step2() {
    Guard g("lock");
    step3();
}

void step1() {
    Guard g("db connection");
    step2();
}

int main() {

    try {
        step1();
    } catch (const exception& e) {
        cout << "caught: " << e.what() << endl;
    }
    // acquire db connection
    // acquire lock
    // acquire file
    // release file
    // release lock
    // release db connection
    // caught: disk full

    return 0;
}


/*
┌── Syntax ─────────────────────────────────────────────────────────────────┐
│  Rethrow ->
│      catch (const exception& e) { log(e); throw; }
│
│  ✔ Definition : "throw;" (with nothing after it) inside a catch sends
│                 the SAME exception object further up.
│  ✔ Use it to log / clean up at a lower level and still let a higher
│    level decide what to do
│  ⚠ Write  throw;  not  throw e;  —  throw e;  makes a COPY of the
│    static type and can SLICE a child exception
└───────────────────────────────────────────────────────────────────────────┘
*/

#include <iostream>
#include <stdexcept>
using namespace std;

class PaymentDeclined : public runtime_error {
public:
    PaymentDeclined() : runtime_error("Card declined") {}
};

void chargeCard() { throw PaymentDeclined(); }

void checkout() {
    try {
        chargeCard();
    } catch (const exception& e) {
        cout << "[log] checkout failed: " << e.what() << endl;
        throw;                           // pass the SAME error up
    }
}

int main() {

    try {
        checkout();
    } catch (const PaymentDeclined& e) { // still the real child type
        cout << "Show user: " << e.what() << ", try another card" << endl;
    }
    // [log] checkout failed: Card declined
    // Show user: Card declined, try another card

    return 0;
}
