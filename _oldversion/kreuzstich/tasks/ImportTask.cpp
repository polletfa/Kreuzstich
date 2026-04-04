// kreuzstich
#include "tasks/ImportTask.h"

// libkreuzstich
#include "kreuzstich/creator.h"

using namespace KreuzstichGUI;
using namespace std;

// *****************************************
// Constructors & destructors
// *****************************************

ImportTask::ImportTask(MainWindow* mainWindow, ImportParameter params)
    : Task(mainWindow), m_params(params)
{
}

ImportTask::~ImportTask()
{
}

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

string ImportTask::taskName() const { return "ImportTask"; }

Kreuzstich::Creator* ImportTask::creator() const {
    return m_params.creator;
}

// *****************************************
// Protected & Private methods
// *****************************************

// *****************************************
// Qt slots
// *****************************************

// *****************************************
// Qt events
// *****************************************

void ImportTask::doTask(TaskProgressCallback& callback) {
    emit showMessage(tr("Loading colortable..."));
    m_params.creator->setColortable(m_params.colortable);
    emit showMessage(tr("Resizing picture..."));
    m_params.creator->resize(m_params.width, m_params.height);
    if(m_params.reduceTo) {
        emit showMessage(tr("Quantizing colors..."));
        m_params.creator->quantizeColors(m_params.maxColors);
    }
    emit showMessage(tr("Selecting thread colors..."));
    m_params.creator->chooseThreads(callback);
}

