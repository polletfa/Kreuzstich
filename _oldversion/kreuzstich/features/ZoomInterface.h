#ifndef ZOOMINTERFACE_H
#define ZOOMINTERFACE_H

namespace KreuzstichGUI {

    class ZoomInterface {
    public:
        virtual void zoomLevelChanged() = 0;

        unsigned int zoomLevel() const;
        void setZoomLevel(unsigned int);

    private:
        unsigned int m_zoomLevel;
    };


}

#endif // ZOOMINTERFACE_H
