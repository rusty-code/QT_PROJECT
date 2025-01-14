#ifndef WIDGET_H
#define WIDGET_H

#include "includes.h"
#include "menu_bar/CustomButton.h"
#include "menu_bar/MenuBar.h"
#include "menu_bar/TopBar.h"
#include "table_view_model/DBViewer.h"

class Widget : public QWidget
{
Q_OBJECT

private:
    // CustomButton* ctm_btm;
    // QVBoxLayout* layout;
    MenuBar* p_mBar;
    TopBar* p_topBar;
    QPalette* p_backColor;

public:
    Widget(QString, QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
