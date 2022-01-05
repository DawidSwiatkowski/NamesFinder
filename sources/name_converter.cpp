#include "name_converter.h"
#include <map>
#include <algorithm>

namespace LetterConverter
{

std::map< char, Group >
createCharsPositionsMap()
{
    return
     {
		  { 'a', Group::A }
		, { 'e', Group::E }
		, { 'o', Group::O }
		, { 'u', Group::U }
		, { 'r', Group::RI },  { 'i', Group::RI }
		, { 'j', Group::JS },  { 's', Group::JS }
		, { 'c', Group::CL },  { 'l', Group::CL }
		, { 'n', Group::NW },  { 'w', Group::NW }
		, { 'x', Group::XF },  { 'f', Group::XF }
		, { 'b', Group::BKT }, { 'k', Group::BKT }, { 't', Group::BKT }
		, { 'm', Group::MDV }, { 'd', Group::MDV }, { 'v', Group::MDV }
		, { 'p', Group::PGY }, { 'g', Group::PGY }, { 'y', Group::PGY }
		, { 'h', Group::HQZ }, { 'q', Group::HQZ }, { 'z', Group::HQZ }
     };
}

Groups
convertLettersToGroups( std::string const& _letters )
{
   static auto charsPositionMaps = createCharsPositionsMap();

   Groups groups = {
		 { Group::A, 0 }
	   , { Group::E, 0 }
	   , { Group::O, 0 }
	   , { Group::U, 0 }
	   , { Group::RI, 0 }
	   , { Group::JS, 0 }
	   , { Group::CL, 0 }
	   , { Group::NW, 0 }
	   , { Group::XF, 0 }
	   , { Group::BKT, 0 }
	   , { Group::MDV, 0 }
	   , { Group::PGY, 0 }
	   , { Group::HQZ, 0 }
   };

    for ( char const& c : _letters )
    {
        auto it = charsPositionMaps.find( tolower( c ) );

        if ( it == charsPositionMaps.end() )
            continue;

		auto groupIt = std::find_if(
					  groups.begin()
					, groups.end()
					, [ & ]( GroupData const& _data )
						{
							return _data.m_group == it->second;
						}
				);

		groupIt->m_count += 1;
    }

	sortGroups( groups );

	return groups;
}

quint64
converGroupsToNumber( Groups const& _groups, Groups* _order )
{
	Groups groups;

	if ( _order )
	{
		for ( auto& group : *_order )
		{
			auto it = std::find_if(
						  _groups.begin()
						, _groups.end()
						, [ & ]( GroupData const& _data )
							{
								return _data.m_group == group.m_group;
							}
						);

			groups.push_back( *it );
		}
	}
	else
	{
		groups = _groups;
	}

    quint64 value = 0;

	for ( std::size_t i = 0; i < groups.size(); ++i )
		value += ( 1ULL * groups[ i ].m_count ) << ( 4 * i );

	return value;
}

QString
groupToString( Group _group )
{
	switch( _group )
	{
	case Group::JS:
		return "J,S";
	case Group::BKT:
		return "B,K,T";
	case Group::CL:
		return "C,L";
	case Group::MDV:
		return "D,M,V";
	case Group::NW:
		return "N,W";
	case Group::XF:
		return "X,F";
	case Group::PGY:
		return "P,G,Y";
	case Group::HQZ:
		return "H,Q,Z";
	case Group::RI:
		return "I,R";
	case Group::A:
		return "A";
	case Group::U:
		return "U";
	case Group::E:
		return "E";
	case Group::O:
		return "O";
	}

	return "Error";
}

void
sortGroups(Groups &_groups)
{
	std::sort(
			  _groups.begin()
			, _groups.end()
			, []( GroupData const& _data1, GroupData const& _data2 )
				{
					if ( _data1.m_count == _data2.m_count )
						return _data1.m_group < _data2.m_group;

					return _data1.m_count > _data2.m_count;
				}
		);
}

}
