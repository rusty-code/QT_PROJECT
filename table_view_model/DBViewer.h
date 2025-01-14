#ifndef DBVIEWER_H
#define DBVIEWER_H

#include "../includes.h"
#include "DBTableViewModel.h"

class DBViewer : public QWidget
{
    Q_OBJECT
private:
    QBoxLayout* p_layout;
    DBTableViewModel* p_models_views;
    QMap<QString, QString>* p_view_mod_queries;

    // TABLE_VIEW_MOD view_mod;
    EMITS_BTN_SIGNALS view_mod;

    QSize* p_size;
    QSize* p_position;

public:
    DBViewer
    (
        QString&, // DB resource
        QMap<QString, QString>*, // table<->query links
        QMap<EMITS_BTN_SIGNALS, QString>*,
        QSize*,
        QSize*,
        QBoxLayout::Direction,
        QWidget* _parent = 0
    );
    ~DBViewer();

public:
    void set_view_mod(EMITS_BTN_SIGNALS);
    void clean_layout();

public slots:
    void table_swapper(EMITS_BTN_SIGNALS);
    void view_mod_swapper(EMITS_BTN_SIGNALS);

    void exec_filter(const QString&);
    void add_new_row();
    void remove_row(const QString&);

signals:
    void name_current_table(QString&);
};

#endif // DBVIEWER_H
