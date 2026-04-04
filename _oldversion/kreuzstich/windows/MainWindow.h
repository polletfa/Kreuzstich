#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// libkreuzstich

// kreuzstich
namespace KreuzstichGUI { class ChildWindow; }
namespace KreuzstichGUI { class Task; }

// Qt
#include <QMainWindow>
#include <QIcon>
class QActionGroup;
class QCloseEvent;
class QProgressBar;
class QSpinBox;
class QLabel;
class QComboBox;

namespace KreuzstichGUI {

    namespace Ui {
    class MainWindow;
    }

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    protected:
        void closeEvent(QCloseEvent*);

    private:
        void addChildWindow(ChildWindow*);

        void initStatusBar();
        void initToolBar();

        void updateMenu();
        void updateToolBar();
        QIcon makeColorIcon(QColor color);

        ChildWindow* activeChild() const;

    public slots:
        void taskCompleted(Task* task);
        void taskFailed(Task* task, const QString& exc);
        void showMessage(const QString&);
        void showProgress(bool);
        void setProgress(double);

    private slots:
        void subwindowActivated();
        void zoom(int);
        void selectColor(int);

        // file menu
        void newEmptyProject();
        void newProjectFromPicture();
        void openProject();
        void saveProject();
        void saveProjectAs();
        void saveAll();

        // generate menu
        void savePicture();
        void generateGrid();
        void generateScriptAsText();
        void generateScriptAsLaTeX();

        // view
        void zoomIn();
        void zoomOut();

        // help menu
        void openAboutBox();

    private:
        Ui::MainWindow *ui;
        QProgressBar* m_progress;
        QActionGroup* m_windowActionGroup;
        QComboBox* m_colors_cmb;
        QSpinBox* m_zoom_sb;
        QLabel* m_zoom_lbl, * m_percent_lbl;
    };

}

#endif // MAINWINDOW_H
