# Understanding Pointers in C++ and Smart Pointers Implementation

In this assignment, I delved into the intricacies of pointers in C++ and explored the advantages and disadvantages associated with them.

    Garbage Collection Mechanism:
        Explored the absence of automatic garbage collection in C++.
        Discussed manual memory management and the responsibility of the programmer.

    Smart Pointers:
        Explored various smart pointers: void pointer, nullptr, auto_ptr, unique_ptr, shared_ptr, and weak_ptr.
        Emphasized the need for smart pointers to manage memory efficiently.

    Cons of Raw Pointers:
        Researched issues like memory leaks, dangling pointers, wild pointers, data inconsistency, and buffer overflow associated with raw pointers.
        Highlighted the importance of avoiding these issues through smart pointer usage.

    Smart Pointer Usage:
        Created a custom SmartPointer class with essential functionalities (constructor, destructor, operator* overload, operator-> overload).
        Implemented and tested std::auto_ptr, std::unique_ptr, std::shared_ptr, and std::weak_ptr.
        Explained the deprecation of auto_ptr and the preference for unique_ptr.

    Ownership Models:
        Discussed ownership models of each smart pointer in memory.
        Clarified scenarios for using each smart pointer based on ownership requirements.

    Coding Implementation:
        Provided a C++ source code file demonstrating the usage of smart pointers.
        Printed memory addresses after each operation to showcase pointer manipulation.

The coding section includes:

    Custom SmartPointer class implementation.
    Utilization of std::auto_ptr, std::unique_ptr, std::shared_ptr, and std::weak_ptr.
    Explanation of functions like get(), move(), use_count(), and reset().

This assignment deepened my understanding of pointers and smart pointers, showcasing their significance in memory management and the prevention of common pitfalls associated with raw pointers.
