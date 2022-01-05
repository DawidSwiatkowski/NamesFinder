#pragma once

#include <QMainWindow>

#include "dictionaries.hpp"
#include "thread.h"
#include "result_file.h"

#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

private slots:
    void findButtonClicked();
	void onPreviewButtonClicked();
	void onSearchResult( QStringList const& _result );
	void onDictionaryTypeChanged( int _index );

private:
	void saveSettings();
	void loadSettings();

private:
    Ui::MainWindow *ui;
	Dictionaries m_dictionaries;

	Thread m_searchThread;
	std::set< QString > m_findNames;
	ResultFile m_resultFile;
};
