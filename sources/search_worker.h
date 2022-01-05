#pragma once

#include "thread_worker.h"
#include "name_converter.h"

#include <vector>
#include <QString>
#include <QStringList>

class SearchWorker : public ThreadWorker
{
    Q_OBJECT

	struct Data
	{
		QString m_string;
		quint64 m_value;
	};

public:
	struct Parameters
	{
		QStringList m_names;
		LetterConverter::Groups m_groups;
		int m_maximumCountOfNames = 10;
		int m_minimumNameLenght = 2;
	};

public:
	SearchWorker( Parameters & _parameters );

protected:
    void doWork() override;
	void search( quint16 const& _min, quint64 _value );
	void emitResult();

signals:
	void onResult( QStringList const& _result );
    void onProgress( int _progress );

private:
	int m_maxCountOfNames = 10;

	quint64 m_searchValue;
	std::vector< Data > m_data;
	std::size_t m_dataCount;

	std::vector< quint16 > m_indexes;
	int m_deep = -1;
};


