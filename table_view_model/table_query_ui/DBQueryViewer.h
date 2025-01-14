#ifndef DBQUERYVIEWER_H
#define DBQUERYVIEWER_H

#include "../../includes.h"
#include "FieldTextLabels.h"

class DBQueryViewer : public QAbstractScrollArea
{
Q_OBJECT
private:
    QMap<EMITS_BTN_SIGNALS, QString>* p_links_sigs_table;
    QMap<QString&, QList<QString&>*>* p_links_tname_indexes;

    QSqlQuery* p_query_agregator;
    QList<FieldTextLabels*>* p_rows_area;

public:
    DBQueryViewer
    (
        QMap<EMITS_BTN_SIGNALS, QString>*,
        QMap<QString&, QList<QString&>*>*,
        QWidget* _parent = nullptr
    );
    ~DBQueryViewer();

public slots:
    void slot_table_swapper(EMITS_BTN_SIGNALS);
    void slot_view_swapper(EMITS_BTN_SIGNALS);

    void slot_append_new(EMITS_BTN_SIGNALS);
    void slot_exec_filter(QString&);

    void to_query_remove_row(int);

signals:
    void current_table_name(QString&);
};

#endif // DBQUERYVIEWER_H
