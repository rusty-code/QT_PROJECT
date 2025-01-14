#include "DBQueryViewer.h"


DBQueryViewer::DBQueryViewer
(
    QMap<EMITS_BTN_SIGNALS, QString>* _links_sig_tname,
    QMap<QString&, QList<QString&>*>* _links_tname_indexes,
    QWidget* _parent
) :
    QAbstractScrollArea(_parent),
    p_links_sigs_table{_links_sig_tname},
    p_links_tname_indexes{_links_tname_indexes}
{
    this->p_query_agregator = new QSqlQuery;
    this->p_rows_area = new QList<FieldTextLabels*>;
}

DBQueryViewer::~DBQueryViewer()
{
    delete this->p_links_sigs_table;
    delete this->p_links_tname_indexes;
    delete this->p_query_agregator;
    delete this->p_rows_area;
}


// slots
void DBQueryViewer::slot_table_swapper(EMITS_BTN_SIGNALS _sig)
{
    // get data from table
    QString query = "select * from %1";
    query = query.arg(this->p_links_sigs_table->lowerBound(_sig).value());

    if(!this->p_query_agregator->exec(query))
    {
        qDebug("tswap error!");
    }

    // transmission record list
    QList<QString> trans_data;
}

void DBQueryViewer::slot_view_swapper(EMITS_BTN_SIGNALS _sig)
{

}

void DBQueryViewer::slot_append_new(EMITS_BTN_SIGNALS _sig)
{

}

void DBQueryViewer::slot_exec_filter(QString& _filter)
{

}
