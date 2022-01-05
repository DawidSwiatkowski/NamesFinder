#pragma once

#include <QObject>
#include <QThread>

class ThreadWorker;

class Thread : public QThread
{
    Q_OBJECT

public:
    explicit Thread( QObject *parent = nullptr );
    ~Thread();

   void setWorker( ThreadWorker* _worker );
};
