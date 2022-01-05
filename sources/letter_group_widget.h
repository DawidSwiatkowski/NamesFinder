#ifndef LETTER_GROUP_WIDGET_H
#define LETTER_GROUP_WIDGET_H

#include <QWidget>

#include "name_converter.h"

namespace Ui {
class LetterGroupWidget;
}

class LetterGroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LetterGroupWidget(QWidget *parent = nullptr);
    ~LetterGroupWidget();

    void setLabelText( QString const& _name );
    void setDescriptionText( QString const& _text );

    unsigned int getValue() const;
    void resetValue();

	void setGroup( LetterConverter::Group _group );
	LetterConverter::Group getGroup() const;

private:
    Ui::LetterGroupWidget *ui;

	LetterConverter::Group m_group;
};

#endif // LETTER_GROUP_WIDGET_H
