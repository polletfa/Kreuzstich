#ifndef IMAGETOOLSINTERFACE_H
#define IMAGETOOLSINTERFACE_H

// libkreuzstich
#include "kreuzstich/thread.h"

namespace KreuzstichGUI {

    class ImageToolsInterface {
    public:
        virtual void colortableChanged() = 0;
        virtual void currentColorChanged() = 0;

        size_t currentColor() const;
        void setCurrentColor(size_t);
        const Kreuzstich::ThreadColors& colortable() const;
        void setColortable(Kreuzstich::ThreadColors);

    private:
        Kreuzstich::ThreadColors m_colortable;
        size_t m_currentColor;
    };


}

#endif // IMAGETOOLSINTERFACE_H
