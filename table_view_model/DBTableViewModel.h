#ifndef DBTABLEVIEWMODEL_H
#define DBTABLEVIEWMODEL_H

#include "../includes.h"

class DBTableViewModel : public QTableView
{
Q_OBJECT
private:
    QMap<EMITS_BTN_SIGNALS, QString>* p_link_sig_names;
    QString* current_table;

public:
    DBTableViewModel
    (
        QMap<EMITS_BTN_SIGNALS, QString>*,
        QWidget* _parent = nullptr
    );

    ~DBTableViewModel();

    QString* get_current_table_name();
    void set_model(EMITS_BTN_SIGNALS);
    void apeendConnect(EMITS_BTN_SIGNALS, QString);
    void to_resize();
    void exec_filter(const QString&);
    void remove_row(const QString&);
    void add_new_row();
};


#endif // DBTABLEVIEWMODEL_H
