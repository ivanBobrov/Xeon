#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <vector>
#include "TestCase.h"

class TestRunner {
public:
    TestRunner();
    bool runTests(std::vector<TestCase*> cases);
};

#endif