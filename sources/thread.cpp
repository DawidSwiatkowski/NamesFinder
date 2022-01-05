#include "thread.h"
#include "thread_worker.h"

Thread::Thread( QObject *parent )
    : QThread( parent )
{
}

Thread::~Thread()
{
    quit();
    wait();
}

void
Thread::setWorker( ThreadWorker* _worker)
{
    _worker->moveToThread( this );

    connect( this, &QThread::started, _worker, &ThreadWorker::doWorkImpl );
    connect( this, &QThread::finished, _worker, &QObject::deleteLater );
}
