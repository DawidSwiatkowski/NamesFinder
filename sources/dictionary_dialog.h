#pragma once

#include <QDialog>

#include "dictionaries.hpp"

namespace Ui {
class DictionaryDialog;
}

class DictionaryDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DictionaryDialog( Dictionaries& _dictionaries, QWidget *parent = nullptr);
	~DictionaryDialog();

private slots:
	void onSearchNameChanged( QString const& _text );
	void onAddClicked();
	void onRemoveClicked();
	void onSelectionChanged();

private:
	void fillList();
	void fillInfo();

private:
	Ui::DictionaryDialog *ui;
	Dictionaries& m_dictionaries;
};

