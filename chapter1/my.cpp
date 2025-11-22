#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cout << "Hello C++ World!" << std::endl;
    std::cout << "Testing basic C++ features..." << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Vector contents: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}