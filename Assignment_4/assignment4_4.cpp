#include <iostream>
#include <ctime>

class Base {
public:
    virtual void virtualFunction() {
        // nothing to do here
    }

    void nonVirtualFunction() {
        // nothing to do here
    }
};

class Derived : public Base {
public:
    void virtualFunction() override {
        // nothing to do here
    }

    void nonVirtualFunction() {
        // nothing to do here
    }
};

int main() {
    const int count = 100000000;
    Derived derivedObj;
    Base* basePtr = &derivedObj;

    // Timing virtual function calls
    clock_t start = clock();
    for (int i = 0; i < count; i++) {
        basePtr->virtualFunction();
    }
    clock_t durationVirtual = clock() - start;

    // Timing non-virtual function calls
    start = clock();
    for (int i = 0; i < count; i++) {
        derivedObj.nonVirtualFunction();
    }
    clock_t durationNonVirtual = clock() - start;

    std::cout << "Virtual function time :" << durationVirtual <<"ms\n";
    std::cout << "Non-virtual function time :" << durationNonVirtual << "ms\n";

    return 0;
}
