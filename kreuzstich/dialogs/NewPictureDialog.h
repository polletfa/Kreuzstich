#ifndef NEWPICTUREDIALOG_H
#define NEWPICTUREDIALOG_H

// stdlib & stl
#include <string>

// Qt
#include <QDialog>

namespace KreuzstichGUI {

    namespace Ui {
    class NewPictureDialog;
    }

    class NewPictureDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit NewPictureDialog(QWidget* parent = 0);
        ~NewPictureDialog();

        int columns() const;
        int rows() const;
        std::string colortable() const;

    private:
        Ui::NewPictureDialog *ui;
    };

}

#endif // IMPORTPICTUREDIALOG_H
