#include "DBTableViewModel.h"


DBTableViewModel::DBTableViewModel
(
    QMap<EMITS_BTN_SIGNALS, QString>* _link_sig_names,
    QWidget* _parent
) : QTableView(_parent), p_link_sig_names(_link_sig_names)
{
    this->setPalette(QPalette(Qt::white));
    this->current_table = new QString("");
}

DBTableViewModel::~DBTableViewModel()
{
    delete this->p_link_sig_names;
}

QString* DBTableViewModel::get_current_table_name()
{
    return this->current_table;
}

void DBTableViewModel::set_model
(
    EMITS_BTN_SIGNALS _emitted_sig
)
{
    *(this->current_table) = this->p_link_sig_names->lowerBound(_emitted_sig).value();
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
    (
        *(this->current_table)
    );
    tmp_rel_mdl->select(); // load data

    // set current model for view
    this->setModel(tmp_rel_mdl);
}

void DBTableViewModel::exec_filter(const QString& _filter)
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
        );
    tmp_rel_mdl->setFilter(_filter);
    tmp_rel_mdl->select(); // load data

    // set current model for view
    this->setModel(tmp_rel_mdl);
}

void DBTableViewModel::add_new_row()
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
            );

    QSqlRecord rec = tmp_rel_mdl->record(0);

    int index_row = 0;
    int count_inserts = 1;
    tmp_rel_mdl->insertRows(index_row, count_inserts);

    // set for all colums val "0"
    for(int col_ind = 0; col_ind < tmp_rel_mdl->columnCount(); ++col_ind)
    {
        tmp_rel_mdl->setData(tmp_rel_mdl->index(index_row, col_ind), "0");
    }

    if(!tmp_rel_mdl->submitAll())
    {
        qDebug("(ERROR): create new row error!");
        qDebug() << "       " << tmp_rel_mdl->lastError();
    }
    this->exec_filter(""); // show append row
}

void DBTableViewModel::remove_row(const QString& _filter)
{
    QSqlTableModel* tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
            );
    tmp_rel_mdl->setFilter(_filter);
    tmp_rel_mdl->select();
    tmp_rel_mdl->removeRows(0, tmp_rel_mdl->rowCount());
    tmp_rel_mdl->submitAll();

    delete tmp_rel_mdl;
    tmp_rel_mdl = new QSqlTableModel;
    tmp_rel_mdl->setTable
        (
            *(this->current_table)
            );
    tmp_rel_mdl->select();
    this->setModel(tmp_rel_mdl);
}

void DBTableViewModel::to_resize()
{
    if(this->model() != NULL)
    {
        int colCount = this->model()->columnCount();
        for(int colNum = 0; colNum < colCount; ++colNum)
        {
            this->resizeColumnToContents(colNum);
        }
    }
}
