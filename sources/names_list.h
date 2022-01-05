#pragma once

#include "name_converter.h"

#include <QStringList>
#include <QString>

class NamesList
{
public:
	bool load( QString const& _fileName );
	bool save();

	QStringList const& getNames() const;
	void setNames( QStringList& _list );

private:
	QString m_fileName;
	QStringList m_names;
};

