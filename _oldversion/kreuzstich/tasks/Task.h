#ifndef TASK_H
#define TASK_H

// kreuzstich
namespace KreuzstichGUI { class MainWindow; }

// libkreuzstich
#include "kreuzstich/creator.h"

// stdlib & stl
#include <string>

// Qt
#include <QThread>
#include <QString>

namespace KreuzstichGUI {

    class Task;
    class TaskProgressCallback : public Kreuzstich::ProgressCallback {
    public:
        TaskProgressCallback(Task* task);
        void operator()(double percent);

    private:
        Task* m_task;
    };

    class Task : public QThread {
        Q_OBJECT

    public:
        Task(MainWindow* mainWindow);
        ~Task();

        void run();

        virtual void doTask(TaskProgressCallback& callback) = 0;
        virtual std::string taskName() const = 0;

#if USE_QT_VERSION == 4
        // signals are protected with Qt4 so we need a public method.
        void emitSetProgress(double);
#endif

    signals:
        void taskCompleted(Task* task);
        void taskFailed(Task* task, const QString& exc);
        void showMessage(const QString& str);
        void showProgress(bool);
        void setProgress(double);

    private:
        MainWindow* m_mainwindow;
    };

}

#endif // TASK_H
