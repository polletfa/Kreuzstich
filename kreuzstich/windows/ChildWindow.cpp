// kreuztich
#include "windows/ChildWindow.h"
#include "windows/MainWindow.h"
#include "features/SaveInterface.h"
#include "error.h"

// Qt
#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>

using namespace KreuzstichGUI;
using namespace std;

// *****************************************
// Constructors & destructors
// *****************************************

ChildWindow::ChildWindow(MainWindow* parent) :
    QWidget(parent), m_mainwindow(parent)
{
    m_windowaction = new QAction(this);
    m_windowaction->setCheckable(true);

    connect(m_windowaction, SIGNAL(triggered()), this, SLOT(show()));
    connect(m_windowaction, SIGNAL(triggered()), this, SLOT(setFocus()));

    connect(this, SIGNAL(showMessage(QString)), parent, SLOT(showMessage(QString)));
    connect(this, SIGNAL(showProgress(bool)), parent, SLOT(showProgress(bool)));
    connect(this, SIGNAL(setProgress(double)), parent, SLOT(setProgress(double)));
}

ChildWindow::~ChildWindow()
{}

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

MainWindow* ChildWindow::mainWindow() const {
    return m_mainwindow;
}

QAction* ChildWindow::windowMenuAction() {
    QString title = this->windowTitle();
    title.replace("[*]", isWindowModified() ? "*" : "");
    m_windowaction->setText(title);
    return m_windowaction;
}

QString ChildWindow::title() const {
    return m_title;
}

void ChildWindow::setTitle(QString str) {
    m_title = str;
    updateTitleBar();
}

std::map<std::string, QString> ChildWindow::titleSuffixList() const {
    return m_titleSuffix;
}

QString ChildWindow::titleSuffix(string key) const {
    if(m_titleSuffix.find(key) != m_titleSuffix.end())
        return m_titleSuffix.at(key);
    else return "";
}

void ChildWindow::setTitleSuffix(std::string key, QString value) {
    if(value.length() > 0)
        m_titleSuffix[key] = value;
    else
        m_titleSuffix.erase(key);
    updateTitleBar();
}

void ChildWindow::clearTitleSuffix() {
    m_titleSuffix.clear();
    updateTitleBar();
}

// *****************************************
// Protected & Private methods
// *****************************************

void ChildWindow::updateTitleBar() {
    QString t = m_title;
    t += "[*]";
    if(m_titleSuffix.size() > 0) {
        t+=" (";
        for(std::map<std::string,QString>::iterator it = m_titleSuffix.begin(); it != m_titleSuffix.end(); ++it) {
            if(it != m_titleSuffix.begin()) t+=", ";
            t+=it->second;
        }
        t += ")";
    }
    setWindowTitle(t);
    m_windowaction->setText(windowTitle());
}

// *****************************************
// Qt slots
// *****************************************

void ChildWindow::forwardMessage(QString str) {
    emit showMessage(str);
}

// *****************************************
// Qt events
// *****************************************

void ChildWindow::closeEvent(QCloseEvent *event) {
    try {
        if(hasSaveInterface() && isWindowModified()) {
            activateWindow();
            setFocus();


            QMessageBox::StandardButton rep;
            rep = QMessageBox::question(this, title(), tr("Do you want to save your changes?"),
                                        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            switch(rep) {
            case QMessageBox::Yes:
                // save & quit
                if(dynamic_cast<SaveInterface*>(this)->save())
                    event->accept();
                else
                    event->ignore();
                break;
            case QMessageBox::No:
                // discard & quit
                event->accept();
                break;
            case QMessageBox::Cancel:
            default:
                // don't quit
                event->ignore();
            }
        } else event->accept();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
        event->ignore();
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
        event->ignore();
    }
}

