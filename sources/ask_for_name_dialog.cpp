#include "ask_for_name_dialog.hpp"
#include "ui_ask_for_name_dialog.h"

#include <QMessageBox>
#include <QPushButton>

AskForNameDialog::AskForNameDialog(Dictionaries & _dictionaries, QWidget *parent ) :
	QDialog(parent),
	m_dictionaries( _dictionaries ),
	ui(new Ui::AskForNameDialog)
{
	ui->setupUi(this);
	ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
}

AskForNameDialog::~AskForNameDialog()
{
	delete ui;
}

QString
AskForNameDialog::getResult()
{
	QString newName = ui->lineEdit->text();

	if ( !newName.isEmpty() )
		newName.front() = newName.front().toUpper();

	return newName;
}

void
AskForNameDialog::onOk()
{
	QString newName = ui->lineEdit->text();

	if ( m_dictionaries.exists( newName ) )
	{
		QMessageBox::warning( this, "Name", "'" + newName + "' already exists." );
		return;
	}

	QDialog::accept();
}

void
AskForNameDialog::onTextChanged(QString _text)
{
	ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( !_text.isEmpty() );
}
