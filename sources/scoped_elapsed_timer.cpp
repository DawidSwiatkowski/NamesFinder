#include "scoped_elapsed_timer.h"

#include <QDebug>
#include <QString>

ScopedElapsedTimer::ScopedElapsedTimer( QString const& _name )
    : m_name( _name )
{
    qDebug() << QString( "Starting [%1]" ).arg( _name );

    m_timer.start();
}

ScopedElapsedTimer::~ScopedElapsedTimer()
{
    qDebug() << QString( "Finished [%1] -> %2 sec" ).arg( m_name ).arg( m_timer.elapsed() / 1000 );
}
