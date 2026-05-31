#include <iostream>
using namespace std;

// Base Class with a virtual function (Introduces vtable and vptr)
class Base {
public:
    int base_data = 10;
    virtual void show() { cout << "Base" << endl; }
};

// Derived Class using Virtual Inheritance (Introduces vbase_ptr)
class Derived : virtual public Base {
public:
    int derived_data = 20;
};

int main() {
    Base b;
    Derived d;

    cout << "--- 1. Verification of vptr (Size Inspection) ---" << endl;
    // An integer is 4 bytes. But 'b' has a virtual function, so it adds an 8-byte vptr.
    // Total size = 4 (int) + 8 (vptr) = 12 bytes -> Padded by compiler to 16 bytes.
    cout << "Size of Base object: " << sizeof(b) << " bytes" << endl;

    cout << "\n--- 2. Printing the vptr Address Value ---" << endl;
    // The vptr is always stored at the very beginning of the object's memory.
    // We can extract it by casting the object pointer into a pointer-to-pointer.
    void** vptr_value = *(reinterpret_cast<void***>(&b));
    cout << "Address of Base's vtable (Value of vptr): " << vptr_value << endl;

    // We can even print the address of the actual 'show' function inside that table
    cout << "Address of show() function inside vtable: " << vptr_value[0] << endl;

    cout << "\n--- 3. Verification of vbase_ptr (Size Inspection) ---" << endl;
    // Derived has base_data (4), derived_data (4), its own vptr (8), AND a vbase_ptr (8)
    // to track where the virtual Base class is.
    cout << "Size of Derived object: " << sizeof(d) << " bytes" << endl;

    return 0;
}



// 1. vtable (Virtual Table)

// What it is: A hidden static array created by the compiler per class (not per object).

// What it stores: Function pointers (memory addresses) of all the virtual functions that the class can run.

// 2. vptr (Virtual Pointer)

// What it is: A hidden pointer added by the compiler inside every object instance.

// What it does: It points directly to the vtable of that object's class. It takes up 8 bytes of space (on 64-bit systems) inside the object.

// 3. vbase_ptr (Virtual Base Pointer)

// What it is: A hidden pointer added to intermediate classes only when virtual inheritance is used.

// What it does: It stores the memory offset required to locate the single, shared grand-parent object in memory, preventing duplicate data copies.

// How dynamic binding/ late binding/ run-time polymorphism happens in c++?
// At runtime, when you call a virtual method through a base pointer, the program looks at the object's vptr, finds the correct vtable, and executes the overridden function.

// The vbase_ptr actually stores a memory offset value (a distance measured in bytes), rather than a direct memory address.
// It tells the compiler exactly how many bytes it needs to move forward or backward from the current location in memory to find the shared virtual base class data.

// Why an Offset and Not an Address?
// If the pointer stored a hardcoded memory address (like 0x7ffebfaf45a0), it would break the moment you created a second object.
// Every single object instance sits at a completely unique location in your computer's RAM.
// By storing an offset (a relative distance), the exact same logic works perfectly for every instance of that class, no matter where the object is allocated in memory.

// A Simple Memory VisualisationImagine a Derived class object that uses virtual inheritance. Its layout in your computer's RAM looks roughly like this:textMemory     Address               Content
// --------------------------------------------------------------
// 0x1000            [ vbase_ptr ]  --> Holds the offset value: +24
// 0x1008            [ Derived Class Data Members ]
// 0x1010            [ More Derived Data / Padding ]
// 0x1018            [ Shared Virtual Base Class Data Starts Here ]
// Use code with caution.When the program executes and needs to access the virtual base class data, it does a quick math calculation at runtime:\(\text{Current\ Address\ }(0x1000)+\text{Offset\ Value\ }(24)=\text{Target\ Address\ }(0x1018)\)

// Step-by-Step Execution at RuntimeWhen you execute code like BasePointer->virtual_function(), the CPU executes these four hidden steps behind the scenes:
// [Base Pointer]
//      │
//      ▼
// 1. Look at Object's Header ──► 2. Read vbase_ptr (Find where Base class data is)
//                                     │
//                                     ▼
// 3. Go to Base Class Memory ──► 4. Read vptr ──► vtable ──► Run Function

// a) Find the Base Object Position:
// The program reads the object's vbase_ptr (or looks up the virtual base offset in the vtable structure).
// This tells the program exactly how many bytes to jump in memory to find the shared base class data.

// b) Locate the Virtual Pointer (vptr):
// Once the program arrives at the shared base class memory block, it looks at the front of that block to find the vptr.

// c)Access the Virtual Table (vtable):
// The vptr redirects the program to the correct vtable for the concrete object currently running.Execute: The program grabs the function pointer from the vtable slot and jumps to the executed code.Code Example: Proving the Double IndirectionIf you look at how the memory locations drift, you can see why the vbase_ptr lookup must happen first.

// #include <iostream>
// using namespace std;

// class GrandParent {
// public:
//     int gp_data = 99;
//     virtual void speak() { cout << "GrandParent speaking" << endl; }
// };

// // Virtual inheritance forces the use of vbase_ptr offsets
// class Parent : virtual public GrandParent {
// public:
//     int p_data = 11;
//     void speak() override { cout << "Parent speaking" << endl; }
// };

// int main() {
//     Parent my_parent;
//     GrandParent* ptr = &my_parent;

//     cout << "--- Memory Location Shift ---" << endl;
//     cout << "Start address of Parent object:     " << &my_parent << endl;
//     cout << "Actual address of GrandParent data: " << ptr << endl;

//     // Notice the difference between the two memory addresses printed above!
//     // The gap between them is what 'vbase_ptr' resolves at runtime.

//     // Late binding happens here:
//     ptr->speak();

//     return 0;
// }
