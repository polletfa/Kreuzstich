#include "MockupBase.hpp"

void MockupBase::SetUp() {
    const auto* info = testing::UnitTest::GetInstance()->current_test_info();
    m_testSuite = info->test_suite_name();
    m_testName = info->name();
}

void MockupBase::TearDown() {
    m_testSuite = nullptr;
    m_testName = nullptr;
}

const char* MockupBase::testSuite() const {
    return m_testSuite;
}

const char* MockupBase::testName() const {
    return m_testName;
}
