#pragma once

#include <QString>

#include <map>

enum class GroupType
{
	  JS
	, BKT
	, CL
	, MDV
	, NW
	, XS
	, PGY
	, HQZ
	, RI
	, A
	, U
	, E
	, O
};

constexpr
int
getGroupsCount()
{
	return static_cast< int >( GroupType::O ) + 1;
}

QString
groupTypeToString( GroupType _type )
{
	switch( _type )
	{
		case GroupType::JS:
			return "J,S";
		case GroupType::BKT:
			return "B,K,T";
		case GroupType::CL:
			return "C,L";
		case GroupType::MDV:
			return "D,M,V";
		case GroupType::NW:
			return "N,W";
		case GroupType::XS:
			return "X,S";
		case GroupType::PGY:
			return "P,G,Y";
		case GroupType::HQZ:
			return "H,Q,Z";
		case GroupType::RI:
			return "I,R";
		case GroupType::A:
			return "A";
		case GroupType::U:
			return "U";
		case GroupType::E:
			return "E";
		case GroupType::O:
			return "O";
	}

	return "Error";
}

std::map< char, GroupType >
createCharsPositionsMap()
{
	return
	 {
		  { 'a', GroupType::A }
		, { 'e', GroupType::E }
		, { 'o', GroupType::O }
		, { 'u', GroupType::U }
		, { 'r', GroupType::RI },  { 'i', GroupType::RI }
		, { 'j', GroupType::JS },  { 's', GroupType::JS }
		, { 'c', GroupType::CL },  { 'l', GroupType::CL }
		, { 'n', GroupType::NW },  { 'w', GroupType::NW }
		, { 'x', GroupType::XS },  { 's', GroupType::XS }
		, { 'b', GroupType::BKT }, { 'k', GroupType::BKT }, { 't', GroupType::BKT }
		, { 'm', GroupType::MDV }, { 'd', GroupType::MDV }, { 'v', GroupType::MDV }
		, { 'p', GroupType::PGY }, { 'g', GroupType::PGY }, { 'y', GroupType::PGY }
		, { 'h', GroupType::HQZ }, { 'q', GroupType::HQZ }, { 'z', GroupType::HQZ }
	 };
}
