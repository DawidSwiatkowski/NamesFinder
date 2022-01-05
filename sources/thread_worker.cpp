#include "thread_worker.h"

#include <QThread>

ThreadWorker::~ThreadWorker()
{
}

void
ThreadWorker::doWorkImpl()
{
    doWork();

    QThread::currentThread()->quit();
}
