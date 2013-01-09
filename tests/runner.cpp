/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    status = CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
    return status;
}
bool suite_XGuardTestSuite_init = false;
#include "testsuite.h"

static XGuardTestSuite suite_XGuardTestSuite;

static CxxTest::List Tests_XGuardTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_XGuardTestSuite( "testsuite.h", 10, "XGuardTestSuite", suite_XGuardTestSuite, Tests_XGuardTestSuite );

static class TestDescription_suite_XGuardTestSuite_testBasicRollbackCommit1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XGuardTestSuite_testBasicRollbackCommit1() : CxxTest::RealTestDescription( Tests_XGuardTestSuite, suiteDescription_XGuardTestSuite, 13, "testBasicRollbackCommit1" ) {}
 void runTest() { suite_XGuardTestSuite.testBasicRollbackCommit1(); }
} testDescription_suite_XGuardTestSuite_testBasicRollbackCommit1;

static class TestDescription_suite_XGuardTestSuite_testBasicRollbackCommit2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XGuardTestSuite_testBasicRollbackCommit2() : CxxTest::RealTestDescription( Tests_XGuardTestSuite, suiteDescription_XGuardTestSuite, 34, "testBasicRollbackCommit2" ) {}
 void runTest() { suite_XGuardTestSuite.testBasicRollbackCommit2(); }
} testDescription_suite_XGuardTestSuite_testBasicRollbackCommit2;

static class TestDescription_suite_XGuardTestSuite_testMethodWithArgs : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XGuardTestSuite_testMethodWithArgs() : CxxTest::RealTestDescription( Tests_XGuardTestSuite, suiteDescription_XGuardTestSuite, 55, "testMethodWithArgs" ) {}
 void runTest() { suite_XGuardTestSuite.testMethodWithArgs(); }
} testDescription_suite_XGuardTestSuite_testMethodWithArgs;

static class TestDescription_suite_XGuardTestSuite_testMethodByRef : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XGuardTestSuite_testMethodByRef() : CxxTest::RealTestDescription( Tests_XGuardTestSuite, suiteDescription_XGuardTestSuite, 83, "testMethodByRef" ) {}
 void runTest() { suite_XGuardTestSuite.testMethodByRef(); }
} testDescription_suite_XGuardTestSuite_testMethodByRef;

static class TestDescription_suite_XGuardTestSuite_testByReference : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XGuardTestSuite_testByReference() : CxxTest::RealTestDescription( Tests_XGuardTestSuite, suiteDescription_XGuardTestSuite, 110, "testByReference" ) {}
 void runTest() { suite_XGuardTestSuite.testByReference(); }
} testDescription_suite_XGuardTestSuite_testByReference;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
