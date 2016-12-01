// kreuztich
#include "features/ZoomInterface.h"

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

unsigned int ZoomInterface::zoomLevel() const { return m_zoomLevel; }

void ZoomInterface::setZoomLevel(unsigned int level) {
    m_zoomLevel = level;
    zoomLevelChanged();
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
