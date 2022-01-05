#pragma once

#include <QFile>
#include <QString>
#include <QTextStream>

#include "name_converter.h"
#include "dictionaries.hpp"

class ResultFile
{

public:
	ResultFile( QString const& _fileName );

	void open();
	void close();

	void writeHeader( LetterConverter::Groups _groups, Dictionaries::Type _dictionaryType );
	void write( QString const& _text );

private:
	QFile m_file;
	QTextStream m_stream;
};
