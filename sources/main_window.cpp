#include "main_window.h"
#include "ui_main_window.h"
#include "search_worker.h"
#include "letter_group_widget.h"
#include "name_converter.h"
#include "dictionary_dialog.h"

#include <QMessageBox>
#include <QString>
#include <QVariant>
#include <QProgressDialog>

#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QDir>
#include <QFile>

#include <vector>

namespace
{

std::vector< LetterGroupWidget* >
getLetterGroupWidgets( QLayout* _layout )
{
	std::vector< LetterGroupWidget* > widgets;

	for ( int i = 0; i < _layout->count(); ++i )
	{
		LetterGroupWidget* widget = dynamic_cast< LetterGroupWidget* >( _layout->itemAt( i )->widget() );
		if ( widget )
			widgets.push_back( widget );
	}

	return widgets;
}

}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m_resultFile( "result.txt" )
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void
MainWindow::init()
{
	auto createWidget
			= [this]( QString const& _name, QString const& _descripton, LetterConverter::Group _group )
			{
				LetterGroupWidget* widget = new LetterGroupWidget( this );
				widget->setLabelText( _name );
				widget->setGroup( _group );
				widget->setDescriptionText( _descripton );

				return widget;
			};

	for ( int i = 0; i < 13; ++i )
	{
		LetterConverter::Group group = static_cast< LetterConverter::Group >( i );

		ui->m_lettersGroupLayout->addWidget( createWidget(
				  QString( "%1.").arg( i + 1 )
				, LetterConverter::groupToString( group )
				, group
				)
		);
	}

	ui->m_dictionariesComboBox->addItem( "Male", static_cast< int >( Dictionaries::Type::Male ) );
	ui->m_dictionariesComboBox->addItem( "Female", static_cast< int >( Dictionaries::Type::Female ) );
	ui->m_dictionariesComboBox->setCurrentIndex( static_cast< int >( m_dictionaries.getType() ) );

	loadSettings();
}

void
MainWindow::findButtonClicked()
{
	m_findNames.clear();
	ui->m_result->clear();

	SearchWorker::Parameters searchParameters;
	searchParameters.m_names = m_dictionaries.getNames();
	searchParameters.m_maximumCountOfNames = ui->m_maximumCountOfNames->value();
	searchParameters.m_minimumNameLenght = ui->m_minimumNameLenght->value();

	{
		for ( auto widget : getLetterGroupWidgets( ui->m_lettersGroupLayout ) )
		{
			LetterConverter::GroupData data;
			data.m_group = widget->getGroup();
			data.m_count = widget->getValue();

			searchParameters.m_groups.push_back( data );
		}

		LetterConverter::sortGroups( searchParameters.m_groups );
	}

	m_resultFile.open();
	m_resultFile.writeHeader( searchParameters.m_groups, m_dictionaries.getType() );

	std::shared_ptr< QProgressDialog > dialog;
	{
		dialog = std::make_shared< QProgressDialog >( "Searching...", "Cancel", 0, 100, this );
		dialog->setWindowTitle( "Names Finder" );
		dialog->resize( width()/2, dialog->height() );
		dialog->setWindowFlags( dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint );
		dialog->setValue( 0 );
		dialog->setAutoClose( false );
	}

	{
		SearchWorker* worker = new SearchWorker( searchParameters );
		m_searchThread.setWorker( worker );

		connect( &m_searchThread, &Thread::finished, dialog.get(), &QProgressDialog::cancel );
		connect( dialog.get(), &QProgressDialog::canceled, &m_searchThread, &Thread::requestInterruption );
		connect( worker, &SearchWorker::onProgress, dialog.get(), &QProgressDialog::setValue );
		connect( worker, &SearchWorker::onResult, this, &MainWindow::onSearchResult );
	}

	m_searchThread.start();

	dialog->exec();
	m_searchThread.requestInterruption();

	m_resultFile.close();
}

void
MainWindow::onPreviewButtonClicked()
{
	DictionaryDialog dialog( m_dictionaries, this );
	dialog.setWindowFlags( dialog.windowFlags() & ~Qt::WindowContextHelpButtonHint );

	dialog.exec();
}

void
MainWindow::onSearchResult( QStringList const& _result )
{
	QString text =_result.join( " " );

	auto it = m_findNames.find( text );
	if ( it != m_findNames.end() )
		return;

	if ( m_findNames.size() <= 1000 )
		ui->m_result->append( text );

	m_resultFile.write( text );
}

void
MainWindow::onDictionaryTypeChanged( int )
{
	m_dictionaries.setType(
				static_cast< Dictionaries::Type >( ui->m_dictionariesComboBox->currentData().toInt() ) );

	saveSettings();
}

void
MainWindow::saveSettings()
{
//	QSettings settings( "settings.ini", QSettings::IniFormat );
//	settings.setValue( "FilePath", m_namesList.getFilePath().c_str() );
}

void
MainWindow::loadSettings()
{
//	QSettings settings( "settings.ini", QSettings::IniFormat );

//	QString namesFilePath = settings.value( "FilePath", "data/female.txt" ).toString();

//	if ( m_namesList.load( namesFilePath.toStdString() ) )
//		ui->m_namesFilePath->setText( namesFilePath );
}
