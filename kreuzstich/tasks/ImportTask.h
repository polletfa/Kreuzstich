#ifndef IMPORTTASK_H
#define IMPORTTASK_H

// kreuzstich
#include "tasks/Task.h"
#include "dialogs/ImportPictureDialog.h"
namespace KreuzstichGUI { class MainWindow; }

// libkreuzstich
#include "kreuzstich/creator.h"

// stdlib & stl
#include <exception>

// Qt
#include <QThread>

namespace KreuzstichGUI {

    class ImportTask: public Task {
        Q_OBJECT

    public:
        ImportTask(MainWindow* mainWindow, ImportParameter params);
        ~ImportTask();

        void doTask(TaskProgressCallback& callback);
        std::string taskName() const;

        Kreuzstich::Creator* creator() const;

    private:
        ImportParameter m_params;
    };

}

#endif // IMPORTTASK_H
