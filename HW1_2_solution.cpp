#include <iostream>
#include <typeinfo>
#include <string>

/*
HW1.2: Find another elegant example where dereferencing a null pointer is valid

The example given: int *a = nullptr; std::println("{}", typeid(*a).name());

Another elegant example: Using nullptr with member function pointers
and decltype to get type information without actually calling the function.
*/

struct TestClass {
    void memberFunction() { std::cout << "Called" << std::endl; }
    int data = 42;
};

int main() {
    // Example 1: Using decltype with dereferenced null pointer
    TestClass* ptr = nullptr;
    
    // This is valid - decltype doesn't evaluate the expression
    decltype((*ptr).data) var = 100;  // var is of type int
    std::cout << "Type of var: " << typeid(var).name() << ", value: " << var << std::endl;
    
    // Example 2: Using sizeof with dereferenced null pointer
    size_t size = sizeof((*ptr).data);  // Valid - sizeof doesn't evaluate
    std::cout << "Size of member: " << size << " bytes" << std::endl;
    
    // Example 3: Using noexcept specification
    bool is_noexcept = noexcept((*ptr).memberFunction());  // Valid
    std::cout << "Member function is noexcept: " << std::boolalpha << is_noexcept << std::endl;
    
    // Example 4: Using typeid with member access
    const std::type_info& info = typeid((*ptr).memberFunction);
    std::cout << "Type info for member function: " << info.name() << std::endl;
    
    return 0;
}
