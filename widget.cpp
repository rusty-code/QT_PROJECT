#include "widget.h"

Widget::Widget(QString _db_source, QWidget *parent)
    : QWidget(parent)
{
    // setup color pallete for main window background
       this->setAutoFillBackground(true);
       this->p_backColor = new QPalette;
       this->p_backColor->setColor(this->backgroundRole(), Qt::white);
       this->setPalette(*p_backColor);

    // settup mainwindow
    this->resize(1000, 800);


    // setup buttons area
    this->p_mBar = new MenuBar
    (
        new QSize(80, 650),
        new QSize(10, 20),
        true,
        this
    );
    {
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG0, ":/ico/empl.png");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG1, ":/ico/spec.png");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG2, ":/ico/prjct.png");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG3, ":/ico/prjct_stat.png");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG4, ":/ico/depart.png");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG5, ":/ico/depart_type.png");
        this->p_mBar->appendObject(EMITS_BTN_SIGNALS::SIG6, ":/ico/doc.png");
    }
        /* buttons signals was connected to menu signal hendler */
    this->p_mBar->show();


    // setup top menu
    this->p_topBar = new TopBar
    (
        new QSize(
            this->p_mBar->size().width(),
            this->p_mBar->pos().y()
            ),
        new QSize(
            this->width()-this->p_mBar->size().width(),
            60
            ),
        this
    );
    this->p_topBar->show();


    // setup DB viewer area

        /* define queries for view mod */
    QMap<QString, QString>* p_queries = nullptr;
        /* define signal<->table links for table swapper */
    QMap<EMITS_BTN_SIGNALS, QString>* p_links_sig_table = new QMap<EMITS_BTN_SIGNALS, QString>;
    {
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG0, "employees");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG1, "sepecializations");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG2, "projects");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG3, "project_status");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG4, "department");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG5, "department_type");
        p_links_sig_table->insert(EMITS_BTN_SIGNALS::SIG6, "project_document");
    }
    int size1 = this->width()-p_mBar->width();
    int size2 = this->height()-p_topBar->height();
    { // show sizes
        qDebug() << size1 << '\n' << size2;
    }
    DBViewer* p_db_viewer = new DBViewer
    (
        _db_source,
        p_queries,
        p_links_sig_table,
        // new QSize(this->width(), this->height()),
        new QSize
        (
            // 1500,
            // 900
            size1,
            size2
        ),
        new QSize
        (
            this->p_mBar->width(),
            this->p_topBar->height()
        ), // not optimazed
        QBoxLayout::Direction::TopToBottom,
        this
    );

    connect // choose table
    (
        this->p_mBar,
        &MenuBar::sig_transmission,
        p_db_viewer,
        &DBViewer::table_swapper
    );

    connect // filter
    (
        this->p_topBar,
        &TopBar::sig_filter_data_transmitter,
        p_db_viewer,
        &DBViewer::exec_filter
    );

    connect // filter for delete row
    (
        this->p_topBar,
        &TopBar::sig_delete_rownum_transmitter,
        p_db_viewer,
        &DBViewer::remove_row
    );

    connect // add button
    (
        this->p_topBar,
        &TopBar::sig_add_new_row,
        p_db_viewer,
        &DBViewer::add_new_row
    );

    connect // swapper current table name label
    (
        p_db_viewer,
        &DBViewer::name_current_table,
        p_topBar,
        &TopBar::slot_set_tname
    );

    p_db_viewer->show();
}


Widget::~Widget()
{
}
