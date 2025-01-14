#include "FieldTextLabels.h"


FieldTextLabels::FieldTextLabels
(
    QList<
        QPair<
            QPair<
                QString&, // column index
                QString& // column content
                >,
            bool // multitext flag
            >
        >* _labels_data,
    bool _read_only_mod,
    int _id,
    QWidget* _parent
) :
    QFrame(_parent),
    read_only_flag{_read_only_mod},
    _unitField_id{_id}
{
    this->p_layout = new QHBoxLayout;
    this->p_labels_field = new QList<UnitTextLabel*>;
    this->setLayout(this->p_layout);

    for
    (
        auto dat_iter = _labels_data->begin();
        dat_iter != _labels_data->end();
        ++dat_iter
    )
    {
        this->append_new_row(*dat_iter);
    }
}

FieldTextLabels::~FieldTextLabels()
{}

QList<QPair<QString&, QString&>>*
FieldTextLabels::
get_field_info()
{
    QList<QPair<QString&, QString&>>* rows_info =
        new QList<QPair<QString&, QString&>>;

    for
    (
        auto utl_iter = this->p_labels_field->begin();
        utl_iter != this->p_labels_field->end();
        ++utl_iter
    )
    {
        rows_info->append
        (
            {
                *((*utl_iter)->get_col_index()),
                *((*utl_iter)->get_text())
            }
        );
    }

    return rows_info;
}

void FieldTextLabels::
    append_new_row(
        QPair<
            QPair<
                QString&,
                QString&
                >,
            bool
        >& _new_row_info
)
{
    int uLabelid = this->p_labels_field->size();
    UnitTextLabel* tmp_utl = new UnitTextLabel(
        _new_row_info.first.second,
        _new_row_info.second,
        uLabelid,
        _new_row_info.first.first,
        this->read_only_flag
        );
    this->p_labels_field->append(tmp_utl);
    this->p_layout->addWidget(tmp_utl);

    connect
    (
        tmp_utl,
        &UnitTextLabel::sig_text_be_changed,
        this,
        &FieldTextLabels::slot_label_changed
    );

    this->update();
}


void FieldTextLabels::slot_label_changed(int _utl_num)
{
    emit this->sig_query_changed(this->_unitField_id, _utl_num);
}

void FieldTextLabels::remove_row(int _utl_num)
{

}
