#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <string>

class TestCase {
public:
    virtual bool runTests() = 0;
    virtual std::string getInfo() = 0;
};

#endif