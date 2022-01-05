#pragma once

#include "names_list.h"

#include <QString>
#include <QStringList>

class Dictionaries
{

public:
	enum class Type
	{
		  Male
		, Female
	};

public:
	Dictionaries();

	void setType( Type _type );
	Type getType() const;

	bool exists( QString const& _name );
	void addName( QString const& _name );
	void removeName( QString const& _name );

	QStringList const& getNames() const;

private:
	Type m_type;
	NamesList m_namesList;
};

