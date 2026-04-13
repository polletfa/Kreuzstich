#include <gtest/gtest.h>

#include "creator/utils/Version.hpp"

// STL
#include <sstream>

// --- replaceVersionVars

TEST(VersionTest, replaceVersionVars) {
    std::ostringstream oss;
    oss << "(abc)" << Version::NAME
        << "(def)" << Version::WEBSITE
        << "(ghi)" << std::to_string(Version::MAJOR)
        << "(jkl)" << std::to_string(Version::MINOR)
        << "(mno)" << std::to_string(Version::BUILD_TIME)
        << "(pqr)" << Version::GIT_COMMIT
        << "(stu)" << ( Version::RELEASE_BUILD ? "true" : "false" )
        << "(vwx)" << Version::VERSION_STRING
        << "(yz0)" << Version::NAME // multiple occurrences
        << "(123)";

    std::string testStr = "(abc)$NAME$(def)$WEBSITE$(ghi)$MAJOR$(jkl)$MINOR$(mno)$BUILD_TIME$";
    testStr += "(pqr)$GIT_COMMIT$(stu)$RELEASE_BUILD$(vwx)$VERSION_STRING$(yz0)$NAME$(123)";

    Version::replaceVersionVars(testStr);
    EXPECT_STREQ(testStr.data(), oss.str().data());
}

// --- getLicense

TEST(VersionTest, getLicense) {
    auto license = Version::getLicense();
    EXPECT_EQ(license.has_value(), true);
    EXPECT_STREQ(license.value().substr(0, 3).data(), "MIT");
}
