#ifndef UNITTEXTLABEL_H
#define UNITTEXTLABEL_H

#include "../../includes.h"


class UnitTextLabel : public QWidget
{
Q_OBJECT
private:
    QString* p_label_text;
    QString* p_index_column;
    QLabel* p_label;
    int _unitLabel_id;

public:
    UnitTextLabel
    (
        QString&,
        bool,
        int,
        QString&,
        bool,
        QWidget* _parent = nullptr
    );
    ~UnitTextLabel();

    void set_text(QString&&);
    void set_label(QLabel*);

    QString* get_text();
    QString* get_col_index();
    QLabel* get_label();
    int get_label_id();
public slots:
    void slot_text_be_changed(const QString&);

signals:
    void sig_text_be_changed(int);
};

#endif // UNITTEXTLABEL_H
