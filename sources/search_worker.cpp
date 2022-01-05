#include "search_worker.h"
#include "name_converter.h"
#include "scoped_elapsed_timer.h"

#include <QThread>
#include <QStringList>
#include <QDebug>

namespace
{

quint64
addValues( quint64& _first, quint64& _second )
{
	quint64 first( _first );
	quint64 second( _second );

	for ( int i = 0; i < 13; ++i )
	{	
		if ( ( ( first & 0xF ) + ( second & 0xF ) ) > 0xF )
			return 0;

		first >>= 4;
		second >>= 4;
	}

	return _first + _second;
}

}

SearchWorker::SearchWorker( Parameters & _parameters )
{
	m_searchValue = LetterConverter::converGroupsToNumber( _parameters.m_groups );
	m_maxCountOfNames = _parameters.m_maximumCountOfNames;

	for ( auto & name : _parameters.m_names )
	{
		if ( name.size() < _parameters.m_minimumNameLenght )
			continue;

		Data data;
		data.m_string = name;
		data.m_value = LetterConverter::converGroupsToNumber(
					  LetterConverter::convertLettersToGroups( name.toStdString() )
					, & _parameters.m_groups
					);
		m_data.push_back( data );
	}

	std::sort(
		  m_data.begin()
		, m_data.end()
		, [ & ]( Data const& _data1, Data const& _data2 )
			{
				return _data1.m_value > _data2.m_value;
			}
		);

	m_indexes.resize( m_maxCountOfNames );
	for ( int i = 0; i < m_maxCountOfNames; ++i )
		m_indexes[ i ] = i;

	m_dataCount = m_data.size();
}

void SearchWorker::doWork()
{
	search( 0, 0 );
}

void
SearchWorker::search( quint16 const& _min, quint64 _value )
{
	++m_deep;

	if ( m_deep < m_maxCountOfNames )
	{
		for ( quint16 i = _min; i < m_dataCount; ++i )
		{
			if ( QThread::currentThread()->isInterruptionRequested() )
				return;

			if ( m_deep == 0 )
				emit onProgress( (float)( i )/ m_dataCount * 100 );

			m_indexes[ m_deep ] = i;

			auto value = addValues( _value, m_data[ i ].m_value );

			if ( value == 0 )
				continue;

			if ( value > m_searchValue )
				continue;

			if ( value == m_searchValue )
			{
				emitResult();
				continue;
			}

			search( i + 1, value );
		}
	}

	--m_deep;
}

void
SearchWorker::emitResult()
{
	if ( m_deep < 0 )
		return;

	QStringList names;
	for ( int i = 0; i <= m_deep; ++i )
		names << m_data[ m_indexes[ i ] ].m_string;

	emit onResult( QStringList( names ) );
}
