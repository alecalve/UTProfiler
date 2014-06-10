#ifndef CATEGORIEDISPLAYWIDGET_H
#define CATEGORIEDISPLAYWIDGET_H

#include "displaywidget.h"

#include "src/structures.hpp"

namespace Ui {
class DisplayWidget;
}

class CategorieDisplayWidget : public DisplayWidget {
    Q_OBJECT

  public:
    CategorieDisplayWidget(QWidget *parent = 0);
    ~CategorieDisplayWidget();
    void displayItem(const QString&);

  public slots:
    void refresh();
    void del();
    void add();
    void change(int row, int column);
    void changed(int row, int column);

};

#endif // CATEGORIEDISPLAYWIDGET_H
