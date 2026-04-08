#include "AboutDialog.hpp"
#include "ui_AboutDialog.h"

// gui
#include "gui/Application.hpp"

// Qt
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QDesktopServices>

// We don't include these strings in QtDesigner directly, because we don't want the whole html stuff to end up in the translation files.
constexpr const char* TITLE = R"(<html><head/><body><p><span style=" font-size:16pt; font-weight:700;">$NAME$</span></p></body></html>)";
constexpr const char* TEXT = R"(<html><head/><body>
    <p>$VERSION_STRING$
    <br/>%1</p>
    <p><a href="$WEBSITE$"><span style=" text-decoration: underline; color:#0000ff;">$WEBSITE$</span></a></p>
    <p>%2</p>
    <ul style="margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;">
       <li style=" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
          <a href="aboutQt"><span style=" text-decoration: underline; color:#0000ff;">Qt 6</span></a>
       </li>
    </ul>
    </body></html>)";
constexpr const char* COPYRIGHT = R"(<html><head/><body><p><span style=" font-weight:700;">%1</span></p></body></html>)";

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);

    m_ui->lbl_title->setText(TITLE);
    m_ui->lbl_text->setText(QString(TEXT)
                            .arg(tr("$NAME$ is an application designed to create complex cross-stitch patterns based on a picture."))
                            .arg(tr("Third-party libraries: ")));
    m_ui->lbl_copyright->setText(QString(COPYRIGHT)
                                 .arg(tr("Copyright &amp; License")));

    Application::replaceVersionVars(this);
    Application::replaceVersionVars(m_ui->lbl_title);
    Application::replaceVersionVars(m_ui->lbl_text);
    Application::replaceVersionVars(m_ui->lbl_copyright);

    QFile license{":/LICENSE"};
    if(license.open(QIODevice::ReadOnly)) {
        QTextStream in(&license);
        m_ui->txt_license->setText(in.readAll());
    } else {
        m_ui->lbl_copyright->hide();
        m_ui->txt_license->hide();
    }
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}

void AboutDialog::linkActivated(const QString& link) {
    if(!link.compare("aboutQt")) {
        QApplication::aboutQt();
    } else if(link.startsWith("http://") || link.startsWith("https://")) {
        QDesktopServices::openUrl(link);
    }
}
