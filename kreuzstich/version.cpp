// kreuzstich
#include "version.h"

// stdlib & stl
#include <sstream>

using namespace std;
using namespace KreuzstichGUI;

string KreuzstichGUI::versionString() {
    stringstream ss;
    ss << PROJECT_NAME << " " << MAJOR_VERSION << "." << MINOR_VERSION << "r"<<SVN_REVISION << " build " << BUILD_TIME
       << " " << SYSTEM << " " << PROCESSOR;
    return ss.str();
}
