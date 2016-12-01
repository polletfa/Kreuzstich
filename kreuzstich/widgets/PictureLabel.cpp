// kreuzstich
#include "widgets/PictureLabel.h"
#include "windows/Editor.h"
#include "error.h"

// libkreuzstich
#include "kreuzstich/thread.h"
#include "kreuzstich/creator.h"

// Qt
#include <QMouseEvent>

// STL
#include <sstream>

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
                stringstream ss;
                ss << x << "x" << y << ": ";
                try{
                    Kreuzstich::ThreadColors::const_iterator it = m_editor->colortable().bestMatch(color);
                    ss << it->second.toStdString();
                    emit showMessage(ss.str().c_str());
                } catch(Kreuzstich::Exception& kexc) {
                    ss << tr(getErrorMessage(kexc).c_str()).toStdString();
                    emit showMessage(ss.str().c_str());
                } catch(std::exception& exc) {
                    ss << tr(exc.what()).toStdString();
                    emit showMessage(ss.str().c_str());
                }
            } else emit showMessage("");
        }
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(parentWidget(), kexc);
    } catch(exception& exc) {
        genericErrorDialog(parentWidget(), exc);
    }
}

