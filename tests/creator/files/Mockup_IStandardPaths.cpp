#include "Mockup_IStandardPaths.hpp"

void Mockup_IStandardPaths::SetUp() {
    MockupBase::SetUp();
    m_root = QString(TEST_FILES) + "/" + testSuite() + "/" + testName();
}

QStringList Mockup_IStandardPaths::standardLocations(QStandardPaths::StandardLocation location) {
    return {
        m_root + "/test/path/1",
        m_root + "/another/test/path",
        m_root + "/one/more/path"
    };
}

QString Mockup_IStandardPaths::writableLocation(QStandardPaths::StandardLocation location) {
    return m_root + "/test/path/1";
}
