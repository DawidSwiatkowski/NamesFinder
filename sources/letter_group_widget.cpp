#include "letter_group_widget.h"
#include "ui_letter_group_widget.h"

LetterGroupWidget::LetterGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LetterGroupWidget)
{
    ui->setupUi(this);
}

LetterGroupWidget::~LetterGroupWidget()
{
    delete ui;
}

void
LetterGroupWidget::setLabelText(const QString & _name )
{
    ui->label->setText( _name );
}

void
LetterGroupWidget::setDescriptionText(const QString &_text)
{
    ui->label_2->setText( _text );
}

unsigned int
LetterGroupWidget::getValue() const
{
    return  ui->comboBox->currentText().toUInt();
}

void
LetterGroupWidget::resetValue()
{
    ui->comboBox->setCurrentIndex( 0 );
}

void
LetterGroupWidget::setGroup(LetterConverter::Group _group)
{
    m_group = _group;
}

LetterConverter::Group
LetterGroupWidget::getGroup() const
{
    return m_group;
}
