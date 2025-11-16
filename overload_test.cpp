/*
===============================================================================
TOPIC: C++ Function Overloading with Initializer Lists
SUBTOPIC: Overload Resolution and Conversion Ranking

KEY CONCEPTS:
1. Initializer lists can be ambiguous in overload resolution
2. C++ ranks conversions by "betterness" 
3. Direct conversions beat user-defined conversions
4. Single-element lists have special behavior

OVERLOAD RESOLUTION RULES (C++ Standard):
- Exact match > Promotion > Standard conversion > User-defined conversion
- {2} can convert to int (standard conversion) OR vector<int> (user-defined)
- Standard conversion wins due to better ranking
===============================================================================
*/

#include <iostream>
#include <vector>

/*
===============================================================================
FUNCTION OVERLOADS - Two candidates for the same call
===============================================================================
*/

// OVERLOAD 1: Takes a single integer by value
// CONVERSION RANKING: Exact match for int arguments
// PERFORMANCE: No construction needed - just copy the integer
void print(int x) {
    // This function is the "winner" for single-element initializer lists
    // because {2} -> int is a STANDARD conversion (better ranking)
    std::cout << "print(int): " << x << std::endl;
}

// OVERLOAD 2: Takes a vector of integers by value
// CONVERSION RANKING: Requires user-defined construction
// PERFORMANCE: Needs to construct vector object (more expensive)
// NOTE: Could be optimized to const std::vector<int>& for better performance
void print(const std::vector<int> n) {
    // This function "loses" for {2} because {2} -> vector<int> 
    // is a USER-DEFINED conversion (worse ranking)
    std::cout << "print(vector) <int>" << std::endl;
}

/*
===============================================================================
MAIN FUNCTION - Testing different overload resolution scenarios
===============================================================================
*/

int main() {
    /*
    ===============================================================================
    TEST CASE 1: Direct integer argument
    ===============================================================================
    CALL: print(2)
    EXPECTED: print(int) overload
    REASONING: Exact match - no conversion needed
    ===============================================================================
    */
    std::cout << "=== TEST 1: Direct integer ===" << std::endl;
    print(2);                    // Obvious choice: print(int) - exact match
    
    /*
    ===============================================================================
    TEST CASE 2: Pre-constructed vector
    ===============================================================================
    CALL: print(v) where v is vector<int>
    EXPECTED: print(vector) overload  
    REASONING: Type already matches exactly - no conversion needed
    ===============================================================================
    */
    std::cout << "\n=== TEST 2: Pre-constructed vector ===" << std::endl;
    std::vector<int> v = {2};    // Vector created first, then passed
    print(v);                    // Type matches print(vector) exactly
    
    /*
    ===============================================================================
    TEST CASE 3: Explicit vector construction
    ===============================================================================
    CALL: print(std::vector<int>{2})
    EXPECTED: print(vector) overload
    REASONING: Explicit type removes all ambiguity
    ===============================================================================
    */
    std::cout << "\n=== TEST 3: Explicit vector construction ===" << std::endl;
    print(std::vector<int>{2});  // Forces vector constructor - no ambiguity
    
    /*
    ===============================================================================
    TEST CASE 4: THE SURPRISING CASE - Single-element initializer list
    ===============================================================================
    CALL: print({2})
    EXPECTED: print(int) overload (surprising!)
    ACTUAL: print(int): 2
    
    WHY THIS HAPPENS - Overload Resolution Analysis:
    
    OPTION A: Convert {2} to int
    - Conversion type: Standard conversion (list-initialization)
    - Ranking: BETTER (3rd best after exact match and promotion)
    - Cost: No object construction, just value extraction
    - Result: Calls print(int)
    
    OPTION B: Convert {2} to vector<int>
    - Conversion type: User-defined conversion (calls vector constructor)
    - Ranking: WORSE (4th best - last in the hierarchy)
    - Cost: Must construct vector object, allocate memory
    - Result: Would call print(vector) - but loses the competition
    
    COMPILER DECISION: Choose Option A (standard conversion beats user-defined)
    ===============================================================================
    */
    std::cout << "\n=== TEST 4: Surprising single-element initializer ===" << std::endl;
    print({2});                   // Calls print(int)! Not print(vector) as many expect
    
    /*
    ===============================================================================
    UNDERSTANDING THE COMPILER WARNING:
    ===============================================================================
    WARNING: braces around scalar initializer [-Wbraced-scalar-init]
    
    What Clang is telling us:
    "Hey programmer, {2} is weird syntax for an integer!
     Normally people write just '2' for integers.
     The braces { } are usually for containers/objects."
    
    This warning actually CONFIRMS our analysis:
    - The compiler sees {2} being treated as scalar (int) initialization
    - It's warning us about the unusual syntax
    - The warning proves {2} is converting to int, not vector<int>
    ===============================================================================
    */
    
    /*
    ===============================================================================
    WORKAROUNDS - How to force vector construction when needed
    ===============================================================================
    
    METHOD 1: Be explicit about the type
    print(std::vector<int>{2});  // Already demonstrated above
    
    METHOD 2: Use double braces (C++17 initializer_list constructor)
    print({{2}});                 // Outer braces for function call, 
                                   // inner braces for initializer_list
    
    METHOD 3: Remove ambiguity with multiple elements  
    print({2, 2});                // Cannot convert to single int, must be vector
    
    METHOD 4: Use std::initializer_list parameter (API design solution)
    void print(std::initializer_list<int> list); // Better for this use case
    ===============================================================================
    */
    
    std::cout << "\n=== SUMMARY ===" << std::endl;
    std::cout << "The key lesson: C++ overload resolution follows strict" << std::endl;
    std::cout << "conversion ranking rules, not programmer intuition!" << std::endl;
    std::cout << "Standard conversions beat user-defined conversions." << std::endl;
    
    return 0;
}

/*
===============================================================================
LESSONS LEARNED:
1. Initializer lists can have surprising overload resolution behavior
2. Single-element lists are ambiguous between direct type and container
3. C++ prefers standard conversions over user-defined constructors
4. Be explicit when you want container construction from single elements
5. This behavior applies to all container types, not just vector

PRACTICAL IMPLICATIONS:
- API design should consider this ambiguity
- Use explicit types or std::initializer_list parameters when needed
- Test edge cases with single-element initializer lists
===============================================================================
*/
