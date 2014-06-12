#ifndef FORMATIONDISPLAYWIDGET_H
#define FORMATIONDISPLAYWIDGET_H

#include "displaywidget.h"

#include "src/structures.hpp"

namespace Ui {
class DisplayWidget;
}

class FormationDisplayWidget : public DisplayWidget {
    Q_OBJECT

  public:
    FormationDisplayWidget(QWidget *parent = 0);
    ~FormationDisplayWidget();
    void displayItem(const QString&);

  public slots:
    void refresh();
    void del();
    void add();
    void change(int row, int column);
    void changed(int row, int column);

};

#endif // FORMATIONDISPLAYWIDGET_H
