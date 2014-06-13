#ifndef UVDISPLAYWIDGET_H
#define UVDISPLAYWIDGET_H

#include "displaywidget.h"

#include "src/uv.hpp"

namespace Ui {
class DisplayWidget;
}

class UvDisplayWidget : public DisplayWidget {
    Q_OBJECT

  public:
    UvDisplayWidget(QWidget *parent = 0);
    ~UvDisplayWidget();
    void displayItem(const QString&);

  public slots:
    void refresh();
    void del();
    void add();
    void modify();
    void change(int row, int column);
    void changed(int row, int column);

};

#endif // UVDISPLAYWIDGET_H
