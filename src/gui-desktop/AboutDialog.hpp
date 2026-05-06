/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

// STL
#include <memory>

// Qt
#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);

private slots:
    void linkActivated(const QString& link); /**< Called when a hyperlink is activated */

private:
    std::shared_ptr<Ui::AboutDialog> m_ui;
};

#endif // ABOUTDIALOG_HPP
