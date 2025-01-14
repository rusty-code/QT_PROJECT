#ifndef FIELDTEXTLABELS_H
#define FIELDTEXTLABELS_H

#include "../../includes.h"
#include "UnitTextLabel.h"

class FieldTextLabels : public QFrame
{
Q_OBJECT
private:
    // QString here is index of column for indexOf
    QList<UnitTextLabel*>* p_labels_field;
    QHBoxLayout* p_layout;
    bool read_only_flag;
    int _unitField_id;

public:
    FieldTextLabels
    (
        QList<
            QPair<
                QPair<
                    QString&,
                    QString&
                >,
                bool
            >
        >*,
        bool,
        int,
        QWidget* _parent = nullptr
    );
    ~FieldTextLabels();

    QList<QPair<QString&, QString&>>* get_field_info();
    void append_new_row(
        QPair<
            QPair<
                QString&,
                QString&
                >,
            bool
            >&
        );

public slots:
    void slot_label_changed(int);
    void remove_row(int);

signals:
    void sig_query_changed(int, int);
};

#endif // FIELDTEXTLABELS_H
