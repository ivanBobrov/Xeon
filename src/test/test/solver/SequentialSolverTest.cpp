#include "SequentialSolverTest.h"

SequentialSolverTest::SequentialSolverTest() {
    info = "No info. Run test first.";
}


bool SequentialSolverTest::runTests() {
    return sequentialSolverTest();
}

std::string SequentialSolverTest::getInfo() {
    return info;
}


bool SequentialSolverTest::sequentialSolverTest() {
    bool result = SolverTests::abstractSolverTest(new SequentialSolver());

    if (result) {
        info = "Sequential solver test: SUCCESS";
        return true;
    } else {
        info = "Sequenial solver test: FAILED";
        return false;
    }
}
