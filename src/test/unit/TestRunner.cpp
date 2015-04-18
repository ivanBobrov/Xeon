#include <iostream>
#include "TestRunner.h"

TestRunner::TestRunner() {
}

bool TestRunner::runTests(std::vector<TestCase*> cases) {
    bool result = true;
    for (std::vector<TestCase*>::iterator it = cases.begin(); it != cases.end(); it++) {
        TestCase *test = *it;

        if (test->runTests()) {
            std::cout << test->getInfo() << std::endl;
        } else {
            std::cout << "****** Test error: " << test->getInfo() << " ******" << std::endl;
            result = false;
        }
    }

    return result;
}