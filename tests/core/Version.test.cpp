#include <gtest/gtest.h>

#include "core/Version.hpp"

// STL
#include <sstream>

// --- replaceVersionVars

TEST(VersionTest, replaceVersionVars) {
    std::ostringstream oss;
    oss << "(abc)" << Version::NAME
        << "(def)" << Version::WEBSITE
        << "(ghi)" << std::to_string(Version::MAJOR)
        << "(jkl)" << std::to_string(Version::MINOR)
        << "(mno)" << Version::BUILD_TIME
        << "(pqr)" << Version::GIT_COMMIT
        << "(stu)" << ( Version::RELEASE_BUILD ? "true" : "false" )
        << "(vwx)" << Version::getVersionString()
        << "(yz0)" << Version::NAME // multiple occurrences
        << "(123)" << Version::LICENSE
        << "(456)";

    std::string testStr = "(abc)$NAME$(def)$WEBSITE$(ghi)$MAJOR$(jkl)$MINOR$(mno)$BUILD_TIME$";
    testStr += "(pqr)$GIT_COMMIT$(stu)$RELEASE_BUILD$(vwx)$VERSION_STRING$(yz0)$NAME$(123)$LICENSE$(456)";

    Version::replaceVersionVars(testStr);
    EXPECT_EQ(testStr, oss.str());
}

// --- Check that LICENSE is loaded properly

TEST(VersionTest, LICENSE) {
    EXPECT_EQ(Version::LICENSE.substr(0, Version::LICENSE.find('\n')), "MIT License");
}
