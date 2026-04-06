#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private slots:
    void linkActivated(const QString& link); /**< Called when a hyperlink is activated */

private:
    Ui::AboutDialog *m_ui;
};

#endif // ABOUTDIALOG_HPP
