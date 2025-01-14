#include "../includes.h"
#include "DBViewer.h"


DBViewer::DBViewer
(
    QString& _db_soruce, // DB resource
    QMap<QString, QString>* _table_query_links, // table<->query links
    QMap<EMITS_BTN_SIGNALS, QString>* _link_sig_table,
    QSize* _size,
    QSize* _position,
    QBoxLayout::Direction _layout_format,
    QWidget* _parent
) :
    QWidget(_parent),
    p_size(_size),
    p_position(_position)
{
    // make layout
    this->p_layout = new QBoxLayout(_layout_format);
    this->setLayout(this->p_layout); // may be not use
    this->setGeometry
    (
        _position->width(),
        _position->height(),
        _size->width(),
        _size->height()
    );

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(_db_soruce);
    if(!db.open())
    {
        qDebug("Error database open");
    }

    // add models view to layout
    this->p_models_views = new DBTableViewModel(_link_sig_table, this);
    this->p_models_views->setGeometry
    (
        _position->width(),
        _position->height(),
        _size->width(),
        _size->height()
    );
    this->p_layout->addWidget(this->p_models_views);


    /*
        TEST SECTION
    */
    // this->view_mod = TABLE_VIEW_MODS::EDIT;
}

DBViewer::~DBViewer()
{
    delete this->p_position;
    delete this->p_size;
}

void DBViewer::set_view_mod(EMITS_BTN_SIGNALS _view_mod)
{
    this->view_mod = _view_mod;
}

void DBViewer::table_swapper(EMITS_BTN_SIGNALS _emitted_sig)
{
    this->p_models_views->set_model(_emitted_sig);
    this->p_models_views->to_resize();

    emit this->name_current_table(
        *(this->p_models_views->get_current_table_name()));
}

void DBViewer::view_mod_swapper(EMITS_BTN_SIGNALS _view_mod)
{
    switch (_view_mod)
    {
    case EMITS_BTN_SIGNALS::EDIT:
            this->p_models_views->to_resize();
            this->p_models_views->show();
        break;
    case EMITS_BTN_SIGNALS::ONLY_VIEW:
            this->p_models_views->hide();
        break;
    default:
        this->p_layout->addWidget
        (
            new QLabel(
            "THE DISPLAY OPTION IS NOT SELECTED\nHint: buttons 'View' and 'Edit' at the top")
        );
        break;
    }
}

void DBViewer::exec_filter(const QString& _filter)
{
    this->p_models_views->exec_filter(_filter);
    this->p_models_views->to_resize();
}

void DBViewer::add_new_row()
{
    this->p_models_views->add_new_row();
    this->p_models_views->to_resize();
}

void DBViewer::remove_row(const QString& _filter)
{
    this->p_models_views->remove_row(_filter);
    this->p_models_views->to_resize();
}
