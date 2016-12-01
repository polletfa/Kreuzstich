#ifndef IMPORTPICTUREDIALOG_H
#define IMPORTPICTUREDIALOG_H

// libkreuzstich
namespace Kreuzstich { class Creator; }

// stdlib & stl
#include <string>

// Qt
#include <QDialog>

namespace KreuzstichGUI {

    namespace Ui {
    class ImportPictureDialog;
    }

    struct ImportParameter {
        Kreuzstich::Creator* creator;
        std::string colortable;
        size_t width;
        size_t height;
        bool reduceTo;
        size_t maxColors;
    };

    class ImportPictureDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit ImportPictureDialog(QWidget* parent = 0);
        ~ImportPictureDialog();

        void setFilename(std::string filename);
        ImportParameter parameters() const;

    private:
        Kreuzstich::Creator* creator() const;

    public slots:
        int exec();

    private slots:
        void updateWidth();
        void updateHeight();
        void reduceToChanged();

    private:
        Ui::ImportPictureDialog *ui;
        std::string m_filename;
        Kreuzstich::Creator* m_creator;
    };

}

#endif // IMPORTPICTUREDIALOG_H
