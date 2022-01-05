#pragma once

#include <QElapsedTimer>
#include <QString>

class ScopedElapsedTimer
{

public:
    ScopedElapsedTimer( QString const& _name );
    ~ScopedElapsedTimer();

private:
    QElapsedTimer m_timer;
    QString m_name;
};
