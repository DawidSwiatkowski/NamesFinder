#include "names_list.h"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDataStream>
#include <QStandardPaths>

namespace
{
	const QString DataFolder = "data";
}

bool
NamesList::load( QString const& _fileName )
{
	m_fileName = _fileName;

	QString defaultFilePath = DataFolder + "/" + m_fileName;

	QString fileToLoad
			= QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) + "/" + defaultFilePath;

	if ( !QFile( fileToLoad ).exists() )
		fileToLoad = defaultFilePath;

	QFile inputFile( fileToLoad );

    if ( !inputFile.open( QIODevice::ReadOnly ) )
        return false;

	m_names.clear();

    QTextStream in( &inputFile );

    while ( !in.atEnd() )
    {
		QString name = in.readLine();
		if ( !name.isEmpty() )
            m_names.push_back( name );
    }

    inputFile.close();
	return true;
}

bool
NamesList::save()
{
	QDir dir = QDir( QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) );
	dir.mkpath( DataFolder );
	dir.cd( DataFolder );

	QFile outputFile( dir.path() + "/" + m_fileName );

	if ( !outputFile.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
		return false;

	QTextStream out( &outputFile );

	for ( auto& name : m_names )
		out << name << "\n";

	outputFile.close();

	return true;
}

QStringList const&
NamesList::getNames() const
{
	return m_names;
}

void
NamesList::setNames(QStringList &_list)
{
	m_names = _list;
}

