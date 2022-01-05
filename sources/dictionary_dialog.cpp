#include "dictionary_dialog.h"
#include "ui_dictionary_dialog.h"
#include "ask_for_name_dialog.hpp"

#include <QString>
#include <QtAlgorithms>
#include <QMessageBox>

DictionaryDialog::DictionaryDialog( Dictionaries& _dictionaries, QWidget *parent) :
	QDialog(parent),
	m_dictionaries( _dictionaries ),
	ui(new Ui::DictionaryDialog)
{
	ui->setupUi(this);

	fillList();
	fillInfo();
}

DictionaryDialog::~DictionaryDialog()
{
	delete ui;
}

void
DictionaryDialog::onSearchNameChanged(const QString &_text)
{
	auto items = ui->listWidget->findItems( _text, Qt::MatchStartsWith );

	if ( items.empty() )
		return;

	auto item = items.front();

	item->setSelected( true );
	ui->listWidget->scrollToItem( item, QAbstractItemView::PositionAtTop) ;
}

void
DictionaryDialog::onAddClicked()
{
	AskForNameDialog dialog( m_dictionaries, this );
	dialog.setWindowFlags( dialog.windowFlags() & ~Qt::WindowContextHelpButtonHint );
	if ( dialog.exec() == QDialog::Rejected )
		return;

	QString newName = dialog.getResult();
	m_dictionaries.addName( newName );

	fillList();
	fillInfo();

	onSearchNameChanged( newName );
}

void
DictionaryDialog::onRemoveClicked()
{
	auto listItem = ui->listWidget->selectedItems().front();

	if ( QMessageBox::question( this, "Delete name", "Delete '" + listItem->text() + "' ?" )
		 == QMessageBox::No )
	{
		return;
	}

	m_dictionaries.removeName( listItem->text() );
	qDeleteAll( ui->listWidget->selectedItems() );

	fillInfo();
}

void
DictionaryDialog::onSelectionChanged()
{
	ui->m_removeButton->setEnabled(
				!ui->listWidget->selectedItems().empty()
				);
}

void
DictionaryDialog::fillInfo()
{
	QString text = "Type: ";
	text += m_dictionaries.getType() == Dictionaries::Type::Male ? "Male" : "Female";
	text += "\n";
	text += "Count of names: " + QString::number( m_dictionaries.getNames().size() );

	ui->label->setText( text );
}

void
DictionaryDialog::fillList()
{
	ui->listWidget->clear();

	QStringList names = m_dictionaries.getNames();
	std::sort( names.begin(), names.end() );

	for ( auto& name : names )
		ui->listWidget->addItem( name );
}
