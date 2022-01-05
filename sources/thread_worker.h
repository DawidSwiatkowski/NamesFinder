#pragma once

#include <QObject>

class ThreadWorker : public QObject
{
    Q_OBJECT

friend class Thread;

public:
    virtual ~ThreadWorker();

protected:
    virtual void doWork() = 0;

private slots:
    void doWorkImpl();
};
