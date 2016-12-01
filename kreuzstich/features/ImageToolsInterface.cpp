// kreuztich
#include "features/ImageToolsInterface.h"

using namespace KreuzstichGUI;
using namespace std;

// *****************************************
// Constructors & destructors
// *****************************************

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

size_t ImageToolsInterface::currentColor() const { return m_currentColor; }

void ImageToolsInterface::setCurrentColor(size_t col) {
    m_currentColor = col;
    currentColorChanged();
}

const Kreuzstich::ThreadColors& ImageToolsInterface::colortable() const { return m_colortable; }

void ImageToolsInterface::setColortable(Kreuzstich::ThreadColors ct) {
    m_colortable = ct;
    colortableChanged();
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
