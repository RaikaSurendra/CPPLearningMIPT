#include <iostream>
#include <stdexcept>
#include <optional>

/*
HW1.3: Find how to write proper protection code for the function
int foo(int *a, int base, int off) { return a[base + off]; }

Multiple approaches for protection:
1. Assert-based protection
2. Exception-based protection
3. Optional return type
4. Reference parameter with bounds checking
*/

// Approach 1: Assert-based protection
#include <cassert>
int foo_assert(int *a, int base, int off, size_t size) {
    assert(a != nullptr && "Pointer cannot be null");
    assert(base + off >= 0 && static_cast<size_t>(base + off) < size && "Index out of bounds");
    return a[base + off];
}

// Approach 2: Exception-based protection
int foo_exception(int *a, int base, int off, size_t size) {
    if (a == nullptr) {
        throw std::invalid_argument("Pointer cannot be null");
    }
    int index = base + off;
    if (index < 0 || static_cast<size_t>(index) >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return a[index];
}

// Approach 3: Optional return type (C++17)
#include <optional>
std::optional<int> foo_optional(int *a, int base, int off, size_t size) {
    if (a == nullptr || base + off < 0 || static_cast<size_t>(base + off) >= size) {
        return std::nullopt;
    }
    return a[base + off];
}

// Approach 4: Safe wrapper with bounds checking
struct SafeArray {
    int* data;
    size_t size;
    
    int get(int base, int off) const {
        if (data == nullptr) {
            throw std::runtime_error("Array data is null");
        }
        int index = base + off;
        if (index < 0 || static_cast<size_t>(index) >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    // Test all approaches
    try {
        std::cout << "Assert approach: " << foo_assert(arr, 1, 2, size) << std::endl;
        std::cout << "Exception approach: " << foo_exception(arr, 1, 2, size) << std::endl;
        
        auto result = foo_optional(arr, 1, 2, size);
        std::cout << "Optional approach: " << (result ? std::to_string(*result) : "nullopt") << std::endl;
        
        SafeArray safe{arr, size};
        std::cout << "Safe wrapper: " << safe.get(1, 2) << std::endl;
        
        // Test error cases
        // foo_assert(nullptr, 0, 0, size);  // Would trigger assert
        // foo_exception(nullptr, 0, 0, size);  // Would throw exception
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
