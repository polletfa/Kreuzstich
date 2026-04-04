#ifndef CHILDWINDOW_H
#define CHILDWINDOW_H

// kreuzstich
namespace KreuzstichGUI { class MainWindow; }

// stdlib & stl
#include <map>
#include <string>

// Qt
#include <QString>
#include <QWidget>
class QAction;
class QCloseEvent;

namespace KreuzstichGUI {

    class ChildWindow : public QWidget
    {
        Q_OBJECT

    public:        
        explicit ChildWindow(MainWindow *parent);
        ~ChildWindow();

        QAction* windowMenuAction();

        // features
        virtual bool hasSaveInterface() const = 0;
        virtual bool hasZoom() const = 0;
        virtual bool hasImageTools() const = 0;
        virtual bool hasGenerateTools() const = 0;

        QString title() const;
        void setTitle(QString);

        std::map<std::string, QString> titleSuffixList() const;
        QString titleSuffix(std::string) const;
        void setTitleSuffix(std::string, QString);
        void clearTitleSuffix();

        void updateTitleBar();

        MainWindow* mainWindow() const;

    protected:
        void closeEvent(QCloseEvent *);

    public slots:
        void forwardMessage(QString);

    signals:
        void showMessage(const QString& str);
        void showProgress(bool);
        void setProgress(double);

    private:
        QAction* m_windowaction;
        QString m_title;
        std::map<std::string,QString> m_titleSuffix;
        MainWindow* m_mainwindow;
    };

}

#endif // CHILDWINDOW_H
