#ifndef MOCKUPBASE_HPP
#define MOCKUPBASE_HPP

#include <gtest/gtest.h>

class MockupBase {
public:
    virtual void SetUp();
    virtual void TearDown();

protected:
    const char* testSuite() const;
    const char* testName() const;

private:
    const char* m_testSuite;
    const char* m_testName;
};

#endif // MOCKUPBASE_HPP
