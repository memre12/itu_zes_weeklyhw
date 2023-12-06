#include <iostream>
#include <memory>

class Emre {
public:
    Emre(){
        std::cout << "Constructor invoked !!!" << std::endl;
    }
    ~Emre(){
        std::cout << "Destructor invoked !!!" << std::endl;
    }
};
int main() {
    


    //unique_ptr is supported on c++14 and later.
    // unique pointer is destroyed at the end of the scope.
    std::unique_ptr<int> unPtr1 = std::make_unique<int>(25); // define a unique_ptr
    std::cout << *unPtr1 << std::endl; // access the value
    std::cout << unPtr1 << std::endl; // access the address
    std::unique_ptr<int> unPtr2 = std::move(unPtr1); // we make it that they have same adress
    std::cout << unPtr2 << std::endl; // access the address
    {
    std::unique_ptr<Emre> unPtr3 = std::make_unique<Emre>();
    }// At the end of the scope, unPtr3 is deleted.
    // std::cout << unPtr3 << std::endl; // To illustrate that unPtr3 is deleted, Try this line.
    std::unique_ptr<int> unPtr6 = std::make_unique<int>(31); // define a unique_ptr6
    int* rawPtr = unPtr6.get(); // Using get() function to get the memory pointed by the std::unique_ptr
    std::cout << "Value pointed by uniqueIntPtr: " << *rawPtr << "\n";
    std::unique_ptr<int> unPtr7 = std::move(unPtr6); // move() function
    if (unPtr6) {
        std::cout << "values: "<< *unPtr6 << ", " << *unPtr7 << std::endl; // compare values
        std::cout << "adresses" << unPtr6.get() << ", " << unPtr7.get() << std::endl; // compare addresses
    } else {
        std::cout << "unPtr6 is null\n"; // After you use std::move(unPtr6), unPtr6 no longer owns the memory.
    }

    
    // shared pointer
    std::shared_ptr<Emre>shPtr1 = std::make_shared<Emre>();
    std::cout << "Shared count: " << shPtr1.use_count() << std::endl;//1
    {
        std::shared_ptr<Emre>shPtr2 = shPtr1;
        std::cout << "Shared count: " << shPtr1.use_count() << std::endl;//2
    }
    std::cout << "Shared count: " << shPtr1.use_count() << std::endl; // 1 because shPtr2 is deleted at the end of the scope.
    shPtr1.reset();
    std::cout << "After reset(), sharedPtr2 use count: " << shPtr1.use_count() << std::endl;
    
    //weak_ptr The move function moves the address of one pointer to another pointer and makes the address of the first pointer NULL.
    std::shared_ptr<int>shPtr5 = std::make_shared<int>();
    *shPtr5 = 52;
    
    std::weak_ptr<int> weak1 = shPtr5;
    
    shPtr5.reset(new int);
    *shPtr5 = 1903;
    
    std::weak_ptr<int> weak2 = shPtr5;

    
    if (auto tmp = weak1.lock()) {
        std::cout << "weak1: " << *tmp << '\n';
    } else {
        std::cout << "weak1 is expired\n";// this code will run
    }

    if (auto tmp = weak2.lock()) {
        std::cout << "weak2: " << *tmp << '\n';
    } else {
        std::cout << "weak2 is expired\n";
    }
    
    // std::auto_ptr (deprecated)
    //std::auto_ptr<int> autoIntPtr(new int(100));
    //int* rawPtr = autoIntPtr.get();
    //std::auto_ptr<int> movedIntPtr = std::move(autoIntPtr); // move() function
    //std::cout << "Value pointed by movedIntPtr: " << *movedIntPtr.get() << "\n";

    return 0;
}
