#include <iostream>
#include <memory>
#include <string>

// A simple class to demonstrate object creation and destruction
class Resource {
private:
    std::string name;
public:
    Resource(std::string n) : name(std::move(n)) {
        std::cout << "Resource '" << name << "' acquired/created.\n";
    }

    // The destructor is called when the object is destroyed
    ~Resource() {
        std::cout << "Resource '" << name << "' destroyed/released.\n";
    }

    void doSomething() const {
        std::cout << "   -> Resource '" << name << "' is doing something.\n";
    }
};

void demonstrateRawPointers() {
    std::cout << "\n--- 1. Raw Pointers (Manual Management) ---\n";
    
    // Dynamic allocation using 'new'
    Resource* res = new Resource("Raw Pointer Resource");
    
    res->doSomething();
    
    // We MUST manually deallocate using 'delete' to prevent a memory leak.
    delete res; 
    
    std::cout << "--- End of Raw Pointers block ---\n";
}

void demonstrateUniquePointers() {
    std::cout << "\n--- 2. std::unique_ptr (Exclusive Ownership) ---\n";
    
    // A scope block to show when memory is freed
    {
        // Allocation using std::make_unique (Preferred way in Modern C++)
        std::unique_ptr<Resource> uniqRes = std::make_unique<Resource>("Unique Resource");
        
        uniqRes->doSomething();
        
        // Ownership CANNOT be copied. This leads to a compile error:
        // std::unique_ptr<Resource> copyRes = uniqRes; 
        
        // Ownership CAN be moved to another unique_ptr
        std::unique_ptr<Resource> movedRes = std::move(uniqRes);
        
        if (!uniqRes) {
            std::cout << "   -> uniqRes is now null; it no longer owns the resource.\n";
        }
        
        movedRes->doSomething();
        
    } // Memory is AUTOMATICALLY FREED here when 'movedRes' goes out of scope!
    
    std::cout << "--- End of std::unique_ptr block ---\n";
}

void demonstrateSharedPointers() {
    std::cout << "\n--- 3. std::shared_ptr (Shared Ownership) ---\n";
    
    {
        // Allocation using std::make_shared (Preferred way for shared_ptr)
        std::shared_ptr<Resource> sharedRes1 = std::make_shared<Resource>("Shared Resource");
        std::cout << "   -> Reference count: " << sharedRes1.use_count() << "\n";
        
        {
            // We can safely copy a shared_ptr
            std::shared_ptr<Resource> sharedRes2 = sharedRes1;
            std::cout << "   -> Reference count inside inner block: " << sharedRes1.use_count() << "\n";
            sharedRes2->doSomething();
            
        } // sharedRes2 goes out of scope here. Ref count drops to 1, but resource is NOT destroyed yet.
        
        std::cout << "   -> Reference count outside inner block: " << sharedRes1.use_count() << "\n";
        sharedRes1->doSomething();
        
    } // sharedRes1 goes out of scope here. Ref count drops to 0. Resource IS automatically destroyed!
    
    std::cout << "--- End of std::shared_ptr block ---\n";
}

int main() {
    std::cout << "=== Memory Management in C++ ===\n";
    
    demonstrateRawPointers();
    demonstrateUniquePointers();
    demonstrateSharedPointers();
    
    std::cout << "\nProgram completely finished.\n";
    return 0;
}
