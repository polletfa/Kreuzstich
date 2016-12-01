// kreuzstich
#include "tasks/Task.h"
#include "error.h"
#include "windows/MainWindow.h"

using namespace KreuzstichGUI;
using namespace std;

TaskProgressCallback::TaskProgressCallback(Task* task) : m_task(task) {}

void TaskProgressCallback::operator()(double percent) {
#if USE_QT_VERSION == 4
    m_task->emitSetProgress(percent);
#else
    emit m_task->setProgress(percent);
#endif
}

// *****************************************
// Constructors & destructors
// *****************************************

Task::Task(MainWindow* mainWindow)
    : m_mainwindow(mainWindow)
{
    connect(this, SIGNAL(taskCompleted(Task*)), mainWindow, SLOT(taskCompleted(Task*)));
    connect(this, SIGNAL(taskFailed(Task*,QString)), mainWindow, SLOT(taskFailed(Task*,QString)));
    connect(this, SIGNAL(showMessage(QString)), mainWindow, SLOT(showMessage(QString)));
    connect(this, SIGNAL(showProgress(bool)), mainWindow, SLOT(showProgress(bool)));
    connect(this, SIGNAL(setProgress(double)), mainWindow, SLOT(setProgress(double)));
}

Task::~Task()
{
}

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

void Task::run() {
    try {
        TaskProgressCallback callback(this);
        emit setProgress(0);
        emit showProgress(true);

        doTask(callback);

        emit showMessage(tr("Done."));
        emit showProgress(false);
        emit taskCompleted(this);
    } catch(Kreuzstich::Exception& kexc) {
        emit taskFailed(this, tr(getErrorMessage(kexc).c_str()));
        emit showProgress(false);
        emit showMessage("");
    } catch(exception& exc) {
        emit taskFailed(this, exc.what());
        emit showProgress(false);
        emit showMessage("");
    }
}

#if USE_QT_VERSION == 4
void Task::emitSetProgress(double percent) {
    emit setProgress(percent);
}
#endif

// *****************************************
// Protected & Private methods
// *****************************************

// *****************************************
// Qt slots
// *****************************************

// *****************************************
// Qt events
// *****************************************
