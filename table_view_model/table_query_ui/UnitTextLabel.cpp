#include "UnitTextLabel.h"


UnitTextLabel::UnitTextLabel
(
    QString& _label_text,
    bool _multy_text,
    int _id,
    QString& _tip_text,
    bool _ro,
    QWidget* _parent
) :
    QWidget(_parent),
    _unitLabel_id{_id}
{
    this->p_label_text = new QString(_label_text);
    this->p_index_column = new QString(_tip_text);

    this->p_label = new QLabel("&"+_tip_text+":", this); // with set tool tip
    if(_multy_text)
    {
        QTextEdit* buddy = new QTextEdit(_label_text);
        buddy->setReadOnly(_ro);
        this->p_label->setBuddy(buddy);
    }
    else
    {
        QLineEdit* buddy = new QLineEdit(_label_text);
        buddy->setReadOnly(_ro);
        this->p_label->setBuddy(buddy);
    }

    connect
    (
        this->p_label->buddy(),
        SIGNAL(textChanged(const QString&)),
        this,
        SLOT(slot_text_be_changed(const QString&))
    );
}

UnitTextLabel::~UnitTextLabel()
{
    delete this->p_label_text;
    delete this->p_index_column;
}

void UnitTextLabel::set_text(QString&& _lbl_txt)
{
    *(this->p_label_text) = _lbl_txt;
}

void UnitTextLabel::set_label(QLabel* _label)
{
    delete this->p_label;
    this->p_label = _label;
}

QString* UnitTextLabel::get_text()
{
    return this->p_label_text;
}

QString* UnitTextLabel::get_col_index()
{
    return this->p_index_column;
}

QLabel* UnitTextLabel::get_label()
{
    return this->p_label;
}

int UnitTextLabel::get_label_id()
{
    return this->_unitLabel_id;
}

void UnitTextLabel::slot_text_be_changed(const QString& _ch_str)
{
    *(this->p_label_text) = _ch_str;
    emit this->sig_text_be_changed(this->_unitLabel_id);
}
