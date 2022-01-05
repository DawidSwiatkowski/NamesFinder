#include "dictionaries.hpp"

#include <QMessageBox>

namespace
{

int
find( QStringList const& _list, QString const& _name )
{
	auto it = std::find_if(
				_list.begin()
				, _list.end()
				, [ & ]( QString const& _val )
					{
						return _name.toLower() == _val.toLower();
					}
				);

	return it == _list.end()
			? -1
			: std::distance( _list.begin(), it )
			;
}

}

Dictionaries::Dictionaries()
{
	setType( Type::Male );
}

void
Dictionaries::setType( Type _type )
{
	m_namesList.load( _type == Type::Male ? "male.txt" : "female.txt" );

	m_type = _type;
}

Dictionaries::Type
Dictionaries::getType() const
{
	return m_type;
}

bool
Dictionaries::exists(const QString &_name)
{
	return find( m_namesList.getNames(), _name ) != -1;
}

void
Dictionaries::addName( QString const& _name )
{
	auto names = m_namesList.getNames();

	int index = find( names, _name );
	if ( index != -1 )
		return;

	names.push_back( _name );
	std::sort( names.begin(), names.end() );

	m_namesList.setNames( names );
	m_namesList.save();
}

void
Dictionaries::removeName( const QString& _name )
{
	auto names = m_namesList.getNames();

	int index = find( names, _name );
	if ( index == -1 )
		return;

	names.erase( names.begin() + index );
	m_namesList.setNames( names );
	m_namesList.save();
}

QStringList const&
Dictionaries::getNames() const
{
	return m_namesList.getNames();
}
