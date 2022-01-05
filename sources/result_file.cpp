#include "result_file.h"


ResultFile::ResultFile( QString const& _fileName )
{
	m_file.setFileName( _fileName );
}

void
ResultFile::open()
{
	if ( !m_file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
		return;

	m_stream.setDevice( &m_file );
}

void
ResultFile::close()
{
	m_file.close();
}

void
ResultFile::writeHeader(
	  LetterConverter::Groups _groups
	, Dictionaries::Type _dictionariesType
)
{
	m_stream << "Dictionary: ";
	m_stream << ( _dictionariesType == Dictionaries::Type::Male ? "Male" : "Female" );
	m_stream<< "\n\n";

	m_stream << "Groups:\n";

	for ( int i = 0; i < 13; ++i )
	{
		LetterConverter::Group group = static_cast< LetterConverter::Group >( i );

		auto it = std::find_if(
					  _groups.begin()
					, _groups.end()
					, [ & ]( LetterConverter::GroupData const& _data )
						{
							return _data.m_group == group;
						}
					);

		if ( it == _groups.end() )
			continue;

		if ( it->m_count == 0 )
			continue;

		m_stream << QString::number( i + 1 );
		m_stream << ". ";
		m_stream << QString::number( it->m_count );
		m_stream << "  (";
		m_stream << LetterConverter::groupToString( it->m_group );
		m_stream << ")";
		m_stream << "\n";
	}

	m_stream << "\n";
}

void
ResultFile::write( QString const& _text )
{
	m_stream << _text;
	m_stream << "\n";
}
