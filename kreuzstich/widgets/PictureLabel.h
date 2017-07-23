#ifndef KREUZSTICHGUI_PICTURELABEL_H
#define KREUZSTICHGUI_PICTURELABEL_H

// kreuzstich
namespace KreuzstichGUI { class Editor; }

// Qt
#include <QLabel>

namespace KreuzstichGUI {

    class PictureLabel : public QLabel
    {
        Q_OBJECT

    public:
        explicit PictureLabel(QWidget*);
        ~PictureLabel();

        void mouseMoveEvent(QMouseEvent*);

        void setEditor(Editor*);

    signals:
        void showMessage(QString);

    private:
        Editor* m_editor;
    };

} // namespace KreuzstichGUI

#endif // KREUZSTICHGUI_PICTURELABEL_H
