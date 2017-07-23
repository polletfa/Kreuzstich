// kreuzstich
#include "widgets/PictureLabel.h"
#include "windows/Editor.h"
#include "error.h"

// libkreuzstich
#include "kreuzstich/thread.h"
#include "kreuzstich/creator.h"

// Qt
#include <QMouseEvent>

using namespace KreuzstichGUI;
using namespace std;

// *****************************************
// Constructors & destructors
// *****************************************

PictureLabel::PictureLabel(QWidget* parent)
    :QLabel(parent)
{
    setMouseTracking(true);
    setAlignment(Qt::AlignCenter);
}

PictureLabel::~PictureLabel() {}

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

void PictureLabel::setEditor(Editor* edit) { m_editor = edit; }

// *****************************************
// Protected & Private methods
// *****************************************

// *****************************************
// Qt slots
// *****************************************

// *****************************************
// Qt events
// *****************************************

void PictureLabel::mouseMoveEvent(QMouseEvent *event) {
    try {
        if(pixmap()) {
            int x = event->x() -(width() - pixmap()->width())/2;
            int y = event->y() -(height() - pixmap()->height())/2;

            if(x > 0 && y > 0 && x < pixmap()->width() && y < pixmap()->height()) {
                x /= m_editor->zoomLevel()/100;
                y /= m_editor->zoomLevel()/100;

                Kreuzstich::ThreadColor color(Magick::ColorRGB(this->m_editor->creator()->image().pixelColor(x, y)));
                try{
                    Kreuzstich::ThreadColors::const_iterator it = m_editor->colortable().bestMatch(color);
                    emit showMessage(it->second.toStdString().c_str());
                } catch(Kreuzstich::Exception& kexc) {
                    emit showMessage(tr(getErrorMessage(kexc).c_str()));
                } catch(std::exception& exc) {
                    emit showMessage(tr(exc.what()));
                }
            } else emit showMessage("");
        }
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(parentWidget(), kexc);
    } catch(exception& exc) {
        genericErrorDialog(parentWidget(), exc);
    }
}

