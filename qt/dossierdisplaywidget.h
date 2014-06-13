#ifndef DOSSIERDISPLAYWIDGET_H
#define DOSSIERDISPLAYWIDGET_H

#include "displaywidget.h"

#include "src/structures.hpp"

namespace Ui {
class DisplayWidget;
}

class DossierDisplayWidget : public DisplayWidget {
    Q_OBJECT

  public:
    DossierDisplayWidget(QWidget *parent = 0);
    ~DossierDisplayWidget();
    void displayItem(const QString&);

  public slots:
    void refresh();
    void del();
    void add();
    void modify();
    void change(int row, int column);
    void changed(int row, int column);

};


#endif // DOSSIERDISPLAYWIDGET_H
