#pragma once

#include <QDialog>
#include <QString>

#include "dictionaries.hpp"

namespace Ui {
class AskForNameDialog;
}

class AskForNameDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AskForNameDialog( Dictionaries & _dictionaries, QWidget *parent = nullptr );
	~AskForNameDialog();

	QString getResult();

private slots:
	void onOk();
	void onTextChanged( QString _text );

private:
	Ui::AskForNameDialog *ui;
	Dictionaries& m_dictionaries;
};

