/*
===============================================================================
TITLE: Debug vs Release Mode Bug Replication
AGE: 11+ year old bug pattern
AUTHOR: Classic C++ undefined behavior scenario

SCENARIO:
A program works in debug mode but fails in release mode due to uninitialized
variables. This bug pattern is at least 11 years old and still catches developers.

KEY INSIGHT:
- Debug mode: Variables are zero-initialized by the runtime
- Release mode: Variables contain garbage from stack/memory
- Result: IF statements behave differently between builds
===============================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

// Simulate logging functionality for instrumentation
class Logger {
private:
    std::ofstream logFile;
public:
    Logger() : logFile("debug_log.txt") {
        logFile << "=== PROGRAM START ===" << std::endl;
    }
    
    void log(const std::string& message) {
        auto now = std::chrono::system_clock::now();
        logFile << "[LOG] " << message << std::endl;
        std::cout << "[LOG] " << message << std::endl; // Also output to console
    }
    
    ~Logger() {
        logFile << "=== PROGRAM END ===" << std::endl;
    }
};

/*
===============================================================================
THE BUGGY FUNCTION - Replicating the 11+ year old bug
===============================================================================

This function simulates the original buggy code:
1. An uninitialized variable 'featureEnabled'
2. Used only in one critical IF statement
3. Left over from an earlier version of the code
4. Causes different behavior in debug vs release

In the original bug:
- Debug mode: featureEnabled was implicitly 0 (false)
- Release mode: featureEnabled contained random garbage (often non-zero)
- Result: Feature worked in debug, failed in release
===============================================================================
*/

void processCriticalData(Logger& logger) {
    logger.log("Entering processCriticalData()");
    
    // THE BUG: Uninitialized variable - this is the core issue!
    int featureEnabled; // NEVER INITIALIZED - contains garbage in release mode
    
    logger.log("Variable 'featureEnabled' declared but not initialized");
    logger.log("Value of featureEnabled: " + std::to_string(featureEnabled));
    
    // Critical business logic that depends on this variable
    if (featureEnabled) { // This is where the bug manifests!
        logger.log("IF CONDITION: featureEnabled is TRUE - executing critical path");
        
        // Important processing that should happen
        std::cout << "Processing critical data..." << std::endl;
        logger.log("Critical processing completed successfully");
        
    } else {
        logger.log("IF CONDITION: featureEnabled is FALSE - skipping critical path");
        
        // The bug: this path should NOT be taken in production
        std::cout << "Skipping critical processing - FEATURE DISABLED" << std::endl;
        logger.log("WARNING: Critical processing was skipped!");
    }
    
    logger.log("Exiting processCriticalData()");
}

/*
===============================================================================
THE FIXED VERSION - Shows how the bug should be fixed
===============================================================================
*/

void processCriticalData_FIXED(Logger& logger) {
    logger.log("Entering processCriticalData_FIXED()");
    
    // THE FIX: Proper initialization
    int featureEnabled = 1; // Explicitly initialized - no more undefined behavior
    
    logger.log("Variable 'featureEnabled' properly initialized to: " + std::to_string(featureEnabled));
    
    // Same critical logic but now predictable
    if (featureEnabled) {
        logger.log("IF CONDITION: featureEnabled is TRUE - executing critical path");
        
        std::cout << "Processing critical data..." << std::endl;
        logger.log("Critical processing completed successfully");
        
    } else {
        logger.log("IF CONDITION: featureEnabled is FALSE - skipping critical path");
        
        std::cout << "Skipping critical processing - FEATURE DISABLED" << std::endl;
        logger.log("WARNING: Critical processing was skipped!");
    }
    
    logger.log("Exiting processCriticalData_FIXED()");
}

int main() {
    Logger logger;
    
    std::cout << "\n=== DEBUG VS RELEASE BUG DEMONSTRATION ===" << std::endl;
    std::cout << "Replicating an 11+ year old bug pattern\n" << std::endl;
    
    logger.log("Starting debug vs release bug demonstration");
    
    // Part 1: Show the buggy behavior
    std::cout << "\n--- PART 1: BUGGY VERSION ---" << std::endl;
    logger.log("=== RUNNING BUGGY VERSION ===");
    processCriticalData(logger);
    
    // Part 2: Show the fixed behavior  
    std::cout << "\n--- PART 2: FIXED VERSION ---" << std::endl;
    logger.log("=== RUNNING FIXED VERSION ===");
    processCriticalData_FIXED(logger);
    
    std::cout << "\n=== SUMMARY ===" << std::endl;
    std::cout << "This demonstrates why uninitialized variables cause" << std::endl;
    std::cout << "different behavior in debug vs release builds." << std::endl;
    std::cout << "\nKey lessons:" << std::endl;
    std::cout << "1. Always initialize variables" << std::endl;
    std::cout << "2. Use compiler warnings (-Wall -Wextra)" << std::endl;
    std::cout << "3. Test in both debug and release configurations" << std::endl;
    std::cout << "4. Use instrumentation to track down mysterious bugs" << std::endl;
    
    logger.log("Bug demonstration completed");
    
    return 0;
}

/*
===============================================================================
COMPILE AND RUN INSTRUCTIONS:

Debug build (often zero-initializes):
clang++ -g -O0 debug_vs_release_bug.cpp -o debug_bug

Release build (no initialization):
clang++ -O2 -DNDEBUG debug_vs_release_bug.cpp -o release_bug

Compare the outputs to see the difference!
===============================================================================
*/
