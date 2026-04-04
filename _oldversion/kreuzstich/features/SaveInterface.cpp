// kreuztich
#include "features/SaveInterface.h"
#include "windows/ChildWindow.h"

using namespace KreuzstichGUI;

// *****************************************
// Constructors & destructors
// *****************************************

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

void SaveInterface::setModified(bool mod) {
    dynamic_cast<ChildWindow*>(this)->setWindowModified(mod);
    dynamic_cast<ChildWindow*>(this)->updateTitleBar();
}

// *****************************************
// Protected & Private methods
// *****************************************

// *****************************************
// Qt slots
// *****************************************

// *****************************************
// Qt events
// *****************************************
