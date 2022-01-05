#pragma once

#include <string>
#include <vector>

#include <QtGlobal>
#include <QString>

namespace LetterConverter
{

enum class Group
{
	  JS
	, BKT
	, CL
	, MDV
	, NW
	, XF
	, PGY
	, HQZ
	, RI
	, A
	, U
    , E
    , O
};

struct GroupData
{
	Group m_group;
	quint8 m_count;
};

using Groups = std::vector< GroupData >;

QString
groupToString( Group _group );

Groups
convertLettersToGroups( std::string const& _letters );

quint64
converGroupsToNumber( Groups const& _groups, Groups* _order = nullptr );

void
sortGroups( Groups & _groups );

}
