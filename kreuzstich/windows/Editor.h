#ifndef EDITOR_H
#define EDITOR_H

// kreuzstich
#include "windows/ChildWindow.h"
#include "features/GenerateToolsInterface.h"
#include "features/ZoomInterface.h"
#include "features/SaveInterface.h"
#include "features/ImageToolsInterface.h"

// libkreuzstich
namespace Kreuzstich { class Creator; }

// stdlib & stl
#include <string>

// Qt
class QImage;
#include <QObject>

namespace KreuzstichGUI {

    namespace Ui {
    class Editor;
    }

    class MainWindow;

    class Editor : public ChildWindow,
            public ImageToolsInterface,
            public ZoomInterface,
            public SaveInterface,
            public GenerateToolsInterface
    {
        Q_OBJECT

    public:
        explicit Editor(MainWindow *parent);
        ~Editor();

        void setCreator(Kreuzstich::Creator* creator);
        Kreuzstich::Creator* creator() const;
        void setFilename(std::string);

        // features
        bool hasSaveInterface() const;
        bool hasZoom() const;
        bool hasImageTools() const;
        bool hasGenerateTools() const;

        // SaveInterface
        bool save();
        bool saveAs();

        // ZoomInterface
        void zoomLevelChanged();

        // ImageToolsInterface
        void colortableChanged();
        void currentColorChanged();

        // GenerateToolsInterface
        void savePicture();
        void generateGrid();
        void generateScriptAsLaTeX();
        void generateScriptAsText();

    private:
        static QImage* toQImage(const Magick::Image &image);
        void updateTitle();

        Ui::Editor *ui;
        Kreuzstich::Creator* m_creator;
        QImage* m_image;
        std::string m_filename;
    };

}

#endif // EDITOR_H
